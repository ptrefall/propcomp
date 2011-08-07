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
#include "../../Common/Vector3.h"

namespace Components
{
	class WheelMount : public Component
	{
	public:
		WheelMount(Entity &owner, const T_String &name);
		virtual ~WheelMount();
		
		virtual void update(F32 deltaTime);

		static T_String getType() { return "WheelMount"; }
		static Component* Create(Entity &owner, const T_String &name) { return new WheelMount(owner, name); }

	protected:
		PropertyList<Entity*> wheels_property_list;
		Property<U32> activeWheelCount_property;
		Property<F32> velocity_property;

		void onAccelerateWheelsEvent(const F32 &force);

		T_StringId accelerateWheelsEventId;
		T_StringId syncVelocityEventId;
		T_StringId forceAngularAccelerationEventId;
	};
}
