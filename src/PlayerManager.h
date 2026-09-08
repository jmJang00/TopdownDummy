#pragma once
#include <unordered_map>
#include <JNet/CSession.h>

struct DummyAccountInfo;
class Player;
class CLogicThread;
class PlayerBT;

template <typename T>
class CFreeList;

typedef std::unordered_map<unsigned long long, Player*> player_list;

class PlayerManager
{
public:
	PlayerManager(CLogicThread* obj);

	~PlayerManager();

	Player* FindPlayer(unsigned long long accountNo);

	Player* AddPlayer(DummyAccountInfo* info, PlayerBT* bt, CLogicThread* thread);

	void Clear();

	int GetPlayerCount()
	{
		return _numPlayers;
	}

	void RemovePlayer(Player* player);

	void Update(unsigned int time);

	CLogicThread* _connector;
	CFreeList<Player>* _pool;
	player_list _playerList;
	int _numPlayers;
};
