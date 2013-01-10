
#pragma once

#include "Engine/Client/UIFramework/ui_screen_manager.h"
#include "Engine/Client/UIFramework/ui_screen.h"
#include "Engine/Client/Scene/layer_manager.h"
#include "GameWorld/client_zone.h"

class Game;

class GameScreen : public UIScreen
{
public:
	GameScreen(UIScreenManager *screen_manager, Game *game, clan::NetGameClient &network, clan::ResourceManager &resources);

	void update();

private:
	void on_activated();

	void on_event_received(const clan::NetGameEvent &e);

	Game *game;

	std::string css_text;

	clan::NetGameClient &network;
	clan::SlotContainer slots;

	std::unique_ptr<LayerManager> layer_manager;
	std::shared_ptr<Layer> test_layer;

	std::unique_ptr<ClientZone> zone;
};
