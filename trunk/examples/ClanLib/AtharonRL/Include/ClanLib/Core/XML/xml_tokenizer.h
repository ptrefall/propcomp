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

/// \addtogroup clanCore_XML clanCore XML
/// \{

#pragma once

#include "../api_core.h"
#include <memory>

namespace clan
{

class IODevice;
class XMLToken;
class XMLTokenizer_Impl;

/// \brief The XML Tokenizer breaks a XML file into XML tokens.
///
/// \xmlonly !group=Core/XML! !header=core.h! \endxmlonly
class CL_API_CORE XMLTokenizer
{
/// \name Construction
/// \{

public:
	XMLTokenizer();

	/// \brief Constructs a XMLTokenizer
	///
	/// \param copy = XMLTokenizer
	XMLTokenizer(const XMLTokenizer &copy);

	/// \brief Constructs a XMLTokenizer
	///
	/// \param input = IODevice
	XMLTokenizer(IODevice &input);

	virtual ~XMLTokenizer();

/// \}
/// \name Attributes
/// \{

public:
	/// \brief Returns true if eat whitespace flag is set.
	bool get_eat_whitespace() const;

	/// \brief If enabled, will eat any whitespace between tags.
	void set_eat_whitespace(bool enable);

/// \}
/// \name Operations
/// \{

public:
	/// \brief Returns the next token available in input stream.
	XMLToken next();

	/// \brief Next
	///
	/// \param out_token = XMLToken
	void next(XMLToken *out_token);

/// \}
/// \name Implementation
/// \{

private:
	std::shared_ptr<XMLTokenizer_Impl> impl;
/// \}
};

}

/// \}
