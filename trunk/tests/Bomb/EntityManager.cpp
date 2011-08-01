/*Component-based Entity Engine
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

Note: Some of the libraries Component-based Entity Engine may link to may have additional
requirements or restrictions.
*/

#pragma once

#include <types_config.h>
#include "EntityManager.h"
#include <Entity.h>

#include <iostream>

namespace { EntityManager* _instance = 0; }

EntityManager& EntityManager::Instance()
{
	if(_instance == 0)
	{
		std::cout << "Instanciate entity manager" << std::endl;
		_instance = new EntityManager();
	}
	return *_instance;
}

void EntityManager::Shutdown()
{
	if(_instance)
	{
		delete _instance;
		_instance = 0;
		std::cout << "Shut down entity manager" << std::endl;
	}
	else
		std::cout << "Entity manager already shut down" << std::endl;
}

EntityManager::~EntityManager()
{
	for(unsigned int i = 0; i < entities.size(); i++)
		delete entities[i];
}

void EntityManager::update(F32 deltaTime)
{
	for(unsigned int i = 0; i < pendingDelete.size(); i++)
		delete pendingDelete[i];
	pendingDelete.clear();

	for(unsigned int i = 0; i < entities.size(); i++)
		entities[i]->updateComponents(deltaTime);
}

Entity &EntityManager::create(ComponentFactory &factory, const T_String &type, const T_String &name)
{
	Entity *entity = new Entity(factory, type, name);
	entities.push_back(entity);
	return *entity;
}

void EntityManager::erase(Entity *entity)
{
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		if(entities[i] == entity)
		{
			//This is a vector element removal trick that's O(1)
			entities[i] = entities.back();
			entities.pop_back();
			break;
		}
	}

	pendingDelete.push_back(entity);
}