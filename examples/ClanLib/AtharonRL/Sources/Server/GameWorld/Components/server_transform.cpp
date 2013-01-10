
#include "precomp.h"
#include "server_transform.h"

using namespace Totem;
using namespace clan;

ServerTransform::ServerTransform(GameObject *owner, const std::string &name)
: Transform(owner, name)
{
}

ServerTransform::~ServerTransform()
{
}
