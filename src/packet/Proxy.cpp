#include "pch.h"
#include <JNet/CPacket.h>
#include <JNet/CSession.h>
#include <JNet/CNetServer.h>
#include <JNet/CNetClient.h>
#include <JNet/FBufferView.h>
//#include <JCore/SLog.h>
#include "PacketManager.h"
#include "Proxy.h"
#include "Packet.h"
#include "DummyClient.h"

//#undef DLOGHA()
//#define DLOGHA()

bool Proxy::C_ReqLoginGameServer(FSessionId sessionId, const std::wstring_view& sessionKey)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_LOGIN_GAME_SERVER;
	*packet << sessionKey;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqLoginGameServer(FSessionId* sessionIds, size_t cnt, const std::wstring_view& sessionKey)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_LOGIN_GAME_SERVER;
	*packet << sessionKey;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqLoginGameServer(FSessionId sessionId, const C_ReqLoginGameServerArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_LOGIN_GAME_SERVER;
	*packet << args->sessionKey;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqLoginGameServer(FSessionId* sessionIds, size_t cnt, const C_ReqLoginGameServerArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_LOGIN_GAME_SERVER;
	*packet << args->sessionKey;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqLoginChatServer(FSessionId sessionId, const std::wstring_view& sessionKey)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_LOGIN_CHAT_SERVER;
	*packet << sessionKey;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqLoginChatServer(FSessionId* sessionIds, size_t cnt, const std::wstring_view& sessionKey)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_LOGIN_CHAT_SERVER;
	*packet << sessionKey;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqLoginChatServer(FSessionId sessionId, const C_ReqLoginChatServerArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_LOGIN_CHAT_SERVER;
	*packet << args->sessionKey;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqLoginChatServer(FSessionId* sessionIds, size_t cnt, const C_ReqLoginChatServerArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_LOGIN_CHAT_SERVER;
	*packet << args->sessionKey;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MatchStart(FSessionId sessionId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MATCH_START;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MatchStart(FSessionId* sessionIds, size_t cnt)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MATCH_START;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MatchStart(FSessionId sessionId, const C_MatchStartArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MATCH_START;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MatchStart(FSessionId* sessionIds, size_t cnt, const C_MatchStartArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MATCH_START;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MatchCancel(FSessionId sessionId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MATCH_CANCEL;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MatchCancel(FSessionId* sessionIds, size_t cnt)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MATCH_CANCEL;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MatchCancel(FSessionId sessionId, const C_MatchCancelArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MATCH_CANCEL;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MatchCancel(FSessionId* sessionIds, size_t cnt, const C_MatchCancelArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MATCH_CANCEL;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_SceneReady(FSessionId sessionId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_SCENE_READY;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_SceneReady(FSessionId* sessionIds, size_t cnt)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_SCENE_READY;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_SceneReady(FSessionId sessionId, const C_SceneReadyArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_SCENE_READY;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_SceneReady(FSessionId* sessionIds, size_t cnt, const C_SceneReadyArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_SCENE_READY;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_WeaponSelect(FSessionId sessionId, uint16_t weaponId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_WEAPON_SELECT;
	*packet << weaponId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_WeaponSelect(FSessionId* sessionIds, size_t cnt, uint16_t weaponId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_WEAPON_SELECT;
	*packet << weaponId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_WeaponSelect(FSessionId sessionId, const C_WeaponSelectArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_WEAPON_SELECT;
	*packet << args->weaponId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_WeaponSelect(FSessionId* sessionIds, size_t cnt, const C_WeaponSelectArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_WEAPON_SELECT;
	*packet << args->weaponId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReturnToLobby(FSessionId sessionId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_RETURN_TO_LOBBY;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReturnToLobby(FSessionId* sessionIds, size_t cnt)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_RETURN_TO_LOBBY;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReturnToLobby(FSessionId sessionId, const C_ReturnToLobbyArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_RETURN_TO_LOBBY;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReturnToLobby(FSessionId* sessionIds, size_t cnt, const C_ReturnToLobbyArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_RETURN_TO_LOBBY;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_AccountInfoDebug(FSessionId sessionId, int64_t accountId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_ACCOUNT_INFO_DEBUG;
	*packet << accountId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_AccountInfoDebug(FSessionId* sessionIds, size_t cnt, int64_t accountId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_ACCOUNT_INFO_DEBUG;
	*packet << accountId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_AccountInfoDebug(FSessionId sessionId, const C_AccountInfoDebugArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_ACCOUNT_INFO_DEBUG;
	*packet << args->accountId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_AccountInfoDebug(FSessionId* sessionIds, size_t cnt, const C_AccountInfoDebugArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_ACCOUNT_INFO_DEBUG;
	*packet << args->accountId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_QuitGame(FSessionId sessionId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_QUIT_GAME;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_QuitGame(FSessionId* sessionIds, size_t cnt)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_QUIT_GAME;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_QuitGame(FSessionId sessionId, const C_QuitGameArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_QUIT_GAME;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_QuitGame(FSessionId* sessionIds, size_t cnt, const C_QuitGameArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_QUIT_GAME;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectateGame(FSessionId sessionId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_GAME;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectateGame(FSessionId* sessionIds, size_t cnt)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_GAME;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectateGame(FSessionId sessionId, const C_ReqSpectateGameArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_GAME;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectateGame(FSessionId* sessionIds, size_t cnt, const C_ReqSpectateGameArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_GAME;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectateNext(FSessionId sessionId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_NEXT;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectateNext(FSessionId* sessionIds, size_t cnt)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_NEXT;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectateNext(FSessionId sessionId, const C_ReqSpectateNextArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_NEXT;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectateNext(FSessionId* sessionIds, size_t cnt, const C_ReqSpectateNextArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_NEXT;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectatePrev(FSessionId sessionId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_PREV;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectatePrev(FSessionId* sessionIds, size_t cnt)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_PREV;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectatePrev(FSessionId sessionId, const C_ReqSpectatePrevArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_PREV;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqSpectatePrev(FSessionId* sessionIds, size_t cnt, const C_ReqSpectatePrevArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_SPECTATE_PREV;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ProjectileShootStart(FSessionId sessionId, int32_t clientTick)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_PROJECTILE_SHOOT_START;
	*packet << clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ProjectileShootStart(FSessionId* sessionIds, size_t cnt, int32_t clientTick)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_PROJECTILE_SHOOT_START;
	*packet << clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ProjectileShootStart(FSessionId sessionId, const C_ProjectileShootStartArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_PROJECTILE_SHOOT_START;
	*packet << args->clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ProjectileShootStart(FSessionId* sessionIds, size_t cnt, const C_ProjectileShootStartArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_PROJECTILE_SHOOT_START;
	*packet << args->clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_HitscanShootStart(FSessionId sessionId, int32_t clientTick, const Vector2& start, const Vector2& end)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_HITSCAN_SHOOT_START;
	*packet << clientTick;
	*packet << start;
	*packet << end;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_HitscanShootStart(FSessionId* sessionIds, size_t cnt, int32_t clientTick, const Vector2& start, const Vector2& end)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_HITSCAN_SHOOT_START;
	*packet << clientTick;
	*packet << start;
	*packet << end;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_HitscanShootStart(FSessionId sessionId, const C_HitscanShootStartArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_HITSCAN_SHOOT_START;
	*packet << args->clientTick;
	*packet << args->start;
	*packet << args->end;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_HitscanShootStart(FSessionId* sessionIds, size_t cnt, const C_HitscanShootStartArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_HITSCAN_SHOOT_START;
	*packet << args->clientTick;
	*packet << args->start;
	*packet << args->end;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_HitscanHit(FSessionId sessionId, int32_t currentTick, uint32_t shooterId, uint32_t targetId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_HITSCAN_HIT;
	*packet << currentTick;
	*packet << shooterId;
	*packet << targetId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_HitscanHit(FSessionId* sessionIds, size_t cnt, int32_t currentTick, uint32_t shooterId, uint32_t targetId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_HITSCAN_HIT;
	*packet << currentTick;
	*packet << shooterId;
	*packet << targetId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_HitscanHit(FSessionId sessionId, const C_HitscanHitArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_HITSCAN_HIT;
	*packet << args->currentTick;
	*packet << args->shooterId;
	*packet << args->targetId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_HitscanHit(FSessionId* sessionIds, size_t cnt, const C_HitscanHitArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_HITSCAN_HIT;
	*packet << args->currentTick;
	*packet << args->shooterId;
	*packet << args->targetId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqReloadBullet(FSessionId sessionId, int32_t clientTick)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_RELOAD_BULLET;
	*packet << clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqReloadBullet(FSessionId* sessionIds, size_t cnt, int32_t clientTick)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_RELOAD_BULLET;
	*packet << clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqReloadBullet(FSessionId sessionId, const C_ReqReloadBulletArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_RELOAD_BULLET;
	*packet << args->clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqReloadBullet(FSessionId* sessionIds, size_t cnt, const C_ReqReloadBulletArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_RELOAD_BULLET;
	*packet << args->clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqPickupItemPicker(FSessionId sessionId, int32_t clientTick, uint32_t entityId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_PICKUP_ITEM_PICKER;
	*packet << clientTick;
	*packet << entityId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqPickupItemPicker(FSessionId* sessionIds, size_t cnt, int32_t clientTick, uint32_t entityId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_PICKUP_ITEM_PICKER;
	*packet << clientTick;
	*packet << entityId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqPickupItemPicker(FSessionId sessionId, const C_ReqPickupItemPickerArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_PICKUP_ITEM_PICKER;
	*packet << args->clientTick;
	*packet << args->entityId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqPickupItemPicker(FSessionId* sessionIds, size_t cnt, const C_ReqPickupItemPickerArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_PICKUP_ITEM_PICKER;
	*packet << args->clientTick;
	*packet << args->entityId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_OpenChest(FSessionId sessionId, int32_t clientTick, uint32_t chestId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_OPEN_CHEST;
	*packet << clientTick;
	*packet << chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_OpenChest(FSessionId* sessionIds, size_t cnt, int32_t clientTick, uint32_t chestId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_OPEN_CHEST;
	*packet << clientTick;
	*packet << chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_OpenChest(FSessionId sessionId, const C_OpenChestArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_OPEN_CHEST;
	*packet << args->clientTick;
	*packet << args->chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_OpenChest(FSessionId* sessionIds, size_t cnt, const C_OpenChestArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_OPEN_CHEST;
	*packet << args->clientTick;
	*packet << args->chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_CloseChest(FSessionId sessionId, int32_t clientTick, uint32_t chestId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_CLOSE_CHEST;
	*packet << clientTick;
	*packet << chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_CloseChest(FSessionId* sessionIds, size_t cnt, int32_t clientTick, uint32_t chestId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_CLOSE_CHEST;
	*packet << clientTick;
	*packet << chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_CloseChest(FSessionId sessionId, const C_CloseChestArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_CLOSE_CHEST;
	*packet << args->clientTick;
	*packet << args->chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_CloseChest(FSessionId* sessionIds, size_t cnt, const C_CloseChestArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_CLOSE_CHEST;
	*packet << args->clientTick;
	*packet << args->chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqInventoryInfo(FSessionId sessionId, int32_t clientTick)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_INVENTORY_INFO;
	*packet << clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqInventoryInfo(FSessionId* sessionIds, size_t cnt, int32_t clientTick)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_INVENTORY_INFO;
	*packet << clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqInventoryInfo(FSessionId sessionId, const C_ReqInventoryInfoArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_INVENTORY_INFO;
	*packet << args->clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqInventoryInfo(FSessionId* sessionIds, size_t cnt, const C_ReqInventoryInfoArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_INVENTORY_INFO;
	*packet << args->clientTick;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqInventoryToChest(FSessionId sessionId, int32_t clientTick, int32_t lastUpdateTick, int32_t lastInventoryUpdateTick, uint32_t entityId, uint32_t inventoryCursor, uint32_t chestId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_INVENTORY_TO_CHEST;
	*packet << clientTick;
	*packet << lastUpdateTick;
	*packet << lastInventoryUpdateTick;
	*packet << entityId;
	*packet << inventoryCursor;
	*packet << chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqInventoryToChest(FSessionId* sessionIds, size_t cnt, int32_t clientTick, int32_t lastUpdateTick, int32_t lastInventoryUpdateTick, uint32_t entityId, uint32_t inventoryCursor, uint32_t chestId)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_INVENTORY_TO_CHEST;
	*packet << clientTick;
	*packet << lastUpdateTick;
	*packet << lastInventoryUpdateTick;
	*packet << entityId;
	*packet << inventoryCursor;
	*packet << chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqInventoryToChest(FSessionId sessionId, const C_ReqInventoryToChestArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_INVENTORY_TO_CHEST;
	*packet << args->clientTick;
	*packet << args->lastUpdateTick;
	*packet << args->lastInventoryUpdateTick;
	*packet << args->entityId;
	*packet << args->inventoryCursor;
	*packet << args->chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqInventoryToChest(FSessionId* sessionIds, size_t cnt, const C_ReqInventoryToChestArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_INVENTORY_TO_CHEST;
	*packet << args->clientTick;
	*packet << args->lastUpdateTick;
	*packet << args->lastInventoryUpdateTick;
	*packet << args->entityId;
	*packet << args->inventoryCursor;
	*packet << args->chestId;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqChestToInventory(FSessionId sessionId, int32_t clientTick, int32_t lastUpdateTick, int32_t lastInventoryUpdateTick, uint32_t entityId, uint32_t chestId, uint32_t chestCursor)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_CHEST_TO_INVENTORY;
	*packet << clientTick;
	*packet << lastUpdateTick;
	*packet << lastInventoryUpdateTick;
	*packet << entityId;
	*packet << chestId;
	*packet << chestCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqChestToInventory(FSessionId* sessionIds, size_t cnt, int32_t clientTick, int32_t lastUpdateTick, int32_t lastInventoryUpdateTick, uint32_t entityId, uint32_t chestId, uint32_t chestCursor)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_CHEST_TO_INVENTORY;
	*packet << clientTick;
	*packet << lastUpdateTick;
	*packet << lastInventoryUpdateTick;
	*packet << entityId;
	*packet << chestId;
	*packet << chestCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqChestToInventory(FSessionId sessionId, const C_ReqChestToInventoryArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_CHEST_TO_INVENTORY;
	*packet << args->clientTick;
	*packet << args->lastUpdateTick;
	*packet << args->lastInventoryUpdateTick;
	*packet << args->entityId;
	*packet << args->chestId;
	*packet << args->chestCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqChestToInventory(FSessionId* sessionIds, size_t cnt, const C_ReqChestToInventoryArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_CHEST_TO_INVENTORY;
	*packet << args->clientTick;
	*packet << args->lastUpdateTick;
	*packet << args->lastInventoryUpdateTick;
	*packet << args->entityId;
	*packet << args->chestId;
	*packet << args->chestCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqUseItem(FSessionId sessionId, int32_t clientTick, int32_t lastInventoryUpdateTick, uint32_t inventoryCursor)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_USE_ITEM;
	*packet << clientTick;
	*packet << lastInventoryUpdateTick;
	*packet << inventoryCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqUseItem(FSessionId* sessionIds, size_t cnt, int32_t clientTick, int32_t lastInventoryUpdateTick, uint32_t inventoryCursor)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_USE_ITEM;
	*packet << clientTick;
	*packet << lastInventoryUpdateTick;
	*packet << inventoryCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqUseItem(FSessionId sessionId, const C_ReqUseItemArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_USE_ITEM;
	*packet << args->clientTick;
	*packet << args->lastInventoryUpdateTick;
	*packet << args->inventoryCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqUseItem(FSessionId* sessionIds, size_t cnt, const C_ReqUseItemArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_USE_ITEM;
	*packet << args->clientTick;
	*packet << args->lastInventoryUpdateTick;
	*packet << args->inventoryCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqDropItem(FSessionId sessionId, int32_t clientTick, int32_t lastInventoryUpdateTick, uint32_t inventoryCursor)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_DROP_ITEM;
	*packet << clientTick;
	*packet << lastInventoryUpdateTick;
	*packet << inventoryCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeaderEx) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqDropItem(FSessionId* sessionIds, size_t cnt, int32_t clientTick, int32_t lastInventoryUpdateTick, uint32_t inventoryCursor)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_DROP_ITEM;
	*packet << clientTick;
	*packet << lastInventoryUpdateTick;
	*packet << inventoryCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqDropItem(FSessionId sessionId, const C_ReqDropItemArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_DROP_ITEM;
	*packet << args->clientTick;
	*packet << args->lastInventoryUpdateTick;
	*packet << args->inventoryCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_ReqDropItem(FSessionId* sessionIds, size_t cnt, const C_ReqDropItemArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_REQ_DROP_ITEM;
	*packet << args->clientTick;
	*packet << args->lastInventoryUpdateTick;
	*packet << args->inventoryCursor;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}

	if (packet->Encoding())
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeaderEx) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}
	else
	{
		DLOGHA(L"Packet", L"Multi Send", (unsigned char*)packet->GetBufferPtr() + sizeof(FHeader) + sizeof(PacketType), packet->GetBufferSize() - sizeof(FHeader) - sizeof(PacketType));
	}

	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MoveStart(FSessionId sessionId, int32_t clientTick, const Vector2& target)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MOVE_START;
	*packet << clientTick;
	*packet << target;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MoveStart(FSessionId* sessionIds, size_t cnt, int32_t clientTick, const Vector2& target)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MOVE_START;
	*packet << clientTick;
	*packet << target;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MoveStart(FSessionId sessionId, const C_MoveStartArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MOVE_START;
	*packet << args->clientTick;
	*packet << args->target;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_MoveStart(FSessionId* sessionIds, size_t cnt, const C_MoveStartArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_MOVE_START;
	*packet << args->clientTick;
	*packet << args->target;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_RotateStart(FSessionId sessionId, int32_t clientTick, float targetAngle)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_ROTATE_START;
	*packet << clientTick;
	*packet << targetAngle;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_RotateStart(FSessionId* sessionIds, size_t cnt, int32_t clientTick, float targetAngle)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_ROTATE_START;
	*packet << clientTick;
	*packet << targetAngle;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_RotateStart(FSessionId sessionId, const C_RotateStartArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_ROTATE_START;
	*packet << args->clientTick;
	*packet << args->targetAngle;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	_server->SendPacket(sessionId, packet->GetPacketBuffer());


	CPacket::Free(packet);

	return true;
}

bool Proxy::C_RotateStart(FSessionId* sessionIds, size_t cnt, const C_RotateStartArgs* args)
{
	CPacket* packet = CPacket::Alloc(false);

	*packet << (unsigned short)PacketType::C_ROTATE_START;
	*packet << args->clientTick;
	*packet << args->targetAngle;

	if (packet->GetLastError() != CPacket::Default)
	{
		CPacket::Free(packet);
		DLOGA(L"Packet", L"Make Packet Fail");
		return false;
	}

	packet->Commit();

	for (size_t i = 0; i < cnt; i++)
	{
		_server->SendPacket(sessionIds[i], packet->GetPacketBuffer());
	}


	CPacket::Free(packet);

	return true;
}


bool Proxy::Send(FSessionId* sessionIds, size_t cnt, const MessageArgs* args)
{
	switch (args->protocol)
	{
	case PacketType::C_REQ_LOGIN_GAME_SERVER:
	{
		return C_ReqLoginGameServer(sessionIds, cnt, (const C_ReqLoginGameServerArgs*)args);
	}
	case PacketType::C_REQ_LOGIN_CHAT_SERVER:
	{
		return C_ReqLoginChatServer(sessionIds, cnt, (const C_ReqLoginChatServerArgs*)args);
	}
	case PacketType::C_MATCH_START:
	{
		return C_MatchStart(sessionIds, cnt, (const C_MatchStartArgs*)args);
	}
	case PacketType::C_MATCH_CANCEL:
	{
		return C_MatchCancel(sessionIds, cnt, (const C_MatchCancelArgs*)args);
	}
	case PacketType::C_SCENE_READY:
	{
		return C_SceneReady(sessionIds, cnt, (const C_SceneReadyArgs*)args);
	}
	case PacketType::C_WEAPON_SELECT:
	{
		return C_WeaponSelect(sessionIds, cnt, (const C_WeaponSelectArgs*)args);
	}
	case PacketType::C_RETURN_TO_LOBBY:
	{
		return C_ReturnToLobby(sessionIds, cnt, (const C_ReturnToLobbyArgs*)args);
	}
	case PacketType::C_ACCOUNT_INFO_DEBUG:
	{
		return C_AccountInfoDebug(sessionIds, cnt, (const C_AccountInfoDebugArgs*)args);
	}
	case PacketType::C_QUIT_GAME:
	{
		return C_QuitGame(sessionIds, cnt, (const C_QuitGameArgs*)args);
	}
	case PacketType::C_REQ_SPECTATE_GAME:
	{
		return C_ReqSpectateGame(sessionIds, cnt, (const C_ReqSpectateGameArgs*)args);
	}
	case PacketType::C_REQ_SPECTATE_NEXT:
	{
		return C_ReqSpectateNext(sessionIds, cnt, (const C_ReqSpectateNextArgs*)args);
	}
	case PacketType::C_REQ_SPECTATE_PREV:
	{
		return C_ReqSpectatePrev(sessionIds, cnt, (const C_ReqSpectatePrevArgs*)args);
	}
	case PacketType::C_PROJECTILE_SHOOT_START:
	{
		return C_ProjectileShootStart(sessionIds, cnt, (const C_ProjectileShootStartArgs*)args);
	}
	case PacketType::C_HITSCAN_SHOOT_START:
	{
		return C_HitscanShootStart(sessionIds, cnt, (const C_HitscanShootStartArgs*)args);
	}
	case PacketType::C_HITSCAN_HIT:
	{
		return C_HitscanHit(sessionIds, cnt, (const C_HitscanHitArgs*)args);
	}
	case PacketType::C_REQ_RELOAD_BULLET:
	{
		return C_ReqReloadBullet(sessionIds, cnt, (const C_ReqReloadBulletArgs*)args);
	}
	case PacketType::C_REQ_PICKUP_ITEM_PICKER:
	{
		return C_ReqPickupItemPicker(sessionIds, cnt, (const C_ReqPickupItemPickerArgs*)args);
	}
	case PacketType::C_OPEN_CHEST:
	{
		return C_OpenChest(sessionIds, cnt, (const C_OpenChestArgs*)args);
	}
	case PacketType::C_CLOSE_CHEST:
	{
		return C_CloseChest(sessionIds, cnt, (const C_CloseChestArgs*)args);
	}
	case PacketType::C_REQ_INVENTORY_INFO:
	{
		return C_ReqInventoryInfo(sessionIds, cnt, (const C_ReqInventoryInfoArgs*)args);
	}
	case PacketType::C_REQ_INVENTORY_TO_CHEST:
	{
		return C_ReqInventoryToChest(sessionIds, cnt, (const C_ReqInventoryToChestArgs*)args);
	}
	case PacketType::C_REQ_CHEST_TO_INVENTORY:
	{
		return C_ReqChestToInventory(sessionIds, cnt, (const C_ReqChestToInventoryArgs*)args);
	}
	case PacketType::C_REQ_USE_ITEM:
	{
		return C_ReqUseItem(sessionIds, cnt, (const C_ReqUseItemArgs*)args);
	}
	case PacketType::C_REQ_DROP_ITEM:
	{
		return C_ReqDropItem(sessionIds, cnt, (const C_ReqDropItemArgs*)args);
	}
	case PacketType::C_MOVE_START:
	{
		return C_MoveStart(sessionIds, cnt, (const C_MoveStartArgs*)args);
	}
	case PacketType::C_ROTATE_START:
	{
		return C_RotateStart(sessionIds, cnt, (const C_RotateStartArgs*)args);
	}
	default:
		return false;
	}
}

bool Proxy::Send(FSessionId sessionId, const MessageArgs* args)
{
	switch (args->protocol)
	{
	case PacketType::C_REQ_LOGIN_GAME_SERVER:
	{
		return C_ReqLoginGameServer(sessionId, (const C_ReqLoginGameServerArgs*)args);
	}
	case PacketType::C_REQ_LOGIN_CHAT_SERVER:
	{
		return C_ReqLoginChatServer(sessionId, (const C_ReqLoginChatServerArgs*)args);
	}
	case PacketType::C_MATCH_START:
	{
		return C_MatchStart(sessionId, (const C_MatchStartArgs*)args);
	}
	case PacketType::C_MATCH_CANCEL:
	{
		return C_MatchCancel(sessionId, (const C_MatchCancelArgs*)args);
	}
	case PacketType::C_SCENE_READY:
	{
		return C_SceneReady(sessionId, (const C_SceneReadyArgs*)args);
	}
	case PacketType::C_WEAPON_SELECT:
	{
		return C_WeaponSelect(sessionId, (const C_WeaponSelectArgs*)args);
	}
	case PacketType::C_RETURN_TO_LOBBY:
	{
		return C_ReturnToLobby(sessionId, (const C_ReturnToLobbyArgs*)args);
	}
	case PacketType::C_ACCOUNT_INFO_DEBUG:
	{
		return C_AccountInfoDebug(sessionId, (const C_AccountInfoDebugArgs*)args);
	}
	case PacketType::C_QUIT_GAME:
	{
		return C_QuitGame(sessionId, (const C_QuitGameArgs*)args);
	}
	case PacketType::C_REQ_SPECTATE_GAME:
	{
		return C_ReqSpectateGame(sessionId, (const C_ReqSpectateGameArgs*)args);
	}
	case PacketType::C_REQ_SPECTATE_NEXT:
	{
		return C_ReqSpectateNext(sessionId, (const C_ReqSpectateNextArgs*)args);
	}
	case PacketType::C_REQ_SPECTATE_PREV:
	{
		return C_ReqSpectatePrev(sessionId, (const C_ReqSpectatePrevArgs*)args);
	}
	case PacketType::C_PROJECTILE_SHOOT_START:
	{
		return C_ProjectileShootStart(sessionId, (const C_ProjectileShootStartArgs*)args);
	}
	case PacketType::C_HITSCAN_SHOOT_START:
	{
		return C_HitscanShootStart(sessionId, (const C_HitscanShootStartArgs*)args);
	}
	case PacketType::C_HITSCAN_HIT:
	{
		return C_HitscanHit(sessionId, (const C_HitscanHitArgs*)args);
	}
	case PacketType::C_REQ_RELOAD_BULLET:
	{
		return C_ReqReloadBullet(sessionId, (const C_ReqReloadBulletArgs*)args);
	}
	case PacketType::C_REQ_PICKUP_ITEM_PICKER:
	{
		return C_ReqPickupItemPicker(sessionId, (const C_ReqPickupItemPickerArgs*)args);
	}
	case PacketType::C_OPEN_CHEST:
	{
		return C_OpenChest(sessionId, (const C_OpenChestArgs*)args);
	}
	case PacketType::C_CLOSE_CHEST:
	{
		return C_CloseChest(sessionId, (const C_CloseChestArgs*)args);
	}
	case PacketType::C_REQ_INVENTORY_INFO:
	{
		return C_ReqInventoryInfo(sessionId, (const C_ReqInventoryInfoArgs*)args);
	}
	case PacketType::C_REQ_INVENTORY_TO_CHEST:
	{
		return C_ReqInventoryToChest(sessionId, (const C_ReqInventoryToChestArgs*)args);
	}
	case PacketType::C_REQ_CHEST_TO_INVENTORY:
	{
		return C_ReqChestToInventory(sessionId, (const C_ReqChestToInventoryArgs*)args);
	}
	case PacketType::C_REQ_USE_ITEM:
	{
		return C_ReqUseItem(sessionId, (const C_ReqUseItemArgs*)args);
	}
	case PacketType::C_REQ_DROP_ITEM:
	{
		return C_ReqDropItem(sessionId, (const C_ReqDropItemArgs*)args);
	}
	case PacketType::C_MOVE_START:
	{
		return C_MoveStart(sessionId, (const C_MoveStartArgs*)args);
	}
	case PacketType::C_ROTATE_START:
	{
		return C_RotateStart(sessionId, (const C_RotateStartArgs*)args);
	}
	default:
		return false;
	}
}

