#include "precomp.h"
#include "client_component_factory.h"
#include "client_gameobject.h"
#include "Components/client_visual.h"
#include "Components/client_transform.h"

using namespace Totem;
using namespace clan;

ClientComponentFactory::ClientComponentFactory(UIScreen *screen, const LayerManagerPtr &layer_manager)
: screen(screen), layer_manager(layer_manager)
{
}

void ClientComponentFactory::create_and_add_component(ClientGameObject *owner, const std::string &type, const std::string &name)
{
	if(type == ClientVisual::getType())
	{
		owner->addComponent(std::make_shared<ClientVisual>(owner, name, layer_manager));
	}
	else if(type == ClientTransform::getType())
	{
		owner->addComponent(std::make_shared<ClientTransform>(owner, name));
	}
	else
	{
		throw Exception("ClientComponentFactory::create_and_add_component - Unknown component type " + type);
	}
}
