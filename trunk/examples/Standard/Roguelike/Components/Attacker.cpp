#include "Attacker.h"
#include "../Engine.h"
#include "Destructible.h"
#include "Gui.h"
#include "Player.h"

#include <iostream>

Attacker::Attacker(const EntityWPtr &owner, float power) 
: Totem::Component<Attacker, PropertyUserData>("Attacker"), owner(owner), power(power)
{
	user_data.entity = owner;
	user_data.component = this;

	owner.lock()->registerToEvent1<EntityPtr>("Attack").connect(this, &Attacker::attack);
}

Attacker::~Attacker()
{
	std::cout << "Attacker is being destroyed!" << std::endl;
}

void Attacker::attack(EntityPtr target) {
	auto gui = Engine::getSingleton()->getGui();
	if ( target->hasComponent<Destructible>() && !target->get<bool>("Dead").get() ) 
	{
		auto target_defense = target->get<float>("Defense").get();
        if ( power - target_defense > 0 ) 
		{
			auto rng = TCODRandom::getInstance();
			auto isPlayer = owner.lock()->hasComponent<Player>();
			auto isCritical = (rng->getInt(0,100) > 80);
			
			if(isPlayer && isCritical)
			{
				float critical = (float)rng->getInt(1,20);
				gui->message(TCODColor::darkRed, "%s attacks %s. CRITICAL: %g hit points!",
								owner.lock()->getName().c_str(), target->getName().c_str(), (power*critical - target_defense));

				target->sendEvent1<float>("TakeDamage", power*critical);
			}
			else if(isCritical)
			{
				float critical = rng->getFloat(1.0f,2.0f);
				gui->message(TCODColor::darkGrey, "%s misses %s and hits himself for %g hit points!",
								owner.lock()->getName().c_str(), target->getName().c_str(), ((int)(power*critical) - target_defense));

				owner.lock()->sendEvent1<float>("TakeDamage", (float)((int)(power*critical)));
			}
			else
			{

				gui->message(owner.lock()->hasComponent<Player>() ? TCODColor::red : TCODColor::lightGrey, "%s attacks %s for %g hit points.",
								owner.lock()->getName().c_str(), target->getName().c_str(), (power - target_defense));

				target->sendEvent1<float>("TakeDamage", power);
			}
        } 
		else 
		{
			gui->message(TCODColor::lightGrey, "%s attacks %s but it has no effect!", owner.lock()->getName().c_str(), target->getName().c_str()); 
        }
    } 
	else 
	{
		gui->message(TCODColor::lightGrey, "%s attacks %s in vain.", owner.lock()->getName().c_str(), target->getName().c_str()); 
    }
}


