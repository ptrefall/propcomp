#pragma once

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
#include <ClanLib\core.h>

#include "../../../editions/ClanLib/include/Totem/ComponentContainer.h"
#include "../../../editions/ClanLib/include/Totem/PropertyContainer.h"
#include "../../../editions/ClanLib/include/Totem/PropertyListContainer.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;

class Entity : public std::enable_shared_from_this<Entity>, public Totem::ComponentContainer<EntityPtr>, public Totem::PropertyContainer<>, public Totem::PropertyListContainer<>
{
public:
    Entity()
		: Totem::ComponentContainer<EntityPtr>(), Totem::PropertyContainer<>(), Totem::PropertyListContainer<>()
    {
    }

protected:
	EntityPtr Totem::ComponentContainer<EntityPtr>::getThisAsEntity() override { return shared_from_this(); }
};