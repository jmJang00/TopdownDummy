#pragma once
#include <stdio.h>
#include "BaseNode.h"
#include "Player.h"
#include "Packet.h"

class PlayerNode : public BaseNode
{
public:
	using member_func = StatusType(Player::* )(BaseNode* node);

	PlayerNode(Player* player, FEnumValue type, member_func func);

	~PlayerNode();

	virtual void Print(int depth) override;

	virtual std::wstring GetNodeStatus() override;

	virtual void Reset() override;

	virtual BaseNode* Clone(Player* player) override;

	virtual StatusType Tick(PlayerBT* bt) override;

private:
	FEnumValue _index;
	Player* _player;
	member_func _func;
};

template <typename T>
class PlayerPacketNode : public BaseNode 
{
public:
	PlayerPacketNode(Player* player, RequestId reqType, T& packet, 
		bool response, PacketType resType = (PacketType)0)
		: _response(response)
		, _reqType(reqType)
		, _resType(resType)
		, _packet(packet)
		, _player(player)
	{
		static_assert(std::is_base_of<MessageArgs, T>::value, "T must be derived from MessageArgs");
	}

	void Print(int depth) override
	{
		for (int i = 0; i < depth; i++)
		{
			printf("    ");
		}
		printf("| %ls\n", FEnumValue(_reqType).ToString());
	}

	virtual std::wstring GetNodeStatus() 
	{ 
		std::wstring str = L"Packet(";
		str += L"type:";
		str += FEnumValue(_reqType).ToString();
		str += L" last:";
		str += std::to_wstring((int)lastStatus);
		str += L")";
		return str; 
	}

	void Reset() override
	{
		lastStatus = StatusType::Success;
	}

	BaseNode* Clone(Player* player) override
	{
		return new PlayerPacketNode<T>(player, _reqType, _packet, _response, _resType);
	}

	StatusType Tick(PlayerBT* bt) override
	{
		if (playerBT == nullptr)
		{
			playerBT = bt;
			bt->PushBase(this);
		}

		if (playerBT->GetLastStatus() == StatusType::None)
		{
			lastStatus = _player->ProcessPacketNode(_reqType, &_packet, _response, _resType, this);
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

private:
	bool _response;
	PacketType _resType;
	RequestId _reqType;
	T _packet;
	Player* _player;
};
