#pragma once
#include <unordered_map>
#include <JCore/CThread.h>
#include <JCore/CRingBuffer.h>
#include <JNet/CSession.h>
#include <JCore/CLockFreeQueue.h>
#include <JNet/CNetClient.h>
#include "Player.h"

class DummyClient;
class Player;
class PlayerManager;
class CPacket;
class PlayerBT;
class PacketManager;
struct ThreadInfo;
class Proxy;
class GridMap;

#pragma pack(push, 1)
struct Message
{
	unsigned char type;
	FSessionId sessionId;
	uint64_t payload;
};
#pragma pack(pop)

enum class MessageType
{
	MSG_QUIT,
	MSG_PACKET,
	MSG_DISCONNECT,
	MSG_CONNECT_SUCCESS,
	MSG_CONNECT_FAIL,
};

enum EActionDelay
{
	ConnectDelay,
	DisconnectDelay,
	LoginDelay,
	MoveDelay,
	ChatDelay,
	NumOfActionDelay,
};

struct FMonitorRecord
{
	unsigned short _type;
	double _avr;
	int _min;
	int _max;
	int _cnt;

	FMonitorRecord()
	{
		_type = 0;
		_cnt = 0;
		_avr = 0;
		_max = 0;
		_min = 0;
	}

	void Clear()
	{
		_type = 0;
		_cnt = 0;
		_avr = 0;
		_max = 0;
		_min = 0;
	}

	FMonitorRecord& operator+=(FMonitorRecord& other)
	{
		if (other._cnt != 0)
		{
			double n_m = (double)_cnt / (other._cnt + _cnt);
			double m_n = (double)other._cnt / (other._cnt + _cnt);
			_min = std::min(_min, other._min);
			_max = std::max(_max, other._max);
			_cnt += other._cnt;
			_avr = _avr * n_m + other._avr * m_n;
		}
		return *this;
	}
};

class MonitorInfo
{
public:
	MonitorInfo()
	{
		for (int i = 0; i < FEnumValue::GetTotalCount(); i++)
		{
			Init(i);
		}
	}

	void Init(unsigned short type)
	{
		FMonitorRecord& record = _records[type];
		record._type = type;
		record._cnt = 0;
		record._avr = 0;
		record._max = 0;
		record._min = INT_MAX;
	}

	void Update(unsigned short type, int val)
	{
		FMonitorRecord& record = _records[type];
		// avg_(n) = avg_(n-1) + (x - avg_(n-1)) / n
		record._cnt = record._cnt + 1;
		record._avr = record._avr + (double)(val - record._avr) / (record._cnt);
		record._max = std::max(record._max, val);
		record._min = std::min(record._min, val);
	}

	void Extract(unsigned short type, FMonitorRecord& outRecord)
	{
		FMonitorRecord& record = _records[type];
		outRecord._type = record._type;
		outRecord._avr = record._avr;
		outRecord._cnt = record._cnt;
		outRecord._max = record._max;
		if (record._min == INT_MAX)
		{
			outRecord._min = 0;
		}
		else
		{
			outRecord._min = record._min;
		}
	}

	void Clear()
	{
		for (int i = 0; i < FEnumValue::GetTotalCount(); i++)
		{
			Init(i);
		}
	}

private:
	FMonitorRecord _records[FEnumValue::GetTotalCount()];
};

typedef std::unordered_map<unsigned long long, Player*> player_map;

class CLogicThread : public CThread
{
public:
	CLogicThread(DummyClient* dummy, ThreadInfo* info, PlayerBT* bt);

	virtual ~CLogicThread();

	virtual void Shutdown();

	void EnqueueMessage(Message* msg);

	int GetMsgQSize() const;

	int GetDequeueTPS() { return InterlockedExchange(&_dequeueCnt, 0); }

	int GetFrame() { return InterlockedExchange(&_frame, 0); }

	void RefreshStatistics() 
	{
		InterlockedExchange(&_dequeueCnt, 0);
		InterlockedExchange(&_downClientCnt, 0);
		InterlockedExchange(&_disconnectedCnt, 0);
	}

	void CheckUpdate();

	unsigned int GetTime();

	unsigned long long GetPacketReceiveTime();

	Proxy* GetProxy() { return _proxy; }

	Player* FindConnectedPlayer(FSessionId sessionId);

	void LogicThread();
	
private:
	HANDLE _hEvent;
	HANDLE _hShutdownEvent;
	CLockFreeQueue<Message> _msgQ;
	player_map _playerMap;
	unsigned int _currentTick;
	unsigned int _frameTick;
	PacketManager* _packetMng;
	Proxy* _proxy;
	unsigned long long _packetReceiveTime;

public:
	GridMap* _map;
	unsigned int _globalTick;
	PlayerManager* _playerMng;
	DummyClient* _dummy;
	long _dequeueCnt;
	long _downClientCnt;
	long _disconnectedCnt;
	unsigned int _frame;
	bool _encoding;
	bool _nagle;
	bool _sendBufZero;
	SOCKADDR_IN _serverAddr;
	SOCKADDR_IN _clientAddr;

	long _clientOnAction[FEnumValue::GetTotalCount()] = { 0 };
};