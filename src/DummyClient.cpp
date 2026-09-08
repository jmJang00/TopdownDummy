#include "pch.h"
#include <cstdio>
#include <atomic>
#include <JCore/SLog.h>
#include <JCore/Profiler.h>
#include <JNet/CPacket.h>
#include <JNet/CNetClient.h>
#include <JNet/CSession.h>
#include <JCore/CTlsMemoryPool.h>
#include <JNet/CMonitorThread.h>
#include <JParse/SourceFile.h>
#include "Player.h"
#include "PlayerBT.h"
#include "DummyClient.h"
#include "BTParser.h"
#include "AccountReader.h"
#include "CLogicThread.h"
#include "CConnectThread.h"
#include "Proxy.h"

DummyClient::DummyClient()
	: _worker(nullptr)
	, _disconnectTotal(0)
	, _isRunning(false)
	, _encoding(false)
	, _sendBufZero(false)
	, _nagle(false)
	, _nextId(1)
	, _sessionCnt(0)
	, _connectTotal(0)
	, _connector(nullptr)
	, _sessionIndexStack(20000)
{
	memset((char*)&_clientAddr, 0, sizeof(_clientAddr));
	memset((char*)&_serverAddr, 0, sizeof(_serverAddr));

	_btParser = new BTParser();
	_accountReader = new AccountReader();
	_proxy = new Proxy(this);

	_clientOnAction.resize(FEnumValue::GetTotalCount());
}

DummyClient::~DummyClient()
{
	if (_isRunning)
		Stop();

	delete _btParser;
	delete _accountReader;
}

bool DummyClient::Start(FDummyConfig& config, const std::vector<FDummyThreadConfig>& threadsConfig)
{
	do
	{
		SLOG(L"DummyClient", L"Start Dummy");

		_encoding = config.encoding;
		_isRunning = true;
		_nagle = config.nagle;
		_sendBufZero = config.sendBufZero;

		_maxSession = 0;
		for (int i = 0; i < threadsConfig.size(); i++)
		{
			_maxSession += threadsConfig[i].userNum;
		}
		_maxSession += 20;

		_sessions.resize(_maxSession);

		for (int i = _maxSession - 1; i >= 0; --i)
		{
			_sessionIndexStack.push(i);
		}

		ZeroMemory(&_clientAddr, sizeof(_clientAddr));
		_clientAddr.sin_family = AF_INET;
		if (inet_pton(AF_INET, config.bindIp.c_str(), &_clientAddr.sin_addr.s_addr) != 1)
		{
			ELOG(L"DummyClient", L"inet_pton failed, [ErrorCode]:%d", WSAGetLastError());
			break;
		}

		_clientAddr.sin_port = 0;

		addrinfo hints{};
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		addrinfo* result = nullptr;
		if (getaddrinfo(config.serverIp.c_str(), config.serverPort.c_str(), &hints, &result) != 0)
		{
			ELOG(L"DummyClient", L"getaddrinfo failed, [ErrorCode]:%d", WSAGetLastError());
			break;
		}

		_serverAddr = *(SOCKADDR_IN*)result->ai_addr;

		wchar_t ipStr[64];
		InetNtop(AF_INET, &_serverAddr.sin_addr, ipStr, 64);
		unsigned short port = ntohs(_serverAddr.sin_port);

		SLOG(L"DummyClient", L"ServerAddr - %s:%d", ipStr, port);

		freeaddrinfo(result);

		_worker = new CWorkerThread(config.workerThreadNum, config.concurrentThreadNum);
		_worker->Start();

		_connector = new CConnectThread(this);
		if (!_connector->Create(true))
		{
			ELOG(L"DummyClient", L"Can't create ConnectThread, [ErrorCode]:%d", GetLastError());
			break;
		}

		bool failed = false;
		_logics.resize(threadsConfig.size());

		SourceFile file;
		SLOG(L"DummyClient", L"Evaluate bt tree...\n");
		for (int i = 0; i < threadsConfig.size(); i++)
		{
			if (_btParser->btMap.find(threadsConfig[i].userBTFile.c_str()) == _btParser->btMap.end())
			{
				file.Clear();
				if (file.ReadFile("Config", threadsConfig[i].userBTFile.c_str()) == 0)
				{
					ELOG(L"DummyClient", L"%S read fail\n", threadsConfig[i].userBTFile.c_str());
					failed = true;
					break;
				}

				if (!_btParser->Run(&file))
				{
					failed = true;
					break;
				}
			}
		}
		SLOG(L"DummyClient", L"Successfully evaluate bt tree\n");

		if (failed)
		{
			break;
		}

		_threadsInfo.resize(threadsConfig.size());
		for (int i = 0; i < threadsConfig.size(); i++)
		{
			if (!_accountReader->ReadAccountFile("Config", 
				threadsConfig[i].userInfoFile.c_str(), threadsConfig[i].userNum, &_threadsInfo[i]))
			{
				break;
			}
			_threadsInfo[i].userNum = threadsConfig[i].userNum;
		}

		for (int i = 0; i < threadsConfig.size(); i++)
		{
			_logics[i] = new CLogicThread(this, &_threadsInfo[i], 
				_btParser->btMap[threadsConfig[i].userBTFile.c_str()]);

			if (!_logics[i]->Create(true))
			{
				ELOG(L"DummyClient", L"can't create WorkerThread, [ErrorCode]:%d", GetLastError());
				failed = true;
				break;
			}
		}

		if (failed)
		{
			break;
		}

		_connector->Resume();
		for (int i = 0; i < _logics.size(); i++)
		{
			_logics[i]->Resume();
		}
		return true;

	} while (0);

	Stop();

	return false;
}

void DummyClient::Stop()
{
	SLOG(L"DummyClient", L"Stop");

	for (int i = 0; i < _logics.size(); i++)
	{
		if (_logics[i] != nullptr)
		{
			_logics[i]->Shutdown();
			_logics[i]->Wait();
			_logics[i]->Close();
		}
	}

	if (_connector != nullptr)
	{
		_connector->Shutdown();
		_connector->Wait();
		_connector->Close();
	}

	_isRunning = false;

	for (int i = 0; i < _maxSession; ++i)
	{
		if (_sessions[i]._refCnt & 0x80000000)
		{
			Disconnect(_sessions[i]._id);
		}
	}

	while (_sessionIndexStack.size() != _maxSession)
	{
		Sleep(10);
	}

	if (_worker != nullptr)
	{
		_worker->Stop();
		delete _worker;
		_worker = nullptr;
	}

	if (_connector != nullptr)
	{
		delete _connector;
		_connector = nullptr;
	}

	for (int i = 0; i < _logics.size(); i++)
	{
		if (_logics[i] != nullptr)
		{
			delete _logics[i];
			_logics[i] = nullptr;
		}
	}
	_logics.clear();
	_sessions.clear();

	_encoding = false;
	_nagle = false;

	while (_sessionIndexStack.size() > 0)
	{
		int arg;
		_sessionIndexStack.pop(&arg);
	}

	for (const auto& it : _btParser->btMap)
	{
		PlayerBT* bt = it.second;
		delete bt;
	}

	_btParser->btMap.clear();
	_threadsInfo.clear();
	_maxSession = 0;
}

bool DummyClient::Disconnect(FSessionId sessionId)
{
	if (sessionId.internal.idx >= (unsigned int)_maxSession)
	{
		return false;
	}

	CSession* session = &_sessions[sessionId.internal.idx];
	if (!session->AddRef())
	{
		session->ReleasePost();
		return false;
	}

	if (session->_id.total != sessionId.total || InterlockedExchange8(&session->_disconnect, 1) == 1)
	{
		session->ReleasePost();
		return false;
	}

	InterlockedExchange8(&session->_invalid, 1);
	long disconnectNum = InterlockedIncrement(&_disconnectTotal);
	CancelIoEx((HANDLE)session->_sock, (OVERLAPPED*)session->_recvOverlapped);
	CancelIoEx((HANDLE)session->_sock, (OVERLAPPED*)session->_sendOverlapped);

	session->ReleasePost();
	return true;
}

bool DummyClient::SendPacket(FSessionId sessionId, CPacketBuffer* message)
{
	if (sessionId.internal.idx >= (unsigned int)_maxSession)
	{
		return false;
	}

	CSession* session = &_sessions[sessionId.internal.idx];

	if (!session->AddRef())
	{
		session->ReleasePost();
		return false;
	}

	if (session->_id.total != sessionId.total || session->_invalid == 1)
	{
		session->ReleasePost();
		return false;
	}

	message->AddRef();

	if (!session->_sendBuf->Enqueue(message))
	{
		OnError(ENetError::SEND_BUFFER_LIMIT_REACHED, "SendPacket(): Packet count exceeds send buffer limit");
		session->ReleasePost();
		message->Release();
		Disconnect(sessionId);
		return false;
	}

	if (InterlockedExchange8(&session->_sending, 1) == 0)
	{
		_worker->PostStatus((ULONG_PTR)session, CWorkerThread::sSendStartOverlapped, 0);
	}
	else
	{
		session->ReleasePost();
	}

	return true;
}

void DummyClient::OnEnterJoinServer(FSessionId id)
{

}

void DummyClient::OnRelease(FSessionId sessionId, void* userData)
{
	Player* player = (Player*)userData; 

	Message msg;
	msg.type = (unsigned char)MessageType::MSG_DISCONNECT;
	msg.sessionId = sessionId;
	msg.payload = (uint64_t)player;

	player->_responseTime = CProfiler::GetNanoSec();
	player->_owner->EnqueueMessage(&msg);
}

void DummyClient::OnRecv(FSessionId sessionId, CPacketView* packet)
{
	Message msg;
	msg.type = (unsigned char)MessageType::MSG_PACKET;
	msg.sessionId = sessionId;
	CPacketView* view = CPacketView::Alloc(*packet);
	msg.payload = (uint64_t)view;
	view->SetReceiveTime(CProfiler::GetNanoSec());

	Player* player = (Player*)_sessions[sessionId.internal.idx]._userData; 
	player->_owner->EnqueueMessage(&msg);
}

CSession* DummyClient::CreateSession(SOCKET sock)
{
	if (_sessionCnt >= _maxSession)
	{
		return nullptr;
	}

	char ip[16] = { 0 };
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(clientAddr);
	getpeername(sock, (SOCKADDR*)&clientAddr, &addrLen);
	inet_ntop(AF_INET, &clientAddr.sin_addr, ip, 16);
	unsigned short port = ntohs(clientAddr.sin_port);

	int idx;
	if (!_sessionIndexStack.pop(&idx))
	{
		return nullptr;
	}

	FSessionId sessionId;
	sessionId.internal.id = _nextId++;
	sessionId.internal.idx = idx;

	CSession* session = &_sessions[sessionId.internal.idx];

	if (!_worker->Register(session, sock))
	{
		_sessionIndexStack.push(idx);
		return nullptr;
	}

	session->Start(sock, _worker, this, nullptr, sessionId, _encoding);

	InterlockedIncrement(&_sessionCnt);

	OnEnterJoinServer(sessionId);

	return session;
}

bool DummyClient::ReleaseSession(CSession* session)
{
	FSessionId id = session->_id;
	void* userData = session->_userData;
	session->Reset();
	OnRelease(id, userData);
	_sessionIndexStack.push(id.internal.idx);
	InterlockedDecrement(&_sessionCnt);

	return true;
}

void DummyClient::OnPrintExternal(CMonitorTable* table)
{
	table->PrintColumnStr(2, L"Connect Total");
	table->PrintColumnStr(2, L"Connect TPS");
	table->PrintColumnStr(2, L"Send TPS");
	table->PrintColumnStr(2, L"Recv TPS");
	table->PrintColumnFormat(2, L"%d", GetConnectTotal());
	table->PrintColumnFormat(2, L"%d", GetConnectTPS());
	table->PrintColumnFormat(2, L"%d", GetSendMessageTPS());
	table->PrintColumnFormat(2, L"%d", GetRecvMessageTPS());
	table->PrintDivider();
	table->PrintColumnStr(2, L"Disconnect Total");
	table->PrintColumnFormat(1, L"%d", GetDisconnectTotal());
	table->PrintColumnStr(2, L"Down Client");
	table->PrintColumnFormat(1, L"%d", GetDownClientTotal());
	table->PrintColumnStr(1, L"Session");
	table->PrintColumnFormat(1, L"%d", GetSessionCount());
	table->PrintDivider();

	for (int i = 0; i < FEnumValue::GetTotalCount(); i++)
	{
		_clientOnAction[i] = 0;
	}

	for (int i = 0; i < _logics.size(); i++)
	{
		for (int j = 0; j < FEnumValue::GetTotalCount(); j++)
		{
			_clientOnAction[j] += _logics[i]->_clientOnAction[j];
		}
	}

	for (int i = 0; i < FEnumValue::GetTotalCount(); i++)
	{
		FEnumValue enumValue = FEnumValue(i);
		if (_clientOnAction[i] > 0)
		{
			table->PrintColumnFormat(1, L"%s >", enumValue.ToString());
			table->PrintColumnFormat(1, L"%d", _clientOnAction[i]);
		}
	}

	table->PrintDivider();

	for (int i = 0; i < _logics.size(); i++)
	{
		table->PrintColumnStr(1, L"Frame");
		table->PrintColumnFormat(1, L"%d", _logics[i]->GetFrame());
		table->PrintColumnStr(1, L"Dequeue TPS");
		table->PrintColumnFormat(1, L"%d", _logics[i]->GetDequeueTPS());
		table->PrintColumnStr(1, L"Queue Size");
		table->PrintColumnFormat(1, L"%d", _logics[i]->GetMsgQSize());
		table->PrintLineFeed();
	}
}

unsigned int DummyClient::GetSessionCount()
{
	return _sessionCnt;
}

unsigned long long DummyClient::GetConnectTotal()
{
	return _connectTotal;
}

unsigned long long DummyClient::GetConnectTPS()
{
	long cnt = InterlockedExchange(&_connector->_connectCnt, 0);
	_connectTotal += cnt;
	return cnt;
}

unsigned long long DummyClient::GetRecvMessageTPS()
{
	return _worker->GetRecvMessageCnt();
}

unsigned long long DummyClient::GetSendMessageTPS()
{
	return _worker->GetSendMessageCnt();
}

unsigned long long DummyClient::GetDisconnectTotal()
{
	long long sum = 0;
	for (int i = 0; i < _logics.size(); i++)
	{
		sum += _logics[i]->_disconnectedCnt;
	}

	return sum;
}

unsigned long long DummyClient::GetDownClientTotal()
{
	long long sum = 0;
	for (int i = 0; i < _logics.size(); i++)
	{
		sum += _logics[i]->_downClientCnt;
	}

	return sum;
}

void DummyClient::RefreshStatistics()
{
	_connectTotal = 0;
	_disconnectTotal = 0;

	for (int i = 0; i < _logics.size(); i++)
	{
		if (_logics[i])
		{
			_logics[i]->RefreshStatistics();
		}
	}

	if (_worker)
	{
		_worker->RefreshStatistics();
	}
}
