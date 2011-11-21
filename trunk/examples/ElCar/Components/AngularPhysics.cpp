/*Totem EDK
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

Note: Some of the libraries Totem EDK may link to may have additional
requirements or restrictions.
*/

#include "AngularPhysics.h"
#include <Entity.h>
#include "../../Common/EntityManager.h"

#include <iostream>

using namespace Components;
using namespace Totem;

AngularPhysics::AngularPhysics(Entity &owner, const T_String &name)
: Component(owner, name), forceAngularAccelerationEventId("FORCE_ANGULAR_ACCELERATION"), syncVelocityEventId("SYNC_VELOCITY")
{
    car_property = owner.addProperty<Entity*>("Car", NULL_PTR);
	angularVelocity_property = owner.addProperty<F32>("AngularVelocity", 0.0f);
	dimension_property = owner.addProperty<F32>("Dimension", 0.5f);
	friction_property = owner.addProperty<F32>("Friction", 0.01f);
	forces_property_list = owner.addPropertyList<F32>("AngularForces");

#if USE_TEMPLATE_EVENT_HANDLER
	owner.registerToEvent1<const F32&>(forceAngularAccelerationEventId).connect(this, &AngularPhysics::onForceAngularAccelerationEvent);
	owner.registerToEvent1<const F32&>(syncVelocityEventId).connect(this, &AngularPhysics::onSyncVelocityEvent);
#elif USE_ANY_EVENT_HANDLER
	owner.registerToEvent1(forceAngularAccelerationEventId).connect(this, &AngularPhysics::onForceAngularAccelerationEvent);
	owner.registerToEvent1(syncVelocityEventId).connect(this, &AngularPhysics::onSyncVelocityEvent);
#endif
}

AngularPhysics::~AngularPhysics()
{
}

void AngularPhysics::update(const F32 &deltaTime)
{
	if(car_property.get() == NULL_PTR ||  car_property.get()->hasProperty("Mass") == false)
		return;

	if(forces_property_list.empty())
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

#if USE_TEMPLATE_EVENT_HANDLER
void AngularPhysics::onForceAngularAccelerationEvent(const F32 &force)
{
#elif USE_ANY_EVENT_HANDLER
void AngularPhysics::onForceAngularAccelerationEvent(T_Any force_any)
{
	const F32 &force = force_any.cast<F32>();
#endif
	// We just sum up the forces acting on this Entity this frame
	forces_property_list.push_back(force);
}

#if USE_TEMPLATE_EVENT_HANDLER
void AngularPhysics::onSyncVelocityEvent(const F32 &velocity)
{
#elif USE_ANY_EVENT_HANDLER
void AngularPhysics::onSyncVelocityEvent(T_Any velocity_any)
{
	const F32 &velocity = velocity_any.cast<F32>();
#endif
	angularVelocity_property = velocity;
}
