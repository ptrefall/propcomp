#include "precomp.h"
#include "player_manager.h"
#include "server_player.h"
#include "server_character.h"
#include "Database/database_users.h"
#include "Engine/Common/Network/netevents.h"
#include <algorithm>

using namespace clan;

/////////////////////////////////////////////////////////////////////////////
// Construction:

PlayerManager::PlayerManager(SqliteConnection &db)
: db(db)
{
}

PlayerManager::~PlayerManager()
{
	for (size_t i = 0; i < players.size(); i++)
		delete players[i];
	players.clear();
}

/////////////////////////////////////////////////////////////////////////////
// Attributes:

ServerPlayer *PlayerManager::find_player(int user_id) const
{
	for(size_t i = 0; i < players.size(); ++i)
	{
		if(players[i]->get_user_id() == user_id)
			return players[i];
	}
	return 0;
}

ServerPlayer *PlayerManager::find_player(NetGameConnection *connection) const
{
	for(size_t i = 0; i < players.size(); ++i)
	{
		if(players[i]->get_connection() == connection)
			return players[i];
	}
	return 0;
}

ServerPlayer *PlayerManager::find_player_with_character(int character_id) const
{
	for(size_t i = 0; i < players.size(); ++i)
	{
		if(players[i]->get_character()->get_id() == character_id)
			return players[i];
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Operations:

void PlayerManager::create_player(int user_id, NetGameConnection *connection)
{
	ServerPlayer *existing_player = find_player(user_id);
	if(existing_player)
		kick_player(existing_player, "You logged in from somewhere else");

	ServerPlayer *player = new ServerPlayer(db, user_id, connection);
	players.push_back(player);
}

void PlayerManager::kick_player(ServerPlayer *player, const std::string &reason)
{
	player->send_event(NetGameEvent(STC_LOGOUT, reason));

	remove_player(player);
}

void PlayerManager::remove_player(NetGameConnection *connection)
{
	ServerPlayer *player = find_player(connection);

	if(player)
		remove_player(player);
}

void PlayerManager::remove_player(ServerPlayer *player)
{
	std::vector<ServerPlayer *>::iterator it = std::find(players.begin(), players.end(), player);
	if (it != players.end())
		players.erase(it);

	if(player->get_character())
		player->get_character()->remove_from_zone();

	delete player;
}

/////////////////////////////////////////////////////////////////////////////
// Implementation:
