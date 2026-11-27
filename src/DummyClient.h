#pragma once

#include <map>
#include <vector>
#include <stack>
#include <JCore/CLockFreeStack.h>
#include <JCore/MyConfigs.h>
#include <JNet/CSession.h>
#include <JNet/INetworkEntity.h>
#include <JNet/CWorkerThread.h>
#include "AccountReader.h"
#include "CLogicThread.h"

class CSession;
class CPacketBuffer;
class CLogicThread;
class CPacket;
class PlayerManager;
class SectorManager;
class Player;
class BTParser;
class AccountReader;
class CMonitorThread;
class CConnectThread;
class Proxy;

struct FDummyThreadConfig
{
	int userNum = 0;
	std::string userInfoFile;
	std::string userBTFile;
};

class DummyClient : public INetworkEntity
{
public:
	friend class CMonitorThread;
	friend class CSession;

	DummyClient();
	virtual ~DummyClient();
	
	virtual bool Start(FDummyConfig& config, const std::vector<FDummyThreadConfig>& threadsConfig);
	virtual void Stop();

	virtual bool Disconnect(FSessionId sessionId);
	bool SendPacket(FSessionId sessionId, CPacketBuffer* message);

	virtual void OnEnterJoinServer(FSessionId sessionId);
	virtual void OnPendingRecv(FSessionId sessionId, CPacketView* packet) {}
	virtual void OnRecv(FSessionId sessionId, CPacketView* packet);
	void OnRelease(FSessionId sessionId, void* userData);

	void OnError(ENetError errCode, const char* errMsg) override 
	{
		SLOGA(L"DummyClient", L"%S", errMsg);
	}

	void OnPrintExternal(CMonitorTable* table) override;
	void OnCollectExternal(MetricsCollector& collector) override {}

	virtual CSession* CreateSession(SOCKET sock);
	virtual bool ReleaseSession(CSession* session);
	unsigned int GetSessionCount();

	unsigned long long GetConnectTotal();
	unsigned long long GetConnectTPS();
	unsigned long long GetRecvMessageTPS();
	unsigned long long GetSendMessageTPS();
	unsigned long long GetDisconnectTotal();
	unsigned long long GetDownClientTotal();
	virtual void RefreshStatistics();

	Proxy* GetProxy() { return _proxy; };
	BTParser* GetBTParser() { return _btParser; }

private:
	long long _connectTotal;
	long _disconnectTotal;
	std::vector<CSession> _sessions;
	long _sessionCnt;
	unsigned int _nextId;
	int _maxSession = 0;
	CLockFreeStack<int> _sessionIndexStack;

public:
	bool _isRunning;
	bool _encoding;
	bool _nagle;
	bool _sendBufZero;
	Proxy* _proxy;
	SOCKADDR_IN _serverAddr;
	SOCKADDR_IN _clientAddr;
	CWorkerThread* _worker;
	std::vector<CLogicThread*> _logics;
	std::vector<long> _clientOnAction;
	CConnectThread* _connector;
	BTParser* _btParser;
	AccountReader* _accountReader;
	std::vector<ThreadInfo> _threadsInfo;
};
