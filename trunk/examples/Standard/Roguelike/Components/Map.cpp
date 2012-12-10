#include "Map.h"
#include "Actor.h"
#include "../Systems/RenderSystem.h"
#include "../Engine.h"
#include "../Utils/BspListener.h"

#include "Destructible.h"
#include "Attacker.h"
#include "Monster.h"
#include "Pickable.h"
#include "Consumable.h"
#include "Magic/Healer.h"

#include <iostream>

Map::Map(const EntityWPtr &owner, int width, int height, const RenderSystemPtr &system) 
: Totem::Component<Map, PropertyUserData>("Map"), owner(owner), width(width), height(height), system(system), currentScentValue(SCENT_THRESHOLD)
{
	user_data.entity = owner;
	user_data.component = this;

	tiles=new Tile[width*height];
	map=new TCODMap(width,height);

    TCODBsp bsp(0,0,width,height);
    bsp.splitRecursive(nullptr,8,ROOM_MAX_SIZE,ROOM_MAX_SIZE,1.75f,1.75f);
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

		auto pos = Vec2i(x,y);
		int scent=SCENT_THRESHOLD - (currentScentValue - getScent(pos));
        scent = CLAMP(0,10,scent);
        float sc=scent * 0.1f;

        if ( isInFov(pos) )
            TCODConsole::root->setCharBackground(x,y, isWall(pos) ? lightWall :lightGround * sc );
        else if ( isExplored(pos) )
            TCODConsole::root->setCharBackground(x,y, isWall(pos) ? darkWall : darkGround * sc);
		else if ( !isWall(pos) )
			TCODConsole::root->setCharBackground(x,y, TCODColor::white * sc);
    }}
}

unsigned int Map::getScent(const Vec2i &pos) const {
    return tiles[pos.x()+pos.y()*width].scent;
}

bool Map::isWall(const Vec2i &pos) const {
    return !map->isWalkable(pos.x(), pos.y());
}

bool Map::isExplored(const Vec2i &pos) const {
    return tiles[pos.x()+pos.y()*width].explored;
}

bool Map::isInFov(const Vec2i &pos) const {
	if ( pos.x() < 0 || pos.x() >= width || pos.y() < 0 || pos.y() >= height ) {
        return false;
    }
    if ( map->isInFov(pos.x(), pos.y()) ) {
        tiles[pos.x()+pos.y()*width].explored=true;
        return true;
    }
    return false;
}
 
void Map::computeFov() {
	auto engine = Engine::getSingleton();
	auto player = engine->getPlayer();
	map->computeFov(player->x(),player->y(),
        engine->fovRadius);

	if(player->isDead())
		return;

	// update scent field
    for (int x=0; x < width; x++) 
	{
        for (int y=0; y < height; y++) 
		{
			auto pos = Vec2i(x,y);
            if (isInFov(pos)) 
			{
                unsigned int oldScent=getScent(pos);
				auto distance = pos.distance(player->getPosition());
                unsigned int newScent=currentScentValue-distance;
                if (newScent > oldScent) {
                    tiles[x+y*width].scent = newScent;
                }
            }
        }
    }
}

bool Map::canWalk(const Vec2i &pos) const
{
    if (isWall(pos)) {
        // this is a wall
        return false;
    }
	auto actors = Engine::getSingleton()->getActors();
    for (unsigned int i = 0; i < actors.size(); i++) {
        auto actor = actors[i];
        if ( actor->blocksTile() && actor->getPosition() == pos ) {
            // there is a blocking actor there. cannot walk
            return false;
        }
    }
    return true;
}

void Map::dig(const Vec2i &pos1, const Vec2i &pos2) 
{
	int x1 = pos1.x();
	int x2 = pos2.x();
	int y1 = pos1.y();
	int y2 = pos2.y();

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

void Map::createRoom(bool first, const Vec2i &pos1, const Vec2i &pos2)
{
	auto engine = Engine::getSingleton();

	int x1 = pos1.x();
	int x2 = pos2.x();
	int y1 = pos1.y();
	int y2 = pos2.y();

    dig (pos1,pos2);
    if ( first ) 
	{
        // put the player in the first room
        engine->getPlayer()->getOwner()->get<Vec2i>("Position") = Vec2i( (x1+x2)/2, (y1+y2)/2 );
    } 
	else 
	{
        auto rng=TCODRandom::getInstance();

		// add monsters
		int nbMonsters = rng->getInt(0,MAX_ROOM_MONSTERS);
		while (nbMonsters > 0) 
		{
			auto rngPos = Vec2i(rng->getInt(x1,x2), rng->getInt(y1,y2));
			if ( canWalk(rngPos) )
				addMonster(rngPos);
			nbMonsters--;
		}

		// add items
		int nbItems = rng->getInt(0,MAX_ROOM_ITEMS);
		while (nbItems > 0) 
		{
			auto rngPos = Vec2i(rng->getInt(x1,x2), rng->getInt(y1,y2));
			if ( canWalk(rngPos) )
				addItem(rngPos);
			nbItems--;
		}
    }
}

void Map::addMonster(const Vec2i &pos) {
    auto rng = TCODRandom::getInstance();
	auto engine = Engine::getSingleton();
    if ( rng->getInt(0,100) < 80 ) 
	{
        // create an orc
		auto orc = engine->createActor("orc", pos, 'o', TCODColor::desaturatedGreen);
		orc = engine->createMonster(orc, "corpse of an orc", 0.0f, 10.0f, 3.0f);
    } 
	else 
	{
        // create a troll            
		auto troll = engine->createActor("troll", pos, 'T', TCODColor::darkerGreen);
		troll = engine->createMonster(troll, "corpse of a troll", 2.0f, 16.0f, 16.0f);
    }
}

void Map::addItem(const Vec2i &pos) {
	auto engine = Engine::getSingleton();

	auto healthPotion = engine->createActor("health potion", pos, '!', TCODColor::violet);
	healthPotion->addComponent( std::make_shared<Pickable>(healthPotion, system) );
	healthPotion->addComponent( std::make_shared<Consumable>(healthPotion) );
	healthPotion->addComponent( std::make_shared<Healer>(healthPotion, 30.0f) );
	healthPotion->get<bool>("Blocks") = false;
}