#include "Player.h"
#include "../Engine.h"
#include "Map.h"
#include "Actor.h"
#include "Gui.h"
#include "../Systems/RenderSystem.h"

#include <iostream>

Player::Player(const EntityWPtr &owner, const RenderSystemPtr &system) 
: Totem::Component<Player, PropertyUserData>("Player"), owner(owner), system(system)
{
	user_data.entity = owner;
	user_data.component = this;

	dead = owner.lock()->add<bool>("Dead", false);
	position = owner.lock()->add<Vec2i>("Position", Vec2i(0,0));
	maxHp = owner.lock()->add<float>("MaxHP", 1);
	hp = owner.lock()->add<float>("HP", 1);

	owner.lock()->registerToEvent0("Dying").connect(this, &Player::OnDying);
	owner.lock()->registerToEvent0("Dead").connect(this, &Player::OnDeath);

	system->set(this);
}

Player::~Player()
{
	std::cout << "Player is being destroyed!" << std::endl;
	system->set(static_cast<Player*>(nullptr));
}

void Player::checkForInput()
{
	if(dead.get())
		return;

	auto engine = Engine::getSingleton();
	int dx=0,dy=0;
	switch(engine->getLastKey().vk) 
	{
		case TCODK_UP : dy=-1; break;
		case TCODK_DOWN : dy=1; break;
		case TCODK_LEFT : dx=-1; break;
		case TCODK_RIGHT : dx=1; break;
		default:break;
	}

	if ( dx != 0 || dy != 0 ) 
	{
		engine->gameStatus=Engine::NEW_TURN;
		if ( moveOrAttack(position.get() + Vec2i(dx,dy)) ) {
			engine->getMap()->getOwner()->sendEvent0("ComputeFOV");
		}
	}
}

void Player::OnDying()
{
	Engine::getSingleton()->getGui()->message(TCODColor::red,"You died!");
}

void Player::OnDeath()
{
	Engine::getSingleton()->gameStatus = Engine::DEFEAT;
}

bool Player::moveOrAttack(Vec2i target_pos) {
	auto engine = Engine::getSingleton();
    if ( engine->getMap()->isWall(target_pos.x(), target_pos.y()) ) 
		return false;

    // look for living actors to attack
	auto actors = engine->getActors();
    for (unsigned int i = 0; i < actors.size(); i++) {
        auto actor = actors[i];
		if ( !actor->getOwner()->get<bool>("Dead").get() && actor->getPosition() == target_pos ) 
		{
			owner.lock()->sendEvent1<EntityPtr>("Attack", actor->getOwner());
            return false;
        }
    }

	// look for corpses
	for (unsigned int i = 0; i < actors.size(); i++) {
        auto actor = actors[i];
		if ( actor->getOwner()->get<bool>("Dead").get() && actor->getPosition() == target_pos ) 
		{
			Engine::getSingleton()->getGui()->message(TCODColor::lightGrey,"There's a %s here.",actor->getOwner()->getName().c_str());
		}
	}

	position = target_pos;
    return true;
}

