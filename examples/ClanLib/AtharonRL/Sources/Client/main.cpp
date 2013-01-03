#include "precomp.h"
#include "game.h"

int main(int argc, char **argv)
{
	try
	{
		clan::SetupCore setup_core;
		clan::SetupNetwork setup_network;
		//clan::SetupVorbis setup_vorbis;

		srand(clan::System::get_time());

		clan::ConsoleLogger logger;

		Game game(argv[0]);
		game.run();

		return 0;
	}
	catch( clan::Exception &e )
	{
		clan::Console::write_line("Exception caught: " + e.get_message_and_stack_trace());
		return -1;
	}
}