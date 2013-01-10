
#include "precomp.h"
#include "looks.h"

using namespace Totem;
using namespace clan;

Looks::Looks(GameObject &owner, const std::string &name)
: Component<Looks>(name)
{
    looks_property = owner.add<int>("Looks", GOL_CHARACTER);
}

Looks::~Looks()
{
}
