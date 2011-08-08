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
#include "ComponentFactory.h"

class Component 
	: public sigslot::has_slots<> //HAS_SIGNALSLOTS_INHERITANCE_TYPE
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

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the component implementation that calls it. It simplifies adding new components, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param component The ComponentImplementation class, for instance COMPONENT_CREATOR_IMPL(Health)
 */
#define COMPONENT(component) \
			static T_String Type() { return T_String(#component); } \
			static Component *Create(Entity &owner, const T_String &name) { return new component(owner, name); } \
			static void RegisterToFactory(ComponentFactory &factory) { factory.registerComponent(component::Type(), &component::Create); }

#define COMPONENT1(component, Custom_type1) \
			static T_String Type() { return T_String(#component); } \
			static Component *Create(Entity &owner, const T_String &name, T_Any &custom1) \
			{ \
				Custom_type1 *custom = NULL_PTR; \
				try { \
					custom = custom1.cast<Custom_type1*>(); \
				}catch(T_Bad_any_cast) { \
					throw T_Exception(("Type of custom was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				return new component(owner, name, *custom); \
			} \
			static void RegisterToFactory(ComponentFactory &factory) { factory.registerComponentCustom1(component::Type(), &component::Create); }
