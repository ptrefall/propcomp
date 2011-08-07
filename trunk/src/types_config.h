#pragma once

/**
 * @file
 *
 * @author P�l Trefall
 * @author Kenneth Gangst�
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
 * The component factory has the job of holding a register of component types and the means
 * to instanciate those registered component types.
 *
 * It holds a function pointer definition ComponentCreator, that each component implementation
 * must adhere to in order to register a component type to the factory.
 * 
 * There's nothing in the design that stops the user from having multiple factory instances
 * active, and use it as a way to organize components, but an entity- and a component-instance
 * will only associate with a single component factory instance.
 * 
 */

//These can overloaded in each specific types implementation:
//-------------------------------------------------------------------
//	Some type implementations might require that the signal-slot system
//	place an inheritance dependency on PropertyData and Component, so that
//	they get the "ability" of owning slots for their signals.
//	If the implementation don't, just leave this definition as empty.
#define HAS_SIGNALSLOTS_INHERITANCE_TYPE
//	Some type implementations might want to use different null pointer conventions.
//	For instance the C++0x nullptr type, or some other approach like (void*)0, etc.
#define NULL_PTR 0x0
//
#define USE_EVENT_STRING_ID_HASHING 1

//And here we define each type, only one should be defined
//-------------------------------------------------------------------
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