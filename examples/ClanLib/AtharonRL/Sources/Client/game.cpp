
#include "precomp.h"
#include "game.h"
#include "Engine/Client/UIFramework/window_manager.h"
#include "LoginScreen/login_screen.h"
#include "CharacterSelectionScreen/character_selection_screen.h"
#include "LoadingScreen/loading_screen.h"
//#include "GameScreen/..."

using namespace clan;

Game::Game(const std::string &arg)
: screen_login(nullptr), screen_loading(nullptr), screen_ingame(nullptr)
{
	resources = new clan::ResourceManager(arg+"Resources/resources.xml");

	ScreenInfo screen_info;
	int primary_screen_index = 0;
	std::vector<Rect> screen_boxes = screen_info.get_screen_geometries(primary_screen_index);

	OpenGLWindowDescription desc;
	desc.set_title("Atharon, the Roguelike Client");
	desc.set_size(Size(screen_boxes[primary_screen_index].get_width() * 90 / 100, (screen_boxes[primary_screen_index].get_height() - 50) * 90 / 100), true);
	desc.set_allow_resize(true);

	screen_manager.reset(new UIScreenManager(desc, arg+"Resources/Icons/gameide-48.png", arg+"Resources/Icons/gameide-16.png"));
	screen_manager->hide_cursor();
	screen_manager->maximize();

	sound_output = SoundOutput(44100);
	screen_login = new LoginScreen(screen_manager.get(), this, network, arg);
	screen_character_selection = new CharacterSelectionScreen(screen_manager.get(), this, network, arg);
	screen_loading = new LoadingScreen(screen_manager.get(), this, network, arg);

	slots.connect(network.sig_event_received(), this, &Game::on_event_received);
}

Game::~Game()
{
	delete screen_login;
	delete screen_loading;
}

void Game::run()
{
	screen_manager->get_window().show();
	change_to_login_screen();

	InputContext ic = screen_manager->get_window().get_ic();
	while (!ic.get_keyboard().get_keycode(keycode_escape))
	{
		music_player.update();
		screen_manager->update();
		KeepAlive::process();
	}

	screen_manager->get_window().hide();
}

void Game::change_to_login_screen()
{
	screen_login->set_active();
}

void Game::change_to_character_selection_screen()
{
	screen_character_selection->set_active();
}

void Game::change_to_loading_screen()
{
	screen_loading->set_active();
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
