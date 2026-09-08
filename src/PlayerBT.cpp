#include "pch.h"
#include <JParse/LCRSTree.h>
#include <JParse/ParseTreeUtil.h>
#include "PlayerBT.h"
#include "Player.h"
#include "BaseNode.h"
#include "PlayerNode.h"
#include "Packet.h"

#define ENUM_CASE(id) case FEnumValue(id).GetTotalIndex():

FEnumValue PlayerBT::GetType(const std::string id)
{
	if (id == "Connect")
	{
		return ActionStatus::ConnectRequested;
	}
	else if (id == "Disconnect")
	{
		return ActionStatus::DisconnectRequested;
	}
	else if (id == "MatchIdle")
	{
		return ActionStatus::Idle;
	}
	else if (id == "GameIdle")
	{
		return ActionStatus::GameIdle;
	}
	else if (id == "Login")
	{
		return RequestId::AccountInfoDebug;
	}
	else if (id == "FindMatch")
	{
		return RequestId::MatchStart;
	}
	else if (id == "Ready")
	{
		return RequestId::SceneReady;
	}

	else if (id == "WeaponSelect")
	{
		return RequestId::WeaponSelect;
	}
	else if (id == "Move")
	{
		return RequestId::MoveStart;
	}
	else if (id == "Rotate")
	{
		return RequestId::RotateStart;
	}
	else if (id == "ProjectileShoot")
	{
		return RequestId::ProjectileShootStart;
	}
	else if (id == "SpawnCheck")
	{
		return ActionStatus::SpawnWait;
	}
	else if (id == "ToLobby")
	{
		return RequestId::ReturnToLobby;
	}
	else
	{
		return ActionStatus::Count;
	}
}

BaseNode* PlayerBT::Parse(FEnumValue& value, LCRSNode* node)
{
	switch (value.GetTotalIndex())
	{
		ENUM_CASE(ActionStatus::ConnectRequested)
		{
			return new PlayerNode(nullptr, ActionStatus::ConnectRequested, 
				&Player::Connect);
		}
		ENUM_CASE(ActionStatus::DisconnectRequested)
		{
			return new PlayerNode(nullptr, ActionStatus::DisconnectRequested, 
				&Player::Disconnect);
		}
		ENUM_CASE(ActionStatus::Idle)
		{
			return new PlayerNode(nullptr, ActionStatus::Idle, 
				&Player::DoMatchIdle);
		}
		ENUM_CASE(ActionStatus::GameIdle)
		{
			return new PlayerNode(nullptr, ActionStatus::GameIdle, 
				&Player::DoGameIdle);
		}
		ENUM_CASE(ActionStatus::SpawnWait)
		{
			return new PlayerNode(nullptr, ActionStatus::SpawnWait, 
				&Player::SpawnCheck);
		}
		ENUM_CASE(RequestId::AccountInfoDebug)
		{
			auto args = C_AccountInfoDebugArgs(0);
			return new PlayerPacketNode<C_AccountInfoDebugArgs>(nullptr, 
				RequestId::AccountInfoDebug, args, true, PacketType::S_RES_LOGIN_GAME_SERVER);
		}
		ENUM_CASE(RequestId::MatchStart)
		{
			auto args = C_MatchStartArgs();
			return new PlayerPacketNode<C_MatchStartArgs>(nullptr, 
				RequestId::MatchStart, args, true, PacketType::S_MATCH_FOUND);
		}
		ENUM_CASE(RequestId::SceneReady)
		{
			auto args = C_SceneReadyArgs();
			return new PlayerPacketNode<C_SceneReadyArgs>(nullptr, 
				RequestId::SceneReady, args, false);
		}
		ENUM_CASE(RequestId::WeaponSelect)
		{
			LCRSNode* typeNode = node->GetChild(0);
			int type = PtUtil::GetIntLiteral(typeNode);
			auto args = C_WeaponSelectArgs((unsigned short)type);
			return new PlayerPacketNode<C_WeaponSelectArgs>(nullptr, 
				RequestId::WeaponSelect, args, false);
		}
		ENUM_CASE(RequestId::MoveStart)
		{
			auto args = C_MoveStartArgs(0, {});
			return new PlayerPacketNode<C_MoveStartArgs>(nullptr, 
				RequestId::MoveStart, args, true, PacketType::S_MOVE_START);
		}
		ENUM_CASE(RequestId::RotateStart)
		{
			auto args = C_RotateStartArgs(0, 0.f);
			return new PlayerPacketNode<C_RotateStartArgs>(nullptr, 
				RequestId::RotateStart, args, true, PacketType::S_ROTATE_START);
		}
		ENUM_CASE(RequestId::ProjectileShootStart)
		{
			auto args = C_ProjectileShootStartArgs(0);
			return new PlayerPacketNode<C_ProjectileShootStartArgs>(nullptr, 
				RequestId::ProjectileShootStart, args, false);
		}
		ENUM_CASE(RequestId::ReturnToLobby)
		{
			auto args = C_ReturnToLobbyArgs();
			return new PlayerPacketNode<C_ReturnToLobbyArgs>(nullptr, 
				RequestId::ReturnToLobby, args, false);
		}
		default:
		{
			return nullptr;
		}
	}
}

PlayerBT::PlayerBT(BaseNode* root, Player* player)
{
	lastStatus = StatusType::None;
	historyIndex = 0;
	mainRoot = root;
	history.resize(20);
}

PlayerBT::~PlayerBT()
{
	delete mainRoot;
}

PlayerBT* PlayerBT::Clone(Player* player)
{
	PlayerBT* copy = new PlayerBT(mainRoot->Clone(player), player);
	return copy;
}

void PlayerBT::Reset()
{
	mainRoot->Reset();
}

void PlayerBT::Print()
{
	mainRoot->Print(0);
}

bool PlayerBT::Tick()
{
	bool result;
	lastStatus = StatusType::None;
	if (nodeStack.size() == 0)
	{
		result = (mainRoot->Tick(this) != StatusType::Failure);
		return result;
	}

	while (!nodeStack.empty())
	{
		BaseNode* node = nodeStack.back();
		lastStatus = node->Tick(this);
		if (lastStatus == StatusType::Running)
		{
			break;
		}
	}

	result = (lastStatus != StatusType::Failure);
	return result;
}

void PlayerBT::PushBase(BaseNode* node)
{
	nodeStack.push_back(node);
	RecordNode();
}

void PlayerBT::PopBase(BaseNode* node)
{
	CRASH(nodeStack.size() == 0);
	CRASH(node != nodeStack.back());
	nodeStack.pop_back();
	RecordNode();
}

void PlayerBT::PrintStack()
{
	std::wstring stackStr = L"Node Stack: ";
	for (int i = 0; i < nodeStack.size(); i++)
	{
		stackStr += nodeStack[nodeStack.size() - i - 1]->GetNodeStatus() + L" ";
	}
	DLOGA(L"DummyClient", L"%s", stackStr.c_str());
}

void PlayerBT::PrintHistory()
{
	std::wstring historyStr = L"Node History: ";
	int size = std::min(6, (int)history.size());
	for (int i = 0; i < size; i++)
	{
		historyStr += history[(historyIndex - i + size) % size]->GetNodeStatus() + L" ";
	}
	DLOGA(L"DummyClient", L"%s", historyStr.c_str());
}

void PlayerBT::RecordNode()
{
	if (nodeStack.size() > 0)
	{
		if (history[historyIndex % history.size()] != nodeStack.back())
		{
			historyIndex++;
			history[historyIndex % history.size()] = nodeStack.back();
		}
	}
}

void PlayerBT::SetLastStatusNone()
{
	lastStatus = StatusType::None;
}

StatusType PlayerBT::GetLastStatus() const
{
	return lastStatus;
}
