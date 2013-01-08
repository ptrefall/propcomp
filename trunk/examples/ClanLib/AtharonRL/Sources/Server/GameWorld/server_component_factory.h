#pragma once

class ServerGameObject;

class ServerComponentFactory
{
public:
	ServerComponentFactory();

	void create_and_add_component(ServerGameObject *owner, const std::string &type, const std::string &name);
};
