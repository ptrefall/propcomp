#include "MapManager.h"
#include "GameManager.h"
#include "Player.h"
#include "Entity.h"
#include "PropertyDefinitions.h"

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

		auto layer = std::make_shared<Map>(info->Layer, Vec2i(info->Width, info->Height));
		layer->groundInViewColor = info->GroundInViewColor;
		layer->wallInViewColor = info->WallInViewColor;
		layer->groundInMemoryColor = info->GroundInMemoryColor;
		layer->wallInMemoryColor = info->WallInMemoryColor;
		_mapLayers[info->Layer] = layer;
	}
}

void MapManager::render(const std::shared_ptr<TCODConsole> &canvas, MapLayer layer)
{
	auto player = GameManager::Get()->getPlayer()->Get();
	auto position = player->get<Vec2i>(PROPERTY_POSITION).get();
	auto radius = player->get<int>(PROPERTY_SIGHT_RADIUS).get();

	auto map = _mapLayers[layer];
	for(int x = 0; x < map->size.x; x++)
	{
		for(int y = 0; y < map->size.y; y++)
		{
			auto cell = Vec2i(x,y);
			if(isInFov(layer, cell))
			{
				auto distance = position.distance(cell);
				auto fadeMod = min(1.0f - (distance / (float)radius) + 0.75f - ((rand()%2+1)*0.025f), 1.0f);
				fadeMod *= fadeMod;
				canvas->setCharBackground(x,y, (isWall(layer, cell) ? map->wallInViewColor : map->groundInViewColor) * fadeMod);
			}
			else if(isExplored(layer, cell))
			{
				canvas->setCharBackground(x,y, isWall(layer, cell) ? map->wallInMemoryColor : map->groundInMemoryColor);
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
	_mapLayers[layer]->data->computeFov(pos.x, pos.y, radius, true, FOV_SHADOW);
}

