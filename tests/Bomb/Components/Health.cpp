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

#include "Health.h"

#include <iostream>

using namespace Components;
using namespace Factotum;

Health::Health(Entity &owner, const T_String &name, EntityManager &entityMgr)
: Component(owner, name), entityMgr(entityMgr), dmgEventId("DMG")//, applyDmgId("APPLY_DMG")
{
	name_property = owner.addProperty<T_String>("Name", "");
    alive_property = owner.addProperty<bool>("Alive", true);
	health_property = owner.addProperty<F32>("Health", 100.0f);
	maxhealth_property = owner.addProperty<F32>("MaxHealth", 100.0f);

    health_property.valueChanged().connect(this, &Health::onHealthChanged);
	alive_property.valueChanged().connect(this, &Health::onAliveChanged);

#if USE_TEMPLATE_EVENT_HANDLER
	owner.registerToEvent2<F32, T_String>(dmgEventId).connect(this, &Health::onDmgEvent);
#elif USE_ANY_EVENT_HANDLER
	owner.registerToEvent2(dmgEventId).connect(this, &Health::onDmgEvent);
#endif

	//owner.registerFunction2<const F32 &, const T_String &, F32>(applyDmgId).bind(this, &Health::applyDmg);
}

Health::~Health()
{
}

#if USE_TEMPLATE_EVENT_HANDLER
void Health::onDmgEvent(const F32 &dmg, const T_String &attackerName)
{
#elif USE_ANY_EVENT_HANDLER
void Health::onDmgEvent(T_Any &dmg_any, T_Any &attackerName_any)
{
	const F32 &dmg = dmg_any.cast<F32>();
	const T_String &attackerName = attackerName_any.cast<T_String>();
#endif
	std::cout << attackerName.c_str() << " inflicted " << dmg << " damage to " << name_property.get().c_str() << std::endl;

	health_property -= dmg;
	if(0 < health_property)
	{
		std::cout << name_property.get().c_str() << "'s remaining health is " << health_property.get() << " hp!" << std::endl;
	}
}

void Health::onHealthChanged(const F32 &/*oldValue*/, const F32 &newValue)
{
	if(newValue <= 0.0f)
	{
		alive_property = false;
	}
}

void Health::onAliveChanged(const bool &/*oldValue*/, const bool &newValue)
{
	//If no longer alive, tell the go's player, if there is a player
	if(!newValue)
	{
		//Could send an event here that we died (useful if someone targets us, or if player should be notified in some way, 
		//or the game manager should put us in a pending_deletion list or something...

		std::cout << name_property.get().c_str() << " died..." << std::endl;
		entityMgr.erase(&owner);
	}
}
