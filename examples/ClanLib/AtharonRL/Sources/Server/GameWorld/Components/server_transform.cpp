
#include "precomp.h"
#include "server_transform.h"

using namespace Totem;
using namespace clan;

ServerTransform::ServerTransform(GameObject *owner, const std::string &name)
: Component<ServerTransform>(name)
{
	position_property = owner->add<Vec2i>("Position", Vec2i(0,0));
}

ServerTransform::~ServerTransform()
{
}
