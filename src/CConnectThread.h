#pragma once
#include <JCore/CThread.h>
#include <JCore/CRingBuffer.h>
#include <JNet/CSession.h>
#include <JCore/CLockFreeQueue.h>
#include "CLogicThread.h"

#pragma pack(push, 1)
struct ConnectMessage
{
	Player* player;
	CLogicThread* owner;
};
#pragma pack(pop)

class DummyClient;

class CConnectThread : public CThread
{
public:
	CConnectThread(DummyClient* dummy);

	virtual ~CConnectThread();

	virtual void Shutdown();

	void EnqueueMessage(ConnectMessage* msg);

	int GetMsgQSize() const;

	int GetDequeueTPS()
	{
		return InterlockedExchange(&_dequeueCnt, 0);
	}

	void RefreshStatistics()
	{
		InterlockedExchange(&_dequeueCnt, 0);
		InterlockedExchange(&_connectCnt, 0);
	}

	void MessageThread();

public:
	SOCKET _sock;
	bool _nagle;
	bool _sendBufZero;
	SOCKADDR_IN _serverAddr;
	SOCKADDR_IN _clientAddr;
	long _connectCnt;

private:
	long _dequeueCnt;
	HANDLE _hEvent;
	HANDLE _hShutdownEvent;
	DummyClient* _dummy;
	CLockFreeQueue<ConnectMessage> msgQ;
};


