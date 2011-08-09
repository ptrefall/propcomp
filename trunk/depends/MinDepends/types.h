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
 * Note: Some of the libraries Component-based Entity Engine may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * Minimal Dependency Types Configuration
 * 
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <exception>
#include <memory>
#include <functional>
#include "sigslot.h"
#include "cdiggins_any.h"

//Sigslot.h requires that PropertyData and Component inherit from
//sigslot::has_slots<>, thus "overload" this preprocessed definition.
//-------------------------------------------------------------------
#undef HAS_SIGNALSLOTS_INHERITANCE_TYPE
#define HAS_SIGNALSLOTS_INHERITANCE_TYPE : public sigslot::has_slots<>

//Base types
//#undef NULL_PTR
//#define NULL_PTR nullptr
typedef std::string T_String;
typedef float F32;
typedef int S32;
typedef unsigned int U32;
typedef unsigned long T_EntityId;
typedef cdiggins::any T_Any;
typedef cdiggins::anyimpl::bad_any_cast T_BadAnyCast;


//Container types
template< typename T >
struct T_Vector {
	typedef std::vector<T> Type;
};
template< typename K, typename V >
struct T_Map {
	typedef std::tr1::unordered_map<K,V> Type;
};
template< typename K, typename V >
struct T_Pair {
	typedef std::pair<K,V> Type;
};

//Exception handling
typedef std::exception T_Exception;

//Signal handling
class NoTemplate {};
template<class T = NoTemplate>
struct T_Signal_v0 {
	typedef sigslot::signal0<> Type;
};

template< typename T >
struct T_Signal_v1 {
	typedef sigslot::signal1<T> Type;
};

template<typename T,typename U>
struct T_Signal_v2 {
   typedef sigslot::signal2<T,U> Type;
};

template<typename T,typename U, typename V>
struct T_Signal_v3 {
   typedef sigslot::signal3<T,U,V> Type;
};

template<typename T,typename U, typename V, typename W>
struct T_Signal_v4 {
   typedef sigslot::signal4<T,U,V,W> Type;
};

template<typename T,typename U, typename V, typename W, typename X>
struct T_Signal_v5 {
   typedef sigslot::signal5<T,U,V,W,X> Type;
};

template<typename T,typename U, typename V, typename W, typename X, typename Y>
struct T_Signal_v6 {
   typedef sigslot::signal6<T,U,V,W,X,Y> Type;
};

template<typename T,typename U, typename V, typename W, typename X, typename Y, typename Z>
struct T_Signal_v7 {
   typedef sigslot::signal7<T,U,V,W,X,Y,Z> Type;
};

template<typename T,typename U, typename V, typename W, typename X, typename Y, typename Z, typename S>
struct T_Signal_v8 {
   typedef sigslot::signal8<T,U,V,W,X,Y,Z,S> Type;
};

template < typename T >
struct T_SharedPtr {
	typedef std::tr1::shared_ptr<T> Type;
};

//--------------------------------------------

typedef unsigned int T_StringIdType;

class T_StringId
{
public:
	T_StringId(const T_String &str)
	{
		this->str = str;
		this->hashId = (T_StringIdType)std::hash_value(str.c_str());
	}

	const T_StringIdType &getId() const { return hashId; }
	const T_String &getStr() const { return str; }

private:
	T_StringIdType hashId;
	T_String str;
};

