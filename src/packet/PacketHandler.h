#pragma once
#include "Stub.h"

class CLogicThread;
class Proxy;

class PacketHandler : public Stub
{
public:
	PacketHandler(CLogicThread* thread, Proxy* proxy);

	int S_ResLoginGameServer(FSessionId sessionId, bool loginOk, const AccountInfo& account) override;

	int S_NtfCreateMyCharacter(FSessionId sessionId, int32_t serverTick, 
		uint32_t entityId, uint16_t health, uint16_t weaponId) override;

	int S_NtfCreateOtherCharacter(FSessionId sessionId, int32_t serverTick, 
		uint32_t entityId, uint16_t health, uint16_t weaponId, int32_t accountId, bool isBot) override;

	int S_DeleteCharacter(FSessionId sessionId, int32_t serverTick, uint32_t id) override;

	int S_MoveStart(FSessionId sessionId, int32_t acceptTick, 
		uint32_t id, const Vector2& target) override;

	int S_MoveState(FSessionId sessionId, int32_t currentTick, 
		uint32_t id, const Vector2& pos, const Vector2& target) override;

	int S_ReturnToLobby(FSessionId sessionId) override;

	int S_TickSync(FSessionId sessionId, int32_t serverTick) override;

	int S_RotateStart(FSessionId sessionId, int32_t acceptTick, uint32_t id, float targetAngle) override;

	int S_RotateState(FSessionId sessionId, int32_t acceptTick, uint32_t id, float currentAngle, float targetAngle) override;

	int S_ProjectileShootStart(FSessionId sessionId, int32_t acceptTick, uint32_t id) override;

	int S_SpawnProjectile(FSessionId sessionId, int32_t acceptTick, uint32_t id, const Vector2& spawnPos, const Vector2& targetPos) override;

	int S_DespawnProjectile(FSessionId sessionId, int32_t acceptTick, uint32_t id) override;

	int S_ProjectileHit(FSessionId sessionId, int32_t acceptTick, uint16_t damage, uint32_t bulletId, uint32_t collisionId) override;

	int S_MatchFound(FSessionId sessionId, bool success) override;

	int S_GameStart(FSessionId sessionId, bool success, int32_t tick) override;

	int S_GameEnd(FSessionId sessionId, bool win, const FBufferView<ResultInfo>& resultInfo) override;

private:
	Proxy* _proxy;
	CLogicThread* _dummy;
};