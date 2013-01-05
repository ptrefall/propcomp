
#include "precomp.h"
#include "html_parser.h"
#include "html_token.h"

using namespace clan;

void HTMLParser::clear()
{
	dom = DomDocument();
	css = CSSDocument();
	layout = CSSLayout();
}

void HTMLParser::set_document(const std::string &html, const std::string &css_text, const std::string &base_uri)
{
	clear();
	set_css_document(css_text);

	HTMLTokenizer tokenizer;
	tokenizer.append(html);

	ParseState parse_state;
	HTMLToken token;
	while (true)
	{
		tokenizer.tokenize(token);
		if (token.type == HTMLToken::type_null)
			break;

		if (token.type == HTMLToken::type_tag_begin || token.type == HTMLToken::type_tag_single)
		{
			parse_state.close_unclosed_tags(token);

			DomElement dom_element = parse_state.create_dom_element(dom, token);

			CSSLayoutElement element;
			if (is_replaced_object(token.name))
				element = layout.create_object();
			else
				element = layout.create_element();
			element.set_col_span(dom_element.get_attribute_int("colspan", 1));
			element.set_row_span(dom_element.get_attribute_int("rowspan", 1));
			element.set_name(string_format("%1.%2#%3", token.name, dom_element.get_attribute("class"), dom_element.get_attribute("id")));

			if (token.name == "body")
			{
				if (layout.get_html_body_element().is_null())
					layout.set_html_body_element(element);
			}

			DomSelectNode select_node(dom_element);
			element.apply_properties(css.select(&select_node));

			apply_html4_properties(element, dom_element, base_uri);
			element.apply_properties(dom_element.get_attribute("style"), base_uri);

			if (!parse_state.css_elements.empty())
			{
				parse_state.css_elements.back().append_child(element);

				CSSLayoutElement pseudo_before = layout.create_element();
				pseudo_before.set_name(":before");
				pseudo_before.apply_properties(css.select(&select_node, "before"));
				parse_state.css_elements.back().insert_before(pseudo_before, element);

				CSSLayoutElement pseudo_after = layout.create_element();
				pseudo_after.set_name(":after");
				pseudo_after.apply_properties(css.select(&select_node, "after"));
				parse_state.css_elements.back().insert_before(pseudo_after, element.get_next_sibling());
			}

			if (!is_end_tag_forbidden(token.name))
			{
				parse_state.level++;
				parse_state.tags.push_back(token.name);
				parse_state.css_elements.push_back(element);
				parse_state.dom_elements.push_back(dom_element);
			}
		}
		else if (token.type == HTMLToken::type_tag_end)
		{
			for (size_t i = parse_state.tags.size(); i > 0; i--)
			{
				if (parse_state.tags[i-1] == token.name)
				{
					if (parse_state.tags.size() > 1)
					{
						parse_state.tags.erase(parse_state.tags.begin()+(i-1), parse_state.tags.end());
						parse_state.css_elements.erase(parse_state.css_elements.begin()+(i-1), parse_state.css_elements.end());
						parse_state.dom_elements.erase(parse_state.dom_elements.begin()+(i-1), parse_state.dom_elements.end());
						parse_state.level = parse_state.tags.size();
					}
					break;
				}
			}
		}
		else if (token.type == HTMLToken::type_text)
		{
			if (!parse_state.css_elements.empty())
			{
				CSSLayoutText text = layout.create_text(token.value);
				parse_state.css_elements.back().append_child(text);
			}
		}
	}

	if (!parse_state.css_elements.empty())
		layout.set_root_element(parse_state.css_elements.front());
}

bool HTMLParser::is_replaced_object(const std::string &name)
{
	return name == "img" || name == "input" || name == "button" || name == "select" || name == "textarea";
}

bool HTMLParser::is_end_tag_forbidden(const std::string &name)
{
	return name == "meta" ||
		name == "br" ||
		name == "col" ||
		name == "link" ||
		name == "base" ||
		name == "img" ||
		name == "param" ||
		name == "area" ||
		name == "basefont" ||
		name == "hr" ||
		name == "input" ||
		name == "isindex";
}

void HTMLParser::apply_html4_properties(CSSLayoutElement element, DomElement dom_element, const std::string &base_uri)
{
	if (dom_element.get_tag_name() == "img")
	{
		if (dom_element.has_attribute("width"))
		{
			std::string width_attr = dom_element.get_attribute("width");
			if (width_attr.find("%") == std::string::npos)
				element.apply_properties("width: " + width_attr + "px", base_uri);
			else
				element.apply_properties("width: " + width_attr, base_uri);
		}
	}
}

void HTMLParser::ParseState::close_unclosed_tags(const HTMLToken &token)
{
/*	if (token.name == "p" || token.name == "table") // Close <p>
	{
		for (size_t i = tags.size(); i > 0; i--)
		{
			if (tags.back() == "p")
			{
				tags.erase(tags.begin()+(i-1), tags.end());
				css_elements.erase(css_elements.begin()+(i-1), css_elements.end());
				dom_elements.erase(dom_elements.begin()+(i-1), dom_elements.end());
				level = tags.size();
				break;
			}
		}
	}*/
}

DomElement HTMLParser::ParseState::create_dom_element(DomDocument &dom, const HTMLToken &token)
{
	DomElement dom_element = dom.create_element(token.name);
	for (size_t i = 0; i < token.attributes.size(); i++)
		dom_element.set_attribute(token.attributes[i].name, token.attributes[i].value);
	if (!dom_elements.empty())
		dom_elements.back().append_child(dom_element);
	return dom_element;
}

void HTMLParser::set_css_document(const std::string &css_text)
{
	css = CSSDocument();
	css.add_default_html_sheet();
	IODevice_Memory device;
	device.write(css_text.data(), css_text.length());
	device.seek(0);
	css.add_sheet(author_sheet_origin, device, "file:Resources/GameIDE");
}
