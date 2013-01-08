#pragma once

//#include "Engine/CollisionWorld/collision_world.h"

class ServerGameObject;
//class ContinentView;

class ServerComponentFactory
{
public:
	ServerComponentFactory(/*CollisionWorld collision_world*/);

	void create_and_add_component(ServerGameObject *owner, const std::string &type, const std::string &name);

private:
	//CollisionWorld collision_world;
	//ContinentView *continent_view;
};
