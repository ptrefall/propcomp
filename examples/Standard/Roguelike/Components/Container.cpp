#include "Container.h"
#include "../Engine.h"

#include <iostream>

Container::Container(const EntityWPtr &owner, int inventoryMaxSize) 
: Totem::Component<Container, PropertyUserData>("Container"), owner(owner), inventoryMaxSize(inventoryMaxSize)
{
	user_data.entity = owner;
	user_data.component = this;

	inventoryList = owner.lock()->addList<EntityPtr>("Inventory");
	//inventoryList.resize(inventoryMaxSize, false);
	//inventory.reserve(inventoryMaxSize);

	inventoryFull = owner.lock()->add<bool>("InventoryFull", false);

	owner.lock()->registerToEvent1<EntityPtr>("PickUp").connect(this, &Container::add);
	owner.lock()->registerToEvent1<EntityPtr>("Remove").connect(this, &Container::remove);
}

Container::~Container()
{
	std::cout << "Container is being destroyed!" << std::endl;
}

void Container::add(EntityPtr entity)
{
	if ( inventoryMaxSize > 0 && inventoryList.size() >= (unsigned int)inventoryMaxSize )
        // inventory full
        return;

	if( inventoryMaxSize > 0 && inventoryList.size() >= (unsigned int)inventoryMaxSize-1 )
		inventoryFull = true;

	inventoryList.push_back(entity);
}

void Container::remove(EntityPtr entity)
{
	for(unsigned int i = 0; i < inventoryList.size(); i++)
	{
		if(inventoryList[i].get() == entity)
		{
			inventoryList.erase(i);
			return;
		}
	}
}
