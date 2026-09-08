#include "pch.h"
#include "PacketHandler.h"
#include "Player.h"
#include "CLogicThread.h"
#include "PlayerManager.h"
#include "Character.h"
#include "Proxy.h"

PacketHandler::PacketHandler(CLogicThread* thread, Proxy* proxy)
{
	_proxy = proxy;
	_dummy = thread;
}

int PacketHandler::S_ResLoginGameServer(FSessionId sessionId, bool loginOk, const AccountInfo& account)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}

	player->RecvProcess(PacketType::S_RES_LOGIN_GAME_SERVER, true, _dummy->GetPacketReceiveTime());
	return PH_SUCCESS;
}

int PacketHandler::S_NtfCreateMyCharacter(FSessionId sessionId, int32_t serverTick, uint32_t entityId, uint16_t health, uint16_t weaponId)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}

	Character* ch = player->GetCharacter();
	ch->Spawn(entityId, _dummy->_map, serverTick);
	return PH_SUCCESS;
}

int PacketHandler::S_NtfCreateOtherCharacter(FSessionId sessionId, int32_t serverTick,
	uint32_t entityId, uint16_t health, uint16_t weaponId, int32_t accountId, bool isBot)
{
	return PH_SUCCESS;
}

int PacketHandler::S_DeleteCharacter(FSessionId sessionId , int32_t serverTick, uint32_t id)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}

	Character* ch = player->GetCharacter();
	if (id == ch->GetId())
	{
		ch->Despawn();
	}

	return PH_SUCCESS;
}


int PacketHandler::S_ReturnToLobby(FSessionId sessionId)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}

	Character* ch = player->GetCharacter();
	if (ch->IsActive())
	{
		ch->Despawn();
	}

	player->_gameStarted = false;

	return PH_SUCCESS;
}

int PacketHandler::S_MoveStart(FSessionId sessionId, int32_t acceptTick, 
	uint32_t id, const Vector2& target)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}

	Character* ch = player->GetCharacter();
	if (ch->GetId() == id)
	{
		player->RecvProcess(PacketType::S_MOVE_START, true, _dummy->GetPacketReceiveTime());
	}
	return PH_SUCCESS;
}

int PacketHandler::S_MoveState(FSessionId sessionId, int32_t currentTick, 
	uint32_t id, const Vector2& pos, const Vector2& target)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}
	Character* ch = player->GetCharacter();
	if (ch->GetId() == id)
	{
		ch->SetPosition(pos, target);
	}
	return PH_SUCCESS;
}

int PacketHandler::S_TickSync(FSessionId sessionId , int32_t serverTick)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}
	Character* ch = player->GetCharacter();
	ch->AddTimeInput(serverTick);
	return PH_SUCCESS;
}

int PacketHandler::S_RotateStart(FSessionId sessionId , int32_t acceptTick, uint32_t id, float targetAngle)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}
	Character* ch = player->GetCharacter();
	if (ch->GetId() == id)
	{
		player->RecvProcess(PacketType::S_ROTATE_START, true, _dummy->GetPacketReceiveTime());
	}
	return PH_SUCCESS;
}

int PacketHandler::S_RotateState(FSessionId sessionId , int32_t acceptTick, uint32_t id, float currentAngle, float targetAngle)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}
	Character* ch = player->GetCharacter();
	if (ch->GetId() == id)
	{
		ch->SetRotation(currentAngle, targetAngle);
	}
	return PH_SUCCESS;
}

int PacketHandler::S_ProjectileShootStart(FSessionId sessionId , int32_t acceptTick, uint32_t id)
{
	return PH_SUCCESS;
}

int PacketHandler::S_SpawnProjectile(FSessionId sessionId, int32_t acceptTick, uint32_t id, const Vector2& spawnPos, const Vector2& targetPos)
{
	return PH_SUCCESS;
}

int PacketHandler::S_DespawnProjectile(FSessionId sessionId, int32_t acceptTick, uint32_t id)
{
	return PH_SUCCESS;
}

int PacketHandler::S_ProjectileHit(FSessionId sessionId, int32_t acceptTick, uint16_t damage, uint32_t bulletId, uint32_t collisionId)
{
	return PH_SUCCESS;
}

int PacketHandler::S_MatchFound(FSessionId sessionId, bool success)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}

	player->RecvProcess(PacketType::S_MATCH_FOUND, true, _dummy->GetPacketReceiveTime());
	player->_gameStarted = true;

	return PH_SUCCESS;
}

int PacketHandler::S_GameStart(FSessionId sessionId, bool success, int32_t tick)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}

	player->RecvProcess(PacketType::S_GAME_START, true, _dummy->GetPacketReceiveTime());

	return PH_SUCCESS;
}

int PacketHandler::S_GameEnd(FSessionId sessionId, bool win, const FBufferView<ResultInfo>& resultInfo)
{
	Player* player = _dummy->FindConnectedPlayer(sessionId);
	if (player == nullptr)
	{
		return PH_FAIL1;
	}

	_proxy->C_ReturnToLobby(sessionId);

	return PH_SUCCESS;
}
