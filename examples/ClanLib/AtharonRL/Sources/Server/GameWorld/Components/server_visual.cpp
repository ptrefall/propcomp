
#include "precomp.h"
#include "server_visual.h"

using namespace Totem;
using namespace clan;

ServerVisual::ServerVisual(GameObject *owner, const std::string &name)
: Visual(owner, name)
{
	replicate_property(visual_property);
	replicate_property(color_background_property);
	replicate_property(color_foreground_property);
}

ServerVisual::~ServerVisual()
{
}
