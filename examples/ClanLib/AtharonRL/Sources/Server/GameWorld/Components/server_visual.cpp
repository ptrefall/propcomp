
#include "precomp.h"
#include "server_visual.h"

using namespace Totem;
using namespace clan;

ServerVisual::ServerVisual(GameObject *owner, const std::string &name)
: Visual(owner, name)
{
	replicate_property(visual_property);
}

ServerVisual::~ServerVisual()
{
}
