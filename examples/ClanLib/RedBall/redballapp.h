
#pragma once

class Entity;

class RedBallApp
{
public:
	void run();

private:
	void on_window_close();
	void on_input_up(const CL_InputEvent &key);

	bool quit;

	std::vector<Entity *> entities;
};
