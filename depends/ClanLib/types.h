#pragma once

/**
 * @file
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @section LICENSE
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 
 * Note: Some of the libraries Totem EDK may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * ClanLib Types Configuration, originally contributed by 'savuporo'.
 * 
 */

#include <ClanLib/core.h>
#include <vector>
#include <map>
#include <unordered_map>
#include "cdiggins_any.h"

typedef cdiggins::any T_Any;
typedef cdiggins::anyimpl::bad_any_cast T_BadAnyCast;
typedef unsigned int T_HashedStringType;

class T_HashedString
{
public:
	T_HashedString(const CL_String &str)
	{
		this->str = str;
		this->hashId = std::hash<CL_String>()(str);
	}
	const T_HashedStringType &getId() const { return hashId; }
	const CL_String &getStr() const { return str; }

private:
	T_HashedStringType hashId;
	CL_String str;
};

//Delegate handling
typedef const void *T_Void;

template<class RetType>
struct T_Delegate_v0 {
	typedef CL_Callback_0<RetType> Type;
};

template<class RetType, class Param1>
struct T_Delegate_v1 {
	typedef CL_Callback_1<RetType, Param1> Type;
};

template<class RetType, class Param1, class Param2>
struct T_Delegate_v2 {
	typedef CL_Callback_2<RetType, Param1, Param2> Type;
};

template<class RetType, class Param1, class Param2, class Param3>
struct T_Delegate_v3 {
	typedef CL_Callback_3<RetType, Param1, Param2, Param3> Type;
};

template<class RetType, class Param1, class Param2, class Param3, class Param4>
struct T_Delegate_v4 {
	typedef CL_Callback_4<RetType, Param1, Param2, Param3, Param4> Type;
};

template<class RetType, class Param1, class Param2, class Param3, class Param4, class Param5>
struct T_Delegate_v5 {
	typedef CL_Callback_5<RetType, Param1, Param2, Param3, Param4, Param5> Type;
};

template<class RetType, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
struct T_Delegate_v6 {
	typedef CL_Callback_6<RetType, Param1, Param2, Param3, Param4, Param5, Param6> Type;
};
