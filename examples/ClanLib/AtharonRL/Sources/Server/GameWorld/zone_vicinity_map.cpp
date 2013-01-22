#include "precomp.h"
#include "zone_vicinity_map.h"
#include "zone.h"
#include "Procedural/zone_map.h"
#include "server_player.h"
#include "server_gameobject.h"
#include "Engine/Common/Network/netevents.h"
#include <algorithm>

using namespace Totem;
using namespace clan;

ZoneVicinityMap::ZoneVicinityMap(Zone *zone, const ZoneMapPtr &map, ServerPlayer *player, NetGameConnection *connection)
: zone(zone), map(map), player(player), connection(connection) 
{
}

ZoneVicinityMap::~ZoneVicinityMap()
{
	visible_map_tiles.clear();
}


void ZoneVicinityMap::sync_map_clear_dirty()
{
	for (size_t i = 0; i < visible_map_tiles.size(); i++)
	{
		auto position = visible_map_tiles[i];
	}
}

void ZoneVicinityMap::sync_map()
{
	// TODO; support component properties

	for (size_t i = 0; i < visible_map_tiles.size(); i++)
	{
		auto position = visible_map_tiles[i];
	}
}

bool ZoneVicinityMap::is_tile_in_visibility(const Vec2i &position) const
{
	return std::find(visible_map_tiles.begin(), visible_map_tiles.end(), position) != visible_map_tiles.end();
}
