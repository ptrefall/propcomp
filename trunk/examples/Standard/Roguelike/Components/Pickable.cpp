#include "Pickable.h"
#include "../Engine.h"
#include "Actor.h"
#include "Container.h"

#include "../Systems/RenderSystem.h"

#include <iostream>

Pickable::Pickable(const EntityWPtr &owner, const RenderSystemPtr &system) 
: Totem::Component<Pickable, PropertyUserData>("Pickable"), owner(owner), system(system)
{
	user_data.entity = owner;
	user_data.component = this;

	owner.lock()->registerToEvent1<EntityPtr>("PickUp").connect(this, &Pickable::pick);

	if(owner.lock()->hasComponent<Actor>())
		system->remove(owner.lock()->getComponent<Actor>().get());

	system->add(this);
}

Pickable::~Pickable()
{
	std::cout << "Pickable is being destroyed!" << std::endl;
}

void Pickable::pick(EntityPtr wearer) {
	if ( wearer->hasComponent<Container>() && !wearer->get<bool>("InventoryFull").get() ) 
	{
		wearer->sendEvent1<EntityPtr>("PickUp", owner.lock());
		system->remove(this);
		if(owner.lock()->hasComponent<Actor>())
			Engine::getSingleton()->remove(owner.lock()->getComponent<Actor>()); //We still want an item's entity to receive updates to components and properties
    }
}
