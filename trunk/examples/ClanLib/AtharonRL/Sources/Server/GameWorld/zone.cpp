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
	map.reset(new ZoneMap(db, Vec2i(40,40)));
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
	return players.find_player_with_gameobject(gameobject);
}

/////////////////////////////////////////////////////////////////////////////
// Operations:

void Zone::add_player(ServerPlayer *player)
{
	players.add_player(player, gameobjects, map);
}

void Zone::remove_player(ServerPlayer *player)
{
	players.remove_player(player);
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
		players.sync();
		save();
//		total_time = 0.0f;
	}
}

void Zone::tick(float time_elapsed)
{
	//map->update(time_elapsed);
	players.update(time_elapsed);
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
	players.notify_players_object_added(gameobject);
}

void Zone::notify_players_object_removed(ServerGameObject *gameobject)
{
	players.notify_players_object_removed(gameobject);
}

void Zone::notify_players_map_changed()
{
	players.notify_players_map_changed();
}

void Zone::save()
{
	//map->save_dirty_tiles();
	gameobjects.save_dirty_properties();
	players.save();
}
