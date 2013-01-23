#pragma once

#include "Engine/Common/GameWorld/map_tile_interface.h"

class ClientMapTile; typedef std::shared_ptr<ClientMapTile> ClientMapTilePtr;

class ClientMapTile : public MapTileInterface
{
public:
	ClientMapTile(const clan::Vec2i &position) : MapTileInterface(position), destroyed(false) {}
	virtual ~ClientMapTile() {}

	void update(float time_elapsed) {}
	bool is_destroyed() const { return destroyed; }

protected:
	bool destroyed;
};
