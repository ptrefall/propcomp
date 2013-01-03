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

/// \addtogroup clanNetwork_Web clanNetwork Web
/// \{

#pragma once

#include "../api_network.h"
#include <memory>

namespace clan
{

class HTTPServerConnection;
class HTTPRequestHandlerProvider;
class HTTPRequestHandler_Impl;

/// \brief HTTP request handler class.
///
/// \xmlonly !group=Network/Web! !header=network.h! \endxmlonly
class CL_API_NETWORK HTTPRequestHandler
{
/// \name Construction
/// \{

public:
	/// \brief Constructs a null instance
	HTTPRequestHandler();

	/// \brief Constructs a HTTPRequestHandler
	///
	/// \param provider = HTTPRequest Handler Provider
	HTTPRequestHandler(HTTPRequestHandlerProvider *provider);

	~HTTPRequestHandler();

/// \}
/// \name Attributes
/// \{

public:
	/// \brief Returns true if this object is invalid.
	bool is_null() const { return !impl; }

	/// \brief Throw an exception if this object is invalid.
	void throw_if_null() const;

	/// \brief Get Provider
	///
	/// \return provider
	HTTPRequestHandlerProvider *get_provider() const;

/// \}
/// \name Operations
/// \{

public:
	bool is_handling_request(
		const std::string &type,
		const std::string &url,
		const std::string &headers);

	/// \brief Handle request
	///
	/// \param connection = HTTPServer Connection
	void handle_request(HTTPServerConnection &connection);

/// \}
/// \name Implementation
/// \{

private:
	std::shared_ptr<HTTPRequestHandler_Impl> impl;

/// \}
};

}

/// \}
