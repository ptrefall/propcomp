#pragma once

#include "ComponentContainer.h"
#include "SharedPropertyContainer.h"
#include "TotemFactory.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;

class Entity : public Totem::ComponentContainer<Entity, TotemFactory>, public Totem::SharedPropertyContainer<TotemFactory>
{
public:
	Entity(TotemFactoryPtr factory)
		: Totem::ComponentContainer<Entity, TotemFactory>(this, factory.get()), Totem::SharedPropertyContainer<TotemFactory>(factory.get())
	{
	}
};
