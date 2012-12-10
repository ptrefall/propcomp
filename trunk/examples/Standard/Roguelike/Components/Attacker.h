#pragma once

#include <Totem/Component.h>
#include <Totem/Property.h>
#include "../Entity.h"

#include <memory>

#include <libtcod.hpp>

class Attacker;
typedef std::shared_ptr<Attacker> AttackerPtr;

class Attacker : public Totem::Component<Attacker, PropertyUserData>
{
public:
	Attacker(const EntityWPtr &owner, float power);
    virtual ~Attacker();

	EntityPtr getOwner() { return owner.lock(); }

	void attack(EntityPtr target);

private:
	EntityWPtr owner;
	PropertyUserData user_data;
	
	float power;
};