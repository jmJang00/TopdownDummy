#pragma once

#include <stdint.h>
#include <vector>
#include <stdio.h>
#include "Packet.h"

struct Waypoint
{
    Vector2 position;

    int32_t firstLink;
    int32_t linkCount;
};

class GridMap
{
public:
    bool Load(const char* path)
    {
        FILE* fp = nullptr;

        fopen_s(&fp, path, "rb");

        if (fp == nullptr)
            return false;

        bool result = LoadInternal(fp);

        fclose(fp);

        return result;
    }

    inline bool IsBlocked(int32_t x, int32_t y) const
    {
        if ((uint32_t)x >= (uint32_t)_width ||
            (uint32_t)y >= (uint32_t)_height)
        {
            return true;
        }

        return _collision[y * _width + x] != 0;
    }

    inline uint8_t GetCell(int32_t x, int32_t y) const
    {
        if ((uint32_t)x >= (uint32_t)_width ||
            (uint32_t)y >= (uint32_t)_height)
        {
            return 1;
        }

        return _collision[y * _width + x];
    }

    inline int32_t GetWidth() const
    {
        return _width;
    }

    inline int32_t GetHeight() const
    {
        return _height;
    }

    inline const std::vector<Waypoint>& GetWaypoints() const
    {
        return _waypoints;
    }

    inline const std::vector<int32_t>& GetWaypointLinks() const
    {
        return _links;
    }

    inline const std::vector<Vector2>& GetSpawns() const
    {
        return _spawns;
    }

    inline const std::vector<uint8_t>& GetCollisionMap() const
    {
        return _collision;
    }

private:
    bool LoadInternal(FILE* fp)
    {
        if (fread(&_width, sizeof(int32_t), 1, fp) != 1)
            return false;

        if (fread(&_height, sizeof(int32_t), 1, fp) != 1)
            return false;

        if (_width <= 0 || _height <= 0)
            return false;

        int32_t cellCount = _width * _height;

        _collision.resize(cellCount);

        if (fread(
            _collision.data(),
            sizeof(uint8_t),
            cellCount,
            fp) != (size_t)cellCount)
        {
            return false;
        }

        // waypoint
		int32_t waypointCount = 0;

		if (fread(&waypointCount, sizeof(int32_t), 1, fp) != 1)
			return false;

		if (waypointCount < 0)
			return false;

		_waypoints.resize(waypointCount);

		for (int32_t i = 0; i < waypointCount; ++i)
		{
			Waypoint& wp = _waypoints[i];

			if (fread(&wp.position.x, sizeof(float), 1, fp) != 1)
				return false;

			if (fread(&wp.position.y, sizeof(float), 1, fp) != 1)
				return false;

			if (fread(&wp.firstLink, sizeof(int32_t), 1, fp) != 1)
				return false;

			if (fread(&wp.linkCount, sizeof(int32_t), 1, fp) != 1)
				return false;
		}


		int32_t totalLinkCount = 0;

		if (fread(&totalLinkCount, sizeof(int32_t), 1, fp) != 1)
			return false;

		if (totalLinkCount < 0)
			return false;

		_links.resize(totalLinkCount);

		if (fread(_links.data(), sizeof(int32_t), totalLinkCount, fp) != (size_t)totalLinkCount)
		{
			return false;
		}

        // spawn
        int32_t spawnCount = 0;

        if (fread(&spawnCount, sizeof(int32_t), 1, fp) != 1)
            return false;

        if (spawnCount < 0)
            return false;

        _spawns.resize(spawnCount);

        for (int32_t i = 0; i < spawnCount; ++i)
        {
            if (fread(&_spawns[i].x, sizeof(float), 1, fp) != 1)
                return false;

            if (fread(&_spawns[i].y, sizeof(float), 1, fp) != 1)
                return false;
        }

        return true;
    }

private:
    int32_t _width = 0;
    int32_t _height = 0;

    std::vector<uint8_t> _collision;
    std::vector<Waypoint> _waypoints;
	std::vector<int32_t> _links;
    std::vector<Vector2> _spawns;
};
