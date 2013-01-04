
#include "precomp.h"
#include "game_world.h"

using namespace clan;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::update()
{
	int ticks = tick_timer.update();
	for (int i = 0; i < ticks; i++)
		tick(tick_timer.get_tick_length());
}

void GameWorld::tick(float time_elapsed)
{
}
