#pragma once
#include <stdint.h>
#include <map>
#include <unordered_map>
#include <JCore/CRingBuffer.h>
#include <JNet/CSession.h>
#include <JCore/SLog.h>
#include <JCore/CTlsMemoryPool.h>
#include <JNet/CNetClient.h>
#include "BaseNode.h"
#include "PacketManager.h"
#include "Packet.h"

//#define DEBUG_PLAYER
struct MessageArgs;
class DummyClient;
class CLogicThread;
class PlayerBT;
class Proxy;
class Character;

enum class ActionStatus : unsigned short
{
    SpawnWait,
	Disconnected,
	ConnectRequested,
	Idle,
	GameIdle,
	DisconnectRequested,
	Stop,
    PacketSent,
    Count,
};

enum class SendStatus : unsigned short
{
    Ignore,
    Success,
    Running,
    Failure,
};

extern const wchar_t* gActionStr[];
extern const int gActionStrCnt;
class CChattingServer;
class PlayerBT;
class Proxy;

struct FEnumValue
{
    enum class EType : uint8_t
    {
        None,
        User,
        Auto,
    };

    union FValue
    {
    public:
        ActionStatus UserValue;
        RequestId AutoValue;
        unsigned short RawValue;

        constexpr FValue()
            : RawValue(0)
        {
        }

        constexpr FValue(ActionStatus value)
            : UserValue(value)
        {
        }

        constexpr FValue(RequestId value)
            : AutoValue(value)
        {
        }

        constexpr FValue(unsigned short value)
            : RawValue(value)
        {
        }
    };

    EType Type;
	FValue Value;

    constexpr FEnumValue()
        : Type(EType::None)
        , Value(0)
    {
    }

    constexpr FEnumValue(ActionStatus value)
        : Type(EType::User)
        , Value(value)
    {
    }

    constexpr FEnumValue(RequestId value)
        : Type(EType::Auto)
        , Value(value)
    {
    }

    explicit FEnumValue(int totalIndex) 
    {
		if (totalIndex < 0 ||
			totalIndex >= GetTotalCount())
		{
			Type = EType::None;
			Value = 0;
			return;
		}

		if (totalIndex < GetUserCount())
		{
			Type = EType::User;
			Value = totalIndex;
			return;
		}

		Type = EType::Auto;
		Value = totalIndex - GetUserCount();
    }

public:

    bool IsUser() const
    {
        return Type == EType::User;
    }

    bool IsAuto() const
    {
        return Type == EType::Auto;
    }

    constexpr unsigned short GetUserIndex() const
    {
        return IsUser() ? Value.RawValue : -1;
    }

    constexpr unsigned short GetAutoIndex() const
    {
        return IsAuto() ? Value.RawValue : -1;
    }

    constexpr unsigned short GetTotalIndex() const
    {
        switch (Type)
        {
        case EType::User:
            return (unsigned short)Value.UserValue;

        case EType::Auto:
            return (int)ActionStatus::Count + (unsigned short)Value.AutoValue;

        default:
            return -1;
        }
    }

	static constexpr unsigned short GetUserCount()
	{
		return (unsigned short)ActionStatus::Count;
	}

	static constexpr unsigned short GetAutoCount()
	{
		return (unsigned short)RequestId::MaxRequest;
	}

	static constexpr unsigned short GetTotalCount() 
	{
		return GetUserCount() + GetAutoCount();
	}

    operator unsigned short()
    {
        return GetTotalIndex();
    }

    const wchar_t* ToString() const
    {
        switch (Type)
        {
        case EType::User:
            return UserToString((ActionStatus)Value.RawValue);

        case EType::Auto:
            return AutoToString((RequestId)Value.RawValue);

        default:
            return L"None";
        }
    }

public:

    static const wchar_t* UserToString(ActionStatus value)
    {
        if ((unsigned short)value >= gActionStrCnt)
        {
            return L"Unknown";
        }

        return gActionStr[(int)value];
    }

    static const wchar_t* AutoToString(RequestId value)
    {
        if ((unsigned short)value >= gRequestIdStrCnt)
        {
            return L"Unknown";
        }

        return gRequestIdStr[(unsigned short)value];
    }

public:

    bool operator==(const FEnumValue& rhs) const
    {
        return Type == rhs.Type &&
               Value.RawValue == rhs.Value.RawValue;
    }

    bool operator!=(const FEnumValue& rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const FEnumValue& rhs) const
    {
        return GetTotalIndex() < rhs.GetTotalIndex();
    }

    bool operator>(const FEnumValue& rhs) const
    {
        return GetTotalIndex() > rhs.GetTotalIndex();
    }

    bool operator<=(const FEnumValue& rhs) const
    {
        return GetTotalIndex() <= rhs.GetTotalIndex();
    }

    bool operator>=(const FEnumValue& rhs) const
    {
        return GetTotalIndex() >= rhs.GetTotalIndex();
    }
};

struct RequestContext
{
    RequestId state;

    bool responded;
    bool success;
    uint32_t timeout;
    uint32_t timeoutStart;
	PacketType responseId;
    uint64_t requestTime;
    uint64_t responseTime;

    RequestContext()
        : state()
        , responded(false)
        , requestTime(0)
        , responseTime(0)
        , success(false)
        , timeout(0)
		, timeoutStart(0)
		, responseId()
    {
    }

    void Reset()
    {
        state = {};
        responded = false;
        requestTime = 0;
        responseTime = 0;
        success = false;
        timeout = 0;
        timeoutStart = 0;
		responseId = (PacketType)0;
    }
};

class Player
{
public:

	Player();

	~Player();

	void Init(CLogicThread* connector, PlayerBT* bt,
		unsigned long long accountNo, const wchar_t* newId, 
		const wchar_t* newNickname, const char* newSessionKey);

	SendStatus SendProcess(MessageArgs* args);

	void ChangeAction(FEnumValue action);

	CSession* CreateSession(SOCKET sock);

	void OnConnected();

	void OnDisconnected();

	void OnConnectFailed();

	StatusType Connect(BaseNode* node);

	StatusType Disconnect(BaseNode* node);

    StatusType SpawnCheck(BaseNode* node);

	StatusType DoMatchIdle(BaseNode* node);

	StatusType DoGameIdle(BaseNode* node);

    void ChangeIdle();

	StatusType ProcessPacketNode(RequestId reqId, 
        MessageArgs* args, bool response, PacketType resId, BaseNode* node);

	void RecvProcess(PacketType type, bool success, uint64_t responseTime);

	void Update(unsigned int time);

    Character* GetCharacter();

	bool _connected = false;
	bool _connectResponded = false;
	bool _disconnectResponded = false;
    bool _gameStarted = false;
	FEnumValue _action = FEnumValue(ActionStatus::Disconnected);
	RequestContext _request;
	bool _malicious = false;
	PlayerBT* _bt = nullptr;
	FSessionId _sessionId = { 0 };
    // 디스커넥트 시간 분리
	uint64_t _requestTime = 0;
	uint64_t _responseTime = 0;
	unsigned long long _accountNo = 0; 
	wchar_t _id[20] = { 0 };
	wchar_t _nickname[20] = { 0 };
	char _sessionKey[64] = { 0 };
	CLogicThread* _owner = nullptr;
	Proxy* _proxy = nullptr;
    Character* _ch = nullptr;
};

