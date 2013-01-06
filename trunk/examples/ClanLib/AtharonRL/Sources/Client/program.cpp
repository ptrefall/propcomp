
#include "precomp.h"
#include "program.h"
#include "game.h"
#include <ClanLib/application.h>

using namespace clan;

Application clanapp(&Program::main);

int Program::main(const std::vector<std::string> &args)
{
	try
	{
		SetupCore setup_core;
		SetupDisplay setup_display;
		SetupGL setup_gl;
		SetupGUI setup_gui;
		SetupNetwork setup_network;
		SetupSound setup_sound;
		SetupVorbis setup_vorbis;

		srand(System::get_time());

		ConsoleLogger logger;

		std::string base_dir = args[0];
		base_dir = base_dir.substr(0, base_dir.find_last_of("\\"));
		base_dir = base_dir.substr(0, base_dir.find_last_of("\\"));
		base_dir = base_dir.substr(0, base_dir.find_last_of("\\"));
		base_dir += "/";

		Game game(base_dir);
		game.run();

		return 0;
	}
	catch (Exception &e)
	{
		ConsoleWindow console("Console", 80, 160);
		Console::write_line("Exception caught: " + e.get_message_and_stack_trace());
		console.display_close_message();
		return -1;
	}
}
