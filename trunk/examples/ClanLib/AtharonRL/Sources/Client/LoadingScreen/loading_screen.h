
#pragma once

#include "Engine/Client/UIFramework/ui_screen_manager.h"
#include "Engine/Client/UIFramework/ui_screen.h"

class UILabel;
class Game;

class LoadingScreen : public UIScreen
{
public:
	LoadingScreen(UIScreenManager *screen_manager, Game *game_test, clan::NetGameClient &network, const std::string &arg);

	virtual void update();
	virtual void on_activated();

private:
	Game *game;
	UILabel *label;
	clan::Image background;
	clan::NetGameClient &network;

	int hack_counter;
};
