
#include "precomp.h"
#include "transform.h"

using namespace Totem;
using namespace clan;


Transform::Transform(GameObject *owner, const std::string &name)
: Component<Transform>(name)
{
    position_property = owner->add<Vec2i>("Position", Vec2i(0,0));
}
