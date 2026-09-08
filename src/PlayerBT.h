#pragma once
#include <stack>
#include "Packet.h"
#include "Proxy.h"
#include "StatusType.h"

class LCRSNode;
class BaseNode;
struct FEnumValue;
class Player;

class PlayerBT
{
public:
	PlayerBT(BaseNode* root, Player* player);

	~PlayerBT();

	PlayerBT* Clone(Player* player);

	void Print();

	void Reset();

	bool Tick();

	void PushBase(BaseNode* node);

	void PopBase(BaseNode* node);

	void PrintStack();

	void PrintHistory();

	void RecordNode();

	void SetLastStatusNone();

	StatusType GetLastStatus() const;

	static FEnumValue GetType(const std::string id);

	static BaseNode* Parse(FEnumValue& value, LCRSNode* node);

private:
	unsigned int historyIndex;
	std::vector<BaseNode*> history;
	StatusType lastStatus;
	std::vector<BaseNode*> nodeStack;
	BaseNode* mainRoot;
};
