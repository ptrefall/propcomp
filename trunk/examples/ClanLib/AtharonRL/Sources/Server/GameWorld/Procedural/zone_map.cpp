#include "precomp.h"
#include "zone_map.h"

using namespace clan;

ZoneMap::ZoneMap(const clan::Vec2i &size)
	: size(size)
{
	tiles=new Tile[size.x * size.y];
	map=new TCODMap(size.x,size.y);
}

ZoneMap::~ZoneMap()
{
	delete[] tiles;
	delete map;
}

void ZoneMap::setProperties(const Vec2i &pos, bool transparent, bool walkable)
{
	map->setProperties(pos.x, pos.y, transparent, walkable);
}
