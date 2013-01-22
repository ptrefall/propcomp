
#pragma once

#include "map_tile_interface.h"

class FieldOfView
{
public:
	enum FieldOfViewAlgorithm
	{
		FOV_SHADOWCASTING = 0
	};
	static std::vector<IMapTilePtr> find_visible_tiles(	const std::vector<IMapTilePtr> &map, const clan::Vec2i &map_size, 
														const clan::Vec2i &source_position, int max_radius = 0, 
														bool light_walls = true, FieldOfViewAlgorithm algorithm = FOV_SHADOWCASTING);
};
