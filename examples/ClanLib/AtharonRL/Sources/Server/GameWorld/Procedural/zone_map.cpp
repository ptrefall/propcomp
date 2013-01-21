#include "precomp.h"
#include "zone_map.h"
#include "../server_player.h"
#include "../server_character.h"
#include "../server_gameobject.h"

using namespace clan;

ZoneMap::ZoneMap(const clan::Vec2i &size)
	: size(size)
{
	map = new TCODMap(size.x, size.y);
}

ZoneMap::~ZoneMap()
{
	delete map;
}

bool ZoneMap::valid(const Vec2i &position) const
{
	if(position.x < 0 || position.y < 0 || position.x >= size.x || position.y >= size.y)
		return false;
	else
		return true;
}

unsigned int ZoneMap::to_index(const clan::Vec2i &position) const
{
	return position.y*size.x + position.x;
}

void ZoneMap::set_properties(const Vec2i &pos, bool transparent, bool walkable)
{
	map->setProperties(pos.x, pos.y, transparent, walkable);

	for(auto it = player_map_info.begin(); it != player_map_info.end(); ++it)
		it->second->map->setProperties(pos.x, pos.y, transparent, walkable);
}

void ZoneMap::add_player(ServerPlayer *player)
{
	if(player_map_info.find(player) != player_map_info.end())
		return;

	player_map_info[player] = new PlayerMapInfo(size, map);
}

void ZoneMap::remove_player(ServerPlayer *player)
{
	auto it = player_map_info.find(player);
	if(it == player_map_info.end())
		return;

	delete it->second;
	player_map_info.erase(it);
}

bool ZoneMap::is_in_fov_of(ServerPlayer *player, const clan::Vec2i &position) const
{
	if( !valid(position) )
		return false;

	auto it = player_map_info.find(player);
	if(it == player_map_info.end())
		return false;

	if(it->second->map->isInFov(position.x, position.y))
	{
		it->second->tiles[to_index(position)].explored = true;
		return true;
	}
	else
	{
		return false;
	}
}

bool ZoneMap::is_wall(const clan::Vec2i &position) const
{
	if( !valid(position) )
		return true;

	return !map->isWalkable(position.x, position.y);
}

bool ZoneMap::is_explored_by(ServerPlayer *player, const clan::Vec2i &position) const
{
	if( !valid(position) )
		return false;

	auto it = player_map_info.find(player);
	if(it == player_map_info.end())
		return false;

	return it->second->tiles[to_index(position)].explored;
}

bool ZoneMap::can_walk(const clan::Vec2i &position) const
{
	if( is_wall(position) )
		return false;

	//TODO: Iterate over list of all game objects and check for collisions...

	return true;
}

void ZoneMap::compute_fov_of(ServerPlayer *player) const
{
	auto it = player_map_info.find(player);
	if(it == player_map_info.end())
		return;

	auto character = player->get_character();
	if( character == nullptr )
		return;

	auto go = character->get_owner_gameobject();
	if( go == nullptr )
		return;

	Vec2i position = Vec2i(0,0);
	if(go->hasProperty("Position"))
		position = go->get<Vec2i>("Position").get();

	int radius = 0;
	if(go->hasProperty("ViewRadius"))
		radius = go->get<int>("ViewRadius").get();

	it->second->map->computeFov(position.x, position.y, radius, true, FOV_BASIC);

	if( go->hasProperty("ScentValue") == false )
		return;

	auto scent = go->get<unsigned int>("ScentValue").get();
	for(int x = 0; x < size.x; x++)
	{
		for(int y = 0; y < size.y; y++)
		{
			auto viewable_pos = Vec2i(x,y);
			if(is_in_fov_of(player, viewable_pos))
			{
				auto old_scent = get_scent_of(player, viewable_pos);
				auto distance = viewable_pos.distance(position);
				auto new_scent = scent - distance;
				if(new_scent > old_scent)
					it->second->tiles[to_index(viewable_pos)].scent = new_scent;
			}
		}
	}
}

unsigned int ZoneMap::get_scent_of(ServerPlayer *player, const clan::Vec2i &position) const
{
	if( !valid(position) )
		return 0;

	auto it = player_map_info.find(player);
	if(it == player_map_info.end())
		return 0;

	return it->second->tiles[to_index(position)].scent;
}
