#pragma once

#include "ComponentContainer.h"
#include "SharedPropertyContainer.h"
#include "PoolComponentFactory.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;

class Entity : public ComponentContainer<Entity, PoolComponentFactoryPtr>, public SharedPropertyContainer<>
{
public:
	Entity(PoolComponentFactoryPtr factory)
		: ComponentContainer<Entity, PoolComponentFactoryPtr>(this, factory), SharedPropertyContainer<>()
	{
	}
};
