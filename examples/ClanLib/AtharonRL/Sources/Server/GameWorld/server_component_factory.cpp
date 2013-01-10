#include "precomp.h"
#include "server_component_factory.h"
#include "server_gameobject.h"
#include "Engine/Common/GameWorld/Components/visual.h"
#include "Engine/Common/GameWorld/Components/transform.h"

using namespace Totem;
using namespace clan;

ServerComponentFactory::ServerComponentFactory()
{
}

void ServerComponentFactory::create_and_add_component(ServerGameObject *owner, const std::string &type, const std::string &name)
{
	if(type == Visual::getType())
	{
		owner->addComponent(std::make_shared<Visual>(owner, name));
	}
	else if(type == Transform::getType())
	{
		owner->addComponent(std::make_shared<Transform>(owner, name));
	}
	/*else if(type == MeshObject::getType())
	{
		owner->addComponent(std::make_shared<ServerMeshObject>(owner, name));
	}
	else if(type == BoxCollider::getType())
	{
		owner->addComponent(std::make_shared<ServerBoxCollider>(owner, collision_world, name));
	}
	else if(type == TriggerDisplayText::getType())
	{
		owner->addComponent(std::make_shared<ServerTriggerDisplayText>(owner, name));
	}*/
	else
	{
		throw Exception("ServerComponentFactory::create_and_add_component - Unknown component type " + type);
	}
}
