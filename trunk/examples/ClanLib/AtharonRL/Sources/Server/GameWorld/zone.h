#pragma once

#include "zone_vicinity_objects.h"
#include "zone_vicinity_map.h"
#include "server_gameobject_container.h"
#include "server_component_factory.h"
#include "Engine/Common/GameWorld/tick_timer.h"

class ServerPlayer;
class ServerGameObject;
class ZoneMap; typedef std::shared_ptr<ZoneMap> ZoneMapPtr;

class Zone
{
// Construction:
public:
	Zone(clan::SqliteConnection &db, int zone_id, int gameobjects_container_id, int generation_seed);

// Attributes:
public:
	int get_id() const;
	int get_generation_seed() const;

	ServerGameObject *find_gameobject(int gameobject_id) const;
	ServerPlayer *find_player_with_gameobject(ServerGameObject *gameobject) const;

// Operations:
public:
	void add_player(ServerPlayer *player);
	void remove_player(ServerPlayer *player);

	void add_gameobject(ServerGameObject *gameobject);
	void remove_gameobject(ServerGameObject *gameobject);
	void set_gameobject_inactive(ServerGameObject *gameobject);

	void update();

	void send_event(const clan::NetGameEvent &event);

	ServerGameObject *load_gameobject(int gameobject_id);

private:
	void tick(float time_elapsed);

	void notify_players_object_added(ServerGameObject *gameobject);
	void notify_players_object_removed(ServerGameObject *gameobject);
	void notify_players_map_changed();

	void sync();
	void save();

	ServerGameObjectContainer gameobjects;

	struct ZoneVicinity
	{
		ZoneVicinityObjects *objects;
		ZoneVicinityMap *map;

		ZoneVicinity(ZoneVicinityMap *map, ZoneVicinityObjects *objects) : map(map), objects(objects) {}
		~ZoneVicinity() { delete map; delete objects; }
	};
	std::map<ServerPlayer *, ZoneVicinity *> players;

	std::shared_ptr<ServerComponentFactory> component_factory;

	int zone_id;
	int generation_seed;
	ZoneMapPtr map;

	TickTimer tick_timer;
};
