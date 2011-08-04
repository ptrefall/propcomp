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
 * The base component class simply holds the means to build components on top of it.
 * It has a type identifier used to associate with what type of component it is, and
 * a reference to the entity that owns it.
 *
 * It also holds two virtual functions, update and onEvent, that can optionally be
 * overloaded by each component implementation.
 *
 * Note that the constructor takes an optional HAS_SIGNALSLOTS_INHERITANCE_TYPE. This is
 * a pre-processor type specified via types_config.h, and allows a user to specify the
 * exact requirement of the signal/slot system in use (Some implementations do require
 * that a class holding slots inherit from some class). Look at MinDepends/types.h for
 * an example of this.
 * 
 */

#include "types_config.h"

#include "Entity.h"
#include "Property.h"

class Component HAS_SIGNALSLOTS_INHERITANCE_TYPE
{
public:
	/**
	 * Destructor
	 */
	virtual ~Component() {}

	/**
	 * Get the type that defines this component.
	 *
	 * @return Returns the type of the component.
	 */
	T_String getType() const { return type; }

	/**
	 * Optional virtual function that can be overloaded by
	 * component implementations. Update is typically called
	 * at least once per frame, and is channeled via the entity.
	 *
	 * @param deltaTime Number of seconds that has passed since our last update.
	 */
    virtual void update(F32 deltaTime) {};

	/**
	 * Optional virtual function that can be overloaded by
	 * component implementations. OnEvent is a way for components
	 * to react to some specific event in the world.
	 *
	 * @param event The object that describes the event.
	 */
	virtual void onEvent(const T_Event &event) {};

protected:
	/**
	 * Protected Constructor
	 *
	 * @param owner Reference to the entity that owns this component.
	 * @param type The type-name assigned to this component from it's implementation.
	 */
	Component(Entity &owner, const T_String &type) : owner(owner), type(type) {};

	/// The entity that owns this component.
	Entity &owner;
	/// The type identifier for this component.
    T_String type;
};
