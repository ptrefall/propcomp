#include "Healer.h"
#include "../../Engine.h"
#include "../Actor.h"
#include "../Container.h"
#include "../Gui.h"

#include <iostream>

Healer::Healer(const EntityWPtr &owner, float amount, const std::string &message) 
: Totem::Component<Healer, PropertyUserData>("Healer"), owner(owner), amount(amount), message(message)
{
	user_data.entity = owner;
	user_data.component = this;

	owner.lock()->registerToEvent1<EntityPtr>("ApplyEffect").connect(this, &Healer::applyEffect);
}

Healer::~Healer()
{
	//std::cout << "Healer is being destroyed!" << std::endl;
}

void Healer::applyEffect(EntityPtr wearer) {
	if(wearer->hasEvent("Heal",1))
	{
		if( !message.empty() )
			Engine::getSingleton()->getGui()->message(TCODColor::lightCyan, message.c_str(),wearer->getName().c_str(), abs(amount));

		wearer->sendEvent1<float>("Heal", amount);
	}
}
