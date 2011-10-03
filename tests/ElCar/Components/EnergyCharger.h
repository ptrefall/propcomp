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
	class EnergyCharger : public Factotum::Component
	{
	public:
		COMPONENT_0(EnergyCharger)
		EnergyCharger(Factotum::Entity &owner, const T_String &name);
		virtual ~EnergyCharger();

	protected:
		Factotum::Property<F32> energy_property;
		Factotum::Property<F32> maxEnergy_property;

#if USE_TEMPLATE_EVENT_HANDLER
		void onAddEffectEvent(const F32 &effect);
#elif USE_ANY_EVENT_HANDLER
		void onAddEffectEvent(T_Any effect);
#endif

		T_HashedString addEffectEventId;
	};
}