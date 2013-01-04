#pragma once

class Layer;

class LayerManager
{
public:
	LayerManager();
	~LayerManager();

	void add(Layer &layer, int zdepth = -1); //If zdepth is -1, it's pushed to the back of the layer list
	void remove(const Layer &layer);

	void draw(clan::Canvas &canvas, int x, int y);

private:
	std::vector<Layer*> layers;
};