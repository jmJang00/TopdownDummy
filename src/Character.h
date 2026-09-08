// Character.h
#pragma once

#include <JNet/CSession.h>
#include "Packet.h"
#include "BaseNode.h"
#include <stdint.h>

class CGameContent;
class CollisionManager;
class CTickScheduler;
class EntityManager;
class Player;
class Proxy;
class CMatchPlayer;
class CAIBrain;
class CJPS;
class GridMap;

enum class Dir
{
	LL,
	LU,
	UU,
	RU,
	RR,
	RD,
	DD,
	LD
};

struct CharacterState
{
    Vector2 pos;
    Vector2 target;

    float currentAngle;
    float targetAngle;
};

class Character
{
public:
    constexpr static int LEAD_WINDOW = 14;
    constexpr static float DELTA_TIME = 0.05f;

    Character();
    ~Character();

    void SetDamage(int damage);

	void Spawn(
        int32_t id,
        GridMap* map,
		int tick);

    void SetPosition(const Vector2& spawnPos, const Vector2& target);
    void SetRotation(float angle, float targetAngle);

    void Despawn();

    bool IsActive();
    bool HasSpawnCompleted();
    bool WaitingServer() { return _waitingForServer; }
    int32_t GetId();
    Vector2 GetPosition();
    bool CanFire();
    float GetRotation();
    int GetCurrentTick();
    const CharacterState& GetState() const;
    bool CheckMapCollision(float x, float y, float radius) const;
    bool CircleVsCell(float cx, float cy, float radius, float cellX, float cellY) const;

    void AddMoveInput();
    void AddRotateInput();
    void AddTimeInput(int tick);

    void Simulate(unsigned int dt);

private:

	void Tick(int tick, float dt);
    void TickRotation(float dt);
    void TickMovement(float dt);

private:
    bool _active;
    bool _waitingForServer;
    bool _moveStarted = false;
    bool _rotateStarted = false;
    int _currentTick;
    int _serverTick;
    float _accum;
    bool _hasServerTick;

    int32_t _id;
    GridMap* _map;
    CharacterState _state;
    int _hp;
    int _lastFireTick;
    float _moveSpeed;
    float _rotateSpeed;
    float _stopThreshold;
    float _radius;
    int _fireDelayTick;
};