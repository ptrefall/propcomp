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

#include "Throttle.h"
#include <Entity.h>

#include <iostream>

using namespace Components;
using namespace Totem;

Throttle::Throttle(Entity &owner, const T_String &name)
: Component(owner, name), throttleEventId("THROTTLE"), spendEffectEventId("SPEND_EFFECT"), accelerateWheelsEventId("ACCELERATE_WHEELS")
{
	type_property = owner.addProperty<T_String>("Type", "");
	velocity_property = owner.addProperty<F32>("Velocity", 0.0f);
	maxVelocity_property = owner.addProperty<F32>("MaxVelocity", 100.0f);
	engineForce_property = owner.addProperty<F32>("EngineForce", 1.0f);
	engineEffect_property = owner.addProperty<F32>("EngineEffect", 1.0f);
	mass_property = owner.addProperty<F32>("Mass", 1.0f);

	owner.registerToEvent0(throttleEventId).connect(this, &Throttle::onThrottleEvent);
}

Throttle::~Throttle()
{
}

void Throttle::onThrottleEvent()
{
	std::cout << "Player presses the gas pedal of his " << type_property.get().c_str() << std::endl;

	engineForce_property = engineEffect_property.get();

	//We spend some energy forcing the wheels to turn
#if USE_TEMPLATE_EVENT_HANDLER
	owner.sendEvent1<const F32&>(spendEffectEventId, engineEffect_property.get());
#elif USE_ANY_EVENT_HANDLER
	owner.sendEvent(spendEffectEventId, T_Any(engineEffect_property.get()));
#endif
	
		
	//Throttling forces wheels to rotate by an acceleration
#if USE_TEMPLATE_EVENT_HANDLER
	owner.sendEvent1<const F32&>(accelerateWheelsEventId, engineForce_property.get());
#elif USE_ANY_EVENT_HANDLER
	owner.sendEvent(accelerateWheelsEventId, T_Any(engineForce_property.get()));
#endif
}
