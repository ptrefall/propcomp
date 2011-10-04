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

#pragma once

#include <Component.h>

namespace Components
{
	class AngularPhysics : public Totem::Component
	{
	public:
		COMPONENT_0(AngularPhysics)
		AngularPhysics(Totem::Entity &owner, const T_String &name);
		virtual ~AngularPhysics();

		virtual void update(const F32 &deltaTime);

	protected:
		Totem::Property<Totem::Entity*> car_property;
		Totem::Property<F32> angularVelocity_property;
		Totem::Property<F32> dimension_property;
		Totem::Property<F32> friction_property;
		Totem::PropertyList<F32> forces_property_list;

#if USE_TEMPLATE_EVENT_HANDLER
		void onForceAngularAccelerationEvent(const F32 &force);
		void onSyncVelocityEvent(const F32 &velocity);
#elif USE_ANY_EVENT_HANDLER
		void onForceAngularAccelerationEvent(T_Any force);
		void onSyncVelocityEvent(T_Any velocity);
#endif

		T_HashedString forceAngularAccelerationEventId;
		T_HashedString syncVelocityEventId;
	};
}
