#pragma once

#include <memory> 

class Layer; typedef std::shared_ptr<Layer> LayerPtr;

class LayerManager
{
public:
	LayerManager();
	~LayerManager();

	void add(const LayerPtr &layer, int zdepth = -1); //If zdepth is -1, it's pushed to the back of the layer list
	void remove(const LayerPtr &layer);

	void draw(clan::Canvas &canvas, int x, int y);

private:
	std::vector<LayerPtr> layers;
};