#pragma once

#include <memory>

class UIScreen;
class ClientGameObject;
class ClientZone;
class LayerManager; typedef std::shared_ptr<LayerManager> LayerManagerPtr;

class ClientComponentFactory
{
public:
	ClientComponentFactory(UIScreen *screen, ClientZone *zone, const LayerManagerPtr &layer_manager);

	void create_and_add_component(ClientGameObject *owner, const std::string &type, const std::string &name);

private:
	UIScreen *screen;
	ClientZone *zone;
	LayerManagerPtr layer_manager;
};
