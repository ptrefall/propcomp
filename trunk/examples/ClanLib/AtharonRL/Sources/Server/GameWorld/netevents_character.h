#pragma once

#include "character_manager.h"

class ServerPlayer;

class NetEventsCharacter
{
// Construction:
public:
	NetEventsCharacter(clan::SqliteConnection &db, CharacterManager &character_manager);

// Operations:
public:
	bool dispatch_net_event(const clan::NetGameEvent &event, ServerPlayer *player);

// Events:
private:
	void on_net_event_character_get_list(const clan::NetGameEvent &e, ServerPlayer *player);
	void on_net_event_character_login(const clan::NetGameEvent &e, ServerPlayer *player);
	void on_net_event_character_logout(const clan::NetGameEvent &e, ServerPlayer *player);
	void on_net_event_character_create(const clan::NetGameEvent &e, ServerPlayer *player);

// Implementation:
private:
	clan::NetGameEventDispatcher_v1<ServerPlayer *> netevents;

	CharacterManager &character_manager;
	clan::SqliteConnection &db;
};
