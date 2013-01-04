
#include "precomp.h"
#include "ui_screen.h"
#include "ui_screen_manager.h"

using namespace clan;

UIScreen::UIScreen(UIScreenManager *manager)
: manager(manager)
{
	manager->add_screen(this);
}

UIScreen::~UIScreen()
{
	manager->remove_screen(this);
}

/*void UIScreen::on_mouse_input_helper(InputEvent e)
{
	sig_mouse_input.invoke(e);
}*/

UIScreenManager *UIScreen::get_manager()
{
	return manager;
}

void UIScreen::set_active()
{
	manager->set_active(this);
}

void UIScreen::enable_mouse(bool enable)
{
}

void UIScreen::update()
{
}

void UIScreen::render()
{
}

void UIScreen::on_activated()
{
}

void UIScreen::on_deactivated()
{
}

void UIScreen::on_mouse_movement(int delta_x, int delta_y)
{
	
	mouse_movement_pos.x += delta_x;
	mouse_movement_pos.y += delta_y;
}

bool UIScreen::is_game_input_enabled()
{
	return true; //get_wm_provider()->is_enabled() && !get_wm_provider()->is_mouse_enabled();
}

Point UIScreen::get_mouse_movement_pos()
{
	return mouse_movement_pos;
}

bool UIScreen::get_keycode(int code)
{
	return false;
	/*if (is_game_input_enabled())
		return get_ic().get_keyboard().get_keycode(code);
	else
		return false;*/
}
