#pragma once

#include <Totem/Component.h>
#include <Totem/Property.h>
#include "../Entity.h"

#include <memory>
#include <vector>

#include <libtcod.hpp>

class Container;
typedef std::shared_ptr<Container> ContainerPtr;

class Container : public Totem::Component<Container, PropertyUserData>
{
public:
	Container(const EntityWPtr &owner, int inventoryMaxSize);
    virtual ~Container();

	EntityPtr getOwner() { return owner.lock(); }

	void add(EntityPtr entity);
	void remove(EntityPtr entity);

private:
	EntityWPtr owner;
	PropertyUserData user_data;
	
	int inventoryMaxSize; // maximum number of entities. 0=unlimited
	std::vector<EntityPtr> inventory;

	Totem::Property<bool> inventoryFull;
};