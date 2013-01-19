#include "precomp.h"
#include "zone.h"
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
	std::map<ServerPlayer *, ZoneVicinityObjects *>::const_iterator it;
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

	players[player] = vicinity_objects;

	NetGameEvent zone_event(STC_ZONE);
	player->send_event(zone_event);
}

void Zone::remove_player(ServerPlayer *player)
{
	std::map<ServerPlayer *, ZoneVicinityObjects *>::iterator it;
	it = players.find(player);
	if (it != players.end())
	{
		ZoneVicinityObjects *vicinity_objects = it->second;
		delete vicinity_objects;
		players.erase(it);
	}
}

void Zone::add_gameobject(ServerGameObject *gameobject)
{
	if(gameobjects.add(gameobject))
	{
		gameobject->set_zone(this);

		notify_players_object_added(gameobject);
	}
}

void Zone::remove_gameobject(ServerGameObject *gameobject)
{
	if(gameobjects.remove(gameobject))
	{
		notify_players_object_removed(gameobject);

		gameobject->set_zone(0);
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
		sync_dirty_properties();
		save_dirty_properties();
//		total_time = 0.0f;
	}
}

void Zone::tick(float time_elapsed)
{
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
	std::map<ServerPlayer *, ZoneVicinityObjects *>::iterator it;
	for(it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityObjects *objects = it->second;
		objects->add_gameobject(gameobject);
	}
}

void Zone::notify_players_object_removed(ServerGameObject *gameobject)
{
	std::map<ServerPlayer *, ZoneVicinityObjects *>::iterator it;
	for(it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityObjects *objects = it->second;
		objects->remove_gameobject(gameobject);
	}
}

void Zone::save_dirty_properties()
{
	gameobjects.save_dirty_properties();
}

void Zone::sync_dirty_properties()
{
	std::map<ServerPlayer *, ZoneVicinityObjects *>::iterator it;
	for(it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityObjects *objects = it->second;
		objects->sync_gameobjects();
	}
}
