#pragma once

#include <Totem/Component.h>
#include <Totem/Property.h>
#include "../Entity.h"

#include <memory>

#include <libtcod.hpp>

class Pickable;
typedef std::shared_ptr<Pickable> PickablePtr;

class Pickable : public Totem::Component<Pickable, PropertyUserData>
{
public:
	Pickable(const EntityWPtr &owner);
    virtual ~Pickable();

	EntityPtr getOwner() { return owner.lock(); }

	bool pick(const EntityPtr &wearer);

private:
	EntityWPtr owner;
	PropertyUserData user_data;
	
	
};