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
**    Harry Storbacka
**    Magnus Norddahl
**    Kenneth Gangstoe
**    Mark Page
*/

/// \addtogroup clanDisplay_Collision clanDisplay Collision
/// \{

#pragma once

#include "../api_display.h"
#include <memory>
#include <vector>

namespace clan
{

class Contour_Impl;
class OutlineCircle;
class Pointf;

/// \brief Collision detection contour.
///
/// <p>A outline consists of contours, which hold the actual outline geometry</p>
/// \xmlonly !group=Display/Collision! !header=display.h! \endxmlonly
class Contour
{
/// \name Construction
/// \{
public:
	/// \brief Construct a contour
	Contour();
	~Contour();

/// \}
/// \name Attributes
/// \{
public:
	// Points forming the countour.
	std::vector<Pointf> &get_points();
	const std::vector<Pointf> &get_points() const;

	// boolean specifying if this contour is inside-out (the inside of a hollow polygon)
	// if that is the case, then the collision-test will skip the inside_contour-test (because you can
	// be inside this one, without causing a collision)
	bool is_inside_contour() const;

	/// \brief Set inside contour
	///
	/// \param is_inside = bool
	void set_inside_contour(bool is_inside);

	// Circles encapsulating a part of the outline.
	// If two circles arent intersecting, none of the lines inside them
	// collide either.
	std::vector<OutlineCircle> &get_sub_circles();
	const std::vector<OutlineCircle> &get_sub_circles() const;
/// \}

/// \name Operators
/// \{
public:
	/// \brief Equality operator
	bool operator==(const Contour &other) const;

	/// \brief Inequality operator
	bool operator!=(const Contour &other) const;

	/// \brief Less than operator
	bool operator<(const Contour &other) const;

	/// \brief Makes a copy of the contour
	Contour clone();
/// \}
	
/// \name Implementation
/// \{
private:
	std::shared_ptr<Contour_Impl> impl;
/// \}
};

}

/// \}
