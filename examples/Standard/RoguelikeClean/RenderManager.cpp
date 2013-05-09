#include "RenderManager.h"
#include "Components/Visual.h"

#include <algorithm>

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::render()
{
	for(auto layer : _canvasLayers)
	{
		for(auto visual : layer->visuals)
		{
			visual->render(layer->console);
		}
		TCODConsole::blit(layer->console.get(), 0,0, layer->console->getWidth(), layer->console->getHeight(), TCODConsole::root, 0,0);
		layer->console->clear();
	}
}

void RenderManager::add(Visual *visual, int layer)
{
	auto canvasLayer = find(layer);
	if(canvasLayer == nullptr)
	{
		canvasLayer = std::make_shared<Canvas>(layer);
		canvasLayer->console = std::make_shared<TCODConsole>(TCODConsole::root->getWidth(), TCODConsole::root->getHeight());
		
		_canvasLayers.push_back(canvasLayer);
		sort( _canvasLayers.begin(), _canvasLayers.end(), RenderManager::SortCanvas );
	}
	
	canvasLayer->visuals.push_back(visual);
}

bool RenderManager::remove(Visual *visual, int layer)
{
	auto canvasLayer = find(layer);
	if(canvasLayer)
	{
		for(auto it = canvasLayer->visuals.begin(); it != canvasLayer->visuals.end(); ++it)
		{
			if((*it) == visual)
			{
				canvasLayer->visuals.erase(it);
				if(canvasLayer->visuals.empty())
				{
					for(auto it2 = _canvasLayers.begin(); it2 != _canvasLayers.end(); ++it2)
					{
						if((*it2) == canvasLayer)
						{
							_canvasLayers.erase(it2);
							sort( _canvasLayers.begin(), _canvasLayers.end(), RenderManager::SortCanvas );
							return true;
						}
					}
				}
				return true;
			}
		}
	}

	return false;
}

std::shared_ptr<RenderManager::Canvas> RenderManager::find(int layer)
{
	for(auto canvasLayer : _canvasLayers)
	{
		if(canvasLayer->layer == layer)
			return canvasLayer;
	}

	return nullptr;
}
