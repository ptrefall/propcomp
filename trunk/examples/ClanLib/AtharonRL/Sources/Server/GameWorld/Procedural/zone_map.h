#pragma once

#include <libtcod.hpp>

class ServerPlayer;

class ZoneMap
{
public:
	ZoneMap(const clan::Vec2i &size);
	~ZoneMap();

	int get_width() const { return size.x; }
	int get_height() const { return size.y; }

	void set_properties(const clan::Vec2i &pos, bool transparent, bool walkable);

	void add_player(ServerPlayer *player);
	void remove_player(ServerPlayer *player);

	bool is_in_fov_of(ServerPlayer *player, const clan::Vec2i &position) const;
	bool is_wall(const clan::Vec2i &position) const;
	bool is_explored_by(ServerPlayer *player, const clan::Vec2i &position) const;
	bool can_walk(const clan::Vec2i &position) const;

	void compute_fov_of(ServerPlayer *player) const;

	unsigned int get_scent_of(ServerPlayer *player, const clan::Vec2i &position) const;

private:
	bool valid(const clan::Vec2i &position) const;
	unsigned int to_index(const clan::Vec2i &position) const;

	clan::Vec2i size;
	TCODMap *map;

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

		PlayerMapInfo(const clan::Vec2i &size, const TCODMap *source_map)
		{
			tiles = new Tile[size.x*size.y];
			map = new TCODMap(size.x, size.y);
			map->copy(source_map);
		}

		~PlayerMapInfo()
		{
			delete[] tiles;
			delete map;
		}
	};
	std::map<ServerPlayer*, PlayerMapInfo*> player_map_info;
};
