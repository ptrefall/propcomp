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
*/

/// \addtogroup clanDisplay_2D clanDisplay 2D
/// \{

#pragma once

#include "../api_display.h"
#include <memory>
#include "../../Core/Math/origin.h"
#include "../Render/graphic_context.h"

namespace clan
{

class Color;
class Gradient;
class Pointf;
class RoundedRect_Impl;
class Canvas;

/// \brief Rounded rects drawing class.
///
/// \xmlonly !group=Display/2D! !header=display.h! \endxmlonly
class RoundedRect
{
/// \name Construction
/// \{

public:

	/// \brief Constructs a RoundedRect
	///
	/// \param size = Sizef
	/// \param rounding_in_pixels = value
	RoundedRect(Sizef size, float rounding_in_pixels=5.0f);
	virtual ~RoundedRect();

/// \}
/// \name Attributes
/// \{

public:
	/// \brief Returns the base rectangle.
	Sizef get_size() const;

	/// \brief Returns the width of the rectangle.
	float get_width() const;

	/// \brief Returns the height of the rectangle.
	float get_height() const;

	/// \brief Returns the distance from a corner (in pixels) at which the rounding starts.
	/** This value is used for corners for which no value has been specified separately.*/
	float get_rounding() const;

	/// \brief Returns the positions of the top-left corners conic bezier control point.
	Pointf get_control_point_tl() const;

	/// \brief Returns the positions of the top-right corners conic bezier control point.
	Pointf get_control_point_tr() const;

	/// \brief Returns the positions of the bottom-left corners conic bezier control point.
	Pointf get_control_point_bl() const;

	/// \brief Returns the positions of the bottom-right corners conic bezier control point.
	Pointf get_control_point_br() const;

	/// \brief Returns the relative offset (0.0-1.0) to the center of the edges connected to the corner.
	Sizef get_rounding_top_left() const;

	/// \brief Returns the relative offset (0.0-1.0) to the center of the edges connected to the corner.
	Sizef get_rounding_top_right() const;

	/// \brief Returns the relative offset (0.0-1.0) to the center of the edges connected to the corner.
	Sizef get_rounding_bottom_left() const;

	/// \brief Returns the relative offset (0.0-1.0) to the center of the edges connected to the corner.
	Sizef get_rounding_bottom_right() const;

/// \}
/// \name Operations
/// \{

public:
	/// \brief Draw the rectangle outline
	void draw(
		Canvas &canvas,
		const Pointf &position,
		const Colorf &color,
		Origin origin=origin_top_left);

	/// \brief Fill the rectangle
	void fill(
		Canvas &canvas,
		const Pointf &position,
		const Colorf &color,
		Origin origin=origin_top_left);

	void fill(
		Canvas &canvas,
		const Pointf &position,
		const Gradient &gradient,
		Origin origin=origin_top_left);

	/// \brief Set the size of the base rectangle
	void set_size(const Sizef &size);

	/// \brief Set the position of the top-left corners conic bezier control point.
	void set_control_point_tl(const Pointf &pos);

	/// \brief Set the positions of the top-right corners conic bezier control point.
	void set_control_point_tr(const Pointf &pos);

	/// \brief Set the positions of the bottom-left corners conic bezier control point.
	void set_control_point_bl(const Pointf &pos);

	/// \brief Set the positions of the bottom-right corners conic bezier control point.
	void set_control_point_br(const Pointf &pos);

	/// \brief Set the distance from a corner (in pixels) at which the rounding starts.
	/** This value is used for corners for which no value has been specified separately.*/
	void set_rounding(float offset_pixels);

	/// \brief Set the relative offset (0.0-1.0) to the center of the edges connected to the corner.
	void set_rounding_top_left(const Sizef &offset);

	/// \brief Set the relative offset (0.0-1.0) to the center of the edges connected to the corner.
	void set_rounding_top_right(const Sizef &offset);

	/// \brief Set the relative offset (0.0-1.0) to the center of the edges connected to the corner.
	void set_rounding_bottom_left(const Sizef &offset);

	/// \brief Set the relative offset (0.0-1.0) to the center of the edges connected to the corner.
	void set_rounding_bottom_right(const Sizef &offset);

/// \}
/// \name Implementation
/// \{

private:
	std::shared_ptr<RoundedRect_Impl> impl;
/// \}
};

}

/// \}
