#pragma once

#include <memory>

class ServerMapTile; typedef std::shared_ptr<ServerMapTile> ServerMapTilePtr;

class ZoneMapTileGroup
{
public:
	ZoneMapTileGroup(const clan::Vec2i &position, const clan::Vec2i &size);
	~ZoneMapTileGroup();

	void add(const ServerMapTilePtr &tile);
	void add(const std::vector<ServerMapTilePtr> &tiles);
	void remove(const ServerMapTilePtr &tile);
};
