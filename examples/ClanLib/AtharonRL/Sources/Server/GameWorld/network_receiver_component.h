
#pragma once

class ServerPlayer;

class NetworkReceiverComponent
{
public:
	virtual bool dispatch_net_event(const clan::NetGameEvent &event, ServerPlayer *player) = 0;
};
