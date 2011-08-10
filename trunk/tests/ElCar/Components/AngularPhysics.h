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

#pragma once

#include <Component.h>
#include "../../Common/Entity.h"

namespace Components
{
	class AngularPhysics : public Component
	{
	public:
		COMPONENT_0(AngularPhysics)
		AngularPhysics(Entity &owner, const T_String &name);
		virtual ~AngularPhysics();

		virtual void update(const F32 &deltaTime);

	protected:
		Property<Entity*> car_property;
		Property<F32> angularVelocity_property;
		Property<F32> dimension_property;
		Property<F32> friction_property;
		PropertyList<F32> forces_property_list;

		void onForceAngularAccelerationEvent(const F32 &force);
		void onSyncVelocityEvent(const F32 &velocity);

		T_HashedString forceAngularAccelerationEventId;
		T_HashedString syncVelocityEventId;
	};
}
