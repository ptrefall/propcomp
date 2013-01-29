
#pragma once

class Player;

class NetworkReceiver
{
public:
	virtual bool dispatch_net_event(const clan::NetGameEvent &event, Player *player) = 0;
};
