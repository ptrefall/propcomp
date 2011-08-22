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

#include "RadiusTargetSeeker.h"

#include <iostream>

using namespace Components;
using namespace Factotum;

RadiusTargetSeeker::RadiusTargetSeeker(Entity &owner, const T_String &name, EntityManager &entityMgr)
: Component(owner, name), entityMgr(entityMgr), seekInRadiusEventId("SEEK_IN_RADIUS")
{
    target_property_list = owner.addPropertyList<Entity*>("Targets");
	position_property = owner.addProperty<T_Vec3f>("Position", T_Vec3f(0.0f, 0.0f, 0.0f));

#if USE_TEMPLATE_EVENT_HANDLER
	owner.registerToEvent1<F32>(seekInRadiusEventId).connect(this, &RadiusTargetSeeker::onSeekInRadiusEvent);
#elif USE_ANY_EVENT_HANDLER
	owner.registerToEvent1(seekInRadiusEventId).connect(this, &RadiusTargetSeeker::onSeekInRadiusEvent);
#endif
}

RadiusTargetSeeker::~RadiusTargetSeeker()
{
}

#if USE_TEMPLATE_EVENT_HANDLER
void RadiusTargetSeeker::onSeekInRadiusEvent(const F32 &radius)
{
#elif USE_ANY_EVENT_HANDLER
void RadiusTargetSeeker::onSeekInRadiusEvent(T_Any radius_any)
{
	const F32 &radius = radius_any.cast<F32>();
#endif
	//Perform some algorithm
	for(U32 i = 0; i < entityMgr.getEntities().size(); i++)
	{
		if(&owner == entityMgr.getEntities()[i])
			continue;

		Entity &entity = *entityMgr.getEntities()[i];

		//Must have a position in order to be affected
		if(entity.hasProperty("Position") == false)
			continue;

		const T_Vec3f &targetPos = entity.getProperty<T_Vec3f>("Position").get();
		F32 distance = position_property.get().distance(targetPos);
		if(distance > radius)
			continue;

		target_property_list.push_back(&entity);
	}
}
