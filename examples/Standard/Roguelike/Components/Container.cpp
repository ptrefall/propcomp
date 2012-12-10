#include "Container.h"
#include "../Engine.h"

#include <iostream>

Container::Container(const EntityWPtr &owner, int inventoryMaxSize) 
: Totem::Component<Container, PropertyUserData>("Container"), owner(owner), inventoryMaxSize(inventoryMaxSize)
{
	user_data.entity = owner;
	user_data.component = this;

	inventory.reserve(inventoryMaxSize);

	inventoryFull = owner.lock()->add<bool>("InventoryFull", false);

	owner.lock()->registerToEvent1<EntityPtr>("PickUp").connect(this, &Container::add);
	owner.lock()->registerToEvent1<EntityPtr>("Consume").connect(this, &Container::remove);
}

Container::~Container()
{
	std::cout << "Container is being destroyed!" << std::endl;
}

void Container::add(EntityPtr entity)
{
	if ( inventoryMaxSize > 0 && inventory.size() >= inventoryMaxSize )
        // inventory full
        return;

	if( inventoryMaxSize > 0 && inventory.size() >= inventoryMaxSize-1 )
		inventoryFull = true;

	inventory.push_back(entity);
}

void Container::remove(EntityPtr entity)
{
	for(unsigned int i = 0; i < inventory.size(); i++)
	{
		if(inventory[i] == entity)
		{
			inventory[i] = inventory.back();
			inventory.pop_back();
			return;
		}
	}
}
