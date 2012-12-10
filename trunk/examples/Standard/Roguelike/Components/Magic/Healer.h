#pragma once

#include <Totem/Component.h>
#include <Totem/Property.h>
#include "../../Entity.h"

#include <memory>

#include <libtcod.hpp>

class Healer;
typedef std::shared_ptr<Healer> HealerPtr;

class Healer : public Totem::Component<Healer, PropertyUserData>
{
public:
	Healer(const EntityWPtr &owner, float amount, const std::string &message = "");
    virtual ~Healer();

	EntityPtr getOwner() { return owner.lock(); }

    void applyEffect(EntityPtr wearer);

private:
	EntityWPtr owner;
	PropertyUserData user_data;
	
	float amount; // how many hp
	std::string message;
};