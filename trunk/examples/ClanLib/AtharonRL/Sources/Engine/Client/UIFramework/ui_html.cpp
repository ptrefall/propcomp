
#include "precomp.h"
#include "ui_html.h"

using namespace clan;

UIHtml::UIHtml(GUIComponent *parent)
: UIComponent(parent)
{
	func_render().set(this, &UIHtml::on_render);
}

UIHtml::UIHtml(UIScreen *screen)
: UIComponent(screen)
{
	func_render().set(this, &UIHtml::on_render);
}

void UIHtml::set_document(const std::string &html, const std::string &css)
{
	html_parser.set_document(html, css, "file:Resources/GameIDE");
	update_html_layout();
}

void UIHtml::clear()
{
	html_parser.clear();
}

void UIHtml::update_geometry()
{
	UIComponent::update_geometry();
	if (get_size() != last_size)
		update_html_layout();
}

void UIHtml::update_html_layout()
{
	if (!html_parser.layout.is_null())
	{
		Canvas canvas = get_canvas();
		html_parser.layout.set_dpi(96.0f * get_scale());
		html_parser.layout.layout(canvas, get_size());
	}
	last_size = get_size();
}

void UIHtml::on_render(Canvas &canvas, const Rect &update_box)
{
	if (!html_parser.layout.is_null())
	{
		if (get_size() != last_size)
			update_html_layout();

		set_cliprect(canvas, get_size());
		html_parser.layout.render(canvas, this);
		reset_cliprect(canvas);
	}
}
