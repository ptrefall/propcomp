
#pragma once

#include "tick_timer.h"

class GameWorld
{
public:
	GameWorld();
	virtual ~GameWorld();

	void update();

protected:
	virtual void tick(float time_elapsed);

private:
	TickTimer tick_timer;
};
