#pragma once

class GameObject;
class UIScreen;
class ClientVicinityObjects;
class ClientComponentFactory;

class ClientZone
{
public:
	ClientZone(UIScreen *screen, clan::NetGameClient &network);
	~ClientZone();

	void tick(float time_elapsed);

	bool dispatch_net_event(const clan::NetGameEvent &event);
	void send_event(const clan::NetGameEvent &event);

private:
	std::shared_ptr<ClientVicinityObjects> objects;
	std::shared_ptr<ClientComponentFactory> component_factory;

	clan::NetGameClient &network;
};