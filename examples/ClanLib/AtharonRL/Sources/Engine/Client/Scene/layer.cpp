#include "precomp.h"
#include "layer.h"

Layer::Layer(const LayerDescription &description, const LayerBitmap &bitmap)
{
}
Layer::~Layer()
{
}

void Layer::set_background_color(const clan::Point &position, clan::Color color)
{
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
