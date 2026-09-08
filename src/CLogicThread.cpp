#include "pch.h"
#include <JCore/SLog.h>
#include <JNet/CPacket.h>
#include "PlayerManager.h"
#include "CLogicThread.h"
#include "DummyClient.h"
#include "Player.h"
#include "PlayerBT.h"
#include "AccountReader.h"
#include "PacketHandler.h"
#include "PacketManager.h"
#include "GridMap.h"

CLogicThread::CLogicThread(DummyClient* dummy, ThreadInfo* info, PlayerBT* bt)
	: CThread([this]() { LogicThread(); }, 1)
	, _dummy(dummy)
	, _msgQ(160000)
	, _dequeueCnt(0)
	, _hEvent(INVALID_HANDLE_VALUE)
	, _hShutdownEvent(INVALID_HANDLE_VALUE)
	, _globalTick(0)
	, _frameTick(0)
	, _frame(0)
	, _disconnectedCnt(0)
	, _downClientCnt(0)
{
	_hEvent = CreateEvent(nullptr, false, false, nullptr);
	_hShutdownEvent = CreateEvent(nullptr, true, false, nullptr);
	_encoding = dummy->_encoding;
	_nagle = dummy->_nagle;
	_serverAddr = dummy->_serverAddr;
	_clientAddr = dummy->_clientAddr;
	_sendBufZero = dummy->_sendBufZero;
	_proxy = dummy->GetProxy();
	_map = new GridMap();
	_map->Load("Data/GridMap.bytes");

	_playerMng = new PlayerManager(this);
	_packetMng = new PacketManager();
	_packetMng->Attach(new PacketHandler(this, _proxy));

	_clientOnAction[(unsigned short)ActionStatus::Disconnected] += info->userNum;

	for (int i = 0; i < info->userNum; i++)
	{
		_playerMng->AddPlayer(&info->info[i], bt, this);
	}
}

CLogicThread::~CLogicThread()
{
	while (1)
	{
		Message msg;
		if (_msgQ.Dequeue(&msg) == 0)
		{
			break;
		}

		if (msg.type == (char)MessageType::MSG_PACKET)
		{
			if (msg.payload != 0)
			{
				CPacketView::Free((CPacketView*)msg.payload);
			}
		}
	}

	_playerMng->Clear();

	delete _playerMng;
	delete _packetMng;
	delete _map;

	CloseHandle(_hEvent);
	CloseHandle(_hShutdownEvent);
}

void CLogicThread::Shutdown()
{
	SetEvent(_hShutdownEvent);
	Message msg;
	msg.type = (unsigned char)MessageType::MSG_QUIT;
	msg.payload = 0;
	msg.sessionId.total = 0;
	EnqueueMessage(&msg);
}

void CLogicThread::EnqueueMessage(Message* msg)
{
	if (msg->type == (unsigned char)MessageType::MSG_PACKET)
	{
		if (_msgQ.Enqueue(*msg))
		{
			SetEvent(_hEvent);
		}
		else
		{
			_dummy->Disconnect(msg->sessionId);
			SLOGA(L"DummyClient", L"# 메시지 큐 사이즈 초과 Disconnect", msg->sessionId.total);
		}
	}
	else
	{
		_msgQ.ForceEnqueue(*msg);
	}
}

int CLogicThread::GetMsgQSize() const
{
	return _msgQ.GetSize();
}

void CLogicThread::LogicThread()
{
	CProfiler::Register(EDummyProfile::DUMMY_PROFILE_PKT_DELAY, L"Delay", L"Packet", 0.5f);
	CProfiler::Register(EDummyProfile::DUMMY_PROFILE_CONN_DELAY, L"Delay", L"Conn", 1.f);
	CProfiler::Register(EDummyProfile::DUMMY_PROFILE_DISCONN_DELAY, L"Delay", L"Disconn", 1.f);
	CProfiler::Register(EDummyProfile::DUMMY_PROFILE_LOGIC_UPDATE, L"Delay", L"Simulate", 1.f);

	DummyClient* dummy = (DummyClient*)_dummy;

	SLOG(L"DummyClient", L"Message Thread Start");

	HANDLE handles[2] = { _hShutdownEvent, _hEvent };

	DWORD profileTick = timeGetTime();
	bool bShutdown = false;
	while (!bShutdown)
	{
		DWORD tick = timeGetTime();
		DWORD deltaTick = tick - _globalTick;
		SMPL_PRO_END(EDummyProfile::DUMMY_PROFILE_LOGIC_UPDATE);
		if (profileTick + 60'000 < tick)
		{
			profileTick = tick;
			CProfiler::Flush();
		}
		DWORD retVal = WaitForMultipleObjects(2, handles, false, std::max(20 - (int)deltaTick, 0));
		SMPL_PRO_BEGIN(EDummyProfile::DUMMY_PROFILE_LOGIC_UPDATE);

		if (retVal == WAIT_OBJECT_0)
		{
			break;
		}

		Message msg;

		while (_msgQ.Dequeue(&msg))
		{
			CheckUpdate();

			++_dequeueCnt;

			if ((MessageType)msg.type == MessageType::MSG_QUIT)
			{
				bShutdown = true;
				break;
			}

			switch ((MessageType)msg.type)
			{
			case MessageType::MSG_CONNECT_SUCCESS:
			{
				Player* player = (Player*)msg.payload;
				player->_sessionId = msg.sessionId;
				_playerMap.insert({ player->_sessionId.total, player });
				player->OnConnected();
				break;
			}
			case MessageType::MSG_CONNECT_FAIL:
			{
				Player* player = (Player*)msg.payload;
				player->OnConnectFailed();
				break;
			}
			case MessageType::MSG_DISCONNECT:
			{
				Player* player = (Player*)msg.payload;
				_playerMap.erase(player->_sessionId.total);
				player->OnDisconnected();
				break;
			}
			case MessageType::MSG_PACKET:
			{
				unsigned short type;
				CPacketView* packet = (CPacketView*)msg.payload;
				*packet >> type;

				_packetReceiveTime = packet->GetReceiveTime();
				if (!_packetMng->PacketProc((PacketType)type, packet, msg.sessionId))
				{
					ELOG(L"DummyClient", L"Packet Handle Fail %d", type);
					dummy->Disconnect(msg.sessionId);
				}
				CPacketView::Free(packet);
				break;
			}
			default:
				break;
			}
		}

		CheckUpdate();
	}

	SLOG(L"DummyClient", L"Message Thread Exit");
}

void CLogicThread::CheckUpdate()
{
	_currentTick = timeGetTime();
	DWORD deltaTick = _currentTick - _globalTick;
	if (deltaTick >= 20)
	{
		InterlockedIncrement(&_frame);
		do 
		{
			_globalTick += 20;
			deltaTick -= 20;

		} while (deltaTick >= 20);
		_playerMng->Update(deltaTick);
	}
}

unsigned int CLogicThread::GetTime()
{
	return _currentTick;
}

unsigned long long CLogicThread::GetPacketReceiveTime()
{
	return _packetReceiveTime;
}

Player* CLogicThread::FindConnectedPlayer(FSessionId sessionId)
{
	player_map::iterator iter = _playerMap.find(sessionId.total);
	if (iter == _playerMap.end())
	{
		ELOG(L"DummyClient", L"Can't find player");
		return nullptr;
	}

	return iter->second;
}
