#pragma once

#include "ComponentContainer.h"
#include "SharedPropertyContainer.h"
#include "PoolComponentFactory.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;

class Entity : public Totem::ComponentContainer<Entity, PoolComponentFactoryPtr>, public Totem::SharedPropertyContainer<>
{
public:
	Entity(PoolComponentFactoryPtr factory)
		: Totem::ComponentContainer<Entity, PoolComponentFactoryPtr>(this, factory), Totem::SharedPropertyContainer<>()
	{
	}
};
