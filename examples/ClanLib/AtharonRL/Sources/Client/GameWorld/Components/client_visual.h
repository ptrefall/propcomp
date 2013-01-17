
#pragma once

#include "Engine/Common/GameWorld/Components/visual.h"

class LayerManager; typedef std::shared_ptr<LayerManager> LayerManagerPtr;
class Layer; typedef std::shared_ptr<Layer> LayerPtr;

class ClientVisual : public Visual
{
public:
	ClientVisual(GameObject *owner, const std::string &name, const LayerManagerPtr &layer_manager);
	virtual ~ClientVisual();

	void update(const float &delta_time) override;

private:
	LayerManagerPtr layer_manager;
	LayerPtr character_layer;
	LayerPtr dungeon_layer;

	Totem::Property<clan::Vec2i> position_property;
};
