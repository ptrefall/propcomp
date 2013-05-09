#pragma once

#include "Parser.h"

#include "Math/vec2.h"

#include <memory>
#include <vector>
#include <libtcod.hpp>

class MapManager
{
public:
	MapManager();
	~MapManager();

	enum MapLayer
	{
		LAYER_GROUND,
		LAYER_AIR,
		MAP_LAYER_COUNT
	};

	void initialize(const Parser::MapsInfo &mapsInfo);
	void render(const std::shared_ptr<TCODConsole> &canvas, MapLayer layer);

	bool isInFov(MapLayer layer, const clan::Vec2i &pos) const;
	bool isWall(MapLayer layer, const clan::Vec2i &pos) const;
    bool isExplored(MapLayer layer, const clan::Vec2i &pos) const;
    void computeFov(MapLayer layer, const clan::Vec2i &pos, int radius);

private:
	class Map
	{
	public:
		Map(int layer, const clan::Vec2i &size) 
			: layer(layer), size(size) 
		{ 
			data = std::make_shared<TCODMap>(size.x, size.y); 
			data->clear(true,true);
			data->setProperties(30,22, false,false);
			data->setProperties(50,22, false,false);
			tiles.resize(size.x*size.y, nullptr);
			for(unsigned int i = 0; i < tiles.size(); i++)
				tiles[i] = std::make_shared<Tile>();
		}
		~Map() {}

		struct Tile
		{
			bool explored;

			Tile() : explored(false) {}
		};

		const int layer;
		clan::Vec2i size;
		std::shared_ptr<TCODMap> data;
		std::vector<std::shared_ptr<Tile>> tiles;

		TCODColor wallInViewColor;
		TCODColor groundInViewColor;
		TCODColor wallInMemoryColor;
		TCODColor groundInMemoryColor;
	};

	std::vector<std::shared_ptr<Map>> _mapLayers;

	int _toIndex(const clan::Vec2i &pos, int width) const { return pos.x + pos.y * width; }
};