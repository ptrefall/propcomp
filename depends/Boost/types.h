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
 * Boost Types Configuration
 * 
 */

#include <string>
#include <vector>
#include <map>
#include <boost/exception/all.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

//Base types
typedef std::string T_String;
typedef float F32;

//Container types
template< typename T >
struct T_Vector {
	typedef std::vector<T> Type;
};
template< typename K, typename V >
struct T_Map {
	typedef std::map<K,V> Type;
};

//Event handling
struct sEvent
{
};
typedef sEvent T_Event;

//Exception handling
typedef boost::exception T_Exception;

//Signal handling
template< typename T >
struct T_Signal_v1 {
	typedef boost::signal1<T> Type;
};

template<typename T,typename U>
struct T_Signal_v2 {
   typedef boost::signal2<T,U> Type;
};

template < typename T >
struct T_SharedPtr {
	typedef boost::shared_ptr<T> Type;
};
