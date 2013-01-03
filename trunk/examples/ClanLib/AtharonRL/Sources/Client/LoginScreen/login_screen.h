
#pragma once

#include "Engine/UIFramework/ui_screen_manager.h"
#include "Engine/UIFramework/ui_screen.h"

/*class UIButton;
class UILineEdit;
class UILabel;
class UIHtml;
class UIFrame;*/
class Game;

class LoginScreen : public UIScreen
{
public:
	LoginScreen(UIScreenManager *screen_manager, Game *game, clan::NetGameClient &network, const std::string &background);

	void update();
	void render();

private:
	void connect();

	void on_activated();

	void on_login_clicked();
	void on_connect_clicked();

	void on_connected();
	void on_disconnected();

	void on_event_received(const clan::NetGameEvent &e);
	void on_event_motd(const clan::NetGameEvent &e);
	void on_event_login_fail(const clan::NetGameEvent &e);
	void on_event_login_success(const clan::NetGameEvent &e);

	Game *game;

	/*UIButton *button_connect;

	UIFrame *frame_login;
	UIButton *button_login;
	UILineEdit *input_username;
	UILineEdit *input_password;
	UILabel *label_login_status;
	UIHtml *html_motd;*/

	std::string css_text;

	//clan::Image background;
	TCODImage background;

	clan::NetGameClient &network;

	clan::SlotContainer slots;

	clan::NetGameEventDispatcher_v0 netevents;
};
