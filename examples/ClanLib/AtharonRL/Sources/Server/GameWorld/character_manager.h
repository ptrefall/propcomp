#pragma once

#include "zone_manager.h"

class ServerPlayer;

class CharacterManager
{
// Construction:
public:
	CharacterManager(clan::SqliteConnection &db, ZoneManager &zone_manager);

// Operations:
public:
	void login_character(int character_id, ServerPlayer *player);

	int create_character(int user_id, const std::string &character_name);

// Implementation:
private:
	void initialize_character(int character_id, ServerPlayer *player);

	clan::SqliteConnection &db;
	ZoneManager &zone_manager;
};
