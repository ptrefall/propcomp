/*Factotum EDK
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

Note: Some of the libraries Factotum EDK may link to may have additional
requirements or restrictions.
*/

#include "WheelMount.h"
#include "../../Common/EntityManager.h"

#include <iostream>

using namespace Components;

WheelMount::WheelMount(Entity &owner, const T_String &name)
: Component(owner, name), accelerateWheelsEventId("ACCELERATE_WHEELS"), syncVelocityEventId("SYNC_VELOCITY"), forceAngularAccelerationEventId("FORCE_ANGULAR_ACCELERATION")
{
	type_property = owner.addProperty<T_String>("Type", "");
    wheels_property_list = owner.addPropertyList<Entity*>("Wheels");
	activeWheelCount_property = owner.addProperty<U32>("ActiveWheelCount", 2); //Two wheels can accelerate by throttling by default
	velocity_property = owner.addProperty<F32>("Velocity", 0.0f);

	owner.registerToEvent1<F32>(accelerateWheelsEventId).connect(this, &WheelMount::onAccelerateWheelsEvent);
}

WheelMount::~WheelMount()
{
}

void WheelMount::update(const F32 &/*deltaTime*/)
{
	F32 avgVelocity = 0.0f;
	for(U32 i = 0; i < wheels_property_list.size(); i++)
	{
		if(wheels_property_list.get()[i]->hasProperty("AngularVelocity"))
			avgVelocity += wheels_property_list.get()[i]->getProperty<F32>("AngularVelocity").get();
	}
	avgVelocity /= wheels_property_list.size();
	velocity_property = avgVelocity;
	std::cout << type_property.get().c_str() << " velocity changed to " << avgVelocity << std::endl;

	//Now force all wheels to turn at same speed as the car
	for(U32 i = 0; i < wheels_property_list.size(); i++)
	{
		for(U32 i = 0; i < wheels_property_list.size(); i++)
			wheels_property_list.get()[i]->sendEvent1<F32>(syncVelocityEventId, avgVelocity);
	}
}

void WheelMount::onAccelerateWheelsEvent(const F32 &force)
{
	//Force wheels to spin
	for(U32 i = 0; i < wheels_property_list.size() && i < activeWheelCount_property.get(); i++)
		wheels_property_list.get()[i]->sendEvent1<F32>(forceAngularAccelerationEventId, force);
}
