#pragma once

#include "Packet.h"
#include <math.h>

inline Vector2 operator+(const Vector2& a, const Vector2& b)
{
    return { a.x + b.x, a.y + b.y };
}

inline Vector2 operator-(const Vector2& a, const Vector2& b)
{
    return { a.x - b.x, a.y - b.y };
}

inline Vector2 operator*(const Vector2& v, float s)
{
    return { v.x * s, v.y * s };
}

inline float Dot(const Vector2& a, const Vector2& b)
{
    return a.x * b.x + a.y * b.y;
}

inline float LengthSq(const Vector2& v)
{
    return Dot(v, v);
}

inline float Length(const Vector2& v)
{
    return sqrtf(LengthSq(v));
}

inline Vector2 Normalize(const Vector2& v)
{
    float len = Length(v);

    if (len <= 0.00001f) return { 0, 0 };

    float inv = 1.0f / len;

    return { v.x * inv, v.y * inv };
}

inline float NormalizeAngle(float angle)
{
	angle = fmodf(angle, 360.0f);

	if (angle > 180.0f)
		angle -= 360.0f;
	else if (angle < -180.0f)
		angle += 360.0f;

	return angle;
}

inline float DeltaAngle(float current, float target)
{
    float delta = fmodf(target - current, 360.0f);

    if (delta > 180.0f)
        delta -= 360.0f;
    else if (delta < -180.0f)
        delta += 360.0f;

    return delta;
}

inline float Sign(float v)
{
    return v >= 0.0f ? 1.0f : -1.0f;
}

constexpr float PI = 3.14159265359f;

inline float Deg2Rad(float deg)
{
    return deg * (PI / 180.0f);
}

inline float Rad2Deg(float rad)
{
    return rad * (180.0f / PI);
}

inline Vector2 Rotate(const Vector2& v, const Vector2& dir)
{
    Vector2 r;

    r.x = v.x * dir.x - v.y * dir.y;
    r.y = v.x * dir.y + v.y * dir.x;

    return r;
}

inline Vector2 DirectionFromDegree(float degree)
{
    float rad = Deg2Rad(degree);
    return Vector2{ cosf(rad), sinf(rad) };
}

inline float DegreeFromDirection(const Vector2& dir)
{
    float angle = atan2f(dir.y, dir.x);
    return NormalizeAngle(Rad2Deg(angle));
}

inline float Distance(const Vector2& v, const Vector2& w)
{
    Vector2 d;
    d.x = v.x - w.x;
    d.y = v.y - w.y;
    return Length(d);
}

inline float Clamp(float v, float min, float max)
{
    if (v < min)
        return min;

    if (v > max)
        return max;

    return v;
}
