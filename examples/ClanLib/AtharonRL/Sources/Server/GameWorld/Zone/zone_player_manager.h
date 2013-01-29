#pragma once

//TODO: This class should replace a lot of player handling that currently happens in Zone.
//		Should replace std::map<ServerPlayer *, ZoneVicinity *> players, and implement all
//		current interactions Zone has with this map.

#include "zone_vicinity_objects.h"
#include "zone_vicinity_map.h"

class ServerPlayer;
class ServerGameObject;
class ServerGameObjectContainer;
class ZoneMap; typedef std::shared_ptr<ZoneMap> ZoneMapPtr;

class ZonePlayerManager
{
public:
	ZonePlayerManager();
	~ZonePlayerManager();

	ServerPlayer *find_player_with_gameobject(ServerGameObject *gameobject) const;

	void add_player(ServerPlayer *player, const ServerGameObjectContainer &gameobjects, const ZoneMapPtr &map);
	void remove_player(ServerPlayer *player);

	void update(float time_elapsed);

	void notify_players_object_added(ServerGameObject *gameobject);
	void notify_players_object_removed(ServerGameObject *gameobject);
	void notify_players_map_changed();

	void sync();
	void save();

private:
	struct ZoneVicinity
	{
		ZoneVicinityObjects *objects;
		ZoneVicinityMap *map;

		ZoneVicinity(ZoneVicinityMap *map, ZoneVicinityObjects *objects) : map(map), objects(objects) {}
		~ZoneVicinity() { delete map; delete objects; }
	};
	std::map<ServerPlayer *, ZoneVicinity *> players;
};