/*Totem EDK
Copyright (c) 2009 Pål Trefall and Kenneth Gangstø

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Note: Some of the libraries Totem EDK may link to may have additional
requirements or restrictions.
*/

#pragma once

#include <types_config.h>
#include <cmath>

template<typename T>
class Vector3
{
public:
	Vector3() : x((T)0.0), y((T)0.0), z((T)0.0) {}
	Vector3(T x, T y, T z) : x(x),y(y),z(z) {}
	Vector3(const Vector3<T> &copy) { x = copy.x; y = copy.y; z = copy.z; }

	T distance(const Vector3<T> &rhs) const;

	Vector3<T> operator= (const Vector3<T>& rhs);
	bool operator== (const Vector3<T>& rhs);
	bool operator!= (const Vector3<T>& rhs);
	Vector3<T> operator+ (const Vector3<T>& rhs) const;
	Vector3<T> operator* (F32 rhs) const;
	
	T x,y,z;
};

template<typename T>
inline T Vector3<T>::distance(const Vector3<T> &rhs) const
{
	F32 tmp_x = x - rhs.x;
	F32 tmp_y = y - rhs.y;
	F32 tmp_z = z - rhs.z;
	//return (T)floor(sqrt(tmp_x*tmp_x + tmp_y*tmp_y+tmp_z*tmp_z)+0.5f);
	return sqrt(tmp_x*tmp_x + tmp_y*tmp_y+tmp_z*tmp_z);
}

template<class T>
inline Vector3<T> Vector3<T>::operator =(const Vector3<T> &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

template<typename T>
inline bool Vector3<T>::operator ==(const Vector3<T> &rhs)
{
	return ((x == rhs.x) ||
			(y == rhs.y) ||
			(z == rhs.z));
}

template<typename T>
inline bool Vector3<T>::operator !=(const Vector3<T> &rhs)
{
	return ((x != rhs.x) ||
			(y != rhs.y) ||
			(z != rhs.z));
}

template<typename T>
inline Vector3<T> Vector3<T>::operator +(const Vector3<T> &rhs) const
{
	Vector3<T> tmp;
	tmp.x = x + rhs.x;
	tmp.y = y + rhs.y;
	tmp.z = z + rhs.z;
	return tmp;
}

template<typename T>
inline Vector3<T> Vector3<T>::operator *(F32 rhs) const
{
	Vector3<T> tmp;
	tmp.x = x * rhs;
	tmp.y = y * rhs;
	tmp.z = z * rhs;
	return tmp;
}

typedef Vector3<S32> T_Vec3i;
typedef Vector3<U32> T_Vec3u;
typedef Vector3<F32> T_Vec3f;
