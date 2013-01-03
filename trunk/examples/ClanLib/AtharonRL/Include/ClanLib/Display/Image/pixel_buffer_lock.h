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
**    Mark Page
*/

/// \addtogroup clanDisplay_Display clanDisplay Display
/// \{

#pragma once

#include "../api_display.h"
#include <memory>
#include "../../Core/Math/vec1.h"
#include "../../Core/Math/vec2.h"
#include "../../Core/Math/vec3.h"
#include "../../Core/Math/vec4.h"
#include "../../Core/Math/half_float_vector.h"
#include "pixel_buffer.h"

namespace clan
{

/// \brief PixelBuffer locking helper.
///
/// \xmlonly !group=Display/Display! !header=display.h! \endxmlonly
template<typename Type>
class CL_API_DISPLAY PixelBufferLock
{
/// \name Construction
/// \{
public:
	/// \brief Constructs a gpu pixel buffer lock
	PixelBufferLock(GraphicContext &gc, PixelBuffer &pixel_buffer, BufferAccess access, bool lock_pixelbuffer = true)
	: pixel_buffer(pixel_buffer), lock_count(0), pitch(0), data(0)
	{
		width = pixel_buffer.get_width();
		height = pixel_buffer.get_height();
		if (lock_pixelbuffer)
			lock(gc, access);
	}

	/// \brief Constructs a system pixel buffer lock
	PixelBufferLock(PixelBuffer &pixel_buffer, bool lock_pixelbuffer = true)
	: pixel_buffer(pixel_buffer), lock_count(0), pitch(0), data(0)
	{
		width = pixel_buffer.get_width();
		height = pixel_buffer.get_height();
		if (lock_pixelbuffer)
			lock();
	}

	~PixelBufferLock()
	{
		if (lock_count > 0 && !(pixel_buffer.is_null()))
			pixel_buffer.unlock();
		lock_count = 0;
	}
/// \}

/// \name Attributes
/// \{
public:
	/// \brief Returns the amounts of recursive pixel_buffer locks performed by this section.
	int get_lock_count() const
	{
		return lock_count;
	}

	Type *get_data() { return reinterpret_cast<Type*>(data); }
	Type *get_row(int y) { return reinterpret_cast<Type*>(data + pitch * y); }
	Type &get_pixel(int x, int y) { return *(reinterpret_cast<Type*>(data + pitch * y) + x); }
	int get_width() const { return width; }
	int get_height() const { return height; }
	int get_pitch() const { return pitch; }
/// \}

/// \name Operations
/// \{
public:
	/// \brief Lock the gpu pixel_buffer.
	void lock(GraphicContext &gc, BufferAccess access)
	{
		if (!pixel_buffer.is_null())
		{
			pixel_buffer.lock(gc, access);
			data = static_cast<unsigned char*>(pixel_buffer.get_data());
			pitch = pixel_buffer.get_pitch();
		}
		lock_count++;
	}

	/// \brief Lock the system pixel_buffer.
	void lock()
	{
		if (!pixel_buffer.is_null())
		{
			if (pixel_buffer.is_gpu())
				throw Exception("Incorrect PixelBufferLock constructor called with a GPU pixelbuffer");

			// lock() does not do anything on system pixel buffers, so we do not call it

			data = static_cast<unsigned char*>(pixel_buffer.get_data());
			pitch = pixel_buffer.get_pitch();
		}
		lock_count++;
	}

	/// \brief Unlock pixel_buffer.
	void unlock()
	{
		if (lock_count <= 0)
			return;

		if (!pixel_buffer.is_null())
		{
			pixel_buffer.unlock();
			pitch = 0;
			data = 0;
		}
		lock_count--;
	}
/// \}

/// \name Implementation
/// \{
private:
	PixelBuffer pixel_buffer;
	int lock_count;
	int width;
	int height;
	int pitch;
	unsigned char *data;
/// \}
};

typedef PixelBufferLock<Vec1ub> PixelBufferLock1ub;
typedef PixelBufferLock<Vec2ub> PixelBufferLock2ub;
typedef PixelBufferLock<Vec3ub> PixelBufferLock3ub;
typedef PixelBufferLock<Vec4ub> PixelBufferLock4ub;
typedef PixelBufferLock<Vec1us> PixelBufferLock1us;
typedef PixelBufferLock<Vec2us> PixelBufferLock2us;
typedef PixelBufferLock<Vec3us> PixelBufferLock3us;
typedef PixelBufferLock<Vec4us> PixelBufferLock4us;
typedef PixelBufferLock<Vec1ui> PixelBufferLock1ui;
typedef PixelBufferLock<Vec2ui> PixelBufferLock2ui;
typedef PixelBufferLock<Vec3ui> PixelBufferLock3ui;
typedef PixelBufferLock<Vec4ui> PixelBufferLock4ui;

typedef PixelBufferLock<Vec1b> PixelBufferLock1b;
typedef PixelBufferLock<Vec2b> PixelBufferLock2b;
typedef PixelBufferLock<Vec3b> PixelBufferLock3b;
typedef PixelBufferLock<Vec4b> PixelBufferLock4b;
typedef PixelBufferLock<Vec1s> PixelBufferLock1s;
typedef PixelBufferLock<Vec2s> PixelBufferLock2s;
typedef PixelBufferLock<Vec3s> PixelBufferLock3s;
typedef PixelBufferLock<Vec4s> PixelBufferLock4s;
typedef PixelBufferLock<Vec1i> PixelBufferLock1i;
typedef PixelBufferLock<Vec2i> PixelBufferLock2i;
typedef PixelBufferLock<Vec3i> PixelBufferLock3i;
typedef PixelBufferLock<Vec4i> PixelBufferLock4i;

typedef PixelBufferLock<Vec1hf> PixelBufferLock1hf;
typedef PixelBufferLock<Vec2hf> PixelBufferLock2hf;
typedef PixelBufferLock<Vec3hf> PixelBufferLock3hf;
typedef PixelBufferLock<Vec4hf> PixelBufferLock4hf;

typedef PixelBufferLock<Vec1f> PixelBufferLock1f;
typedef PixelBufferLock<Vec2f> PixelBufferLock2f;
typedef PixelBufferLock<Vec3f> PixelBufferLock3f;
typedef PixelBufferLock<Vec4f> PixelBufferLock4f;
typedef PixelBufferLock<Vec1d> PixelBufferLock1d;
typedef PixelBufferLock<Vec2d> PixelBufferLock2d;
typedef PixelBufferLock<Vec3d> PixelBufferLock3d;
typedef PixelBufferLock<Vec4d> PixelBufferLock4d;

typedef PixelBufferLock<unsigned char> PixelBufferLockAny;

}

/// \}
