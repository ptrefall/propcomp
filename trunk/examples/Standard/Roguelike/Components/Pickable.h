#pragma once

#include <Totem/Component.h>
#include <Totem/Property.h>
#include "../Entity.h"

#include <memory>

#include <libtcod.hpp>

class RenderSystem;
typedef std::shared_ptr<RenderSystem> RenderSystemPtr;

class Pickable;
typedef std::shared_ptr<Pickable> PickablePtr;

class Pickable : public Totem::Component<Pickable, PropertyUserData>
{
public:
	Pickable(const EntityWPtr &owner, const RenderSystemPtr &system);
    virtual ~Pickable();

	EntityPtr getOwner() { return owner.lock(); }

	void pick(EntityPtr wearer);

private:
	EntityWPtr owner;
	PropertyUserData user_data;
	RenderSystemPtr system;
	
	
};