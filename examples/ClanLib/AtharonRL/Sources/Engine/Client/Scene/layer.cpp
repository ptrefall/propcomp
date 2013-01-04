#include "precomp.h"
#include "layer.h"
#include "tile_character_mapper.h"

Layer::Layer(const LayerDescription &description, const LayerBitmap &bitmap)
	: offset(description.offset), size(description.size), default_tile(description.default_tile),
	  bitmap(bitmap.bitmap), glyph_size(bitmap.glyph_size), mapper(bitmap.mapper)
{
	tilemap.reserve(size.x);
	for(int x = 0; x < size.x; x++)
	{
		tilemap[x].reserve(size.y);
		for(int y = 0; y < size.y; y++)
		{
			tilemap[x].push_back(default_tile);
		}
	}
}
Layer::~Layer()
{
}

bool Layer::valid(const clan::Point &position)
{
	if(position.x >= size.x || position.y >= size.y)
		return false;
	else if(position.x < 0 || position.y < 0)
		return false;
	else return true;
}

void Layer::set_background_color(const clan::Point &position, clan::Color color)
{
	if( !valid(position) )
		return;

	tilemap[position.x][position.y].background_color = color;
}

void Layer::set_foreground_color(const clan::Point &position, clan::Color color)
{
	if( !valid(position) )
		return;

	tilemap[position.x][position.y].foreground_color = color;
}

void Layer::set_character(const clan::Point &position, int character)
{
	if( !valid(position) )
		return;

	tilemap[position.x][position.y].character = mapper->filter(character);
}
void Layer::set_character(const clan::Point &position, int character, clan::Color foreground_color)
{
	set_foreground_color(position, foreground_color);
	set_character(position, character);
}

void Layer::set_tile(const clan::Point &position, clan::Color background_color, clan::Color foreground_color, int character)
{
	set_background_color(position, background_color);
	set_foreground_color(position, foreground_color);
	set_character(position, character);
}
void Layer::set_tile(const clan::Point &position, const TileData &data)
{
	set_background_color(position, data.background_color);
	set_foreground_color(position, data.foreground_color);
	set_character(position, data.character);
}

void Layer::clear()
{
	for(int x = 0; x < size.x; x++)
	{
		for(int y = 0; y < size.y; y++)
		{
			tilemap[x][y] = default_tile;
		}
	}
}
void Layer::clear(const TileData &default_data)
{
	this->default_tile = default_data;
	clear();
}
void Layer::clear(clan::Color background_color, clan::Color foreground_color, int character)
{
	default_tile = TileData(background_color, foreground_color, character);
	clear();
}

void Layer::draw(clan::Canvas &canvas, int x, int y)
{
}
