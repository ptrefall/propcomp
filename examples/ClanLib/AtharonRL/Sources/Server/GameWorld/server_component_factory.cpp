#include "precomp.h"
#include "server_component_factory.h"
#include "server_gameobject.h"
#include "Components/server_visual.h"
#include "Components/server_transform.h"

using namespace Totem;
using namespace clan;

ServerComponentFactory::ServerComponentFactory()
{
}

void ServerComponentFactory::create_and_add_component(ServerGameObject *owner, const std::string &type, const std::string &name)
{
	if(type == ServerVisual::getType())
	{
		owner->addComponent(std::make_shared<ServerVisual>(owner, name));
	}
	else if(type == ServerTransform::getType())
	{
		owner->addComponent(std::make_shared<ServerTransform>(owner, name));
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
