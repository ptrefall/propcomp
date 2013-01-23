#pragma once

class Zone;
class ServerGameObject;
class ServerPlayer;

class ServerCharacter
{
// Construction:
public:
	ServerCharacter(clan::SqliteConnection &db, int character_id, const std::string &character_name, ServerPlayer *player, ServerGameObject *gameobject);
	~ServerCharacter();

// Attributes:
public:
	ServerGameObject *get_owner_gameobject() const { return owner_gameobject; }

	int get_id() const { return character_id; }
	std::string get_name() const { return character_name; }

// Operations:
public:
	void move_to_zone(Zone *new_zone, bool set_start_position);
	void remove_from_zone();

	ServerCharacter &operator=(const ServerCharacter &rhs)
	{
		if(this == &rhs)
			return *this;

		player = rhs.player;
		character_id = rhs.character_id;
		zone = rhs.zone;
		character_name = rhs.character_name;
		owner_gameobject = rhs.owner_gameobject;
		db = rhs.db;
		return *this;
	}

// Implementation:
private:
	void set_owner_gameobject(ServerGameObject *gameobject);

	Zone *zone;
	ServerPlayer *player;

	int character_id;
	std::string character_name;

	ServerGameObject *owner_gameobject;

	clan::SqliteConnection &db;
};