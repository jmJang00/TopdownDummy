#pragma once

#include <JNet/CSession.h>
#include <JNet/INetworkEntity.h>
#include "Packet.h"

class CNetServer;
class CNetClient;
class DummyClient;

struct MessageArgs
{
	MessageArgs(PacketType protocol_)
        : protocol(protocol_)
    {
    }

	PacketType protocol;
};

struct C_ReqLoginGameServerArgs : public MessageArgs
{
	C_ReqLoginGameServerArgs(const std::wstring_view& sessionKey_, PacketType protocol_ = PacketType::C_REQ_LOGIN_GAME_SERVER)
		: MessageArgs(protocol_)
		, sessionKey(sessionKey_)
	{
	}

	std::wstring_view sessionKey;
};

struct C_ReqLoginChatServerArgs : public MessageArgs
{
	C_ReqLoginChatServerArgs(const std::wstring_view& sessionKey_, PacketType protocol_ = PacketType::C_REQ_LOGIN_CHAT_SERVER)
		: MessageArgs(protocol_)
		, sessionKey(sessionKey_)
	{
	}

	std::wstring_view sessionKey;
};

struct C_MatchStartArgs : public MessageArgs
{
	C_MatchStartArgs(PacketType protocol_ = PacketType::C_MATCH_START)
		: MessageArgs(protocol_)
	{
	}

};

struct C_MatchCancelArgs : public MessageArgs
{
	C_MatchCancelArgs(PacketType protocol_ = PacketType::C_MATCH_CANCEL)
		: MessageArgs(protocol_)
	{
	}

};

struct C_SceneReadyArgs : public MessageArgs
{
	C_SceneReadyArgs(PacketType protocol_ = PacketType::C_SCENE_READY)
		: MessageArgs(protocol_)
	{
	}

};

struct C_WeaponSelectArgs : public MessageArgs
{
	C_WeaponSelectArgs(uint16_t weaponId_, PacketType protocol_ = PacketType::C_WEAPON_SELECT)
		: MessageArgs(protocol_)
		, weaponId(weaponId_)
	{
	}

	uint16_t weaponId;
};

struct C_ReturnToLobbyArgs : public MessageArgs
{
	C_ReturnToLobbyArgs(PacketType protocol_ = PacketType::C_RETURN_TO_LOBBY)
		: MessageArgs(protocol_)
	{
	}

};

struct C_AccountInfoDebugArgs : public MessageArgs
{
	C_AccountInfoDebugArgs(int64_t accountId_, PacketType protocol_ = PacketType::C_ACCOUNT_INFO_DEBUG)
		: MessageArgs(protocol_)
		, accountId(accountId_)
	{
	}

	int64_t accountId;
};

struct C_QuitGameArgs : public MessageArgs
{
	C_QuitGameArgs(PacketType protocol_ = PacketType::C_QUIT_GAME)
		: MessageArgs(protocol_)
	{
	}

};

struct C_ReqSpectateGameArgs : public MessageArgs
{
	C_ReqSpectateGameArgs(PacketType protocol_ = PacketType::C_REQ_SPECTATE_GAME)
		: MessageArgs(protocol_)
	{
	}

};

struct C_ReqSpectateNextArgs : public MessageArgs
{
	C_ReqSpectateNextArgs(PacketType protocol_ = PacketType::C_REQ_SPECTATE_NEXT)
		: MessageArgs(protocol_)
	{
	}

};

struct C_ReqSpectatePrevArgs : public MessageArgs
{
	C_ReqSpectatePrevArgs(PacketType protocol_ = PacketType::C_REQ_SPECTATE_PREV)
		: MessageArgs(protocol_)
	{
	}

};

struct C_ProjectileShootStartArgs : public MessageArgs
{
	C_ProjectileShootStartArgs(int32_t clientTick_, PacketType protocol_ = PacketType::C_PROJECTILE_SHOOT_START)
		: MessageArgs(protocol_)
		, clientTick(clientTick_)
	{
	}

	int32_t clientTick;
};

struct C_HitscanShootStartArgs : public MessageArgs
{
	C_HitscanShootStartArgs(int32_t clientTick_, float startX_, float startY_, float endX_, float endY_, PacketType protocol_ = PacketType::C_HITSCAN_SHOOT_START)
		: MessageArgs(protocol_)
		, clientTick(clientTick_)
		, startX(startX_)
		, startY(startY_)
		, endX(endX_)
		, endY(endY_)
	{
	}

	int32_t clientTick;
	float startX;
	float startY;
	float endX;
	float endY;
};

struct C_HitscanHitArgs : public MessageArgs
{
	C_HitscanHitArgs(int32_t currentTick_, uint32_t shooterId_, uint32_t targetId_, PacketType protocol_ = PacketType::C_HITSCAN_HIT)
		: MessageArgs(protocol_)
		, currentTick(currentTick_)
		, shooterId(shooterId_)
		, targetId(targetId_)
	{
	}

	int32_t currentTick;
	uint32_t shooterId;
	uint32_t targetId;
};

struct C_ReqReloadBulletArgs : public MessageArgs
{
	C_ReqReloadBulletArgs(int32_t clientTick_, PacketType protocol_ = PacketType::C_REQ_RELOAD_BULLET)
		: MessageArgs(protocol_)
		, clientTick(clientTick_)
	{
	}

	int32_t clientTick;
};

struct C_ReqPickupItemPickerArgs : public MessageArgs
{
	C_ReqPickupItemPickerArgs(int32_t clientTick_, uint32_t entityId_, PacketType protocol_ = PacketType::C_REQ_PICKUP_ITEM_PICKER)
		: MessageArgs(protocol_)
		, clientTick(clientTick_)
		, entityId(entityId_)
	{
	}

	int32_t clientTick;
	uint32_t entityId;
};

struct C_OpenChestArgs : public MessageArgs
{
	C_OpenChestArgs(int32_t clientTick_, uint32_t chestId_, PacketType protocol_ = PacketType::C_OPEN_CHEST)
		: MessageArgs(protocol_)
		, clientTick(clientTick_)
		, chestId(chestId_)
	{
	}

	int32_t clientTick;
	uint32_t chestId;
};

struct C_CloseChestArgs : public MessageArgs
{
	C_CloseChestArgs(int32_t clientTick_, uint32_t chestId_, PacketType protocol_ = PacketType::C_CLOSE_CHEST)
		: MessageArgs(protocol_)
		, clientTick(clientTick_)
		, chestId(chestId_)
	{
	}

	int32_t clientTick;
	uint32_t chestId;
};

struct C_ReqInventoryInfoArgs : public MessageArgs
{
	C_ReqInventoryInfoArgs(int32_t clientTick_, PacketType protocol_ = PacketType::C_REQ_INVENTORY_INFO)
		: MessageArgs(protocol_)
		, clientTick(clientTick_)
	{
	}

	int32_t clientTick;
};

struct C_ReqInventoryToChestArgs : public MessageArgs
{
	C_ReqInventoryToChestArgs(int32_t clientTick_, int32_t lastUpdateTick_, int32_t lastInventoryUpdateTick_, uint32_t entityId_, uint32_t inventoryCursor_, uint32_t chestId_, PacketType protocol_ = PacketType::C_REQ_INVENTORY_TO_CHEST)
		: MessageArgs(protocol_)
		, clientTick(clientTick_)
		, lastUpdateTick(lastUpdateTick_)
		, lastInventoryUpdateTick(lastInventoryUpdateTick_)
		, entityId(entityId_)
		, inventoryCursor(inventoryCursor_)
		, chestId(chestId_)
	{
	}

	int32_t clientTick;
	int32_t lastUpdateTick;
	int32_t lastInventoryUpdateTick;
	uint32_t entityId;
	uint32_t inventoryCursor;
	uint32_t chestId;
};

struct C_ReqChestToInventoryArgs : public MessageArgs
{
	C_ReqChestToInventoryArgs(int32_t clientTick_, int32_t lastUpdateTick_, int32_t lastInventoryUpdateTick_, uint32_t entityId_, uint32_t chestId_, uint32_t chestCursor_, PacketType protocol_ = PacketType::C_REQ_CHEST_TO_INVENTORY)
		: MessageArgs(protocol_)
		, clientTick(clientTick_)
		, lastUpdateTick(lastUpdateTick_)
		, lastInventoryUpdateTick(lastInventoryUpdateTick_)
		, entityId(entityId_)
		, chestId(chestId_)
		, chestCursor(chestCursor_)
	{
	}

	int32_t clientTick;
	int32_t lastUpdateTick;
	int32_t lastInventoryUpdateTick;
	uint32_t entityId;
	uint32_t chestId;
	uint32_t chestCursor;
};

struct C_MoveStartArgs : public MessageArgs
{
	C_MoveStartArgs(int32_t clientTick_, const Vector2& target_, PacketType protocol_ = PacketType::C_MOVE_START)
		: MessageArgs(protocol_)
		, clientTick(clientTick_)
		, target(target_)
	{
	}

	int32_t clientTick;
	Vector2 target;
};

struct C_RotateStartArgs : public MessageArgs
{
	C_RotateStartArgs(int32_t clientTick_, float targetAngle_, PacketType protocol_ = PacketType::C_ROTATE_START)
		: MessageArgs(protocol_)
		, clientTick(clientTick_)
		, targetAngle(targetAngle_)
	{
	}

	int32_t clientTick;
	float targetAngle;
};


class Proxy
{
public:
	Proxy(DummyClient* server)
	{
		_server = server;
	}

public:
	bool C_ReqLoginGameServer(FSessionId sessionId, const std::wstring_view& sessionKey);
	bool C_ReqLoginGameServer(FSessionId* sessionIds, size_t cnt, const std::wstring_view& sessionKey);
	bool C_ReqLoginGameServer(FSessionId sessionId, const C_ReqLoginGameServerArgs* args);
	bool C_ReqLoginGameServer(FSessionId* sessionIds, size_t cnt, const C_ReqLoginGameServerArgs* args);

	bool C_ReqLoginChatServer(FSessionId sessionId, const std::wstring_view& sessionKey);
	bool C_ReqLoginChatServer(FSessionId* sessionIds, size_t cnt, const std::wstring_view& sessionKey);
	bool C_ReqLoginChatServer(FSessionId sessionId, const C_ReqLoginChatServerArgs* args);
	bool C_ReqLoginChatServer(FSessionId* sessionIds, size_t cnt, const C_ReqLoginChatServerArgs* args);

	bool C_MatchStart(FSessionId sessionId);
	bool C_MatchStart(FSessionId* sessionIds, size_t cnt);
	bool C_MatchStart(FSessionId sessionId, const C_MatchStartArgs* args);
	bool C_MatchStart(FSessionId* sessionIds, size_t cnt, const C_MatchStartArgs* args);

	bool C_MatchCancel(FSessionId sessionId);
	bool C_MatchCancel(FSessionId* sessionIds, size_t cnt);
	bool C_MatchCancel(FSessionId sessionId, const C_MatchCancelArgs* args);
	bool C_MatchCancel(FSessionId* sessionIds, size_t cnt, const C_MatchCancelArgs* args);

	bool C_SceneReady(FSessionId sessionId);
	bool C_SceneReady(FSessionId* sessionIds, size_t cnt);
	bool C_SceneReady(FSessionId sessionId, const C_SceneReadyArgs* args);
	bool C_SceneReady(FSessionId* sessionIds, size_t cnt, const C_SceneReadyArgs* args);

	bool C_WeaponSelect(FSessionId sessionId, uint16_t weaponId);
	bool C_WeaponSelect(FSessionId* sessionIds, size_t cnt, uint16_t weaponId);
	bool C_WeaponSelect(FSessionId sessionId, const C_WeaponSelectArgs* args);
	bool C_WeaponSelect(FSessionId* sessionIds, size_t cnt, const C_WeaponSelectArgs* args);

	bool C_ReturnToLobby(FSessionId sessionId);
	bool C_ReturnToLobby(FSessionId* sessionIds, size_t cnt);
	bool C_ReturnToLobby(FSessionId sessionId, const C_ReturnToLobbyArgs* args);
	bool C_ReturnToLobby(FSessionId* sessionIds, size_t cnt, const C_ReturnToLobbyArgs* args);

	bool C_AccountInfoDebug(FSessionId sessionId, int64_t accountId);
	bool C_AccountInfoDebug(FSessionId* sessionIds, size_t cnt, int64_t accountId);
	bool C_AccountInfoDebug(FSessionId sessionId, const C_AccountInfoDebugArgs* args);
	bool C_AccountInfoDebug(FSessionId* sessionIds, size_t cnt, const C_AccountInfoDebugArgs* args);

	bool C_QuitGame(FSessionId sessionId);
	bool C_QuitGame(FSessionId* sessionIds, size_t cnt);
	bool C_QuitGame(FSessionId sessionId, const C_QuitGameArgs* args);
	bool C_QuitGame(FSessionId* sessionIds, size_t cnt, const C_QuitGameArgs* args);

	bool C_ReqSpectateGame(FSessionId sessionId);
	bool C_ReqSpectateGame(FSessionId* sessionIds, size_t cnt);
	bool C_ReqSpectateGame(FSessionId sessionId, const C_ReqSpectateGameArgs* args);
	bool C_ReqSpectateGame(FSessionId* sessionIds, size_t cnt, const C_ReqSpectateGameArgs* args);

	bool C_ReqSpectateNext(FSessionId sessionId);
	bool C_ReqSpectateNext(FSessionId* sessionIds, size_t cnt);
	bool C_ReqSpectateNext(FSessionId sessionId, const C_ReqSpectateNextArgs* args);
	bool C_ReqSpectateNext(FSessionId* sessionIds, size_t cnt, const C_ReqSpectateNextArgs* args);

	bool C_ReqSpectatePrev(FSessionId sessionId);
	bool C_ReqSpectatePrev(FSessionId* sessionIds, size_t cnt);
	bool C_ReqSpectatePrev(FSessionId sessionId, const C_ReqSpectatePrevArgs* args);
	bool C_ReqSpectatePrev(FSessionId* sessionIds, size_t cnt, const C_ReqSpectatePrevArgs* args);

	bool C_ProjectileShootStart(FSessionId sessionId, int32_t clientTick);
	bool C_ProjectileShootStart(FSessionId* sessionIds, size_t cnt, int32_t clientTick);
	bool C_ProjectileShootStart(FSessionId sessionId, const C_ProjectileShootStartArgs* args);
	bool C_ProjectileShootStart(FSessionId* sessionIds, size_t cnt, const C_ProjectileShootStartArgs* args);

	bool C_HitscanShootStart(FSessionId sessionId, int32_t clientTick, float startX, float startY, float endX, float endY);
	bool C_HitscanShootStart(FSessionId* sessionIds, size_t cnt, int32_t clientTick, float startX, float startY, float endX, float endY);
	bool C_HitscanShootStart(FSessionId sessionId, const C_HitscanShootStartArgs* args);
	bool C_HitscanShootStart(FSessionId* sessionIds, size_t cnt, const C_HitscanShootStartArgs* args);

	bool C_HitscanHit(FSessionId sessionId, int32_t currentTick, uint32_t shooterId, uint32_t targetId);
	bool C_HitscanHit(FSessionId* sessionIds, size_t cnt, int32_t currentTick, uint32_t shooterId, uint32_t targetId);
	bool C_HitscanHit(FSessionId sessionId, const C_HitscanHitArgs* args);
	bool C_HitscanHit(FSessionId* sessionIds, size_t cnt, const C_HitscanHitArgs* args);

	bool C_ReqReloadBullet(FSessionId sessionId, int32_t clientTick);
	bool C_ReqReloadBullet(FSessionId* sessionIds, size_t cnt, int32_t clientTick);
	bool C_ReqReloadBullet(FSessionId sessionId, const C_ReqReloadBulletArgs* args);
	bool C_ReqReloadBullet(FSessionId* sessionIds, size_t cnt, const C_ReqReloadBulletArgs* args);

	bool C_ReqPickupItemPicker(FSessionId sessionId, int32_t clientTick, uint32_t entityId);
	bool C_ReqPickupItemPicker(FSessionId* sessionIds, size_t cnt, int32_t clientTick, uint32_t entityId);
	bool C_ReqPickupItemPicker(FSessionId sessionId, const C_ReqPickupItemPickerArgs* args);
	bool C_ReqPickupItemPicker(FSessionId* sessionIds, size_t cnt, const C_ReqPickupItemPickerArgs* args);

	bool C_OpenChest(FSessionId sessionId, int32_t clientTick, uint32_t chestId);
	bool C_OpenChest(FSessionId* sessionIds, size_t cnt, int32_t clientTick, uint32_t chestId);
	bool C_OpenChest(FSessionId sessionId, const C_OpenChestArgs* args);
	bool C_OpenChest(FSessionId* sessionIds, size_t cnt, const C_OpenChestArgs* args);

	bool C_CloseChest(FSessionId sessionId, int32_t clientTick, uint32_t chestId);
	bool C_CloseChest(FSessionId* sessionIds, size_t cnt, int32_t clientTick, uint32_t chestId);
	bool C_CloseChest(FSessionId sessionId, const C_CloseChestArgs* args);
	bool C_CloseChest(FSessionId* sessionIds, size_t cnt, const C_CloseChestArgs* args);

	bool C_ReqInventoryInfo(FSessionId sessionId, int32_t clientTick);
	bool C_ReqInventoryInfo(FSessionId* sessionIds, size_t cnt, int32_t clientTick);
	bool C_ReqInventoryInfo(FSessionId sessionId, const C_ReqInventoryInfoArgs* args);
	bool C_ReqInventoryInfo(FSessionId* sessionIds, size_t cnt, const C_ReqInventoryInfoArgs* args);

	bool C_ReqInventoryToChest(FSessionId sessionId, int32_t clientTick, int32_t lastUpdateTick, int32_t lastInventoryUpdateTick, uint32_t entityId, uint32_t inventoryCursor, uint32_t chestId);
	bool C_ReqInventoryToChest(FSessionId* sessionIds, size_t cnt, int32_t clientTick, int32_t lastUpdateTick, int32_t lastInventoryUpdateTick, uint32_t entityId, uint32_t inventoryCursor, uint32_t chestId);
	bool C_ReqInventoryToChest(FSessionId sessionId, const C_ReqInventoryToChestArgs* args);
	bool C_ReqInventoryToChest(FSessionId* sessionIds, size_t cnt, const C_ReqInventoryToChestArgs* args);

	bool C_ReqChestToInventory(FSessionId sessionId, int32_t clientTick, int32_t lastUpdateTick, int32_t lastInventoryUpdateTick, uint32_t entityId, uint32_t chestId, uint32_t chestCursor);
	bool C_ReqChestToInventory(FSessionId* sessionIds, size_t cnt, int32_t clientTick, int32_t lastUpdateTick, int32_t lastInventoryUpdateTick, uint32_t entityId, uint32_t chestId, uint32_t chestCursor);
	bool C_ReqChestToInventory(FSessionId sessionId, const C_ReqChestToInventoryArgs* args);
	bool C_ReqChestToInventory(FSessionId* sessionIds, size_t cnt, const C_ReqChestToInventoryArgs* args);

	bool C_MoveStart(FSessionId sessionId, int32_t clientTick, const Vector2& target);
	bool C_MoveStart(FSessionId* sessionIds, size_t cnt, int32_t clientTick, const Vector2& target);
	bool C_MoveStart(FSessionId sessionId, const C_MoveStartArgs* args);
	bool C_MoveStart(FSessionId* sessionIds, size_t cnt, const C_MoveStartArgs* args);

	bool C_RotateStart(FSessionId sessionId, int32_t clientTick, float targetAngle);
	bool C_RotateStart(FSessionId* sessionIds, size_t cnt, int32_t clientTick, float targetAngle);
	bool C_RotateStart(FSessionId sessionId, const C_RotateStartArgs* args);
	bool C_RotateStart(FSessionId* sessionIds, size_t cnt, const C_RotateStartArgs* args);


	bool Send(FSessionId* sessionIds, size_t cnt, const MessageArgs* args);
	bool Send(FSessionId sessionId, const MessageArgs* args);

private:
	DummyClient* _server;

};
