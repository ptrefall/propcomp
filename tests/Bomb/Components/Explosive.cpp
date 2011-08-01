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

#include "types_config.h"
#include "Explosive.h"
#include "../EntityManager.h"

#include <iostream>

using namespace Components;

Explosive::Explosive(Entity &owner, const T_String &name)
: Component(owner, name)
{
    timeout_property = owner.addProperty<bool>("Timeout", false);

	timeout_property.valueChanged().connect(this, &Explosive::onTimeoutChanged);
}

Explosive::~Explosive()
{
}

void Explosive::onTimeoutChanged(const bool &oldValue, const bool &newValue)
{
	//If no longer alive, EXPLODE!
	if(newValue)
	{
		std::cout << "The " << owner.getType().c_str() << " explodes in a hughe blast of flames!" << std::endl;

		//Affect all other entities
		EntityManager &mgr = EntityManager::Instance();
		for(U32 i = 0; i < mgr.getEntities().size(); i++)
		{
			Entity *entity = mgr.getEntities()[i];
			if(&owner == entity)
				continue;

			std::cout << "The " << entity->getType().c_str() << " is engulfed by the flames of the powerful explotion!" << std::endl;

			T_Event event("DMG");
			event.arg0.f = 200.0f;
			event.arg1.str = owner.getName().c_str();
			entity->onEvent(event);
		}
	}
}
