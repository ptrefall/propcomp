#include "precomp.h"
#include "zone.h"
#include "zone_map.h"
#include "Procedural/zone_architect.h"
#include "server_player.h"
#include "server_gameobject.h"
#include "server_character.h"
#include "Engine/Common/Network/netevents.h"

using namespace clan;

Zone::Zone(SqliteConnection &db, int zone_id, int gameobjects_container_id, int generation_seed)
: gameobjects(db, gameobjects_container_id), 
  zone_id(zone_id), 
  generation_seed(generation_seed)
{
	component_factory = std::make_shared<ServerComponentFactory>();

	gameobjects.load_from_database(component_factory);

	//We set up an empty 100x100 map, and then let the ZoneArchitect fill it with rooms and corridors!
	//TODO: Nothing is persisted, nor is the ZoneMap data synced to the client yet either :P Server-only so far!
	//		In addition, the architect spawns no game objects at this point. When we start dealing with that, then
	//		it probably needs to take in the component factory and the gameobjects list.
	map.reset(new ZoneMap(db, Vec2i(100,100)));
	ZoneArchitect architect(generation_seed);
	
	if(gameobjects.is_empty())
		architect.generate(map, true);
	else
		architect.generate(map, false);
}

/////////////////////////////////////////////////////////////////////////////
// Attributes:

int Zone::get_id() const
{
	return zone_id;
}

int Zone::get_generation_seed() const
{ 
	return generation_seed; 
}

ServerGameObject *Zone::find_gameobject(int gameobject_id) const
{
	return gameobjects.find(gameobject_id);
}

ServerPlayer *Zone::find_player_with_gameobject(ServerGameObject *gameobject) const
{
	std::map<ServerPlayer *, ZoneVicinity *>::const_iterator it;
	for(it = players.begin(); it != players.end(); ++it)
	{
		ServerPlayer *player = it->first;
		ServerCharacter *character = player->get_character();
		if(character->get_owner_gameobject() == gameobject)
			return player;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Operations:

void Zone::add_player(ServerPlayer *player)
{
	ZoneVicinityObjects *vicinity_objects = new ZoneVicinityObjects(this, player->get_connection());

	// TODO: For now just add all objects to visibility
	const std::vector<ServerGameObject *> &objects = gameobjects.get_all();
	for (std::vector<ServerGameObject *>::const_iterator it = objects.begin(); it != objects.end(); ++it)
		vicinity_objects->add_gameobject((*it));

	ZoneVicinityMap *vicinity_map = new ZoneVicinityMap(this, map, player, player->get_connection());
	ZoneVicinity *vicinity = new ZoneVicinity(vicinity_map, vicinity_objects);

	players[player] = vicinity;

	NetGameEvent zone_event(STC_ZONE);
	player->send_event(zone_event);
}

void Zone::remove_player(ServerPlayer *player)
{
	std::map<ServerPlayer *, ZoneVicinity *>::iterator it;
	it = players.find(player);
	if (it != players.end())
	{
		ZoneVicinity *vicinity = it->second;
		delete vicinity;
		players.erase(it);
	}
}

void Zone::add_gameobject(ServerGameObject *gameobject)
{
	if(gameobjects.add(gameobject))
	{
		notify_players_object_added(gameobject);
	}
}

void Zone::remove_gameobject(ServerGameObject *gameobject)
{
	if(gameobjects.remove(gameobject))
	{
		notify_players_object_removed(gameobject);
	}
}

void Zone::set_gameobject_inactive(ServerGameObject *gameobject)
{
	if(gameobjects.set_inactive(gameobject))
	{
		notify_players_object_removed(gameobject);
	}
}

void Zone::update()
{
	int ticks = tick_timer.update();
	for (int i = 0; i < ticks; i++)
		tick(tick_timer.get_tick_length());

//	static float total_time = 0;
//	total_time += time_elapsed;
	//	if(total_time > 10.0f)
	{
		sync_map();
		save_map();
		sync_gameobjects();
		save_gameobjects();
//		total_time = 0.0f;
	}
}

void Zone::tick(float time_elapsed)
{
	map->update(time_elapsed);
	gameobjects.update(time_elapsed);
}

ServerGameObject *Zone::load_gameobject(int gameobject_id)
{
	ServerGameObject *gameobject = gameobjects.load_gameobject_from_database(gameobject_id, component_factory);
	return gameobject;
}

/////////////////////////////////////////////////////////////////////////////
// Implementation:

void Zone::notify_players_object_added(ServerGameObject *gameobject)
{
	std::map<ServerPlayer *, ZoneVicinity *>::iterator it;
	for(it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityObjects *objects = it->second->objects;
		objects->add_gameobject(gameobject);
	}
}

void Zone::notify_players_object_removed(ServerGameObject *gameobject)
{
	std::map<ServerPlayer *, ZoneVicinity *>::iterator it;
	for(it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityObjects *objects = it->second->objects;
		objects->remove_gameobject(gameobject);
	}
}

void Zone::notify_players_map_changed()
{
	/*std::map<ServerPlayer *, ZoneVicinity *>::iterator it;
	for(it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityMap *map = it->second->map;
		map->
	}*/
}

void Zone::save_gameobjects()
{
	gameobjects.save_dirty_properties();
}

void Zone::sync_gameobjects()
{
	std::map<ServerPlayer *, ZoneVicinity *>::iterator it;
	for(it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityObjects *objects = it->second->objects;
		objects->sync_gameobjects();
	}

	for(it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityObjects *objects = it->second->objects;
		objects->clear_dirty_gameobjects();
	}
}

void Zone::save_map()
{
	map->save_dirty_tiles();
}

void Zone::sync_map()
{
	std::map<ServerPlayer *, ZoneVicinity *>::iterator it;
	for(it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityMap *vicinity_map = it->second->map;
		vicinity_map->sync_map();
	}

	for(it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityMap *vicinity_map = it->second->map;
		vicinity_map->clear_dirty_map();
	}
}
