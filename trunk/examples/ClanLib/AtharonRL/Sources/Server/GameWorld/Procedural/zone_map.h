#pragma once

#include <libtcod.hpp>

class ZoneMap
{
public:
	ZoneMap(const clan::Vec2i &size);
	~ZoneMap();

	int get_width() const { return size.x; }
	int get_height() const { return size.y; }

	void setProperties(const clan::Vec2i &pos, bool transparent, bool walkable);

private:
	clan::Vec2i size;

	//This needs to be modified to work per player...
	struct Tile 
	{
		bool explored; // has the player already seen this tile ?
		unsigned int scent; // amount of player scent on this cell
		Tile() : explored(false), scent(0) {}
	};
	Tile *tiles;
	TCODMap *map;
};
