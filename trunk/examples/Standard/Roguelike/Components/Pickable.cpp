#include "Pickable.h"
#include "../Engine.h"
#include "Actor.h"
#include "Container.h"

#include <iostream>

Pickable::Pickable(const EntityWPtr &owner) 
: Totem::Component<Pickable, PropertyUserData>("Pickable"), owner(owner)
{
	user_data.entity = owner;
	user_data.component = this;

}

Pickable::~Pickable()
{
	std::cout << "Pickable is being destroyed!" << std::endl;
}

bool Pickable::pick(const EntityPtr &wearer) {
    if ( !wearer->get<bool>("InventoryFull").get() ) 
	{
		wearer->sendEvent1<EntityPtr>("PickUp", owner.lock());
		if(owner.lock()->hasComponent<Actor>())
			Engine::getSingleton()->remove(owner.lock()->getComponent<Actor>()); //We still want an item's entity to receive updates to components and properties
        return true;
    }
    return false;
}
