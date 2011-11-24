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
#include "FastDelegate.h"
#include "FastDelegateBind.h"

typedef cdiggins::any T_Any;
typedef cdiggins::anyimpl::bad_any_cast T_BadAnyCast;
typedef unsigned int T_HashedStringType;

class T_HashedString
{
public:
	T_HashedString(const CL_String &str)
	{
		this->str = str;
		//this->hashId = (T_HashedStringType)stdext::hash_value(str.c_str());
		this->hashId = 0;
	}
	const T_HashedStringType &getId() const { return hashId; }
	const CL_String &getStr() const { return str; }

private:
	T_HashedStringType hashId;
	CL_String str;
};

//Delegate handling
typedef const void *T_Void;

template<class RetType=T_Void>
struct T_Delegate_v0 {
	typedef fastdelegate::FastDelegate0<RetType> Type;
};

template<class Param1, class RetType=T_Void>
struct T_Delegate_v1 {
	typedef fastdelegate::FastDelegate1<Param1, RetType> Type;
};

template<class Param1, class Param2, class RetType=T_Void>
struct T_Delegate_v2 {
	typedef fastdelegate::FastDelegate2<Param1, Param2, RetType> Type;
};

template<class Param1, class Param2, class Param3, class RetType=T_Void>
struct T_Delegate_v3 {
	typedef fastdelegate::FastDelegate3<Param1, Param2, Param3, RetType> Type;
};

template<class Param1, class Param2, class Param3, class Param4, class RetType=T_Void>
struct T_Delegate_v4 {
	typedef fastdelegate::FastDelegate4<Param1, Param2, Param3, Param4, RetType> Type;
};

template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType=T_Void>
struct T_Delegate_v5 {
	typedef fastdelegate::FastDelegate5<Param1, Param2, Param3, Param4, Param5, RetType> Type;
};

template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType=T_Void>
struct T_Delegate_v6 {
	typedef fastdelegate::FastDelegate6<Param1, Param2, Param3, Param4, Param5, Param6, RetType> Type;
};
