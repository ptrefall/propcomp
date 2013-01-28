#include "precomp.h"
#include "server_player_container.h"
#include "server_player.h"
#include "server_character.h"
#include "server_gameobject.h"
#include "server_gameobject_container.h"
#include "Engine/Common/Network/netevents.h"

using namespace clan;

ServerPlayerContainer::ServerPlayerContainer()
{
}

ServerPlayerContainer::~ServerPlayerContainer()
{
}

ServerPlayer *ServerPlayerContainer::find_player_with_gameobject(ServerGameObject *gameobject) const
{
	for(auto it = players.begin(); it != players.end(); ++it)
	{
		ServerPlayer *player = it->first;
		ServerCharacter *character = player->get_character();
		if(character->get_owner_gameobject() == gameobject)
			return player;
	}
	return nullptr;
}

void ServerPlayerContainer::add_player(ServerPlayer *player, const ServerGameObjectContainer &gameobjects, const ZoneMapPtr &map)
{
	ZoneVicinityObjects *vicinity_objects = new ZoneVicinityObjects(player->get_connection());

	// TODO: For now just add all objects to visibility
	const std::vector<ServerGameObject *> &objects = gameobjects.get_all();
	for (auto it = objects.begin(); it != objects.end(); ++it)
		vicinity_objects->add_gameobject((*it));

	ZoneVicinityMap *vicinity_map = new ZoneVicinityMap(map, player, player->get_connection());
	ZoneVicinity *vicinity = new ZoneVicinity(vicinity_map, vicinity_objects);

	players[player] = vicinity;

	NetGameEvent zone_event(STC_ZONE);
	player->send_event(zone_event);
}

void ServerPlayerContainer::remove_player(ServerPlayer *player)
{
	auto it = players.find(player);
	if (it != players.end())
	{
		ZoneVicinity *vicinity = it->second;
		delete vicinity;
		players.erase(it);
	}
}

void ServerPlayerContainer::update(float time_elapsed)
{
	for(auto it = players.begin(); it != players.end(); ++it)
	{
		it->second->map->update(time_elapsed);
	}
}

void ServerPlayerContainer::notify_players_object_added(ServerGameObject *gameobject)
{
	for(auto it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityObjects *objects = it->second->objects;
		objects->add_gameobject(gameobject);
	}
}

void ServerPlayerContainer::notify_players_object_removed(ServerGameObject *gameobject)
{
	for(auto it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityObjects *objects = it->second->objects;
		objects->remove_gameobject(gameobject);
	}
}

void ServerPlayerContainer::notify_players_map_changed()
{
	/*for(auto it = players.begin(); it != players.end(); ++it)
	{
		ZoneVicinityMap *map = it->second->map;
		map->
	}*/
}

void ServerPlayerContainer::save()
{
}

void ServerPlayerContainer::sync()
{
	//Sync map
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

	//Sync gameobjects
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
}
