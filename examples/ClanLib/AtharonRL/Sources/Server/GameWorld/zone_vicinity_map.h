#pragma once

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

// Implementation:
private:
	bool is_tile_in_visibility(const clan::Vec2i &position) const;

	Zone *zone;
	ZoneMapPtr map;
	ServerPlayer *player;
	clan::NetGameConnection *connection;

	std::vector<clan::Vec2i> visible_map_tiles;
};
