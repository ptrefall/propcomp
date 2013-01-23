#pragma once

#include <memory>

class IMapTile; typedef std::shared_ptr<IMapTile> IMapTilePtr;

class IMapTile
{
public:
	IMapTile(const clan::Vec2i &position, bool transparent, bool walkable) : position(position), transparent(transparent), walkable(walkable) {}
	virtual ~IMapTile() {}
	
	const clan::Vec2i &get_position() const { return position; }
	bool is_transparent() const { return transparent; }
	bool is_walkable() const { return walkable; }

	void set_position(const clan::Vec2i &position) { this->position = position; }
	void set_transparent(bool transparent = true) { this->transparent = transparent; }
	void set_walkable(bool walkable = true) { this->walkable = walkable; }

protected:
	clan::Vec2i position;
	bool transparent;
	bool walkable;
};
