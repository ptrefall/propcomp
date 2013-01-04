
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

	bool is_window_closed();

	const clan::Rect &get_window() const { return window; }

private:
	void add_screen(UIScreen *screen);
	void remove_screen(UIScreen *screen);
	void reset_mouse_position();

	clan::Rect window;

	//MouseMovement mouse_movement;
	clan::Point mouse_movement_pos;
	UIScreen *current;
	std::vector<UIScreen *> screens;

	friend class UIScreen;
};
