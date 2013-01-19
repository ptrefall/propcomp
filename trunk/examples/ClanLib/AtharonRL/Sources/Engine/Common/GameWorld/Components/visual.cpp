
#include "precomp.h"
#include "visual.h"

using namespace Totem;
using namespace clan;

Visual::Visual(GameObject *owner, const std::string &name)
: Component<Visual>(name)
{
	visual_property = owner->add<int>("Visual", GOV_CHARACTER);
	color_foreground_property = owner->add<clan::Colorf>("ColorForeground", Colorf::white);
	color_background_property = owner->add<clan::Colorf>("ColorBackground", Colorf::black);
}
