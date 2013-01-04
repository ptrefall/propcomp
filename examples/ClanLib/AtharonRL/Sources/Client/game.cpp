
#include "precomp.h"
#include "game.h"
//#include "LoginScreen/login_screen.h"
//#include "LoadingScreen/loading_screen.h"
//#include "GameScreen/..."

using namespace clan;

Game::Game(const std::string &arg)
: screen_login(nullptr), screen_loading(nullptr), screen_ingame(nullptr)
{
	//screen_manager.reset(new UIScreenManager("Atharon, the Roguelike", Rect(0,0, 80,43), false, arg+"/Resources/Fonts/terminal.png"));

	//screen_login = new LoginScreen(screen_manager.get(), this, network, arg+"/Resources/Backgrounds/Login.png");
	//screen_loading = new LoadingScreen(screen_manager.get(), this, network);

	slots.connect(network.sig_event_received(), this, &Game::on_event_received);
}

Game::~Game()
{
	//delete screen_login;
	//delete screen_loading;
}

void Game::run()
{
	change_to_login_screen();

	/*while( screen_manager->is_window_closed() == false )
	{
		screen_manager->update();
		screen_manager->render();
		network.process_events();
		clan::KeepAlive();
	}*/
}

void Game::change_to_login_screen()
{
	//screen_login->set_active();
}

void Game::change_to_loading_screen()
{
	//screen_loading->set_active();
}

void Game::change_to_game_screen()
{
	/*if (!screen_ingame)
		screen_ingame = new GameScreen(this, "WoWMaps/ab.continent", network);
	screen_ingame->set_active();*/
}

void Game::on_event_received(const NetGameEvent &e)
{
	cl_log_event("Network", "Event: %1", e.to_string());
}
