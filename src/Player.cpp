#include "pch.h"
#include "Player.h"
#include <stdio.h>
#include <map>
#include <JCore/CTlsMemoryPool.h>
#include <JCore/SLog.h>
#include <JCore/Profiler.h>
#include <JNet/CPacket.h>
#include "DummyClient.h"
#include "PlayerManager.h"
#include "CLogicThread.h"
#include "PlayerBT.h"
#include "CConnectThread.h"
#include "Proxy.h"
#include "Character.h"
#include "MathUtil.h"
#include "StatusType.h"

const wchar_t* gActionStr[] =
{
	L"spawnwait",
	L"discon",
	L"conreq",
	L"lobbyidle",
	L"gameidle",
	L"disconreq",
	L"stop",
	L"packet",
};

extern const int gActionStrCnt = sizeof(gActionStr) / sizeof(gActionStr[0]);

SendStatus Player::SendProcess(MessageArgs* args)
{
	switch (args->protocol)
	{
	case PacketType::C_MOVE_START:
	{
		// 등록
		if (!_gameStarted || !_ch->IsActive())
			return SendStatus::Failure;

		if (_ch->WaitingServer())
			return SendStatus::Running;

		C_MoveStartArgs* param = (C_MoveStartArgs*)args;
		_ch->AddMoveInput();
		param->clientTick = _ch->GetCurrentTick();
		param->target = _ch->GetState().target;
		_request.timeout = 3000;
		break;
	}
	case PacketType::C_ROTATE_START:
	{
		// 등록
		if (!_gameStarted || !_ch->IsActive())
			return SendStatus::Failure;

		if (_ch->WaitingServer())
			return SendStatus::Running;

		C_RotateStartArgs* param = (C_RotateStartArgs*)args;
		_ch->AddRotateInput();
		param->clientTick = _ch->GetCurrentTick();
		param->targetAngle = _ch->GetState().targetAngle;
		_request.timeout = 3000;
		break;
	}
	case PacketType::C_PROJECTILE_SHOOT_START:
	{
		// 등록
		if (!_gameStarted || !_ch->IsActive())
			return SendStatus::Failure;

		if (_ch->WaitingServer())
			return SendStatus::Running;

		if (!_ch->CanFire())
			return SendStatus::Running;

		C_ProjectileShootStartArgs* param = (C_ProjectileShootStartArgs*)args;
		param->clientTick = _ch->GetCurrentTick();
		_request.timeout = 3000;
		break;
	}
	case PacketType::C_MATCH_START:
	{
		// 등록
		if (_gameStarted)
			return SendStatus::Ignore;

		C_MatchStartArgs* param = (C_MatchStartArgs*)args;
		break;
	}
	case PacketType::C_MATCH_CANCEL:
	{
		C_MatchCancelArgs* param = (C_MatchCancelArgs*)args;
		break;
	}
	case PacketType::C_SCENE_READY:
	{
		// 등록
		C_SceneReadyArgs* param = (C_SceneReadyArgs*)args;
		break;
	}
	case PacketType::C_WEAPON_SELECT:
	{
		C_WeaponSelectArgs* param = (C_WeaponSelectArgs*)args;
		break;
	}
	case PacketType::C_ACCOUNT_INFO_DEBUG:
	{
		// 등록
		C_AccountInfoDebugArgs* param = (C_AccountInfoDebugArgs*)args;
		param->accountId = _accountNo;
		break;
	}
	case PacketType::C_RETURN_TO_LOBBY:
	{
		// 등록
		C_ReturnToLobbyArgs* param = (C_ReturnToLobbyArgs*)args;
		break;
	}
	default:
	{
		ELOG(L"DummyClient", L"Undefined Packet Node");
		return SendStatus::Failure;
	}
	}

	_proxy->Send(_sessionId, (MessageArgs*)args);

	return SendStatus::Success;
}

Player::Player()
{
	_ch = new Character();
}

Player::~Player()
{
	delete _ch;
	delete _bt;
	_bt = nullptr;
}

void Player::Init(CLogicThread* owner, PlayerBT* bt,
	unsigned long long accountNo, const wchar_t* newId, 
	const wchar_t* newNickname, const char* newSessionKey)
{
	_owner = owner;
	_accountNo = accountNo;
	_bt = bt;
	memcpy(_id, newId, sizeof(_id));
	memcpy(_nickname, newNickname, sizeof(_nickname));
	memcpy(_sessionKey, newSessionKey, sizeof(_sessionKey));
	_action = ActionStatus::Disconnected;
	_malicious = false;
	_sessionId = { 0 };
	_connected = false;
	_connectResponded = false;
	_disconnectResponded = false;
	_requestTime = 0;
	_responseTime = 0;
	_request.Reset();
	_proxy = owner->GetProxy();
}

void Player::OnConnected()
{
	_connected = true;
	_connectResponded = true;
}

void Player::OnDisconnected()
{
	_connected = false;
	if (_action == ActionStatus::DisconnectRequested)
	{
		_disconnectResponded = true;
	}
	else
	{
		if (!_malicious)
		{
			ELOGA(L"DummyClient", L"DownClient Detected, account:%llu", _accountNo);
			_owner->_downClientCnt++;
			_bt->PrintStack();
		}
	}
	_owner->_disconnectedCnt++;
}

void Player::OnConnectFailed()
{
	_connected = false;
	_connectResponded = true;
}

void Player::ChangeAction(FEnumValue action)
{
	_owner->_clientOnAction[_action.GetTotalIndex()]--;
	_action = action;
	_owner->_clientOnAction[_action.GetTotalIndex()]++;
}

StatusType Player::Connect(BaseNode* node)
{
	switch (_action.GetTotalIndex())
	{
	case FEnumValue(ActionStatus::Disconnected).GetTotalIndex():
	{
		ChangeAction(ActionStatus::ConnectRequested);

		_requestTime = CProfiler::GetNanoSec();
		ConnectMessage msg;
		msg.player = this;
		msg.owner = _owner;
		_owner->_dummy->_connector->EnqueueMessage(&msg);
		return StatusType::Running;
	}
	case FEnumValue(ActionStatus::ConnectRequested).GetTotalIndex():
	{
		if (_connectResponded)
		{
			if (_connected)
			{
				SMPL_PRO_RECORD(EDummyProfile::DUMMY_PROFILE_CONN_DELAY, _responseTime - _requestTime);
				_requestTime = 0;
				_responseTime = 0;
				ChangeAction(ActionStatus::Idle);
				return StatusType::Success;
			}
			else
			{
				ChangeAction(ActionStatus::Disconnected);
				return StatusType::Failure;
			}
		}

		return StatusType::Running;
	}
	default:
	{
		ELOGA(L"DummyClient", L"Unexpected Status: %s", _action.ToString());
		_bt->PrintHistory();
		ChangeAction(ActionStatus::Stop);
		return StatusType::Running;
	}
	}
}

StatusType Player::Disconnect(BaseNode* node)
{
	switch (_action.GetTotalIndex())
	{
	case FEnumValue(ActionStatus::Idle).GetTotalIndex():
	case FEnumValue(ActionStatus::GameIdle).GetTotalIndex():
	{
		if (!_connected)
		{
			return StatusType::Failure;
		}

		_requestTime = CProfiler::GetNanoSec();
		_owner->_dummy->Disconnect(_sessionId);
		ChangeAction(ActionStatus::DisconnectRequested);
		return StatusType::Running;
	}
	case FEnumValue(ActionStatus::DisconnectRequested).GetTotalIndex():
	{
		if (_disconnectResponded)
		{
			SMPL_PRO_RECORD(EDummyProfile::DUMMY_PROFILE_DISCONN_DELAY, _responseTime - _requestTime);
			_requestTime = 0;
			_responseTime = 0;
			ChangeAction(ActionStatus::Disconnected);
			return StatusType::Failure;
		}
		return StatusType::Running;
	}
	default:
	{
		ELOGA(L"DummyClient", L"Unexpected Status: %s", _action.ToString());
		_bt->PrintHistory();
		ChangeAction(ActionStatus::Stop);
		return StatusType::Running;
	}
	}
}

StatusType Player::SpawnCheck(BaseNode* node)
{
	if (!_connected)
	{
		return StatusType::Failure;
	}

	if (_ch->IsActive() && _ch->HasSpawnCompleted())
	{
		return StatusType::Success;
	}

	return StatusType::Running;
}

StatusType Player::DoMatchIdle(BaseNode* node)
{
	if (!_connected)
	{
		return StatusType::Failure;
	}

	return StatusType::Success;
}

StatusType Player::DoGameIdle(BaseNode* node)
{
	if (!_connected || !_gameStarted)
	{
		return StatusType::Failure;
	}

	if (!_ch->IsActive())
	{
		return StatusType::Running;
	}

	return StatusType::Success;
}

void Player::ChangeIdle()
{
	if (_gameStarted)
	{
		ChangeAction(ActionStatus::GameIdle);
	}
	else
	{
		ChangeAction(ActionStatus::Idle);
	}
}

StatusType Player::ProcessPacketNode(RequestId reqId, 
	MessageArgs* args, bool response, PacketType resId, BaseNode* node)
{
	if (!_connected)
	{
		return StatusType::Failure;
	}

	if (_action == FEnumValue(ActionStatus::Idle) || _action == FEnumValue(ActionStatus::GameIdle))
	{
		_request.Reset();
		SendStatus status = SendProcess(args);
		if (status == SendStatus::Running)
		{
			return StatusType::Running;
		}
		else if (status == SendStatus::Failure)
		{
			return StatusType::Failure;
		}
		else if (status == SendStatus::Ignore)
		{
			return StatusType::Success;
		}

		ChangeAction(reqId);
		_request.state = reqId;
		_request.responseId = resId;
		if (!response)
		{
			RecvProcess(resId, true, 0);
		}
		else
		{
			_request.requestTime = CProfiler::GetNanoSec();
		}
		return StatusType::Running;
	}
	else if (_action == _request.state)
	{
		if (_request.responded)
		{
			ChangeIdle();
			if (_request.success)
			{
				return StatusType::Success;
			}
			else
			{
				return StatusType::Failure;
			}
		}

		if (_request.timeout != 0)
		{
			if (_ch->IsActive() && _ch->WaitingServer())
			{
				return StatusType::Running;
			}

			if (_request.timeoutStart == 0)
			{
				_request.timeoutStart = _owner->GetTime();
			}
			else if (_owner->GetTime() - _request.timeoutStart > _request.timeout)
			{
				ChangeIdle();
				return StatusType::Failure;
			}
		}

		return StatusType::Running;
	}
	else
	{
		ELOGA(L"DummyClient", L"Unexpected Status: %s", _action.ToString());
		_bt->PrintHistory();
		ChangeAction(ActionStatus::Stop);
		return StatusType::Running;
	}
}

void Player::RecvProcess(PacketType type, bool success, uint64_t responseTime)
{
	if (type != _request.responseId)
		return;

    _request.responded = true;
	_request.success = success;
	if (_request.requestTime != 0)
	{
		_request.responseTime = responseTime;
		
		if (type != PacketType::S_MATCH_FOUND)
		{
			SMPL_PRO_RECORD(EDummyProfile::DUMMY_PROFILE_PKT_DELAY, _request.responseTime - _request.requestTime);
		}

		_request.responseTime = 0;
		_request.requestTime = 0;
	}
}

void Player::Update(unsigned int time)
{
	if (_action == ActionStatus::Stop)
	{
		return;
	}

	if (!_bt->Tick())
	{
		if (_action != ActionStatus::Disconnected)
		{
			ELOGA(L"DownClient", L"Disconnected When Status: %s", _action.ToString());
			ChangeAction(ActionStatus::Disconnected);
		}

		_connected = false;
		_connectResponded = false;
		_disconnectResponded = false;
		_gameStarted = false;
		_request.Reset();
	}

	_ch->Simulate(time);
}

Character* Player::GetCharacter()
{
	return _ch;
}
