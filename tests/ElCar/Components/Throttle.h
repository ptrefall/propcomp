/*Factotum EDK
Copyright (c) 2009 P�l Trefall and Kenneth Gangst�

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

#pragma once

#include <Component.h>
#include "../../Common/Vector3.h"

namespace Components
{
	class Throttle : public Factotum::Component
	{
	public:
		COMPONENT_0(Throttle)
		Throttle(Factotum::Entity &owner, const T_String &name);
		virtual ~Throttle();

	protected:
		Factotum::Property<T_String> type_property;
		Factotum::Property<F32> velocity_property;
		Factotum::Property<F32> maxVelocity_property;
		Factotum::Property<F32> engineForce_property;
		Factotum::Property<F32> mass_property;
		Factotum::Property<F32> engineEffect_property;

		void onThrottleEvent();

		T_HashedString throttleEventId;
		T_HashedString spendEffectEventId;
		T_HashedString accelerateWheelsEventId;
	};
}