#include "precomp.h"
#include "layer.h"
#include "tile_character_mapper.h"

Layer::Layer(const std::string &name, const LayerDescription &description, const LayerBitmap &bitmap)
	: name(name), offset(description.offset), size(description.size), default_tile(description.default_tile),
	  bitmap(bitmap.bitmap), glyph_size(bitmap.glyph_size), mapper(bitmap.mapper)
{
	this->bitmap.set_frame(64);
	this->bitmap.set_color(default_tile.foreground_color);
	tilemap.resize(size.x*size.y);
	for(int i = 0; i < size.x*size.y; i++)
		tilemap.push_back(default_tile);
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

int Layer::to_index(const clan::Point &position)
{
	return (position.y*size.x)+position.x;
}

void Layer::set_background_color(const clan::Point &position, clan::Colorf color)
{
	if( !valid(position) )
		return;

	tilemap[to_index(position)].background_color = color;
}

void Layer::set_foreground_color(const clan::Point &position, clan::Colorf color)
{
	if( !valid(position) )
		return;

	tilemap[to_index(position)].foreground_color = color;
}

void Layer::set_character(const clan::Point &position, int character)
{
	if( !valid(position) )
		return;

	tilemap[to_index(position)].character = mapper->filter(character);
}
void Layer::set_character(const clan::Point &position, int character, clan::Colorf foreground_color)
{
	set_foreground_color(position, foreground_color);
	set_character(position, character);
}

void Layer::set_tile(const clan::Point &position, clan::Colorf background_color, clan::Colorf foreground_color, int character)
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
			tilemap[to_index(clan::Point(x,y))] = default_tile;
		}
	}
}
void Layer::clear(const TileData &default_data)
{
	this->default_tile = default_data;
	clear();
}
void Layer::clear(clan::Colorf background_color, clan::Colorf foreground_color, int character)
{
	default_tile = TileData(background_color, foreground_color, character);
	clear();
}

void Layer::draw(clan::Canvas &canvas, int /*x*/, int /*y*/)
{
	for(int x = 0; x < size.x; x++)
	{
		for(int y = 0; y < size.y; y++)
		{
			float dx = x*(float)glyph_size.x;
			float dy = y*(float)glyph_size.y;

			auto &tile = tilemap[to_index(clan::Point(x,y))];
			canvas.fill(clan::Rectf(dx, dy, dx+(float)glyph_size.x, dy+(float)glyph_size.y), tile.background_color);
			bitmap.set_color(tile.foreground_color);
			bitmap.set_frame(tile.character);
			bitmap.draw(canvas, dx, dy);
		}
	}
}
