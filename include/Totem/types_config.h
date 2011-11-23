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
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 * 
 * Note: Some of the libraries Totem EDK may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * Types Configuration, originally contributed by 'savuporo'.
 * 
 */

//These can overloaded in each specific types implementation:
//-------------------------------------------------------------------
/**	
 * Some type implementations might require that the signal-slot system
 * place an inheritance dependency on PropertyData and Component, so that
 * they get the "ability" of owning slots for their signals.
 * If the implementation don't, just leave this definition as empty.
 */
#define HAS_SIGNALSLOTS_INHERITANCE_TYPE

/**
 * Some type implementations might want to use different null pointer conventions.
 * For instance the C++0x nullptr type, or some other approach like (void*)0, etc.
 */
#define NULL_PTR 0x0

/**
 * The Template-based event handler uses templates to send typesafe arguments with an event.
 */
#define USE_TEMPLATE_EVENT_HANDLER 1
#ifndef USE_TEMPLATE_EVENT_HANDLER
/**
 * The Any-based event handler uses the Any type to send typesafe arguments with an event.
 * This implementation also supports scheduled events seamlessly.
 */
#define USE_ANY_EVENT_HANDLER 1
#endif

/**
 * Std Vector has a special handling of vector<bool> that doesn't support referencing the
 * values of the list. Since we're using templates throughout Totem, in order to treat
 * bool as a special case, we need to use RTTI in order to recognize the use of booleans.
 * The problem is that this forces RTTI on all types, and may slow down your performance.
 * When looking up the vector<bool> problem online, one solution that's often suggested,
 * is to store bools as unsigned chars, and manualy cast to bool upon usage.
 * The reason why this affects PropertyList, is because of how the PropertyListIndexValue
 * works, which has a const T &get() const { return data->value[index]; } method. This works
 * for all cases except for bool, which has to be handled as a special case of
 * const bool get() const { return data->value[index]; }. If you're NOT using bool with
 * PropertyList, you can leave this define as 0, and no RTTI will toll your execution.
 */
#define USE_PROPERTY_LIST_BOOL_VECTOR_RTTI_WORKAROUND 0

/**
 * When enabled, the PropertyList class will perform an internal RTTI on its type id, to
 * check whether it's a bool, and if bool, it will throw an exception if
 * USE_PROPERTY_LIST_BOOL_VECTOR_RTTI_WORKAROUND was NOT enabled/0. This is a safeguard to
 * prevent unaware users from using bool with PropertyList, and to make them aware of the
 * problem related to use of bool with std::vector, and how it can impact PropertyList.
 * Disable this/0 if you understand the problem and won't get caught by it, as it does add
 * an RTTI for each time a new PropertyList is constructed.
 */
#define USE_PROPERTY_LIST_BOOL_VECTOR_RTTI_INTERNAL_TYPE_CHECK 1

//And here we define each type, only one should be defined
//-------------------------------------------------------------------
/// Define this if the system should use the minimal dependency types
#define USE_MINIMAL_DEPENDS_TYPES
//#define USE_BOOST_TYPES
//#define USE_CLANLIB_TYPES

//And include the defined types.h
//-------------------------------------------------------------------
#ifdef USE_MINIMAL_DEPENDS_TYPES
#include "../depends/MinDepends/types.h"
#elif USE_BOOST_TYPES
#include "../depends/Boost/types.h"
#elif USE_CLANLIB_TYPES
#include "../depends/ClanLib/types.h"
#endif