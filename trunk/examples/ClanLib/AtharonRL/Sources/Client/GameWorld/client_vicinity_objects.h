#pragma once

class ClientGameObject;
class ClientZone;
class ClientComponentFactory;

class ClientVicinityObjects
{
// Construction:
public:
	ClientVicinityObjects(ClientZone *zone, std::shared_ptr<ClientComponentFactory> component_factory);
	~ClientVicinityObjects();

// Attributes:
public:
	ClientGameObject *find_gameobject(int id);

// Operations:
public:
	bool dispatch_net_event(const clan::NetGameEvent &event);

	void add_object(ClientGameObject *object);

	void update(float time_elapsed);

	void clear();

// Implementation:
private:
	void on_net_event_object_create(const clan::NetGameEvent &e);
	void on_net_event_object_destroy(const clan::NetGameEvent &e);
	void on_net_event_object_player_own(const clan::NetGameEvent &e);
	void on_net_event_object_event(const clan::NetGameEvent &e);

	std::vector<ClientGameObject *> visible_objects;

	clan::NetGameEventDispatcher_v0 netevents;

	int player_gameobject_id;

	ClientZone *zone;
	std::shared_ptr<ClientComponentFactory> component_factory;
};
