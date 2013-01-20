#pragma once

class ServerGameObject;
class Zone;

class ZoneVicinityObjects
{
// Construction:
public:
	ZoneVicinityObjects(Zone *zone, clan::NetGameConnection *connection);
	~ZoneVicinityObjects();

// Attributes:
public:
	ServerGameObject *find(int id) const;

// Operations:
public:
	void sync_gameobjects();
	void sync_gameobjects_clear_dirty();

	void gameobject_position_changed(ServerGameObject *gameobject);
	void add_gameobject(ServerGameObject *gameobject);
	void remove_gameobject(ServerGameObject *gameobject);

// Implementation:
private:
	void add_visible_object(ServerGameObject *object);
	void remove_visible_object(ServerGameObject *object);
	bool is_object_in_visibility(ServerGameObject *gameobject) const;

	Zone *zone;

	clan::NetGameConnection *connection;

	std::vector<ServerGameObject *> visible_objects;
};
