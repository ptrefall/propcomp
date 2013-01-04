#include "precomp.h"
#include "layer_manager.h"
#include "layer.h"

LayerManager::LayerManager()
{
}
LayerManager::~LayerManager()
{
}

void LayerManager::add(Layer &layer, int zdepth)
{
	if(zdepth == -1)
		layers.push_back(&layer);
	else
		layers.insert(layers.begin()+zdepth, &layer);
}
void LayerManager::remove(const Layer &layer)
{
	for(unsigned int i = 0; i < layers.size(); i++)
	{
		if(layers[i] == &layer)
		{
			layers.erase(layers.begin()+i);
			return;
		}
	}
}
void LayerManager::draw(clan::Canvas &canvas, int x, int y)
{
	for(unsigned int i = 0; i < layers.size(); i++)
	{
		layers[i]->draw(canvas, x,y);
	}
}