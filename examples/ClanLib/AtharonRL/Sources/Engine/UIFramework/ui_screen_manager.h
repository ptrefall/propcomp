
#pragma once

#include "ui_screen.h"

class UIScreenManager
{
public:
//	UIScreenManager();
	UIScreenManager(const std::string &title, clan::Rect window, bool fullscreen, const std::string &font);
	~UIScreenManager();

	//MouseMovement &get_mouse_movement() { return mouse_movement; }

	void hide_cursor();
	void maximize();

	void set_active(UIScreen *screen);
	void update();
	void render();

	bool isWindowClosed();

private:
	void add_screen(UIScreen *screen);
	void remove_screen(UIScreen *screen);
	void reset_mouse_position();

	//MouseMovement mouse_movement;
	clan::Point mouse_movement_pos;
	UIScreen *current;
	std::vector<UIScreen *> screens;

	friend class UIScreen;
};
