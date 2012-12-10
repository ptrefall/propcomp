#pragma once

#include <Totem/Component.h>
#include <Totem/Property.h>
#include "../Entity.h"

#include <libtcod.hpp>
#include <memory>

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;
static const int MAX_ROOM_MONSTERS = 3;

struct Tile {
    bool explored; // has the player already seen this tile ?
    Tile() : explored(false) {}
};

class RenderSystem;
typedef std::shared_ptr<RenderSystem> RenderSystemPtr;

class Map;
typedef std::shared_ptr<Map> MapPtr;

class Map : public Totem::Component<Map, PropertyUserData>
{
public:
	Map(const EntityWPtr &owner, int width, int height, const RenderSystemPtr &system);
    virtual ~Map();

	EntityPtr getOwner() { return owner.lock(); }

	bool isInFov(int x, int y) const;
	bool isWall(int x, int y) const;
    bool isExplored(int x, int y) const;
    void computeFov();

	bool canWalk(int x, int y) const;

	void render() const;

	void addMonster(int x, int y);

protected:
	Tile *tiles;
	TCODMap *map;
	friend class BspListener;
	void dig(int x1, int y1, int x2, int y2);
    void createRoom(bool first, int x1, int y1, int x2, int y2);

private:
	EntityWPtr owner;
	PropertyUserData user_data;
	RenderSystemPtr system;
	
	int width,height;
};