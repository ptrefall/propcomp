#pragma once

class GameObject; typedef std::shared_ptr<GameObject> GameObjectPtr;
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

	void set_camera_target(const GameObjectPtr &camera_target) { this->camera_target = camera_target; }
	GameObjectPtr get_camera_target() const { return camera_target; }

	ClientZone &operator=(const ClientZone &rhs)
	{
		if(this == &rhs)
			return *this;

		objects = rhs.objects;
		component_factory = rhs.component_factory;
		network = rhs.network;
		camera_target = rhs.camera_target;
		return *this;
	}

private:
	std::shared_ptr<ClientVicinityObjects> objects;
	std::shared_ptr<ClientComponentFactory> component_factory;

	clan::NetGameClient &network;
	GameObjectPtr camera_target;
};