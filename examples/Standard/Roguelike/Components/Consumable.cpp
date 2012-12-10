#include "Consumable.h"
#include "../Engine.h"
#include "Actor.h"
#include "Container.h"

#include <iostream>

Consumable::Consumable(const EntityWPtr &owner) 
: Totem::Component<Consumable, PropertyUserData>("Consumable"), owner(owner)
{
	user_data.entity = owner;
	user_data.component = this;

	owner.lock()->registerToEvent1<EntityPtr>("Use").connect(this, &Consumable::use);
}

Consumable::~Consumable()
{
	std::cout << "Consumable is being destroyed!" << std::endl;
}

void Consumable::use(EntityPtr wearer) {
	wearer->sendEvent1<EntityPtr>("Consume", owner.lock());
	Engine::getSingleton()->remove(owner.lock());
}
