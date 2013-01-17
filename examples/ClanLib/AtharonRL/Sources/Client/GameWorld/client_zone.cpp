#include "precomp.h"
#include "client_zone.h"
#include "client_vicinity_objects.h"
#include "client_component_factory.h"
#include "client_camera.h"
#include "client_gameobject.h"
#include "Engine/Client/Scene/layer_manager.h"
#include "Engine/Client/Scene/layer.h"

using namespace clan;

ClientZone::ClientZone(UIScreen *screen, clan::NetGameClient &network, const LayerManagerPtr &layer_manager)
	: network(network), layer_manager(layer_manager)
{
	component_factory = std::make_shared<ClientComponentFactory>(screen, this, layer_manager);
	objects = std::make_shared<ClientVicinityObjects>(this, component_factory);
	camera = std::make_shared<ClientCamera>();
}

ClientZone::~ClientZone()
{
}

void ClientZone::tick(float time_elapsed)
{
	objects->update(time_elapsed);
	if(camera_target && camera_target->hasProperty("Position"))
		camera->set_position(camera_target->get<Vec2i>("Position").get());

	sig_draw().invoke(camera);
}

bool ClientZone::dispatch_net_event(const NetGameEvent &event)
{
//	cl_log_event("Game", "Event: %1", event.to_string());

	return objects->dispatch_net_event(event);
}

void ClientZone::send_event(const NetGameEvent &event)
{
	network.send_event(event);
}
