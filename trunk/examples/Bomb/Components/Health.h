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

#include <Totem/Component.h>
#include "../../Common/Entity.h"
#include "../../Common/EntityManager.h"

namespace Components
{
	class Health : public Totem::Component
	{
	public:
		COMPONENT_1(Entity, Health, EntityManager)
		Health(Entity &owner, const T_String &name, EntityManager &entityMgr);
		virtual ~Health();

	protected:
		Totem::Property<T_String> name_property;
		Totem::Property<bool> alive_property;
		Totem::Property<F32> health_property;
		Totem::Property<F32> maxhealth_property;

		void onHealthChanged(const F32 &oldValue, const F32 &newValue);
		void onAliveChanged(const bool &oldValue, const bool &newValue);

#if USE_TEMPLATE_EVENT_HANDLER
		void onDmgEvent(const F32 &dmg, const T_String &attackerName);
#elif USE_ANY_EVENT_HANDLER
		void onDmgEvent(T_Any dmg, T_Any attackerName);
#endif

		//F32 applyDmg(const F32 &dmg, const T_String &) { return dmg; }

		T_HashedString dmgEventId;
		//T_HashedString applyDmgId;

		EntityManager &entityMgr;
	};
}
