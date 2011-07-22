/*Component-based Entity Engine
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

Note: Some of the libraries Component-based Entity Engine may link to may have additional
requirements or restrictions.
*/

#pragma once

#include <string>
#include <vector>
#include <map>
#include <exception>
#include <memory>
#include "sigslot.h"

//Base types
typedef std::string T_String;
typedef float F32;
typedef int S32;
typedef unsigned int U32;


//Container types
template< typename T >
struct T_Vector {
	typedef std::vector<T> Type;
};
template< typename K, typename V >
struct T_Map {
	typedef std::map<K,V> Type;
};
template< typename K, typename V >
struct T_Pair {
	typedef std::pair<K,V> Type;
};

//Event handling
struct sEvent
{
	T_String type;

	union {
		const char *str;
		F32 f;
		S32 i;
		U32 u;
	} arg0;

	union {
		const char *str;
		F32 f;
		S32 i;
		U32 u;
	} arg1;

	sEvent(const T_String &type) : type(type) {}
};
typedef sEvent T_Event;

//Exception handling
typedef std::exception T_Exception;

//Signal handling
template< typename T >
struct T_Signal_v1 {
	typedef sigslot::signal1<T> Type;
	void invoke(T a1) { T_Signal_v1::Type::emit(a1); }
};

template<typename T,typename U>
struct T_Signal_v2 {
   typedef sigslot::signal2<T,U> Type;
   void invoke(T a1, U a2) { T_Signal_v2::Type::emit(a1, a2); }
};

template < typename T >
struct T_SharedPtr {
	typedef std::tr1::shared_ptr<T> Type;
};
