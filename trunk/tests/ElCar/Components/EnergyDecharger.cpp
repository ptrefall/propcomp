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

#include "EnergyDecharger.h"
#include "../../Common/EntityManager.h"

#include <iostream>

using namespace Components;

EnergyDecharger::EnergyDecharger(Entity &owner, const T_String &name)
: Component(owner, name), spendEffectEventId("SPEND_EFFECT")
{
	energy_property = owner.addProperty<F32>("Energy", 100.0f);
	minEnergy_property = owner.addProperty<F32>("MinEnergy", 0.0f);
	maxEnergy_property = owner.addProperty<F32>("MaxEnergy", 100.0f);

	owner.registerToEvent1<F32>(spendEffectEventId).connect(this, &EnergyDecharger::onSpendEffectEvent);
}

EnergyDecharger::~EnergyDecharger()
{
}

void EnergyDecharger::onSpendEffectEvent(const F32 &effect)
{
	if(energy_property.get() == minEnergy_property.get())
	{
		std::cout << "Energy has already been decharged to the minimum level!" << std::endl;
		return;
	}

	energy_property -= effect;

	if(energy_property.get() <= minEnergy_property.get())
	{
		std::cout << "Energy has been decharged to the minimum level!" << std::endl;
		energy_property = minEnergy_property.get();
	}
	else
	{
		std::cout << "Energy was decharged down to " << ((energy_property.get() / maxEnergy_property.get()) * 100.0f) << "% of full capacity!" << std::endl;
	}
}
