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
	Healer(const EntityWPtr &owner, float amount);
    virtual ~Healer();

	EntityPtr getOwner() { return owner.lock(); }

    void use(EntityPtr wearer);

private:
	EntityWPtr owner;
	PropertyUserData user_data;
	
	float amount; // how many hp
};