
#pragma once

#include "Engine/Client/UIFramework/ui_screen_manager.h"

class LoginScreen;
class LoadingScreen;
class GameScreen;

class Game
{
public:
	Game(const std::string &arg);
	~Game();

	void run();

	void change_to_login_screen();
	void change_to_loading_screen();
	void change_to_game_screen();

private:
	void on_event_received(const clan::NetGameEvent &e);
	
	std::unique_ptr<UIScreenManager> screen_manager;
	clan::NetGameClient network;

	std::string filename;

	LoginScreen *screen_login;
	LoadingScreen *screen_loading;
	GameScreen *screen_ingame;

	clan::SlotContainer slots;
};