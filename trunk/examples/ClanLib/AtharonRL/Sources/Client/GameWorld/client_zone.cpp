#include "precomp.h"
#include "client_zone.h"
#include "client_vicinity_objects.h"
#include "client_component_factory.h"

using namespace clan;

ClientZone::ClientZone(UIScreen *screen, clan::NetGameClient &network, const LayerManagerPtr &layer_manager)
	: network(network)
{
	component_factory = std::make_shared<ClientComponentFactory>(screen, layer_manager);
	objects = std::make_shared<ClientVicinityObjects>(this, component_factory);
}

ClientZone::~ClientZone()
{
}

void ClientZone::tick(float time_elapsed)
{
	objects->update(time_elapsed);
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
