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

class ComponentFactory;
class Entity;

class EntityManager
{
public:
	static EntityManager& Instance();
	static void Shutdown();
	~EntityManager();

	void update(F32 deltaTime);

	Entity &create(ComponentFactory &factory, const T_String &type);
	void erase(Entity *entity);
	T_Vector<Entity*>::Type &getEntities() { return entities; }

protected:
	EntityManager() : nextEntityId(0) {}
	T_Vector<Entity*>::Type entities;
	T_Vector<Entity*>::Type pendingDelete;
	T_EntityId nextEntityId;
};