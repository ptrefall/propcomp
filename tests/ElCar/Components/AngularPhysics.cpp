/*Component-based Entity Engine
Copyright (c) 2009 P�l Trefall and Kenneth Gangst�

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

#include "types_config.h"
#include "AngularPhysics.h"
#include "../EntityManager.h"

#include <iostream>

using namespace Components;

AngularPhysics::AngularPhysics(Entity &owner, const T_String &name)
: Component(owner, name)
{
    car_property = owner.addProperty<Entity*>("Car", NULL_PTR);
	angularVelocity_property = owner.addProperty<F32>("AngularVelocity", 0.0f);
	dimension_property = owner.addProperty<F32>("Dimension", 0.5f);
	friction_property = owner.addProperty<F32>("Friction", 0.01f);
	forces_property_list = owner.addPropertyList<F32>("AngularForces");
}

AngularPhysics::~AngularPhysics()
{
}

void AngularPhysics::update(F32 deltaTime)
{
	if(car_property.get() == NULL_PTR ||  car_property.get()->hasProperty("Mass") == false)
		return;

	F32 sumForces = 0.0f;
	for(U32 i = 0; i < forces_property_list.size(); i++)
		sumForces += forces_property_list.get()[i];
	forces_property_list.clear();

	//We don't care enough to go through the hassle of calculating actual angular physics,
	//just do it linearly...
	F32 mass = car_property.get()->getProperty<F32>("Mass").get();
	F32 acceleration = sumForces / mass;
	angularVelocity_property = angularVelocity_property.get() + acceleration * deltaTime;
}

void AngularPhysics::onEvent(const T_Event &event)
{
	//If some force has forced the entity to spin
	if(event.type == "FORCE_ANGULAR_ACCELERATION")
	{
		// We just sum up the forces acting on this entity this frame
		forces_property_list.add(event.arg0.f);
	}
}
