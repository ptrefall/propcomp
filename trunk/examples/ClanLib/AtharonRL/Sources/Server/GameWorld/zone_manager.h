#pragma once

class Zone;
class ServerPlayer;
class ServerGameObject;

class ZoneManager
{
public:
	ZoneManager(clan::SqliteConnection &db);
	~ZoneManager();

	ServerGameObject *find_gameobject(int gameobject_id) const;

	Zone *get_or_load_zone(int zone_id);

	void update();

	bool dispatch_net_event(const clan::NetGameEvent &event, ServerPlayer *player);

	ZoneManager &operator=(const ZoneManager &rhs)
	{
		if(this == &rhs)
			return *this;

		zones = rhs.zones;
		netevents = rhs.netevents;
		db = rhs.db;
		return *this;
	}

private:
	Zone *find_zone(int zone_id);
	Zone *load_zone(int zone_id);

	void on_net_event_object_event(const clan::NetGameEvent &e, ServerPlayer *player);

	clan::SqliteConnection &db;

	std::vector<Zone *> zones;

	clan::NetGameEventDispatcher_v1<ServerPlayer *> netevents;
};
