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
	{
		for(unsigned int i = 0; i < layers.size(); i++)
		{
			if(layers[i]->getZDepth() == -1 || zdepth < layers[i]->getZDepth())
			{
				layer.setZDepth(zdepth);
				layers.insert(layers.begin()+i, &layer);
				return;
			}
		}

		layer.setZDepth(zdepth);
		layers.push_back(&layer);
	}
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