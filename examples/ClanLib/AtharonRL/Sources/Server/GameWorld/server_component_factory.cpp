#include "precomp.h"
#include "server_component_factory.h"
#include "server_gameobject.h"
//#include "Components/server_click_move_controller.h"
//#include "Components/server_first_person_move_controller.h"
//#include "Components/server_mesh_object.h"
//#include "Components/server_box_collider.h"
//#include "Components/server_trigger_display_text.h"
//#include "Engine/GameWorld/Components/trigger_transport.h"

using namespace Totem;
using namespace clan;

ServerComponentFactory::ServerComponentFactory()
{
}

void ServerComponentFactory::create_and_add_component(ServerGameObject *owner, const std::string &type, const std::string &name)
{
	/*if(type == ClickMoveController::getType())
	{
		owner->addComponent(std::make_shared<ServerClickMoveController>(owner, collision_world, name));
	}
	else if(type == FirstPersonMoveController::getType())
	{
		owner->addComponent(std::make_shared<ServerFirstPersonMoveController>(owner, collision_world, name));
	}
	else if(type == MeshObject::getType())
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
	}
	else
	{
		throw Exception("ServerComponentFactory::create_and_add_component - Unknown component type " + type);
	}*/
}
