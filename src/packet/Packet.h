#pragma once
#include <stdint.h>
#include <JNet/FBufferView.h>
#include <JCore/Warnings.h>

class CPacket;
class CPacketView;

enum PacketHandleCode
{
	PH_SUCCESS,
	PH_FAIL1,
	PH_FAIL2,
	PH_FAIL3,
	PH_FAIL4,
	PH_FAIL5,
	PH_FAIL6,
	PH_FAIL7,
	PH_FAIL8,
	PH_FAIL9,
	PH_NOT_DEFINED,
};

enum class PacketType: uint16_t 
{
    C_REQ_LOGIN_GAME_SERVER=100,
    S_RES_LOGIN_GAME_SERVER=101,
    C_REQ_LOGIN_CHAT_SERVER=102,
    S_RES_LOGIN_CHAT_SERVER=103,
    S_NTF_ACCOUNT_INFO=104,
    C_MATCH_START=400,
    C_MATCH_CANCEL=401,
    S_NTF_CREATE_MY_CHARACTER=500,
    S_NTF_CREATE_OTHER_CHARACTER=501,
    S_DELETE_CHARACTER=502,
    S_MATCH_FOUND=600,
    S_GAME_START=601,
    S_GAME_END=602,
    C_SCENE_READY=603,
    C_WEAPON_SELECT=604,
    C_RETURN_TO_LOBBY=605,
    S_RETURN_TO_LOBBY=606,
    C_ACCOUNT_INFO_DEBUG=607,
    C_QUIT_GAME=608,
    C_REQ_SPECTATE_GAME=609,
    S_NTF_SPECTATE_USER=610,
    C_REQ_SPECTATE_NEXT=611,
    C_REQ_SPECTATE_PREV=612,
    C_PROJECTILE_SHOOT_START=700,
    S_PROJECTILE_SHOOT_START=701,
    S_SPAWN_PROJECTILE=702,
    S_DESPAWN_PROJECTILE=703,
    S_PROJECTILE_HIT=704,
    C_HITSCAN_SHOOT_START=720,
    S_HITSCAN_SHOOT_START=721,
    S_NTF_HITSCAN_SHOOT_START=722,
    S_NTF_HITSCAN_SHOOT_STATE=723,
    C_HITSCAN_HIT=724,
    S_HITSCAN_HIT=725,
    C_REQ_RELOAD_BULLET=726,
    S_NTF_UPDATE_BULLET=727,
    S_NTF_SPAWN_ITEM_PICKER=900,
    S_NTF_DESPAWN_ITEM_PICKER=901,
    C_REQ_PICKUP_ITEM_PICKER=902,
    S_NTF_CREATE_CHEST=1000,
    S_NTF_DESTROY_CHEST=1001,
    C_OPEN_CHEST=1002,
    C_CLOSE_CHEST=1003,
    S_OPEN_CHEST=1004,
    S_CLOSE_CHEST=1005,
    S_NTF_CHEST_INFO=1006,
    C_REQ_INVENTORY_TO_CHEST=1007,
    S_RES_INVENTORY_TO_CHEST=1008,
    C_REQ_CHEST_TO_INVENTORY=1009,
    S_RES_CHEST_TO_INVENTORY=1010,
    C_REQ_INVENTORY_INFO=1011,
    S_RES_INVENTORY_INFO=1012,
    C_REQ_USE_ITEM=1013,
    S_RES_USE_ITEM=1014,
    C_REQ_DROP_ITEM=1015,
    S_RES_DROP_ITEM=1016,
    C_MOVE_START=1100,
    S_MOVE_START=1101,
    S_MOVE_STATE=1102,
    S_TICK_SYNC=1103,
    C_ROTATE_START=1104,
    S_ROTATE_START=1105,
    S_ROTATE_STATE=1106,
}; 
 
inline constexpr int PACKET_TYPE_MAX = 63;


DISABLE_WARNINGS_BEGIN(WARNING_26495)

struct Vector2;
struct ItemElem;
struct AccountInfo;
struct ResultInfo;

#pragma pack(push, 1)
struct Vector2
{
	float x;
	float y;
};
#pragma pack(pop)

CPacket& operator<<(CPacket& packet, const Vector2& obj);
CPacketView& operator>>(CPacketView& packet, Vector2& obj);

CPacket& operator<<(CPacket& packet, const FBufferView<Vector2>& obj);
CPacketView& operator>>(CPacketView& packet, FBufferView<Vector2>& obj);

#pragma pack(push, 1)
struct ItemElem
{
	uint32_t cursor;
	uint32_t itemId;
	uint32_t quantity;
};
#pragma pack(pop)

CPacket& operator<<(CPacket& packet, const ItemElem& obj);
CPacketView& operator>>(CPacketView& packet, ItemElem& obj);

CPacket& operator<<(CPacket& packet, const FBufferView<ItemElem>& obj);
CPacketView& operator>>(CPacketView& packet, FBufferView<ItemElem>& obj);

#pragma pack(push, 1)
struct AccountInfo
{
	int32_t id;
	std::wstring_view nickname;
	int32_t level;
};
#pragma pack(pop)

CPacket& operator<<(CPacket& packet, const AccountInfo& obj);
CPacketView& operator>>(CPacketView& packet, AccountInfo& obj);

CPacket& operator<<(CPacket& packet, const FBufferView<AccountInfo>& obj);
CPacketView& operator>>(CPacketView& packet, FBufferView<AccountInfo>& obj);

#pragma pack(push, 1)
struct ResultInfo
{
	int32_t accountId;
	int32_t score;
	int32_t exp;
	int32_t kill;
};
#pragma pack(pop)

CPacket& operator<<(CPacket& packet, const ResultInfo& obj);
CPacketView& operator>>(CPacketView& packet, ResultInfo& obj);

CPacket& operator<<(CPacket& packet, const FBufferView<ResultInfo>& obj);
CPacketView& operator>>(CPacketView& packet, FBufferView<ResultInfo>& obj);


DISABLE_WARNINGS_END()

extern const wchar_t* gRequestIdStr[];
extern const int gRequestIdStrCnt;

enum class RequestId : unsigned short
{
    ReqLoginGameServer,
    ReqLoginChatServer,
    MatchStart,
    MatchCancel,
    SceneReady,
    WeaponSelect,
    ReturnToLobby,
    AccountInfoDebug,
    QuitGame,
    ReqSpectateGame,
    ReqSpectateNext,
    ReqSpectatePrev,
    ProjectileShootStart,
    HitscanShootStart,
    HitscanHit,
    ReqReloadBullet,
    ReqPickupItemPicker,
    OpenChest,
    CloseChest,
    ReqInventoryInfo,
    ReqInventoryToChest,
    ReqChestToInventory,
    ReqUseItem,
    ReqDropItem,
    MoveStart,
    RotateStart,
	MaxRequest
};

