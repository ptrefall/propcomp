
#include "precomp.h"
#include "ui_screen_manager.h"
#include <algorithm>

using namespace clan;

UIScreenManager::UIScreenManager(const std::string &title, clan::Rect window, bool fullscreen, const std::string &font)
: current(nullptr)
{
	TCODConsole::setCustomFont(font.c_str());
	TCODConsole::initRoot(window.get_width(), window.get_height(), title.c_str(), fullscreen);
}

UIScreenManager::~UIScreenManager()
{
	while (!screens.empty())
		delete screens.back();
}

bool UIScreenManager::isWindowClosed()
{
	return TCODConsole::isWindowClosed();
}

void UIScreenManager::hide_cursor()
{
	//window.hide_cursor();
}

void UIScreenManager::maximize()
{
	//window.maximize();
	TCODConsole::setFullscreen(true);
}

void UIScreenManager::add_screen(UIScreen *screen)
{
	screens.push_back(screen);
}

void UIScreenManager::remove_screen(UIScreen *screen)
{
	screens.erase(std::find(screens.begin(), screens.end(), screen));
}

void UIScreenManager::set_active(UIScreen *screen)
{
	if (screen != current)
	{
		if (current)
			current->on_deactivated();
		current = screen;
		if (current)
			current->on_activated();
	}
}

void UIScreenManager::update()
{
	ScopeTimerResults::start();
	if (current)
	{
		current->update();
	}
	ScopeTimerResults::end();
}

void UIScreenManager::render()
{
	ScopeTimerResults::start();
	if (current)
	{
		current->render();
	}
	TCODConsole::flush();
	ScopeTimerResults::end();
}

void UIScreenManager::reset_mouse_position()
{
	/*bool we_really_do_have_focus = window.has_focus();
	if (window.get_hwnd() != ::GetForegroundWindow())
		we_really_do_have_focus = false;

	if (we_really_do_have_focus)
	{
		Point client_pos(window.get_viewport().get_center());
		Point screen_pos = window.client_to_screen(client_pos);
		SetCursorPos(screen_pos.x, screen_pos.y);
	}*/
	//MouseMovement::has_focus = we_really_do_have_focus;
}
