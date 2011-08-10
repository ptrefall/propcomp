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

#include <types_config.h>
#include "EntityManager.h"
#include "Entity.h"

#include <iostream>

EntityManager::~EntityManager()
{
	for(unsigned int i = 0; i < entities.size(); i++)
		delete entities[i];
}

void EntityManager::update(F32 deltaTime)
{
	if(!pendingDelete.empty())
	{
		for(unsigned int i = 0; i < pendingDelete.size(); i++)
		{
			for(unsigned int j = 0; j < entities.size(); j++)
			{
				if(entities[j] == pendingDelete[i])
				{
					//This is a vector element removal trick that's O(1)
					entities[j] = entities.back();
					entities.pop_back();
					break;
				}
			}
			delete pendingDelete[i];
		}
		pendingDelete.clear();
	}

	for(unsigned int i = 0; i < entities.size(); i++)
		entities[i]->updateComponents(deltaTime);
}

Entity &EntityManager::create(ComponentFactory &factory, const T_String &type)
{
	Entity *entity = new Entity(factory); //, nextEntityId++, type);
	entities.push_back(entity);
		return *entity;
}

void EntityManager::erase(Entity *entity)
{
	pendingDelete.push_back(entity);
}
