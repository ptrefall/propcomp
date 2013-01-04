#pragma once

struct TileData
{
	clan::Color background_color;
	clan::Color foreground_color;
	int character;
	//BlendType blender; //How character + foreground color interact with background color

	TileData(const clan::Color &background_color, const clan::Color &foreground_color, int character) 
		: background_color(background_color), foreground_color(foreground_color), character(character)
	{
	}

	TileData(const TileData &data) 
		: background_color(data.background_color), foreground_color(data.foreground_color), character(data.character)
	{
	}

	TileData() {}
};

class TileCharacterMapper;
struct LayerBitmap
{
	clan::Image bitmap;
	clan::Point glyph_size;
	TileCharacterMapper *mapper;
};

struct LayerDescription
{
	clan::Point offset;
	clan::Point size;
	const TileData &default_tile;
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

private:
	clan::Point offset;
	clan::Point size;
	TileData default_tile;
	
	clan::Image bitmap;
	clan::Point glyph_size;
	TileCharacterMapper *mapper;

	std::vector<std::vector<TileData>> tilemap;
};