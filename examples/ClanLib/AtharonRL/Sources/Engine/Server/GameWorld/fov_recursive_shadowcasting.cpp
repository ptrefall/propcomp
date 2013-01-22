
#include "precomp.h"
#include "fov_recursive_shadowcasting.h"

using namespace clan;

//Encapsulate in anonymous namespace to prevent globalization
namespace 
{
	static int mult[4][8] = {
		{1,0,0,-1,-1,0,0,1},
		{0,1,-1,0,0,-1,1,0},
		{0,1,1,0,0,-1,-1,0},
		{1,0,0,1,-1,0,0,-1},
	};
}

FOVRecursiveShadowcasting::FOVRecursiveShadowcasting()
{
}

FOVRecursiveShadowcasting::~FOVRecursiveShadowcasting()
{
}

std::vector<IMapTilePtr> FOVRecursiveShadowcasting::find_visible_tiles(	const std::vector<IMapTilePtr> &map, const clan::Vec2i &map_size, 
																		const clan::Vec2i &source_position, int max_radius, bool light_walls)
{
	std::vector<IMapTilePtr> vicinity_map;

	if ( max_radius == 0 ) 
	{
		Vec2i max_radius_vec = map_size - source_position;
		max_radius_vec.x = max(max_radius_vec.x, source_position.x);
		max_radius_vec.y = max(max_radius_vec.y, source_position.y);
		max_radius = max_radius_vec.length();
	}

	int r2 = max_radius * max_radius;

	/* recursive shadow casting */
	for(int oct = 0; oct < 8; oct++) 
	{
		cast_light(	map, map_size, source_position, 
					1, 1.0, 0.0, 
					max_radius, r2, 
					mult[0][oct], mult[1][oct], mult[2][oct], mult[3][oct], 
					0, light_walls, 
					vicinity_map);
	}

	//make sure the source can see itself
	vicinity_map.push_back(map[to_index(source_position, map_size.x)]);

	return vicinity_map;
}

void FOVRecursiveShadowcasting::cast_light(const std::vector<IMapTilePtr> &map, const clan::Vec2i &map_size, const clan::Vec2i &source_position, 
				int row, float start, float end, 
				int radius, int r2, 
				int xx, int xy, int yx, int yy, 
				int id, bool light_walls,
				std::vector<IMapTilePtr> &vicinity_map)
{
	float new_start = 0.0f;
	
	if( start < end ) 
		return;

	for(int j = row; j < radius+1; j++) 
	{
		int dx = -j-1;
		int dy = -j;
		bool blocked = false;

		while( dx <= 0 ) 
		{
			Vec2i current_position;
			dx++;

			current_position.x = source_position.x + dx*xx + dy*xy;
			current_position.y = source_position.y + dx*yx + dy*yy;

			if(current_position < map_size) 
			{
				int offset = to_index(current_position, map_size.x);
				float l_slope = (dx-0.5f) / (dy+0.5f);
				float r_slope = (dx+0.5f) / (dy-0.5f);
				
				if( start < r_slope ) 
					continue;

				else if( end > l_slope ) 
					break;

				if( dx*dx + dy*dy <= r2 && (light_walls || map[offset]->is_transparent())) 
					vicinity_map.push_back(map[offset]);

				if(blocked) 
				{
					if( !map[offset]->is_transparent() ) 
					{
						new_start = r_slope;
						continue;
					} 
					else 
					{
						blocked = false;
						start = new_start;
					}
				} 
				else 
				{
					if( !map[offset]->is_transparent() && j < radius ) 
					{
						blocked = true;
						cast_light(	map, map_size, source_position, 
									j+1, start, l_slope, 
									radius, r2,
									xx, xy, yx, yy,
									id+1, light_walls,
									vicinity_map);

						new_start = r_slope;
					}
				}
			}
		}
		if(blocked) 
		{
			break;
		}
	}
}
