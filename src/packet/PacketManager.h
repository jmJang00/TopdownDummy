#pragma once
#include <type_traits>
#include <JNet/CSession.h>
#include "Stub.h"
#include "Packet.h"

class CPacket;
class CPacketView;

class PacketManager
{
public:
	PacketManager()
	{
		_stub = new Stub();
	}

	~PacketManager()
	{
		delete _stub;
	}

	void Attach(Stub* stub)
	{
        delete _stub;
        _stub = stub;
	}

	int GetLastError() { return _lastError; }

	bool PacketProc(PacketType type, CPacketView* packet, FSessionId sessionId);

private:

	bool PP_S_ResLoginGameServer(CPacketView* packet, FSessionId sessionId);
	bool PP_S_ResLoginChatServer(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfAccountInfo(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfCreateMyCharacter(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfCreateOtherCharacter(CPacketView* packet, FSessionId sessionId);
	bool PP_S_DeleteCharacter(CPacketView* packet, FSessionId sessionId);
	bool PP_S_MatchFound(CPacketView* packet, FSessionId sessionId);
	bool PP_S_GameStart(CPacketView* packet, FSessionId sessionId);
	bool PP_S_GameEnd(CPacketView* packet, FSessionId sessionId);
	bool PP_S_ReturnToLobby(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfSpectateUser(CPacketView* packet, FSessionId sessionId);
	bool PP_S_ProjectileShootStart(CPacketView* packet, FSessionId sessionId);
	bool PP_S_SpawnProjectile(CPacketView* packet, FSessionId sessionId);
	bool PP_S_DespawnProjectile(CPacketView* packet, FSessionId sessionId);
	bool PP_S_ProjectileHit(CPacketView* packet, FSessionId sessionId);
	bool PP_S_HitscanShootStart(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfHitscanShootStart(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfHitscanShootState(CPacketView* packet, FSessionId sessionId);
	bool PP_S_HitscanHit(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfUpdateBullet(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfSpawnItemPicker(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfDespawnItemPicker(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfCreateChest(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfDestroyChest(CPacketView* packet, FSessionId sessionId);
	bool PP_S_OpenChest(CPacketView* packet, FSessionId sessionId);
	bool PP_S_CloseChest(CPacketView* packet, FSessionId sessionId);
	bool PP_S_NtfChestInfo(CPacketView* packet, FSessionId sessionId);
	bool PP_S_ResInventoryInfo(CPacketView* packet, FSessionId sessionId);
	bool PP_S_ResInventoryToChest(CPacketView* packet, FSessionId sessionId);
	bool PP_S_ResChestToInventory(CPacketView* packet, FSessionId sessionId);
	bool PP_S_MoveStart(CPacketView* packet, FSessionId sessionId);
	bool PP_S_MoveState(CPacketView* packet, FSessionId sessionId);
	bool PP_S_TickSync(CPacketView* packet, FSessionId sessionId);
	bool PP_S_RotateStart(CPacketView* packet, FSessionId sessionId);
	bool PP_S_RotateState(CPacketView* packet, FSessionId sessionId);

	Stub* _stub;
	int _lastError;
};
