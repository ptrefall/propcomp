
#pragma once

#include "ui_component.h"
#include "html_parser.h"

class UIHtml : public UIComponent
{
public:
	UIHtml(clan::GUIComponent *parent);
	UIHtml(UIScreen *screen);

	void set_document(const std::string &html, const std::string &css);
	void clear();

	void update_geometry();

private:
	void update_html_layout();
	void on_render(clan::Canvas &canvas, const clan::Rect &update_box);

	clan::Size last_size;
	HTMLParser html_parser;
};
