
#include "precomp.h"
#include "server_visual.h"

using namespace Totem;
using namespace clan;

ServerVisual::ServerVisual(GameObject *owner, const std::string &name)
: Component<ServerVisual>(name)
{
	visual_property = owner->add<int>("Visual", GOV_CHARACTER);
}

ServerVisual::~ServerVisual()
{
}
