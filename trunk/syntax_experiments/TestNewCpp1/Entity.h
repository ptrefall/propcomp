#pragma once

#include "ComponentContainer.h"
#include "SharedPropertyContainer.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;

class Entity : public Totem::ComponentContainer<Entity>, public Totem::SharedPropertyContainer<>
{
public:
	Entity()
		: Totem::ComponentContainer<Entity>(this), Totem::SharedPropertyContainer<>()
	{
	}
};
