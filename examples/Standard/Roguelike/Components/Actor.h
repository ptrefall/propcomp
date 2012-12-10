#pragma once

#include <Totem/Component.h>
#include <Totem/Property.h>
#include "../Entity.h"
#include "../Utils/Vec2i.h"

#include <memory>

#include <libtcod.hpp>

class RenderSystem;
typedef std::shared_ptr<RenderSystem> RenderSystemPtr;

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

class Actor : public Totem::Component<Actor, PropertyUserData>
{
public:
	Actor(const EntityWPtr &owner, const RenderSystemPtr &system);
    virtual ~Actor();
	void update(const float &deltaTime) override;
	void render() const;

	bool moveOrAttack(int x,int y);

	bool blocksTile() const { return blocks.get(); }

	EntityPtr getOwner() { return owner.lock(); }

	Vec2i getPosition() const { return position.get(); }
	int x() const { return position.get().x(); }
	int y() const { return position.get().y(); }

private:
	EntityWPtr owner;
	PropertyUserData user_data;
	RenderSystemPtr system;
	
	//Shared properties
	Totem::Property<int> ch;
	Totem::Property<TCODColor> col;
	Totem::Property<bool> blocks;
	Totem::Property<Vec2i> position;
	Totem::Property<bool> hide;
};