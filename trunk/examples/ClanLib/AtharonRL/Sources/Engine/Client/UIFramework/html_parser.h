
#pragma once

#include "html_tokenizer.h"

class HTMLParser
{
public:
	void clear();
	void set_document(const std::string &html, const std::string &css, const std::string &base_uri);

	clan::DomDocument dom;
	clan::CSSDocument css;
	clan::CSSLayout layout;

private:
	struct ParseState
	{
		ParseState() : level(0) { }
		void close_unclosed_tags(const HTMLToken &token);
		clan::DomElement create_dom_element(clan::DomDocument &dom, const HTMLToken &token);

		int level;
		std::vector<std::string> tags;
		std::vector<clan::CSSLayoutElement> css_elements;
		std::vector<clan::DomElement> dom_elements;
	};

	bool is_replaced_object(const std::string &name);
	bool is_end_tag_forbidden(const std::string &name);
	void apply_html4_properties(clan::CSSLayoutElement element, clan::DomElement dom_element, const std::string &base_uri);
	void set_css_document(const std::string &css);

	HTMLTokenizer tokenizer;
};
