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

#include "api_csslayout.h"

namespace clan
{

class CL_API_CSSLAYOUT CSSSelectNode
{
public:
	virtual ~CSSSelectNode() { }
	virtual bool parent() = 0;
	virtual bool prev_sibling() = 0;
	virtual void push() = 0;
	virtual void pop() = 0;

	virtual std::string name() = 0;
	virtual std::string lang() = 0;
	virtual std::string id() = 0;
	virtual std::vector<std::string> element_classes() = 0;
	virtual std::vector<std::string> pseudo_classes() = 0;
	virtual std::string get_attribute_value(const std::string &name, bool &out_found) = 0;
	virtual int child_index() { return 0; }
};

}