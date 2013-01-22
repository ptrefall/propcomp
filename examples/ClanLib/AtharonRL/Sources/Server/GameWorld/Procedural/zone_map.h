#pragma once

#include <libtcod.hpp>

class ServerPlayer;
class ZoneVicinityObjects;

class ZoneMap
{
public:
	ZoneMap(clan::SqliteConnection &db, const clan::Vec2i &size);
	~ZoneMap();

	void update(float time_elapsed);

	int get_width() const { return size.x; }
	int get_height() const { return size.y; }

	void set_properties(const clan::Vec2i &pos, bool transparent, bool walkable, bool architected = false);

	void add_player(ServerPlayer *player, ZoneVicinityObjects *vicinity_objects);
	void remove_player(ServerPlayer *player);

	bool is_in_fov_of(ServerPlayer *player, const clan::Vec2i &position) const;
	bool is_wall(const clan::Vec2i &position) const;
	bool is_explored_by(ServerPlayer *player, const clan::Vec2i &position) const;
	bool can_walk(ServerPlayer *player, const clan::Vec2i &position) const;

	void compute_fov_of(ServerPlayer *player) const;
	void compute_fov() const;

	unsigned int get_scent_of(ServerPlayer *player, const clan::Vec2i &position) const;

	void load_from_database();
	void save_dirty_tiles();

private:
	bool valid(const clan::Vec2i &position) const;
	unsigned int to_index(const clan::Vec2i &position) const;

	clan::Vec2i size;
	TCODMap *map;

	clan::SqliteConnection &db;

	//This needs to be modified to work per player...
	struct Tile 
	{
		bool explored; // has the player already seen this tile ?
		unsigned int scent; // amount of player scent on this cell
		Tile() : explored(false), scent(0) {}
	};

	struct PlayerMapInfo
	{
		Tile *tiles;
		TCODMap *map;
		ZoneVicinityObjects *vicinity_objects;

		PlayerMapInfo(const clan::Vec2i &size, const TCODMap *source_map, ZoneVicinityObjects *vicinity_objects)
		{
			tiles = new Tile[size.x*size.y];
			map = new TCODMap(size.x, size.y);
			map->copy(source_map);
			this->vicinity_objects = vicinity_objects;
		}

		~PlayerMapInfo()
		{
			delete[] tiles;
			delete map;
		}
	};
	std::map<ServerPlayer*, PlayerMapInfo*> player_map_info;

	std::vector<clan::Vec2i> dirty_tiles;
};
