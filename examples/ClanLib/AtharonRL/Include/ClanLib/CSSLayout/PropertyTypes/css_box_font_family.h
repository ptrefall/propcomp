/*
**  ClanLib SDK
**  Copyright (c) 1997-2012 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

#pragma once

#include "../css_box_property.h"

namespace clan
{

class CSSBoxFontFamilyName
{
public:
	CSSBoxFontFamilyName() : type(type_serif) { }
	CSSBoxFontFamilyName(const std::string &name) : type(type_family_name), name(name) { }

	enum Type
	{
		type_family_name,
		type_serif,
		type_sans_serif,
		type_cursive,
		type_fantasy,
		type_monospace
	};
	Type type;
	std::string name;
};

class CSSBoxFontFamily : public CSSBoxProperty
{
public:
	CSSBoxFontFamily();
	void compute(const CSSBoxFontFamily *parent, CSSResourceCache *layout, float em_size, float ex_size);
	std::string to_string() const;

	enum Type
	{
		type_names,
		type_inherit
	};
	Type type;
	std::vector<CSSBoxFontFamilyName> names;
};

}
