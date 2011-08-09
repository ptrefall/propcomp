/*Component-based Entity Engine
Copyright (c) 2009 Pål Trefall and Kenneth Gangstø

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Note: Some of the libraries Component-based Entity Engine may link to may have additional
requirements or restrictions.
*/

#include "LinearPhysics.h"
#include "../../Common/EntityManager.h"

#include <iostream>

using namespace Components;

LinearPhysics::LinearPhysics(Entity &owner, const T_String &name)
: Component(owner, name)
{
	velocity_property = owner.addProperty<F32>("Velocity", 0.0f);
	position_property = owner.addProperty<T_Vec3f>("Position", T_Vec3f(0.0f, 0.0f, 0.0f));
}

LinearPhysics::~LinearPhysics()
{
}

void LinearPhysics::update(const F32 &deltaTime)
{
	position_property += T_Vec3f(0.0f, 0.0f, velocity_property.get() * deltaTime);
	std::cout << owner.getType().c_str() << " moved to (" << position_property.get().x << ", " << position_property.get().y << ", " << position_property.get().z << ")" << std::endl;
}
