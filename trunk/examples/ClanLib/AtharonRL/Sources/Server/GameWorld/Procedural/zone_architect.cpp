#include "precomp.h"
#include "zone_architect.h"
#include "zone_map.h"

using namespace clan;

bool BspTraversalListener::visitNode(TCODBsp *node, void *userData)
{
	if ( node->isLeaf() ) 
	{
		int x,y,w,h;
		int room_min_size = architect->get_room_min_size();
		// dig a room
		TCODRandom *rng = architect->get_rng();
		w = rng->getInt(room_min_size, node->w-2);
		h = rng->getInt(room_min_size, node->h-2);
		x = rng->getInt(node->x+1, node->x+node->w-w-1);
		y = rng->getInt(node->y+1, node->y+node->h-h-1);
		architect->create_room(room_num == 0, Vec2i(x, y), Vec2i(x+w-1, y+h-1), (bool)userData);

		if ( room_num != 0 ) 
		{
			// dig a corridor from last room
			architect->dig( Vec2i(last_x,last_y), Vec2i(x+w/2,last_y) );
			architect->dig( Vec2i(x+w/2,last_y), Vec2i(x+w/2,y+h/2) );
		}
		else
		{
			last_x=x+w/2;
            last_y=y+h/2;
            room_num++;
        }
        return true;
	}
	return false;
}

ZoneArchitect::ZoneArchitect(const ZoneMapPtr &map, int seed)
	: map(map), seed(seed), room_min_size(3), room_max_size(20)
{
	if(seed == -1)
		seed = TCODRandom::getInstance()->getInt(0, 0x7FFFFFFF);

}

ZoneArchitect::~ZoneArchitect()
{
}

void ZoneArchitect::generate(bool withEntities)
{
	rng = new TCODRandom(seed, TCOD_RNG_CMWC);

	TCODBsp bsp(0,0,map->get_width(),map->get_height());
    bsp.splitRecursive(rng, 8, room_min_size, room_max_size, 1.75f, 1.75f);
    BspTraversalListener listener(this);
    bsp.traverseInvertedLevelOrder(&listener,(void*)withEntities);
}

void ZoneArchitect::dig(const Vec2i &pos1, const Vec2i &pos2)
{
	int x1 = pos1.x;
	int x2 = pos2.x;
	int y1 = pos1.y;
	int y2 = pos2.y;

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
	for (int tilex=x1; tilex <= x2; tilex++) 
	{
		for (int tiley=y1; tiley <= y2; tiley++) 
		{
			map->setProperties(Vec2i(tilex,tiley),true,true);
		}
	}
}

void ZoneArchitect::create_room(bool first, const Vec2i &pos1, const Vec2i &pos2, bool withEntities)
{
	int x1 = pos1.x;
	int x2 = pos2.x;
	int y1 = pos1.y;
	int y2 = pos2.y;

    dig (pos1,pos2);

	if(!withEntities)
		return;

	//Else, we add some entities to the room here, like items, monsters, etc
}
