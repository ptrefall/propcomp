#pragma once

#include "Engine/Server/GameWorld/map_tile_interface.h"

class ServerPlayer;
class Zone;
class ZoneMap; typedef std::shared_ptr<ZoneMap> ZoneMapPtr;

class ZoneVicinityMap
{
// Construction:
public:
	ZoneVicinityMap(Zone *zone, const ZoneMapPtr &map, ServerPlayer *player, clan::NetGameConnection *connection);
	~ZoneVicinityMap();

// Attributes:
public:

// Operations:
public:
	void update(float time_elapsed);
	void sync_map();
	void sync_map_clear_dirty();

	//Computes new list of visible tiles, and marks any newly discovered tiles
	//that is then stored in tile memory
	void compute_vicinity();

	//Checks whether this tile can be seen by the player
	bool is_in_vicinity(const clan::Vec2i &position) const;

	//Checks whether this tile has already been discovered by the player
	bool is_explored(const clan::Vec2i &position) const;

// Implementation:
private:
	bool valid(const clan::Vec2i &position) const;

	Zone *zone;
	ZoneMapPtr map;
	ServerPlayer *player;
	clan::NetGameConnection *connection;

	std::vector<IMapTilePtr> tile_memory; //Remember all tiles you've ever visited in this zone
	std::vector<IMapTilePtr> visible_tiles;	//List of all tiles currently in your vicinity
	std::vector<IMapTilePtr> new_visible_tiles; //List of all new tiles that you've never seen before
};
