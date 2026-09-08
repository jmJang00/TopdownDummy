#pragma once
#include <string>
#include <vector>
#include <JCore/Profiler.h>
#include "PlayerBT.h"
#include "StatusType.h"

class Player;
class PlayerBT;

class BaseNode
{
public:

	virtual void Reset() {};
	virtual void Print(int depth) {};
	virtual std::wstring GetNodeStatus() { return L"BaseNode()"; };
	virtual BaseNode* Clone(Player* player) = 0;
	virtual StatusType Update() { return StatusType::Failure; };
	virtual StatusType Tick(PlayerBT* bt)
	{
		return StatusType::Failure;
	}

protected:
	PlayerBT* playerBT = nullptr;
	StatusType lastStatus = StatusType::Success;
};

class SequenceNode : public BaseNode
{
public:
	std::vector<BaseNode*> children;
	int index;

	SequenceNode()
		: index(0)
	{

	}

	~SequenceNode()
	{
		for (int i = 0; i < children.size(); i++)
		{
			delete children[i];
		}
		children.clear();
	}

	virtual void Reset() override
	{
		index = 0;
		lastStatus = StatusType::Success;
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->Reset();
		}
	}

	virtual void Print(int depth) override
	{
		for (int i = 0; i < depth; i++)
		{
			printf("    ");
		}
		printf("| Sequence\n");

		for (int i = 0; i < children.size(); i++)
		{
			children[i]->Print(depth + 1);
		}
	}

	virtual std::wstring GetNodeStatus() 
	{ 
		std::wstring str = L"Seq(";
		str += L"index:";
		str += std::to_wstring(index);
		str += L" last:";
		str += std::to_wstring((int)lastStatus);
		str += L")";
		return str; 
	}

	virtual BaseNode* Clone(Player* player) override
	{
		SequenceNode* node = new SequenceNode();
		for (int i = 0; i < children.size(); i++)
		{
			node->children.push_back(children[i]->Clone(player));
		}
		return node;
	}

	virtual StatusType Tick(PlayerBT* bt) override
	{
		if (playerBT == nullptr)
		{
			playerBT = bt;
			bt->PushBase(this);
		}

		if (lastStatus != StatusType::Running)
		{
			index = 0;
		}

		for (int i = index; i < children.size(); ++i)
		{
			if (playerBT->GetLastStatus() == StatusType::None)
			{
				lastStatus = children[i]->Tick(bt);
			}
			else
			{
				lastStatus = playerBT->GetLastStatus();
				playerBT->SetLastStatusNone();
			}

			if (lastStatus == StatusType::Running)
			{
				index = i;
				return lastStatus;
			}

			if (lastStatus == StatusType::Failure)
			{
				index = 0;
				playerBT = nullptr;
				bt->PopBase(this);
				return lastStatus;
			}
		}

		index = 0;
		playerBT = nullptr;
		bt->PopBase(this);
		return lastStatus;
	}
};

class SelectorNode : public BaseNode
{
public:
	std::vector<BaseNode*> children;
	int index;

	SelectorNode()
		: index(0)
	{

	}

	~SelectorNode()
	{
		for (int i = 0; i < children.size(); i++)
		{
			delete children[i];
		}
		children.clear();
	}

	virtual void Print(int depth) override
	{
		for (int i = 0; i < depth; i++)
		{
			printf("    ");
		}
		printf("| Selector\n");

		for (int i = 0; i < children.size(); i++)
		{
			children[i]->Print(depth + 1);
		}
	}

	virtual std::wstring GetNodeStatus() 
	{ 
		std::wstring str = L"Sel(";
		str += L"index:";
		str += std::to_wstring(index);
		str += L" last:";
		str += std::to_wstring((int)lastStatus);
		str += L")";
		return str; 
	}

	virtual void Reset() override
	{
		index = 0;
		lastStatus = StatusType::Success;
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->Reset();
		}
	}

	virtual BaseNode* Clone(Player* player) override
	{
		SelectorNode* node = new SelectorNode();
		for (int i = 0; i < children.size(); i++)
		{
			node->children.push_back(children[i]->Clone(player));
		}
		return node;
	}

	virtual StatusType Tick(PlayerBT* bt) override
	{
		if (playerBT == nullptr)
		{
			playerBT = bt;
			bt->PushBase(this);
		}

		if (lastStatus != StatusType::Running)
		{
			index = 0;
		}

		for (int i = index; i < children.size(); ++i)
		{
			if (playerBT->GetLastStatus() == StatusType::None)
			{
				lastStatus = children[i]->Tick(bt);
			}
			else
			{
				lastStatus = playerBT->GetLastStatus();
				playerBT->SetLastStatusNone();
			}

			if (lastStatus == StatusType::Running)
			{
				index = i;
				return lastStatus;
			}

			if (lastStatus == StatusType::Success)
			{
				index = 0;
				playerBT = nullptr;
				bt->PopBase(this);
				return lastStatus;
			}
		}

		index = 0;
		playerBT = nullptr;
		bt->PopBase(this);
		return lastStatus;
	}
};

class RandomNode : public BaseNode
{
public:
	BaseNode* child;
	int prob;
	bool allowed;

	RandomNode(int percent)
		: allowed(false)
		, child(nullptr)
	{
		if (percent > 100)
		{
			percent = 100;
		}
		else if (percent < 0)
		{
			percent = 0;
		}

		prob = percent;
	}

	~RandomNode()
	{
		delete child;
	}

	virtual void Print(int depth) override
	{
		for (int i = 0; i < depth; i++)
		{
			printf("    ");
		}
		printf("| Random(%d)\n", prob);

		child->Print(depth + 1);
	}

	virtual std::wstring GetNodeStatus() 
	{ 
		std::wstring str = L"Rand(";
		str += L"run:";
		str += std::to_wstring(allowed);
		str += L" last:";
		str += std::to_wstring((int)lastStatus);
		str += L")";
		return str; 
	}

	virtual void Reset() override
	{
		lastStatus = StatusType::Success;
		child->Reset();
	}

	virtual BaseNode* Clone(Player* player) override
	{
		RandomNode* node = new RandomNode(prob);
		node->child = child->Clone(player);
		return node;
	}

	virtual StatusType Tick(PlayerBT* bt) override
	{
		if (playerBT == nullptr)
		{
			playerBT = bt;
			bt->PushBase(this);
		}

		if (lastStatus != StatusType::Running)
		{
			allowed = (rand() % 100) < prob;
		}

		if (allowed)
		{
			if (playerBT->GetLastStatus() == StatusType::None)
			{
				lastStatus = child->Tick(bt);
			}
			else
			{
				lastStatus = playerBT->GetLastStatus();
				playerBT->SetLastStatusNone();
			}

			if (lastStatus != StatusType::Running)
			{
				playerBT = nullptr;
				bt->PopBase(this);
			}
			return lastStatus;
		}

		playerBT = nullptr;
		bt->PopBase(this);
		return lastStatus = StatusType::Failure;
	}
};

class RepeatUntilFailNode : public BaseNode
{
public:
	BaseNode* child;

	RepeatUntilFailNode()
		: child(nullptr)
	{
	}

	~RepeatUntilFailNode()
	{
		delete child;
	}

	virtual void Print(int depth) override
	{
		for (int i = 0; i < depth; i++)
		{
			printf("    ");
		}
		printf("| RepeatUntilFail\n");

		child->Print(depth + 1);
	}

	virtual std::wstring GetNodeStatus() 
	{ 
		std::wstring str = L"RepInf(";
		str += L"last:";
		str += std::to_wstring((int)lastStatus);
		str += L")";
		return str; 
	}

	virtual void Reset() override
	{
		lastStatus = StatusType::Success;
		child->Reset();
	}

	virtual BaseNode* Clone(Player* player) override
	{
		RepeatUntilFailNode* node = new RepeatUntilFailNode();
		node->child = child->Clone(player);
		return node;
	}

	virtual StatusType Tick(PlayerBT* bt) override
	{
		if (playerBT == nullptr)
		{
			playerBT = bt;
			bt->PushBase(this);
		}

		if (playerBT->GetLastStatus() == StatusType::None)
		{
			lastStatus = child->Tick(bt);
		}
		else
		{
			lastStatus = playerBT->GetLastStatus();
			playerBT->SetLastStatusNone();
		}

		if (lastStatus == StatusType::Running || lastStatus == StatusType::Success)
		{
			return StatusType::Running;
		}
		else
		{
			playerBT = nullptr;
			bt->PopBase(this);
			return StatusType::Failure;
		}
	}
};

class RepeatNode : public BaseNode
{
public:
	BaseNode* child;
	int count;
	int repeat;

	RepeatNode(int count)
		: count(count)
		, repeat(0)
		, child(nullptr)
	{
	}

	~RepeatNode()
	{
		delete child;
	}

	virtual void Print(int depth) override
	{
		for (int i = 0; i < depth; i++)
		{
			printf("    ");
		}
		printf("| Repeat(%d)\n", repeat);

		child->Print(depth + 1);
	}

	virtual std::wstring GetNodeStatus() 
	{ 
		std::wstring str = L"Rep(";
		str += L"cnt:";
		str += std::to_wstring(count);
		str += L" last:";
		str += std::to_wstring((int)lastStatus);
		str += L")";
		return str; 
	}

	virtual void Reset() override
	{
		repeat = 0;
		lastStatus = StatusType::Success;
		child->Reset();
	}

	virtual BaseNode* Clone(Player* player) override
	{
		RepeatNode* node = new RepeatNode(count);
		node->child = child->Clone(player);
		return node;
	}

	virtual StatusType Tick(PlayerBT* bt) override
	{
		if (playerBT == nullptr)
		{
			playerBT = bt;
			bt->PushBase(this);
		}

		if (playerBT->GetLastStatus() == StatusType::None)
		{
			lastStatus = child->Tick(bt);
		}
		else
		{
			lastStatus = playerBT->GetLastStatus();
			playerBT->SetLastStatusNone();
		}

		if (lastStatus == StatusType::Running)
		{
			return StatusType::Running;
		}
		else if (lastStatus == StatusType::Failure)
		{
			repeat = 0;
			playerBT = nullptr;
			bt->PopBase(this);
			return StatusType::Failure;
		}
		else // StatusType::Success
		{
			++repeat;
			if (repeat == count)
			{
				playerBT = nullptr;
				bt->PopBase(this);
				return StatusType::Success;
			}

			return lastStatus = StatusType::Running;
		}
	}
};

class CooldownNode : public BaseNode
{
public:
	BaseNode* child;
	uint64_t currTime;
	uint64_t lastTime;
	uint64_t allowedTime;

	CooldownNode(long long millisec)
		: allowedTime(millisec * 1000000)
		, lastTime(0)
		, child(nullptr)
	{
	}

	~CooldownNode()
	{
		delete child;
	}

	virtual void Print(int depth) override
	{
		for (int i = 0; i < depth; i++)
		{
			printf("    ");
		}
		printf("| Cooldown(%lld ms)\n", allowedTime / 1'000'000);

		child->Print(depth + 1);
	}

	virtual std::wstring GetNodeStatus() 
	{ 
		std::wstring str = L"Cool(";
		str += L"run:";
		str += std::to_wstring((int)(currTime - lastTime >= allowedTime));
		str += L"last:";
		str += std::to_wstring((int)lastStatus);
		str += L")";
		return str; 
	}

	virtual void Reset() override
	{
		lastTime = 0;
		lastStatus = StatusType::Success;
		child->Reset();
	}

	virtual BaseNode* Clone(Player* player) override
	{
		CooldownNode* node = new CooldownNode(allowedTime / 1'000'000);
		node->child = child->Clone(player);
		return node;
	}

	virtual StatusType Tick(PlayerBT* bt) override
	{
		if (playerBT == nullptr)
		{
			playerBT = bt;
			bt->PushBase(this);
		}

		currTime = CProfiler::GetNanoSec();
		if (currTime - lastTime < allowedTime)
		{
			playerBT = nullptr;
			bt->PopBase(this);
			return lastStatus = StatusType::Failure;
		}

		if (playerBT->GetLastStatus() == StatusType::None)
		{
			lastStatus = child->Tick(bt);
		}
		else
		{
			lastStatus = playerBT->GetLastStatus();
			playerBT->SetLastStatusNone();
		}

		if (lastStatus != StatusType::Running)
		{
			lastTime = CProfiler::GetNanoSec();
			playerBT = nullptr;
			bt->PopBase(this);
		}

		return lastStatus;
	}
};

class DelayNode : public BaseNode
{
public:
	uint64_t lastTime;
	uint64_t allowedTime;

	DelayNode(long long millisec)
		: allowedTime(millisec * 1'000'000)
		, lastTime(0)
	{
	}

	~DelayNode()
	{
	}

	virtual void Print(int depth) override
	{
		for (int i = 0; i < depth; i++)
		{
			printf("    ");
		}
		printf("| Delay(%lld ms)\n", allowedTime / 1'000'000);
	}

	virtual std::wstring GetNodeStatus() 
	{ 
		std::wstring str = L"Del(";
		str += L"last:";
		str += std::to_wstring((int)lastStatus);
		str += L")";
		return str; 
	}

	virtual void Reset() override
	{
		lastStatus = StatusType::Success;
		lastTime = 0;
	}

	virtual BaseNode* Clone(Player* player) override
	{
		return new DelayNode(allowedTime / 1'000'000);
	}

	virtual StatusType Tick(PlayerBT* bt) override
	{
		if (playerBT == nullptr)
		{
			playerBT = bt;
			bt->PushBase(this);
		}

		uint64_t now = CProfiler::GetNanoSec();

		if (lastStatus != StatusType::Running)
		{
			lastTime = now;
		}

		if (now - lastTime < allowedTime)
		{
			return lastStatus = StatusType::Running;
		}

		lastTime = now;

		playerBT = nullptr;
		bt->PopBase(this);
		return lastStatus = StatusType::Success;
	}
};
