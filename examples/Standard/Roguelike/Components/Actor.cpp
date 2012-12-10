#include "Actor.h"
#include "../Systems/RenderSystem.h"
#include "../Engine.h"

#include <iostream>

Actor::Actor(const EntityWPtr &owner, const RenderSystemPtr &system) 
: Totem::Component<Actor, PropertyUserData>("Actor"), owner(owner), system(system)
{
	user_data.entity = owner;
	user_data.component = this;

	ch = owner.lock()->add<int>("Character", '@');
	col = owner.lock()->add<TCODColor>("Color", TCODColor::white);
	blocks = owner.lock()->add<bool>("Blocks", true);
	position = owner.lock()->add<Vec2i>("Position", Vec2i(0,0));
	hide = owner.lock()->add<bool>("Hide", false);

	dead = owner.lock()->add<bool>("Dead", false);

	owner.lock()->registerToEvent0("Render").connect(this, &Actor::render);

	system->add(this);
}

Actor::~Actor()
{
	std::cout << "Actor is being destroyed!" << std::endl;
	system->remove(this);
}

void Actor::update(const float &/*deltaTime*/)
{
	//std::cout << "The " << owner.lock()->getName() << " growls!" << std::endl;
}

void Actor::render()
{
	if( hide.get() )
		return;

	TCODConsole::root->setChar(x(),y(),ch);
    TCODConsole::root->setCharForeground(x(),y(),col);
}

bool Actor::moveOrAttack(const Vec2i &pos)
{
	auto engine = Engine::getSingleton();
	if ( engine->getMap()->isWall(pos) ) 
		return false;

	auto actors = engine->getActors();
	for (unsigned int i = 0; i < actors.size(); i++) 
	{
		auto actor = actors[i];
		if ( position == pos ) 
		{
			std::cout << "The " << actor->getOwner()->getName() << " laughs at your puny efforts to attack him!" << std::endl;
			return false;
		}
	}

	position = pos;
	return true;
}
