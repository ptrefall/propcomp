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

#include "EnergyCharger.h"

#include <iostream>

using namespace Components;
using namespace Totem;

EnergyCharger::EnergyCharger(Entity &owner, const T_String &name)
: Component(name), owner(owner), addEffectEventId("ADD_EFFECT")
{
	energy_property = owner.addProperty<F32>("Energy", 100.0f);
	maxEnergy_property = owner.addProperty<F32>("MaxEnergy", 100.0f);

#if USE_TEMPLATE_EVENT_HANDLER
	owner.registerToEvent1<const F32&>(addEffectEventId).connect(this, &EnergyCharger::onAddEffectEvent);
#elif USE_ANY_EVENT_HANDLER
	owner.registerToEvent1(addEffectEventId).connect(this, &EnergyCharger::onAddEffectEvent);
#endif
}

EnergyCharger::~EnergyCharger()
{
}

#if USE_TEMPLATE_EVENT_HANDLER
void EnergyCharger::onAddEffectEvent(const F32 &effect)
{
#elif USE_ANY_EVENT_HANDLER
void EnergyCharger::onAddEffectEvent(T_Any effect_any)
{
	const F32 &effect = effect_any.cast<F32>();
#endif
	if(energy_property.get() == maxEnergy_property.get())
	{
		std::cout << "Energy is already at full capacity!" << std::endl;
		return;
	}

	energy_property += effect;

	if(energy_property.get() >= maxEnergy_property.get())
	{
		std::cout << "Energy has been charged to full capacity!" << std::endl;
		energy_property = maxEnergy_property.get();
	}
	else
	{
		std::cout << "Energy was charged up to " << ((energy_property.get() / maxEnergy_property.get()) * 100.0f) << "% of full capacity!" << std::endl;
	}
}
