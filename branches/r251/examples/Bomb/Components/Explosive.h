/*Totem EDK
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

Note: Some of the libraries Totem EDK may link to may have additional
requirements or restrictions.
*/

#pragma once

#include <Totem/Component.h>
#include <Totem/PropertyList.h>
#include "../../Common/Entity.h"
#include "../../Common/Vector3.h"

namespace Components
{
	class Explosive : public Totem::Component
	{
	public:
		COMPONENT_0(Entity, Explosive)
		Explosive(Entity &owner, const T_String &name);
		virtual ~Explosive();

	protected:
		Totem::Property<T_String> type_property;
		Totem::Property<T_String> name_property;
		Totem::Property<bool> timeout_property;
		Totem::Property<F32> base_damage_property;
		Totem::Property<F32> blast_radius_property;
		Totem::Property<T_Vec3f> position_property;

		Totem::PropertyList<Entity*> target_property_list;

		//Property Slots
		void onTimeoutChanged(const bool &oldValue, const bool &newValue);

		//PropertyList Slots
		void onTargetAdded(const U32 &index, Entity * const &newValue);

		//Event Ids
		T_HashedString seekInRadiusEventId;
		T_HashedString dmgEventId;
	};
}
