#include "Destructible.h"
#include "../Engine.h"
#include "../Systems/RenderSystem.h"

#include <iostream>

Destructible::Destructible(const EntityWPtr &owner, const std::string &corpseName, const RenderSystemPtr &system) 
: Totem::Component<Destructible, PropertyUserData>("Destructible"), owner(owner), corpseName(corpseName), system(system)
{
	user_data.entity = owner;
	user_data.component = this;

	this->ch = owner.lock()->add<int>("Character", '@');
	this->col = owner.lock()->add<TCODColor>("Color", TCODColor::white);
	this->blocks = owner.lock()->add<bool>("Blocks", true);
	dead = owner.lock()->add<bool>("Dead", false);
	this->defense = owner.lock()->add<float>("Defense", 1);

	this->maxHp = owner.lock()->add<float>("MaxHP", 1);
	this->hp = owner.lock()->add<float>("HP", 1);

	owner.lock()->registerToEvent1<float>("TakeDamage").connect(this, &Destructible::takeDamage);
	owner.lock()->registerToEvent1<float>("Heal").connect(this, &Destructible::heal);
}

Destructible::~Destructible()
{
	//std::cout << "Destructible is being destroyed!" << std::endl;
}

void Destructible::takeDamage(float damage) {
    damage -= defense;
    if ( damage > 0 ) {
        hp -= damage;
        if ( hp <= 0 ) {
            die();
        }
    } else {
        damage=0;
    }
}

void Destructible::die() {

	try{ owner.lock()->sendEvent0("Dying");
	} catch(std::exception &/*e*/) {
	}

    // transform the actor into a corpse!
    ch='%';
    col=TCODColor::darkRed;   
	owner.lock()->updateName(corpseName);
    blocks=false;

	dead = true;

    // make sure corpses are drawn before living actors
	system->add(owner);
	try{ owner.lock()->sendEvent0("Dead");
	} catch(std::exception &/*e*/) {
	}
}

void Destructible::heal(float amount) 
{
    hp += amount;
    if ( hp.get() > maxHp.get() ) {
        hp=maxHp.get();
    }
	else if ( hp <= 0 ) {
            die();
    }
}

