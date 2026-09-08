#include "pch.h"
#include <JCore/SLog.h>
#include <JNet/CPacket.h>
#include "CConnectThread.h"
#include "PlayerManager.h"
#include "DummyClient.h"
#include "Player.h"

CConnectThread::CConnectThread(DummyClient* dummy)
	: CThread([this]() { MessageThread(); }, 1)
	, _dummy(dummy)
	, msgQ(320000)
	, _dequeueCnt(0)
	, _hEvent(INVALID_HANDLE_VALUE)
	, _hShutdownEvent(INVALID_HANDLE_VALUE)
	, _connectCnt(0)
	, _sock(INVALID_SOCKET)
{
	_hEvent = CreateEvent(nullptr, false, false, nullptr);
	_hShutdownEvent = CreateEvent(nullptr, true, false, nullptr);
	_nagle = dummy->_nagle;
	_sendBufZero = dummy->_sendBufZero;
	_serverAddr = dummy->_serverAddr;
	_clientAddr = dummy->_clientAddr;
}

CConnectThread::~CConnectThread()
{
	while (1)
	{
		ConnectMessage msg;
		if (msgQ.Dequeue(&msg) == false)
		{
			break;
		}
	}

	CloseHandle(_hEvent);
	CloseHandle(_hShutdownEvent);
}

void CConnectThread::Shutdown()
{
	ConnectMessage msg;
	msg.player = nullptr;
	msg.owner = 0;
	EnqueueMessage(&msg);
	SetEvent(_hShutdownEvent);
	closesocket(_sock);
}

void CConnectThread::EnqueueMessage(ConnectMessage* msg)
{
	msgQ.ForceEnqueue(*msg);
	SetEvent(_hEvent);
}

int CConnectThread::GetMsgQSize() const
{
	return msgQ.GetSize();
}

void CConnectThread::MessageThread()
{
	SLOG(L"DummyClient", L"Message Thread Start");

	HANDLE handles[2] = { _hShutdownEvent, _hEvent };

	bool bShutdown = false;

	while (!bShutdown)
	{
		DWORD retVal = WaitForMultipleObjects(2, handles, false, INFINITE);

		if (retVal == WAIT_OBJECT_0)
		{
			bShutdown = true;
			break;
		}

		ConnectMessage request;

		while (!bShutdown && msgQ.Dequeue(&request))
		{
			InterlockedIncrement(&_dequeueCnt);

			bool success = false;
			_sock = INVALID_SOCKET;

			if (request.player == nullptr && request.owner == nullptr)
			{
				bShutdown = true;
				break;
			}

			do
			{
				_sock = socket(AF_INET, SOCK_STREAM, 0);
				if (_sock == INVALID_SOCKET)
				{
					ELOG(L"DummyClient", L"socket failed, [ErrorCode]:%d", WSAGetLastError());
					break;
				}

				int retval = bind(_sock, (SOCKADDR*)&_clientAddr, sizeof(_clientAddr));
				if (retval == SOCKET_ERROR)
				{
					ELOG(L"DummyClient", L"bind failed, [ErrorCode]:%d", WSAGetLastError());
					closesocket(_sock);
					break;
				}

				if (_sendBufZero)
				{
					int size = 0;
					if (setsockopt(_sock, SOL_SOCKET,
						SO_SNDBUF, (char*)&size, sizeof(size)) != 0)
					{
						DLOG(L"DummyClient", L"setsockopt failed, [ErrorCode]:%d", WSAGetLastError());
						closesocket(_sock);
						break;
					}
				}

				if (_nagle == false)
				{
					DWORD opt = 1;
					if (setsockopt(_sock, IPPROTO_TCP, TCP_NODELAY, (char*)&opt, sizeof(opt)) != 0)
					{
						DLOG(L"DummyClient", L"setsockopt failed, [ErrorCode]:%d", WSAGetLastError());
						closesocket(_sock);
						break;
					}
				}

				LINGER linger = { 1, 0 };
				setsockopt(_sock, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger));

				int connectRet = connect(_sock, (SOCKADDR*)&_serverAddr, sizeof(_serverAddr));
				if (connectRet == SOCKET_ERROR)
				{
					int err = WSAGetLastError();
					if (err == WSAENOTSOCK)
					{
						bShutdown = true;
						break;
					}

					if (err != WSAECONNREFUSED)
					{
						DLOG(L"DummyClient", L"connect failed, [ErrorCode]:%d", err);
					}
					closesocket(_sock);
					break;
				}

				success = true;

			} while (0);

			Message response;
			CLogicThread* thread = request.owner;
			Player* player = request.player;

			if (success)
			{
				CSession* session = _dummy->CreateSession(_sock);
				if (session == nullptr)
				{
					ELOG(L"DummyClient", L"Create CSession Failed");
					closesocket(_sock);
					continue;
				}

				session->_userData = player;
				InterlockedIncrement(&_connectCnt);
				response.type = (unsigned char)MessageType::MSG_CONNECT_SUCCESS;
				response.sessionId = session->_id;
				response.payload = (uint64_t)player;
				if (player != nullptr)
				{
					player->_responseTime = CProfiler::GetNanoSec();
				}

				thread->EnqueueMessage(&response);

				if (!session->RecvPost())
				{
					session->Release();
				}
			}
			else
			{
				response.type = (unsigned char)MessageType::MSG_CONNECT_FAIL;
				response.sessionId.total = 0;
				response.payload = (uint64_t)player;
				thread->EnqueueMessage(&response);
			}
		}
	}

	SLOG(L"DummyClient", L"Message Thread Exit");
}
