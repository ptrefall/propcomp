#pragma once

class ServerCharacter;
class ServerGameObject;

class ServerPlayer
{
// Construction:
public:
	ServerPlayer(clan::SqliteConnection &db, int user_id, clan::NetGameConnection *connection);
	~ServerPlayer();

// Attributes:
public:
	clan::NetGameConnection *get_connection() const { return connection; }

	int get_user_id() const { return user_id; }

	ServerCharacter *get_character() const { return character; }

// Operations:
public:
	ServerCharacter *create_character(int character_id, const std::string &character_name, ServerGameObject *gameobject);

	void send_event(const clan::NetGameEvent &event);

// Implementation:
private:
	clan::NetGameConnection *connection;
	clan::SqliteConnection &db;

	int user_id;

	ServerCharacter *character;
};
