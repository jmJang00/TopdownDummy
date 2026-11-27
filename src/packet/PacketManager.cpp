#include "pch.h"
#include <JNet/CPacket.h>
#include <JNet/CPacketView.h>
#include <JNet/CSession.h>
//#include <JCore/SLog.h>
#include "PacketManager.h"
#include "Packet.h"

//#undef DLOGHA()
//#define DLOGHA()

bool PacketManager::PP_S_ResLoginGameServer(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	bool loginOk;
	*packet >> loginOk;
	AccountInfo account;
	*packet >> account;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_ResLoginGameServer(sessionId, loginOk, account);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_ResLoginChatServer(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	bool loginOk;
	*packet >> loginOk;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_ResLoginChatServer(sessionId, loginOk);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfAccountInfo(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	FBufferView<AccountInfo> account;
	*packet >> account;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfAccountInfo(sessionId, account);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfCreateMyCharacter(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t serverTick;
	*packet >> serverTick;
	uint32_t entityId;
	*packet >> entityId;
	uint16_t health;
	*packet >> health;
	uint16_t weaponId;
	*packet >> weaponId;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfCreateMyCharacter(sessionId, serverTick, entityId, health, weaponId);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfCreateOtherCharacter(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t serverTick;
	*packet >> serverTick;
	uint32_t entityId;
	*packet >> entityId;
	uint16_t health;
	*packet >> health;
	uint16_t weaponId;
	*packet >> weaponId;
	int32_t accountId;
	*packet >> accountId;
	bool isBot;
	*packet >> isBot;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfCreateOtherCharacter(sessionId, serverTick, entityId, health, weaponId, accountId, isBot);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_DeleteCharacter(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t serverTick;
	*packet >> serverTick;
	uint32_t id;
	*packet >> id;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_DeleteCharacter(sessionId, serverTick, id);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_MatchFound(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	bool success;
	*packet >> success;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_MatchFound(sessionId, success);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_GameStart(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	bool success;
	*packet >> success;
	int32_t tick;
	*packet >> tick;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_GameStart(sessionId, success, tick);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_GameEnd(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	bool win;
	*packet >> win;
	FBufferView<ResultInfo> resultInfo;
	*packet >> resultInfo;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_GameEnd(sessionId, win, resultInfo);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_ReturnToLobby(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());


	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_ReturnToLobby(sessionId);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfSpectateUser(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t tick;
	*packet >> tick;
	uint32_t entityId;
	*packet >> entityId;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfSpectateUser(sessionId, tick, entityId);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_ProjectileShootStart(CPacketView* packet, FSessionId sessionId)
{

	int32_t acceptTick;
	*packet >> acceptTick;
	uint32_t id;
	*packet >> id;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_ProjectileShootStart(sessionId, acceptTick, id);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_SpawnProjectile(CPacketView* packet, FSessionId sessionId)
{

	int32_t acceptTick;
	*packet >> acceptTick;
	uint32_t id;
	*packet >> id;
	Vector2 spawnPos;
	*packet >> spawnPos;
	Vector2 targetPos;
	*packet >> targetPos;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_SpawnProjectile(sessionId, acceptTick, id, spawnPos, targetPos);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_DespawnProjectile(CPacketView* packet, FSessionId sessionId)
{

	int32_t acceptTick;
	*packet >> acceptTick;
	uint32_t id;
	*packet >> id;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_DespawnProjectile(sessionId, acceptTick, id);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_ProjectileHit(CPacketView* packet, FSessionId sessionId)
{

	int32_t acceptTick;
	*packet >> acceptTick;
	uint16_t damage;
	*packet >> damage;
	uint32_t bulletId;
	*packet >> bulletId;
	uint32_t collisionId;
	*packet >> collisionId;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_ProjectileHit(sessionId, acceptTick, damage, bulletId, collisionId);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_HitscanShootStart(CPacketView* packet, FSessionId sessionId)
{

	int32_t acceptTick;
	*packet >> acceptTick;
	uint32_t entityId;
	*packet >> entityId;
	Vector2 start;
	*packet >> start;
	Vector2 end;
	*packet >> end;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_HitscanShootStart(sessionId, acceptTick, entityId, start, end);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfHitscanShootStart(CPacketView* packet, FSessionId sessionId)
{

	int32_t accpetTick;
	*packet >> accpetTick;
	uint32_t accountId;
	*packet >> accountId;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfHitscanShootStart(sessionId, accpetTick, accountId);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfHitscanShootState(CPacketView* packet, FSessionId sessionId)
{

	int32_t serverTick;
	*packet >> serverTick;
	uint32_t accountId;
	*packet >> accountId;
	uint64_t bulletMaskLow;
	*packet >> bulletMaskLow;
	uint64_t bulletMaskHigh;
	*packet >> bulletMaskHigh;
	int32_t baseTick;
	*packet >> baseTick;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfHitscanShootState(sessionId, serverTick, accountId, bulletMaskLow, bulletMaskHigh, baseTick);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_HitscanHit(CPacketView* packet, FSessionId sessionId)
{

	int32_t serverTick;
	*packet >> serverTick;
	uint16_t damage;
	*packet >> damage;
	uint32_t shooterId;
	*packet >> shooterId;
	uint32_t targetId;
	*packet >> targetId;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_HitscanHit(sessionId, serverTick, damage, shooterId, targetId);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfUpdateBullet(CPacketView* packet, FSessionId sessionId)
{

	int32_t serverTick;
	*packet >> serverTick;
	uint16_t bulletCount;
	*packet >> bulletCount;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfUpdateBullet(sessionId, serverTick, bulletCount);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfSpawnItemPicker(CPacketView* packet, FSessionId sessionId)
{

	int32_t serverTick;
	*packet >> serverTick;
	uint32_t entityId;
	*packet >> entityId;
	uint32_t itemType;
	*packet >> itemType;
	float targetX;
	*packet >> targetX;
	float targetY;
	*packet >> targetY;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfSpawnItemPicker(sessionId, serverTick, entityId, itemType, targetX, targetY);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfDespawnItemPicker(CPacketView* packet, FSessionId sessionId)
{

	int32_t serverTick;
	*packet >> serverTick;
	uint32_t entityId;
	*packet >> entityId;
	uint32_t itemType;
	*packet >> itemType;
	bool isObtained;
	*packet >> isObtained;
	uint32_t obtainEntityId;
	*packet >> obtainEntityId;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfDespawnItemPicker(sessionId, serverTick, entityId, itemType, isObtained, obtainEntityId);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfCreateChest(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t serverTick;
	*packet >> serverTick;
	uint32_t entityId;
	*packet >> entityId;
	Vector2 target;
	*packet >> target;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfCreateChest(sessionId, serverTick, entityId, target);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfDestroyChest(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t serverTick;
	*packet >> serverTick;
	uint32_t entityId;
	*packet >> entityId;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfDestroyChest(sessionId, serverTick, entityId);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_OpenChest(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t serverTick;
	*packet >> serverTick;
	uint32_t chestId;
	*packet >> chestId;
	uint16_t resultCode;
	*packet >> resultCode;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_OpenChest(sessionId, serverTick, chestId, resultCode);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_CloseChest(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t clientTick;
	*packet >> clientTick;
	uint32_t chestId;
	*packet >> chestId;
	uint16_t resultCode;
	*packet >> resultCode;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_CloseChest(sessionId, clientTick, chestId, resultCode);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_NtfChestInfo(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t serverTick;
	*packet >> serverTick;
	uint32_t chestId;
	*packet >> chestId;
	FBufferView<ItemElem> itemLists;
	*packet >> itemLists;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_NtfChestInfo(sessionId, serverTick, chestId, itemLists);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_ResInventoryInfo(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t serverTick;
	*packet >> serverTick;
	FBufferView<ItemElem> itemLists;
	*packet >> itemLists;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_ResInventoryInfo(sessionId, serverTick, itemLists);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_ResInventoryToChest(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t serverTick;
	*packet >> serverTick;
	uint16_t resultCode;
	*packet >> resultCode;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_ResInventoryToChest(sessionId, serverTick, resultCode);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_ResChestToInventory(CPacketView* packet, FSessionId sessionId)
{
	DLOGHA(L"Packet", L"Recv", (unsigned char*)packet->GetBufferPtr(), packet->GetBufferSize());

	int32_t serverTick;
	*packet >> serverTick;
	uint16_t resultCode;
	*packet >> resultCode;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_ResChestToInventory(sessionId, serverTick, resultCode);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_MoveStart(CPacketView* packet, FSessionId sessionId)
{

	int32_t acceptTick;
	*packet >> acceptTick;
	uint32_t id;
	*packet >> id;
	Vector2 target;
	*packet >> target;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_MoveStart(sessionId, acceptTick, id, target);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_MoveState(CPacketView* packet, FSessionId sessionId)
{

	int32_t currentTick;
	*packet >> currentTick;
	uint32_t id;
	*packet >> id;
	Vector2 pos;
	*packet >> pos;
	Vector2 target;
	*packet >> target;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_MoveState(sessionId, currentTick, id, pos, target);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_TickSync(CPacketView* packet, FSessionId sessionId)
{

	int32_t serverTick;
	*packet >> serverTick;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_TickSync(sessionId, serverTick);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_RotateStart(CPacketView* packet, FSessionId sessionId)
{

	int32_t acceptTick;
	*packet >> acceptTick;
	uint32_t id;
	*packet >> id;
	float targetAngle;
	*packet >> targetAngle;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_RotateStart(sessionId, acceptTick, id, targetAngle);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}
bool PacketManager::PP_S_RotateState(CPacketView* packet, FSessionId sessionId)
{

	int32_t acceptTick;
	*packet >> acceptTick;
	uint32_t id;
	*packet >> id;
	float currentAngle;
	*packet >> currentAngle;
	float targetAngle;
	*packet >> targetAngle;

	if (packet->GetLastError() != CPacketView::Default)
	{
		DLOGA(L"Packet", L"Packet Deserialize Fail");
		return false;
	}

	_lastError = _stub->S_RotateState(sessionId, acceptTick, id, currentAngle, targetAngle);
	if (_lastError != PH_SUCCESS)
	{
		DLOGA(L"Packet", L"Packet Process Fail %d", _lastError);
		return false;
	}
	else
	{
		return true;
	}
}

bool PacketManager::PacketProc(PacketType type, CPacketView* packet, FSessionId sessionId)
{
	if (_stub == nullptr)
	{
		return false;
	}

	switch (type)
	{
	case PacketType::S_RES_LOGIN_GAME_SERVER:
	{
		return PP_S_ResLoginGameServer(packet, sessionId);
	}
	case PacketType::S_RES_LOGIN_CHAT_SERVER:
	{
		return PP_S_ResLoginChatServer(packet, sessionId);
	}
	case PacketType::S_NTF_ACCOUNT_INFO:
	{
		return PP_S_NtfAccountInfo(packet, sessionId);
	}
	case PacketType::S_NTF_CREATE_MY_CHARACTER:
	{
		return PP_S_NtfCreateMyCharacter(packet, sessionId);
	}
	case PacketType::S_NTF_CREATE_OTHER_CHARACTER:
	{
		return PP_S_NtfCreateOtherCharacter(packet, sessionId);
	}
	case PacketType::S_DELETE_CHARACTER:
	{
		return PP_S_DeleteCharacter(packet, sessionId);
	}
	case PacketType::S_MATCH_FOUND:
	{
		return PP_S_MatchFound(packet, sessionId);
	}
	case PacketType::S_GAME_START:
	{
		return PP_S_GameStart(packet, sessionId);
	}
	case PacketType::S_GAME_END:
	{
		return PP_S_GameEnd(packet, sessionId);
	}
	case PacketType::S_RETURN_TO_LOBBY:
	{
		return PP_S_ReturnToLobby(packet, sessionId);
	}
	case PacketType::S_NTF_SPECTATE_USER:
	{
		return PP_S_NtfSpectateUser(packet, sessionId);
	}
	case PacketType::S_PROJECTILE_SHOOT_START:
	{
		return PP_S_ProjectileShootStart(packet, sessionId);
	}
	case PacketType::S_SPAWN_PROJECTILE:
	{
		return PP_S_SpawnProjectile(packet, sessionId);
	}
	case PacketType::S_DESPAWN_PROJECTILE:
	{
		return PP_S_DespawnProjectile(packet, sessionId);
	}
	case PacketType::S_PROJECTILE_HIT:
	{
		return PP_S_ProjectileHit(packet, sessionId);
	}
	case PacketType::S_HITSCAN_SHOOT_START:
	{
		return PP_S_HitscanShootStart(packet, sessionId);
	}
	case PacketType::S_NTF_HITSCAN_SHOOT_START:
	{
		return PP_S_NtfHitscanShootStart(packet, sessionId);
	}
	case PacketType::S_NTF_HITSCAN_SHOOT_STATE:
	{
		return PP_S_NtfHitscanShootState(packet, sessionId);
	}
	case PacketType::S_HITSCAN_HIT:
	{
		return PP_S_HitscanHit(packet, sessionId);
	}
	case PacketType::S_NTF_UPDATE_BULLET:
	{
		return PP_S_NtfUpdateBullet(packet, sessionId);
	}
	case PacketType::S_NTF_SPAWN_ITEM_PICKER:
	{
		return PP_S_NtfSpawnItemPicker(packet, sessionId);
	}
	case PacketType::S_NTF_DESPAWN_ITEM_PICKER:
	{
		return PP_S_NtfDespawnItemPicker(packet, sessionId);
	}
	case PacketType::S_NTF_CREATE_CHEST:
	{
		return PP_S_NtfCreateChest(packet, sessionId);
	}
	case PacketType::S_NTF_DESTROY_CHEST:
	{
		return PP_S_NtfDestroyChest(packet, sessionId);
	}
	case PacketType::S_OPEN_CHEST:
	{
		return PP_S_OpenChest(packet, sessionId);
	}
	case PacketType::S_CLOSE_CHEST:
	{
		return PP_S_CloseChest(packet, sessionId);
	}
	case PacketType::S_NTF_CHEST_INFO:
	{
		return PP_S_NtfChestInfo(packet, sessionId);
	}
	case PacketType::S_RES_INVENTORY_INFO:
	{
		return PP_S_ResInventoryInfo(packet, sessionId);
	}
	case PacketType::S_RES_INVENTORY_TO_CHEST:
	{
		return PP_S_ResInventoryToChest(packet, sessionId);
	}
	case PacketType::S_RES_CHEST_TO_INVENTORY:
	{
		return PP_S_ResChestToInventory(packet, sessionId);
	}
	case PacketType::S_MOVE_START:
	{
		return PP_S_MoveStart(packet, sessionId);
	}
	case PacketType::S_MOVE_STATE:
	{
		return PP_S_MoveState(packet, sessionId);
	}
	case PacketType::S_TICK_SYNC:
	{
		return PP_S_TickSync(packet, sessionId);
	}
	case PacketType::S_ROTATE_START:
	{
		return PP_S_RotateStart(packet, sessionId);
	}
	case PacketType::S_ROTATE_STATE:
	{
		return PP_S_RotateState(packet, sessionId);
	}
	default:
		return false;
	}
}
