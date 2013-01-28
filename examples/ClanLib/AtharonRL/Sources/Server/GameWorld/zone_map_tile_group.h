#pragma once

#include <memory>
#include "Engine/Server/GameWorld/server_map_tile.h"

class ServerMapTile; typedef std::shared_ptr<ServerMapTile> ServerMapTilePtr;

class ZoneMapTileGroup
{
public:
	ZoneMapTileGroup(const clan::Vec2i &position, const clan::Vec2i &size);
	~ZoneMapTileGroup();

	void add(const ServerMapTilePtr &tile);
	void add(const std::vector<ServerMapTilePtr> &tiles);
	void remove(const ServerMapTilePtr &tile);

private:
	void calculate_bounds();

	std::string name;
	std::string prefab;

	std::vector<ServerMapTilePtr> data; //Should this be replaced by a ZoneMapTileContainer?

	clan::Point position;				//How is position defined? Center of tiles in the group? A corner?
	clan::Point bounds;					//This is the bounds of the tile group, and will need to be dynamic based on add/remove of tiles...
};
