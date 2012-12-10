#include "Healer.h"
#include "../../Engine.h"
#include "../Actor.h"
#include "../Container.h"

#include <iostream>

Healer::Healer(const EntityWPtr &owner, float amount) 
: Totem::Component<Healer, PropertyUserData>("Healer"), owner(owner), amount(amount)
{
	user_data.entity = owner;
	user_data.component = this;

	owner.lock()->registerToEvent1<EntityPtr>("Use").connect(this, &Healer::use);
}

Healer::~Healer()
{
	std::cout << "Healer is being destroyed!" << std::endl;
}

void Healer::use(EntityPtr wearer) {
	wearer->sendEvent1<float>("Heal", amount);
}
