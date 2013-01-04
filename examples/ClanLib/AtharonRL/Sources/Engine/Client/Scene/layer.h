#pragma once

struct TileData
{
	clan::Color background_color;
	clan::Color foreground_color;
	int character;
	//BlendType blender; //How character + foreground color interact with background color
};

class TileCharacterMapper;
struct LayerBitmap
{
	clan::Image bitmap;
	clan::Point bitmap_character_size;
	TileCharacterMapper *mapper;
};

struct LayerDescription
{
	clan::Point offset;
	clan::Point size;
	TileData *default_tile;
};

class Layer
{
public:
	Layer(const LayerDescription &description, const LayerBitmap &bitmap);
	~Layer();

	void set_background_color(const clan::Point &position, clan::Color color);

	void set_foreground_color(const clan::Point &position, clan::Color color);
	//void set_foreground_color(const clan::Point &position, clan::Color color, BlendType blending);

	void set_character(const clan::Point &position, int character);
	void set_character(const clan::Point &position, int character, clan::Color foreground_color);
	//void set_character(const clan::Point &position, int character, clan::Color foreground_color, BlendType blending);

	void set_tile(const clan::Point &position, clan::Color background_color, clan::Color foreground_color, int character);
	//void set_tile(const clan::Point &position, clan::Color background_color, clan::Color foreground_color, int character, BlendType blending);
	void set_tile(const clan::Point &position, const TileData &data);

	void clear();
	void clear(const TileData &default_data);
	void clear(clan::Color background_color, clan::Color foreground_color, int character);
	//void clear(clan::Color background_color, clan::Color foreground_color, int character, BlendType blending);

	void draw(clan::Canvas &canvas, int x, int y);
};