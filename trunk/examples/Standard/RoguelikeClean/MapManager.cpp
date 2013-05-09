#include "MapManager.h"

using namespace clan;

MapManager::MapManager()
{
}

MapManager::~MapManager()
{
}

void MapManager::initialize(const Parser::MapsInfo &mapsInfo)
{
	_mapLayers.resize(MAP_LAYER_COUNT, nullptr);

	for(auto info : mapsInfo.Maps)
	{
		if(info->Layer < 0 || info->Layer >= MAP_LAYER_COUNT)
			continue;

		_mapLayers[info->Layer] = std::make_shared<Map>(info->Layer, Vec2i(info->Width, info->Height));
	}
}

void MapManager::render(const std::shared_ptr<TCODConsole> &canvas, MapLayer layer)
{
	auto map = _mapLayers[layer];
	for(int x = 0; x < map->size.x; x++)
	{
		for(int y = 0; y < map->size.y; y++)
		{
			if(isInFov(layer, Vec2i(x,y)))
			{
				canvas->setCharBackground(x,y, isWall(layer, Vec2i(x,y)) ? map->wallInViewColor : map->groundInViewColor);
			}
			else if(isExplored(layer, Vec2i(x,y)))
			{
				canvas->setCharBackground(x,y, isWall(layer, Vec2i(x,y)) ? map->wallInMemoryColor : map->groundInMemoryColor);
			}
		}
	}
}

bool MapManager::isInFov(MapLayer layer, const clan::Vec2i &pos) const
{
	auto map = _mapLayers[layer];
	if(map->data->isInFov(pos.x, pos.y))
	{
		map->tiles[ _toIndex(pos,map->size.x) ]->explored = true;
		return true;
	}

	return false;
}

bool MapManager::isWall(MapLayer layer, const clan::Vec2i &pos) const
{
	return !_mapLayers[layer]->data->isWalkable(pos.x, pos.y);
}

bool MapManager::isExplored(MapLayer layer, const clan::Vec2i &pos) const
{
	auto map = _mapLayers[layer];
	return map->tiles[ _toIndex(pos,map->size.x) ]->explored;
}

void MapManager::computeFov(MapLayer layer, const clan::Vec2i &pos, int radius)
{
	_mapLayers[layer]->data->computeFov(pos.x, pos.y, radius);
}

