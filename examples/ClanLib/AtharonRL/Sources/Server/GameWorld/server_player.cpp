#include "precomp.h"
#include "server_player.h"
#include "server_character.h"

using namespace clan;

ServerPlayer::ServerPlayer(SqliteConnection &db, int user_id, NetGameConnection *connection)
: db(db), connection(connection), user_id(user_id), character(0)
{
}

ServerPlayer::~ServerPlayer()
{
	delete character;
}

void ServerPlayer::send_event(const NetGameEvent &event)
{
	connection->send_event(event);
}

ServerCharacter *ServerPlayer::create_character(int character_id, const std::string &character_name, ServerGameObject *gameobject)
{
	character = new ServerCharacter(db, character_id, character_name, this, gameobject);

	return character;
}
