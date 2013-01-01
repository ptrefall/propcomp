#pragma once

#include <Totem/Component.h>
#include <Totem/Property.h>
#include "../Entity.h"
#include "../Utils/Vec2i.h"

#include <memory>

#include <libtcod.hpp>

static const int TRACKING_TURNS=3;

class MonsterSystem;
typedef std::shared_ptr<MonsterSystem> MonsterSystemPtr;

class Monster;
typedef std::shared_ptr<Monster> MonsterPtr;

class Monster : public Totem::Component<Monster, PropertyUserData>
{
public:
	Monster(const EntityWPtr &owner, const MonsterSystemPtr &system);
    virtual ~Monster();

	void update(const float &/*deltaTime*/) override;

	EntityPtr getOwner() { return owner.lock(); }

private:
	EntityWPtr owner;
	PropertyUserData user_data;
	MonsterSystemPtr system;

	void moveOrAttack(const Vec2i &target_pos);
	
	void OnDying();

	Totem::Property<bool> dead;
	Totem::Property<Vec2i> position;

	int moveCount;
};