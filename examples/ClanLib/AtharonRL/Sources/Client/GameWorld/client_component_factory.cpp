#include "precomp.h"
#include "client_component_factory.h"
#include "client_gameobject.h"

using namespace Totem;
using namespace clan;

ClientComponentFactory::ClientComponentFactory(UIScreen *screen)
: screen(screen)
{
}

void ClientComponentFactory::create_and_add_component(ClientGameObject *owner, const std::string &type, const std::string &name)
{
	/*if(type == ClickMoveController::getType())
	{
		owner->addComponent(std::make_shared<ClientClickMoveController>(owner, screen, continent_view, name));
	}
	else if(type == FirstPersonMoveController::getType())
	{
		owner->addComponent(std::make_shared<ClientFirstPersonMoveController>(owner, screen, continent_view->get_collision_world(), name));
	}
	else if(type == MeshObject::getType())
	{
		owner->addComponent(std::make_shared<ClientMeshObject>(owner, continent_view, name));
	}
	else if(type == BoxCollider::getType())
	{
		owner->addComponent(std::make_shared<BoxCollider>(owner, continent_view->get_collision_world(), name));
	}
	else
	{
		throw Exception("ClientComponentFactory::create_and_add_component - Unknown component type " + type);
	}*/
}
