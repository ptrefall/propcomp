
#include "precomp.h"
#include "visual.h"

using namespace Totem;
using namespace clan;

Visual::Visual(GameObject *owner, const std::string &name)
: Component<Visual>(name)
{
    visual_property = owner->add<int>("Visual", GOV_CHARACTER);
}
