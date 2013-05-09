#pragma once

#include <libtcod.hpp>
#include <memory>
#include <vector>

class Visual;

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	void render();

	void add(Visual *visual, int layer);
	bool remove(Visual *visual, int layer);

	enum CanvasLayer
	{
		LAYER_MAP,
		LAYER_CLUTTER,
		LAYER_ITEM,
		LAYER_CORPSE,
		LAYER_ACTOR
	};

private:
	class Canvas
	{
	public:
		Canvas(int layer) : layer(layer) {}
		~Canvas() {}

		const int layer;
		std::shared_ptr<TCODConsole> console;
		std::vector<Visual*> visuals;
	};
	std::vector<std::shared_ptr<Canvas>> _canvasLayers;

	std::shared_ptr<Canvas> find(int layer);

	static bool SortCanvas(const std::shared_ptr<Canvas> &a, const std::shared_ptr<Canvas> &b)
	{
		return a->layer < b->layer;
	}
};
