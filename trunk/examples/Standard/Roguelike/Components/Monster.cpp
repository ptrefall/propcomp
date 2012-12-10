#include "Monster.h"
#include "../Engine.h"
#include "Map.h"
#include "Actor.h"
#include "Gui.h"

#include <iostream>

Monster::Monster(const EntityWPtr &owner) 
: Totem::Component<Monster, PropertyUserData>("Monster"), owner(owner)
{
	user_data.entity = owner;
	user_data.component = this;

	dead = owner.lock()->add<bool>("Dead", false);
	position = owner.lock()->add<Vec2i>("Position", Vec2i(0,0));

	owner.lock()->registerToEvent0("Dying").connect(this, &Monster::OnDying);
}

Monster::~Monster()
{
	std::cout << "Monster is being destroyed!" << std::endl;
}

void Monster::update(const float &/*deltaTime*/)
{
	if(dead.get())
		return;

	auto engine = Engine::getSingleton();
	if(engine->getMap()->isInFov(position.get().x(), position.get().y()))
	{
		// we can see the player. move towards him
        moveCount=TRACKING_TURNS;
	}
	else
	{
		moveCount--;
	}

	if(moveCount > 0)
		moveOrAttack(engine->getPlayer()->getPosition());
}

void Monster::OnDying()
{
	Engine::getSingleton()->getGui()->message(TCODColor::lightGrey,"The %s is dead",owner.lock()->getName().c_str());
}

void Monster::moveOrAttack(Vec2i target_pos) {
	auto engine = Engine::getSingleton();
	auto dpos = target_pos - position.get();
	auto distance = dpos.length();
	if(distance >= 2)
	{
		dpos.normalize();
		auto step = Vec2i(dpos.x() > 0 ? 1:-1, dpos.y() > 0 ? 1:-1);


		auto tp = position.get() + dpos;
		if(engine->getMap()->canWalk(tp.x(), tp.y())) {
			position += dpos;
		} else if ( engine->getMap()->canWalk(position.get().x()+step.x(),position.get().y()) ) {
            position += Vec2i(step.x(), 0);
        } else if ( engine->getMap()->canWalk(position.get().x(),position.get().y()+step.y()) ) {
            position += Vec2i(0, step.y());
        }
	}
	else
	{
		owner.lock()->sendEvent1<EntityPtr>("Attack", engine->getPlayer()->getOwner());
	}
}
