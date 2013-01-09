#include "precomp.h"
#include "client_zone.h"
#include "client_vicinity_objects.h"

ClientZone::ClientZone(UIScreen *screen, clan::NetGameClient &network)
	: network(network)
{
	//component_factory = std::make_shared<ClientComponentFactory>(screen);
	objects = std::make_shared<ClientVicinityObjects>(this, component_factory);
}

ClientZone::~ClientZone()
{
}
