#pragma once

#include <memory>

class IMapTile; typedef std::shared_ptr<IMapTile> IMapTilePtr;

class IMapTile
{
public:
	IMapTile(bool transparent, bool walkable, const clan::Vec2i &position) : transparent(transparent), walkable(walkable), position(position) {}
	virtual ~IMapTile() {}
	
	bool is_transparent() const { return transparent; }
	bool is_walkable() const { return walkable; }
	clan::Vec2i get_position() const { return position; }

	void set_transparent(bool transparent = true) { this->transparent = transparent; }
	void set_walkable(bool walkable = true) { this->walkable = walkable; }
	void set_position(const clan::Vec2i &position) { this->position = position; }

protected:
	bool transparent;
	bool walkable;
	clan::Vec2i position;
};
