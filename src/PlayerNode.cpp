#include "pch.h"
#include "PlayerNode.h"

PlayerNode::PlayerNode(Player* player, FEnumValue type, member_func func)
	: _player(player)
{
	_index = type;
	_func = func;
}

PlayerNode::~PlayerNode()
{

}

void PlayerNode::Print(int depth)
{
	for (int i = 0; i < depth; i++)
	{
		printf("    ");
	}
	printf("| %ls\n", _index.ToString());
}

std::wstring PlayerNode::GetNodeStatus()
{
	std::wstring str = L"Player(";
	str += L"type:";
	str += _index.ToString();
	str += L" last:";
	str += std::to_wstring((int)lastStatus);
	str += L")";
	return str; 
}

void PlayerNode::Reset()
{
	lastStatus = StatusType::Success;
}

BaseNode* PlayerNode::Clone(Player* player)
{
	return new PlayerNode(player, _index, _func);
}

StatusType PlayerNode::Tick(PlayerBT* bt)
{
	if (playerBT == nullptr)
	{
		playerBT = bt;
		bt->PushBase(this);
	}

	if (playerBT->GetLastStatus() == StatusType::None)
	{
		lastStatus = (_player->*_func)(this);
	}
	else
	{
		lastStatus = playerBT->GetLastStatus();
		playerBT->SetLastStatusNone();
	}

	if (lastStatus == StatusType::Running)
	{
		return lastStatus;
	}

	playerBT = nullptr;
	bt->PopBase(this);
	return lastStatus;
}
