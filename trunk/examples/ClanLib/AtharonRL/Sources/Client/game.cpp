
#include "precomp.h"
#include "game.h"
#include "Engine/Client/UIFramework/window_manager.h"
#include "LoginScreen/login_screen.h"
#include "CharacterSelectionScreen/character_selection_screen.h"
#include "LoadingScreen/loading_screen.h"
#include "GameScreen/game_screen.h"

using namespace clan;

Game::Game(const std::string &arg)
: screen_login(nullptr), screen_character_selection(nullptr), screen_loading(nullptr), screen_ingame(nullptr)
{
	std::string base_dir = clan::System::get_exe_path();
	base_dir = base_dir.substr(0, base_dir.find_last_of("\\"));
	base_dir = base_dir.substr(0, base_dir.find_last_of("\\"));
	base_dir = base_dir.substr(0, base_dir.find_last_of("\\"));

	clan::VirtualFileSystem vfs(base_dir);
	clan::VirtualDirectory vd(vfs, "Resources");

	resources = new clan::ResourceManager(vd.open_file("resources.xml"), vd);
	
	auto font_dir = vd.open_directory("Fonts");
	auto font_dir_list = font_dir.get_directory_listing();
	while(true)
	{
		auto font_file = font_dir_list.get_filename();
		if(font_file.find(".xml") == std::string::npos)
		{
			if( font_dir_list.next() == false )
				break;
			else
				continue;
		}

		resources->add_resources(clan::ResourceManager(font_dir.open_file(font_file), font_dir));

		if( font_dir_list.next() == false )
			break;
	}

	auto engine_dir = vd.open_directory("Engine");
	auto engine_dir_list = engine_dir.get_directory_listing();
	while(true)
	{
		auto engine_file = engine_dir_list.get_filename();
		if(engine_file.find(".xml") == std::string::npos)
		{
			if( engine_dir_list.next() == false )
				break;
			else
				continue;
		}

		resources->add_resources(clan::ResourceManager(engine_dir.open_file(engine_file), engine_dir));

		if( engine_dir_list.next() == false )
			break;
	}

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
	screen_login = new LoginScreen(screen_manager.get(), this, network, *resources);
	screen_character_selection = new CharacterSelectionScreen(screen_manager.get(), this, network, *resources);
	screen_loading = new LoadingScreen(screen_manager.get(), this, network, *resources);

	slots.connect(network.sig_event_received(), this, &Game::on_event_received);
}

Game::~Game()
{
	delete screen_login;
	delete screen_character_selection;
	delete screen_loading;
	if(screen_ingame)
		delete screen_ingame;
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
	if (screen_ingame == nullptr)
		screen_ingame = new GameScreen(screen_manager.get(), this, network, *resources);
		//screen_ingame = new GameScreen(this, "WoWMaps/ab.continent", network);
	screen_ingame->set_active();
}

void Game::on_event_received(const NetGameEvent &e)
{
	cl_log_event("Network", "Event: %1", e.to_string());
}
