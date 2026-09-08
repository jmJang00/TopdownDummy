#pragma once

#include <JNet/CSession.h>
#include "Packet.h"

class Stub
{
public:
	virtual int S_ResLoginGameServer(FSessionId sessionId, bool loginOk, const AccountInfo& account)
	{
		return PH_SUCCESS;
	}

	virtual int S_ResLoginChatServer(FSessionId sessionId, bool loginOk)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfAccountInfo(FSessionId sessionId, const FBufferView<AccountInfo>& account)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfCreateMyCharacter(FSessionId sessionId, int32_t serverTick, uint32_t entityId, uint16_t health, uint16_t weaponId)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfCreateOtherCharacter(FSessionId sessionId, int32_t serverTick, uint32_t entityId, uint16_t health, uint16_t weaponId, int32_t accountId, bool isBot)
	{
		return PH_SUCCESS;
	}

	virtual int S_DeleteCharacter(FSessionId sessionId, int32_t serverTick, uint32_t id)
	{
		return PH_SUCCESS;
	}

	virtual int S_MatchFound(FSessionId sessionId, bool success)
	{
		return PH_SUCCESS;
	}

	virtual int S_GameStart(FSessionId sessionId, bool success, int32_t tick)
	{
		return PH_SUCCESS;
	}

	virtual int S_GameEnd(FSessionId sessionId, bool win, const FBufferView<ResultInfo>& resultInfo)
	{
		return PH_SUCCESS;
	}

	virtual int S_ReturnToLobby(FSessionId sessionId)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfSpectateUser(FSessionId sessionId, int32_t tick, uint32_t entityId)
	{
		return PH_SUCCESS;
	}

	virtual int S_ProjectileShootStart(FSessionId sessionId, int32_t acceptTick, uint32_t id)
	{
		return PH_SUCCESS;
	}

	virtual int S_SpawnProjectile(FSessionId sessionId, int32_t acceptTick, uint32_t id, const Vector2& spawnPos, const Vector2& targetPos)
	{
		return PH_SUCCESS;
	}

	virtual int S_DespawnProjectile(FSessionId sessionId, int32_t acceptTick, uint32_t id)
	{
		return PH_SUCCESS;
	}

	virtual int S_ProjectileHit(FSessionId sessionId, int32_t acceptTick, uint16_t damage, uint32_t bulletId, uint32_t collisionId)
	{
		return PH_SUCCESS;
	}

	virtual int S_HitscanShootStart(FSessionId sessionId, int32_t acceptTick, uint32_t entityId, float startX, float startY, float endX, float endY)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfHitscanShootStart(FSessionId sessionId, int32_t accpetTick, uint32_t accountId)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfHitscanShootState(FSessionId sessionId, int32_t serverTick, uint32_t accountId, uint64_t bulletMaskLow, uint64_t bulletMaskHigh, int32_t baseTick)
	{
		return PH_SUCCESS;
	}

	virtual int S_HitscanHit(FSessionId sessionId, int32_t serverTick, uint16_t damage, uint32_t shooterId, uint32_t targetId)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfUpdateBullet(FSessionId sessionId, int32_t serverTick, uint16_t bulletCount)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfSpawnItemPicker(FSessionId sessionId, int32_t serverTick, uint32_t entityId, uint32_t itemType, float targetX, float targetY)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfDespawnItemPicker(FSessionId sessionId, int32_t serverTick, uint32_t entityId, uint32_t itemType)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfCreateChest(FSessionId sessionId, int32_t serverTick, uint32_t entityId, const Vector2& target)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfDestroyChest(FSessionId sessionId, int32_t serverTick, uint32_t entityId)
	{
		return PH_SUCCESS;
	}

	virtual int S_OpenChest(FSessionId sessionId, int32_t serverTick, uint32_t chestId, uint16_t resultCode)
	{
		return PH_SUCCESS;
	}

	virtual int S_CloseChest(FSessionId sessionId, int32_t clientTick, uint32_t chestId, uint16_t resultCode)
	{
		return PH_SUCCESS;
	}

	virtual int S_NtfChestInfo(FSessionId sessionId, int32_t serverTick, uint32_t chestId, const FBufferView<ItemElem>& itemLists)
	{
		return PH_SUCCESS;
	}

	virtual int S_ResInventoryInfo(FSessionId sessionId, int32_t serverTick, const FBufferView<ItemElem>& itemLists)
	{
		return PH_SUCCESS;
	}

	virtual int S_ResInventoryToChest(FSessionId sessionId, int32_t serverTick, uint16_t resultCode)
	{
		return PH_SUCCESS;
	}

	virtual int S_ResChestToInventory(FSessionId sessionId, int32_t serverTick, uint16_t resultCode)
	{
		return PH_SUCCESS;
	}

	virtual int S_MoveStart(FSessionId sessionId, int32_t acceptTick, uint32_t id, const Vector2& target)
	{
		return PH_SUCCESS;
	}

	virtual int S_MoveState(FSessionId sessionId, int32_t currentTick, uint32_t id, const Vector2& pos, const Vector2& target)
	{
		return PH_SUCCESS;
	}

	virtual int S_TickSync(FSessionId sessionId, int32_t serverTick)
	{
		return PH_SUCCESS;
	}

	virtual int S_RotateStart(FSessionId sessionId, int32_t acceptTick, uint32_t id, float targetAngle)
	{
		return PH_SUCCESS;
	}

	virtual int S_RotateState(FSessionId sessionId, int32_t acceptTick, uint32_t id, float currentAngle, float targetAngle)
	{
		return PH_SUCCESS;
	}

};
