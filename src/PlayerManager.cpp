#include "pch.h"
#include <JCore/CFreeList.h>
#include <JCore/DebugTypeRegistry.h>
#include "PlayerManager.h"
#include "Player.h"
#include "DummyClient.h"
#include "CLogicThread.h"
#include "PlayerBT.h"
#include "AccountReader.h"

PlayerManager::PlayerManager(CLogicThread* obj)
{
	_connector = obj;
	_pool = new CFreeList<Player>("Player", false);
	_numPlayers = 0;
}

PlayerManager::~PlayerManager()
{
	delete _pool;
}

Player* PlayerManager::FindPlayer(unsigned long long accountNo)
{
	player_map::iterator iter = _playerList.find(accountNo);
	if (iter == _playerList.end())
	{
		return nullptr;
	}

	return iter->second;
}

Player* PlayerManager::AddPlayer(DummyAccountInfo* info, PlayerBT* templateBT, CLogicThread* thread)
{
	++_numPlayers;

	Player* player = _pool->Alloc();
	if (player->_bt != nullptr)
	{
		delete player->_bt;
	}

	PlayerBT* newBt = templateBT->Clone(player);
	player->Init(thread, newBt, info->accountNo, info->id, info->nickname, info->sessionKey);
	_playerList.insert({ info->accountNo, player });

	return player;
}

void PlayerManager::RemovePlayer(Player* player)
{
	--_numPlayers;

	_playerList.erase(player->_accountNo);
	_pool->Free(player);
}

void PlayerManager::Clear()
{
	while (_playerList.size())
	{
		RemovePlayer(_playerList.begin()->second);
	}
}

void PlayerManager::Update(unsigned int time)
{
	for (auto iter = _playerList.begin(); iter != _playerList.end(); ++iter)
	{
		Player* player = iter->second;
		player->Update(time);
	}
}
