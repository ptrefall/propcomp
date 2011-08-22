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

#include "Explosive.h"

#include <iostream>

using namespace Components;
using namespace Factotum;

Explosive::Explosive(Entity &owner, const T_String &name)
: Component(owner, name), seekInRadiusEventId("SEEK_IN_RADIUS"), dmgEventId("DMG")
{
	type_property = owner.addProperty<T_String>("Type", "");
	name_property = owner.addProperty<T_String>("Name", "");
    timeout_property = owner.addProperty<bool>("Timeout", false);
	base_damage_property = owner.addProperty<F32>("BaseDamage", 100.0f);
	blast_radius_property = owner.addProperty<F32>("BlastRadius", 10.0f);
	position_property = owner.addProperty<Vector3<F32>>("Position", T_Vec3f(0.0f, 0.0f, 0.0f));

	target_property_list = owner.addPropertyList<Entity*>("Targets");

	timeout_property.valueChanged().connect(this, &Explosive::onTimeoutChanged);
	target_property_list.valueAdded().connect(this, &Explosive::onTargetAdded);
}

Explosive::~Explosive()
{
}

void Explosive::onTimeoutChanged(const bool &/*oldValue*/, const bool &newValue)
{
	//If no longer alive, EXPLODE!
	if(newValue)
	{
		std::cout << "The " << type_property.get().c_str() << " explodes in a hughe blast of flames!" << std::endl;

		//Affect all entities in blast radius
#if USE_TEMPLATE_EVENT_HANDLER
		owner.sendEvent1<F32>(seekInRadiusEventId, blast_radius_property.get());
#elif USE_ANY_EVENT_HANDLER
		owner.sendEvent(seekInRadiusEventId, T_Any(blast_radius_property.get()));
#endif
	}
}

void Explosive::onTargetAdded(const U32 &/*index*/, Entity * const &newValue)
{
	//Must have a position in order to be affected
	if(newValue->hasProperty("Position") == false)
		return;

	const T_Vec3f &targetPos = newValue->getProperty<T_Vec3f>("Position").get();
	F32 distance = position_property.get().distance(targetPos);
	const F32 &radius = blast_radius_property.get();
	if(distance > radius)
		return;

	std::cout << newValue->getProperty<T_String>("Name").get().c_str() << " is engulfed by the flames of the powerful explotion " << distance << " units away!" << std::endl;

	F32 half_radius = radius * 0.5f;
	F32 dmg_weight = 1.0f - ((distance - half_radius) / half_radius);

	F32 dmg = 200.0f * dmg_weight;
#if USE_TEMPLATE_EVENT_HANDLER
	newValue->sendEvent2<F32, T_String>(dmgEventId, dmg, name_property.get());
#elif USE_ANY_EVENT_HANDLER
	newValue->sendEvent(dmgEventId, T_Any(dmg), T_Any(name_property.get()));
#endif
}
