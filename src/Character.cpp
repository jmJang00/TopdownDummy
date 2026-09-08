// Character.cpp
#include "pch.h"
#include "Character.h"
#include "Player.h"
#include "Proxy.h"
#include "MathUtil.h"
#include "GridMap.h"

int gDeltaX[9] = { -1, -1, 0, 1, 1, 1, 0, -1, 0 };
int gDeltaY[9] = { 0, -1, -1, -1, 0, 1, 1, 1, 0 };
float gDeltaAngle[8] = { 0, 45, 90, 135, 180, -135, -90, -45};

Character::Character()
{
    _moveSpeed = 4.0f;
    _rotateSpeed = 270.0f;

    _stopThreshold = 0.05f;

    _radius = 0.3f;
    _hp = 0;
    _lastFireTick = 0;
    _fireDelayTick = 10;

    _state.pos = { 0, 0 };
    _state.target = { 0, 0 };

    _state.currentAngle = 0;
    _state.targetAngle = 0;
    _hasServerTick = false;

    _active = false;
    _accum = 0.f;
    _currentTick = 0;
    _serverTick = 0;
    _waitingForServer = false;
    _id = 0;
    _map = nullptr;
}

Character::~Character()
{
}

void Character::Spawn(
	int32_t id,
	GridMap* map, 
    int tick)
{
    _id = id;
    _map = map;
    _lastFireTick = tick;
    _hp = 150;
    _active = true;
    _waitingForServer = false;
    _currentTick = tick;
    _serverTick = tick;
    _accum = 0.f;
    _moveStarted = false;
    _rotateStarted = false;
}

void Character::SetPosition(const Vector2& spawnPos, const Vector2& target)
{
    _state.pos = spawnPos;
    _state.target = target;
    _moveStarted = true;
}

void Character::SetRotation(float angle, float targetAngle)
{
    _state.currentAngle = angle;
    _state.targetAngle = targetAngle;
    _rotateStarted = true;
}

void Character::Despawn()
{
    _active = false;
}

void Character::SetDamage(int damage)
{
    if (_hp > damage)
    {
		_hp -= damage;
    }
    else
    {
        _hp = 0;
    }

    if (_hp == 0)
    {
        Despawn();
    }
}

void Character::TickRotation(float dt)
{
	float diff = DeltaAngle(_state.currentAngle, _state.targetAngle);

    float maxStep = _rotateSpeed * dt;

    if (fabsf(diff) <= maxStep)
    {
        _state.currentAngle = _state.targetAngle;
    }
    else
    {
        _state.currentAngle += Sign(diff) * maxStep;
    }
}

void Character::TickMovement(float dt)
{
    Vector2 dir = _state.target - _state.pos; 

    float dist = Length(dir);

    if (dist < _stopThreshold)
    {
        _state.pos = _state.target;
        return;
    }

    float step = _moveSpeed * dt;

    Vector2 nextPos;

    if (dist <= step)
    {
        nextPos = _state.target;
    }
    else
    {
        nextPos = _state.pos + Normalize(dir) * step;
    }

    bool blocked = CheckMapCollision(nextPos.x, nextPos.y, _radius);

    if (!blocked)
    {
        _state.pos = nextPos;
    }
    else
    {
        _state.target = _state.pos;
    }
}

void Character::Tick(int tick, float dt)
{
    TickRotation(dt);

    TickMovement(dt);
}

bool Character::IsActive()
{
    return _active;
}

bool Character::HasSpawnCompleted()
{
    return _rotateStarted && _moveStarted;
}

int32_t Character::GetId()
{
    return _id;
}

Vector2 Character::GetPosition()
{
    return _state.pos;
}

bool Character::CanFire()
{
    return _currentTick >= _lastFireTick + _fireDelayTick;
}

float Character::GetRotation()
{
    return _state.currentAngle;
}

int Character::GetCurrentTick()
{
    return _currentTick;
}

const CharacterState& Character::GetState() const
{
    return _state;
}

bool Character::CheckMapCollision(float x, float y, float radius) const
{
    int32_t minX = (int32_t)floorf(x - radius);
    int32_t minY = (int32_t)floorf(y - radius);
    int32_t maxX = (int32_t)floorf(x + radius);
    int32_t maxY = (int32_t)floorf(y + radius);

    for (int32_t gy = minY; gy <= maxY; ++gy)
    {
        for (int32_t gx = minX; gx <= maxX; ++gx)
        {
            if (!_map->IsBlocked(gx, gy))
                continue;

            if (CircleVsCell(x, y, radius, (float)gx, (float)gy))
                return true;
        }
    }

    return false;
}

bool Character::CircleVsCell(float cx, float cy, float radius, float cellX, float cellY) const
{
    float nearestX = Clamp(cx, cellX, cellX + 1.0f);
    float nearestY = Clamp(cy, cellY, cellY + 1.0f);

    float dx = cx - nearestX;
    float dy = cy - nearestY;

    return (dx * dx + dy * dy) <= (radius * radius);
}

void Character::AddMoveInput()
{
    int startIdx = rand() % 8;
    for (int i = 0; i < 8; i++)
    {
        int dx = gDeltaX[(startIdx + i) % 8];
        int dy = gDeltaY[(startIdx + i) % 8];
        float targetX = _state.pos.x + dx;
        float targetY = _state.pos.y + dy;
        if (!CheckMapCollision(targetX, targetY, _radius))
        {
			_state.target.x = targetX;
            _state.target.y = targetY;
            break;
        }
    }
}

void Character::AddRotateInput()
{
	float angle = gDeltaAngle[rand() % 8];
    _state.targetAngle = angle;
}

void Character::AddTimeInput(int tick)
{
    if (!_hasServerTick)
    {
		_hasServerTick = true;
    }

    _serverTick = tick;
}

void Character::Simulate(unsigned int dt)
{
	if (!_hasServerTick)
	{
		return;
	}

	if (!_active)
	{
		return;
	}

	if (!_waitingForServer)
	{
		if (_currentTick >= _serverTick + LEAD_WINDOW)
		{
			_waitingForServer = true;
		}
	}
	else
	{
		// 서버가 충분히 따라왔는가?
		if (_serverTick >= _currentTick)
		{
			_waitingForServer = false;
		}
	}

	int diff = _serverTick - _currentTick;

	float scale = 1.0f;
	// 틱 차이가 너무 많이 나면 고정
	if (diff > 10)
	{
		_accum = diff * DELTA_TIME;
	}
	else
	{
		if (diff > 0)
		{
			if (diff >= 5)
				scale = ((float)6 / 3);
			else if (diff >= 3)
				scale = ((float)5 / 3);
			else if (diff >= 1)
				scale = ((float)4 / 3);
		}
		else if (diff < 0)
		{
			if (diff <= -7)
				scale = ((float)1 / 3);
			else if (diff <= -5)
				scale = ((float)2 / 3);
		}

		_accum += ((float)dt * 0.001f) * scale;
	}

	while (_accum >= DELTA_TIME)
	{
        _currentTick++;
		_accum -= DELTA_TIME;
        if (HasSpawnCompleted())
        {
			Tick(_currentTick, DELTA_TIME);
        }
	}
}

