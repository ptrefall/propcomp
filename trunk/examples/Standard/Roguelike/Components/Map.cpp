#include "Map.h"
#include "Actor.h"
#include "../Systems/RenderSystem.h"
#include "../Engine.h"
#include "../Utils/BspListener.h"

#include "Destructible.h"
#include "Attacker.h"
#include "Monster.h"

#include <iostream>

Map::Map(const EntityWPtr &owner, int width, int height, const RenderSystemPtr &system) 
: Totem::Component<Map, PropertyUserData>("Map"), owner(owner), width(width), height(height), system(system)
{
	user_data.entity = owner;
	user_data.component = this;

	tiles=new Tile[width*height];
	map=new TCODMap(width,height);

    TCODBsp bsp(0,0,width,height);
    bsp.splitRecursive(nullptr,8,ROOM_MAX_SIZE,ROOM_MAX_SIZE,1.5f,1.5f);
    BspListener listener(this);
    bsp.traverseInvertedLevelOrder(&listener,nullptr);

	owner.lock()->registerToEvent0("ComputeFOV").connect(this, &Map::computeFov);

	system->set(this);
}

Map::~Map()
{
	std::cout << "Map is being destroyed!" << std::endl;
	delete [] tiles;
	delete map;
	system->set(static_cast<Map*>(nullptr));
}

void Map::render() const
{ 
	static const TCODColor darkWall(0,0,100);	
	static const TCODColor darkGround(50,50,150);
	static const TCODColor lightWall(130,110,50);
	static const TCODColor lightGround(200,180,50);

	for (int x=0; x < width; x++) {
    for (int y=0; y < height; y++){
        if ( isInFov(x,y) )
            TCODConsole::root->setCharBackground(x,y, isWall(x,y) ? lightWall :lightGround );
        else if ( isExplored(x,y) )
            TCODConsole::root->setCharBackground(x,y, isWall(x,y) ? darkWall : darkGround );
    }}
}

bool Map::isWall(int x, int y) const {
    return !map->isWalkable(x,y);
}

bool Map::isExplored(int x, int y) const {
    return tiles[x+y*width].explored;
}

bool Map::isInFov(int x, int y) const {
	if ( x < 0 || x >= width || y < 0 || y >= height ) {
        return false;
    }
    if ( map->isInFov(x,y) ) {
        tiles[x+y*width].explored=true;
        return true;
    }
    return false;
}
 
void Map::computeFov() {
	auto engine = Engine::getSingleton();
	auto player = engine->getPlayer();
	map->computeFov(player->x(),player->y(),
        engine->fovRadius);
}

bool Map::canWalk(int x, int y) const
{
    if (isWall(x,y)) {
        // this is a wall
        return false;
    }
	auto actors = Engine::getSingleton()->getActors();
    for (unsigned int i = 0; i < actors.size(); i++) {
        auto actor = actors[i];
        if ( actor->blocksTile() && actor->getPosition() == Vec2i(x,y) ) {
            // there is a blocking actor there. cannot walk
            return false;
        }
    }
    return true;
}

void Map::dig(int x1, int y1, int x2, int y2) 
{
    if ( x2 < x1 ) 
	{
        int tmp=x2;
        x2=x1;
        x1=tmp;
    }
    if ( y2 < y1 ) 
	{
        int tmp=y2;
        y2=y1;
        y1=tmp;
    }
    for (int tilex=x1; tilex <= x2; tilex++) {
    for (int tiley=y1; tiley <= y2; tiley++) {
        map->setProperties(tilex,tiley,true,true);
    }
	}
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2)
{
	auto engine = Engine::getSingleton();

    dig (x1,y1,x2,y2);
    if ( first ) 
	{
        // put the player in the first room
        engine->getPlayer()->getOwner()->get<Vec2i>("Position") = Vec2i( (x1+x2)/2, (y1+y2)/2 );
    } 
	else 
	{
        auto rng=TCODRandom::getInstance();
		int nbMonsters = rng->getInt(0,MAX_ROOM_MONSTERS);
		while (nbMonsters > 0) 
		{
			int x=rng->getInt(x1,x2);
			int y=rng->getInt(y1,y2);
			if ( canWalk(x,y) )
				addMonster(x,y);
			nbMonsters--;
		}
    }
}

void Map::addMonster(int x, int y) {
    auto rng = TCODRandom::getInstance();
	auto engine = Engine::getSingleton();
    if ( rng->getInt(0,100) < 80 ) 
	{
        // create an orc
		auto orc = engine->createActor("orc", x,y, 'o', TCODColor::desaturatedGreen);
		orc = engine->createMonster(orc, "corpse of an orc", 0.0f, 10.0f, 3.0f);
    } 
	else 
	{
        // create a troll            
		auto troll = engine->createActor("troll", x,y, 'T', TCODColor::darkerGreen);
		troll = engine->createMonster(troll, "corpse of a troll", 2.0f, 16.0f, 16.0f);
    }
}
