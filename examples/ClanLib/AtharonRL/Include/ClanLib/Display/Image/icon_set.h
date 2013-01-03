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

/// \addtogroup clanDisplay_Display clanDisplay Display
/// \{

#pragma once

#include "../api_display.h"
#include <memory>

namespace clan
{

class DataBuffer;
class PixelBuffer;
class IconSet_Impl;

/// \brief Icon set class.
///
/// \xmlonly !group=Display/Display! !header=display.h! \endxmlonly
class CL_API_DISPLAY IconSet
{
/// \name Construction
/// \{
public:
	/// \brief Constructs an icon set.
	IconSet();
/// \}

/// \name Attributes
/// \{
public:
	/// \brief Returns all the images in the icon set
	std::vector<PixelBuffer> get_images() const;
/// \}

/// \name Operations
/// \{
public:
	/// \brief Adds an image to the icon set
	void add_image(const PixelBuffer &image);

	/// \brief Generates a Windows .ICO format icon from the set
	DataBuffer create_win32_icon();
/// \}

/// \name Implementation
/// \{
private:
	std::shared_ptr<IconSet_Impl> impl;
/// \}
};

}

/// \}

