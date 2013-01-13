#pragma once

struct TileData
{
	clan::Colorf background_color;
	clan::Colorf foreground_color;
	int character;
	//BlendType blender; //How character + foreground color interact with background color

	TileData(const clan::Colorf &background_color, const clan::Colorf &foreground_color, int character) 
		: background_color(background_color), foreground_color(foreground_color), character(character)
	{
	}

	TileData(const TileData &data) 
		: background_color(data.background_color), foreground_color(data.foreground_color), character(data.character)
	{
	}

	TileData() {}

	TileData &operator=(const TileData &rhs)
	{
		if(this == &rhs)
			return *this;

		background_color = rhs.background_color;
		foreground_color = rhs.foreground_color;
		character = rhs.character;
		return *this;
	}
};

class TileCharacterMapper;
struct LayerBitmap
{
	clan::Sprite bitmap;
	clan::Point glyph_size;
	TileCharacterMapper *mapper;

	LayerBitmap(const clan::Sprite &bitmap, const clan::Point &glyph_size, TileCharacterMapper *mapper)
		: bitmap(bitmap), glyph_size(glyph_size), mapper(mapper)
	{
	}
};

struct LayerDescription
{
	clan::Point offset;
	clan::Point size;
	TileData &default_tile;

	LayerDescription(const clan::Point &offset, const clan::Point &size, TileData &default_tile) : offset(offset), size(size), default_tile(default_tile) {}
	LayerDescription(const LayerDescription &descr) : offset(descr.offset), size(descr.size), default_tile(descr.default_tile) {}

	LayerDescription &operator=(const LayerDescription &rhs)
	{
		if(this == &rhs)
			return *this;

		offset = rhs.offset;
		size = rhs.size;
		default_tile = rhs.default_tile;
		return *this; 
	}
};

class Layer
{
public:
	Layer(const LayerDescription &description, const LayerBitmap &bitmap);
	~Layer();

	void set_background_color(const clan::Point &position, clan::Colorf color);

	void set_foreground_color(const clan::Point &position, clan::Colorf color);
	//void set_foreground_color(const clan::Point &position, clan::Colorf color, BlendType blending);

	void set_character(const clan::Point &position, int character);
	void set_character(const clan::Point &position, int character, clan::Colorf foreground_color);
	//void set_character(const clan::Point &position, int character, clan::Colorf foreground_color, BlendType blending);

	void set_tile(const clan::Point &position, clan::Colorf background_color, clan::Colorf foreground_color, int character);
	//void set_tile(const clan::Point &position, clan::Colorf background_color, clan::Colorf foreground_color, int character, BlendType blending);
	void set_tile(const clan::Point &position, const TileData &data);

	void clear();
	void clear(const TileData &default_data);
	void clear(clan::Colorf background_color, clan::Colorf foreground_color, int character);
	//void clear(clan::Colorf background_color, clan::Colorf foreground_color, int character, BlendType blending);

	void draw(clan::Canvas &canvas, int x, int y);

	void setZDepth(int zdepth) { this->zdepth = zdepth; }
	int getZDepth() const { return zdepth; }

private:
	bool valid(const clan::Point &position);
	clan::Point offset;
	clan::Point size;
	TileData default_tile;
	
	clan::Sprite bitmap;
	clan::Point glyph_size;
	TileCharacterMapper *mapper;

	std::vector<std::vector<TileData>> tilemap;

	int zdepth;
};