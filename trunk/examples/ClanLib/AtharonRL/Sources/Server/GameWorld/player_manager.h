#pragma once

class ServerPlayer;

class PlayerManager
{
// Construction:
public:
	PlayerManager(clan::SqliteConnection &db);
	~PlayerManager();

// Attributes:
public:
	ServerPlayer *find_player(int user_id) const;
	ServerPlayer *find_player(clan::NetGameConnection *connection) const;
	ServerPlayer *find_player_with_character(int character_id) const;

	const std::vector<ServerPlayer *> &get_players() const { return players; }

// Operations:
public:
	void create_player(int user_id, clan::NetGameConnection *connection);
	void remove_player(clan::NetGameConnection *connection);
	void remove_player(ServerPlayer *player);
	void kick_player(ServerPlayer *player, const std::string &reason);

// Implementation:
private:
	std::vector<ServerPlayer *> players;

	clan::SqliteConnection &db;
};
