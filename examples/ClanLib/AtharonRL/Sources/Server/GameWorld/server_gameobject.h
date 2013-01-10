#pragma once

#include "Engine/Common/GameWorld/gameobject.h"

class ServerPlayer;
class Zone;

class ServerGameObject : public GameObject
{
// Construction:
public:
	ServerGameObject(int id, const std::string &name, clan::SqliteConnection &db);

	Zone *get_zone() const { return zone; }
	void set_zone(Zone *zone);

	void set_container_id(int container_id);
	void set_persist_changes(bool enable);

	void save_dirty_properties();

	void send_event(const clan::NetGameEvent &event, clan::NetGameConnection *player_connection);

	ServerGameObject &operator=(const ServerGameObject &rhs)
	{
		if(this == &rhs)
			return *this;

		container_id = rhs.container_id;
		persist_changes = rhs.persist_changes;
		zone = rhs.zone;
		slots = rhs.slots;
		db = rhs.db;
		return *this;
	}

private:
	void on_property_added(std::shared_ptr<Totem::IProperty> property);
	void on_property_removed(std::shared_ptr<Totem::IProperty> property);
	void on_component_added(std::shared_ptr<Totem::IComponent<>> component);
	void on_component_removed(std::shared_ptr<Totem::IComponent<>> component);

	int container_id;
	bool persist_changes;

	Zone *zone;

	clan::SlotContainer slots;
	clan::SqliteConnection &db;
};
