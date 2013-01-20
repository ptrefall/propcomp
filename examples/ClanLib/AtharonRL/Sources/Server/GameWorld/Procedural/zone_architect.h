#pragma once

#include <libtcod.hpp>
#include <memory>
class ZoneMap; typedef std::shared_ptr<ZoneMap> ZoneMapPtr;
class ZoneArchitect;

class BspTraversalListener : public ITCODBspCallback
{
public:
	BspTraversalListener(ZoneArchitect *architect) : architect(architect), room_num(0) {}
	~BspTraversalListener() {}

	bool visitNode(TCODBsp *node, void * userData) override;

private:
	ZoneArchitect *architect; // a map to dig
	int room_num; // room number
    int last_x,last_y; // center of the last room
};


class ZoneArchitect
{
public:
	ZoneArchitect(const ZoneMapPtr &map, int seed);
	~ZoneArchitect();

	//Only generate with entities the first time, later the entities
	//are stored and persisted in the database!
	void generate(bool withEntities);

protected:
	friend class BspTraversalListener;
	void dig(const clan::Vec2i &pos1, const clan::Vec2i &pos2);
    void create_room(bool first, const clan::Vec2i &pos1, const clan::Vec2i &pos2, bool withEntities);
	int get_room_min_size() const { return room_min_size; }
	int get_room_max_size() const { return room_max_size; }
	TCODRandom *get_rng() const { return rng; }

private:
	int room_min_size;
	int room_max_size;
	ZoneMapPtr map;
	int seed;
	TCODRandom *rng;
};
