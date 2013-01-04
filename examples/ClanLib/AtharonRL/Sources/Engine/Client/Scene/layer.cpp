#include "precomp.h"
#include "layer.h"

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

void Layer::set_background_color(const clan::Point &position, clan::Color color)
{
	if(position.x > size.x || position.y > size.y)
		return;

}

void Layer::set_foreground_color(const clan::Point &position, clan::Color color)
{
}

void Layer::set_character(const clan::Point &position, int character)
{
}
void Layer::set_character(const clan::Point &position, int character, clan::Color foreground_color)
{
}

void Layer::set_tile(const clan::Point &position, clan::Color background_color, clan::Color foreground_color, int character)
{
}
void Layer::set_tile(const clan::Point &position, const TileData &data)
{
}

void Layer::clear()
{
}
void Layer::clear(const TileData &default_data)
{
}
void Layer::clear(clan::Color background_color, clan::Color foreground_color, int character)
{
}

void Layer::draw(clan::Canvas &canvas, int x, int y)
{
}
