#pragma once

class ServerPlayer;

class NetEventsPlayer
{
// Construction:
public:
	NetEventsPlayer();

// Operations:
public:
	bool dispatch_net_event(const clan::NetGameEvent &event, ServerPlayer *player);

// Events:
private:
	void on_net_event_player_move(const clan::NetGameEvent &e, ServerPlayer *player);

// Implementation:
private:
	clan::NetGameEventDispatcher_v1<ServerPlayer *> netevents;
};
