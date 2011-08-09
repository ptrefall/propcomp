#pragma once

/**
 * @file
 * @class Component
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Component base class
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
 * @param component The ComponentImplementation class, for instance Health
 */
#define COMPONENT_0(component) \
			static T_String Type() { return T_String(#component); } \
			static Component *Create(Entity &owner, const T_String &name) { return new component(owner, name); } \
			static void RegisterToFactory(ComponentFactory &factory) { factory.registerComponent(component::Type(), &component::Create); }

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the component implementation that calls it. It simplifies adding new components, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param component The ComponentImplementation class, for instance Health
 * @param Custom_type1 The custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_1(component, Custom_type1) \
			static T_String Type() { return T_String(#component); } \
			static Component *Create(Entity &owner, const T_String &name, T_Any &custom1) \
			{ \
				Custom_type1 *custom = NULL_PTR; \
				try { \
					custom = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				return new component(owner, name, *custom); \
			} \
			static void RegisterToFactory(ComponentFactory &factory) { factory.registerComponentCustom1(component::Type(), &component::Create); }

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the component implementation that calls it. It simplifies adding new components, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param component The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_2(component, Custom_type1, Custom_type2) \
			static T_String Type() { return T_String(#component); } \
			static Component *Create(Entity &owner, const T_String &name, T_Any &custom1, T_Any &custom2) \
			{ \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				return new component(owner, name, *customA, *customB); \
			} \
			static void RegisterToFactory(ComponentFactory &factory) { factory.registerComponentCustom2(component::Type(), &component::Create); }

 /**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the component implementation that calls it. It simplifies adding new components, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param component The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type3 The third custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_3(component, Custom_type1, Custom_type2, Custom_type3) \
			static T_String Type() { return T_String(#component); } \
			static Component *Create(Entity &owner, const T_String &name, T_Any &custom1, T_Any &custom2, T_Any &custom3) \
			{ \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				Custom_type3 *customC = NULL_PTR; \
				try { \
					customC = custom3.cast<Custom_type3*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom3 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type3)).c_str()); \
				} \
				return new component(owner, name, *customA, *customB, *customC); \
			} \
			static void RegisterToFactory(ComponentFactory &factory) { factory.registerComponentCustom3(component::Type(), &component::Create); }

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the component implementation that calls it. It simplifies adding new components, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param component The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type3 The third custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type4 The fourth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_4(component, Custom_type1, Custom_type2, Custom_type3, Custom_type4) \
			static T_String Type() { return T_String(#component); } \
			static Component *Create(Entity &owner, const T_String &name, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4) \
			{ \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				Custom_type3 *customC = NULL_PTR; \
				try { \
					customC = custom3.cast<Custom_type3*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom3 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type3)).c_str()); \
				} \
				Custom_type4 *customD = NULL_PTR; \
				try { \
					customD = custom4.cast<Custom_type4*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom4 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type4)).c_str()); \
				} \
				return new component(owner, name, *customA, *customB, *customC, *customD); \
			} \
			static void RegisterToFactory(ComponentFactory &factory) { factory.registerComponentCustom4(component::Type(), &component::Create); }

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the component implementation that calls it. It simplifies adding new components, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param component The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type3 The third custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type4 The fourth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type5 The fifth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_5(component, Custom_type1, Custom_type2, Custom_type3, Custom_type4, Custom_type5) \
			static T_String Type() { return T_String(#component); } \
			static Component *Create(Entity &owner, const T_String &name, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5) \
			{ \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				Custom_type3 *customC = NULL_PTR; \
				try { \
					customC = custom3.cast<Custom_type3*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom3 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type3)).c_str()); \
				} \
				Custom_type4 *customD = NULL_PTR; \
				try { \
					customD = custom4.cast<Custom_type4*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom4 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type4)).c_str()); \
				} \
				Custom_type5 *customE = NULL_PTR; \
				try { \
					customE = custom5.cast<Custom_type5*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom5 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type5)).c_str()); \
				} \
				return new component(owner, name, *customA, *customB, *customC, *customD, *customE); \
			} \
			static void RegisterToFactory(ComponentFactory &factory) { factory.registerComponentCustom5(component::Type(), &component::Create); }

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the component implementation that calls it. It simplifies adding new components, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param component The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type3 The third custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type4 The fourth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type5 The fifth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type6 The sixth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_6(component, Custom_type1, Custom_type2, Custom_type3, Custom_type4, Custom_type5, Custom_type6) \
			static T_String Type() { return T_String(#component); } \
			static Component *Create(Entity &owner, const T_String &name, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5, T_Any &custom6) \
			{ \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				Custom_type3 *customC = NULL_PTR; \
				try { \
					customC = custom3.cast<Custom_type3*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom3 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type3)).c_str()); \
				} \
				Custom_type4 *customD = NULL_PTR; \
				try { \
					customD = custom4.cast<Custom_type4*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom4 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type4)).c_str()); \
				} \
				Custom_type5 *customE = NULL_PTR; \
				try { \
					customE = custom5.cast<Custom_type5*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom5 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type5)).c_str()); \
				} \
				Custom_type6 *customF = NULL_PTR; \
				try { \
					customF = custom6.cast<Custom_type6*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom6 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type6)).c_str()); \
				} \
				return new component(owner, name, *customA, *customB, *customC, *customD, *customE, *customF); \
			} \
			static void RegisterToFactory(ComponentFactory &factory) { factory.registerComponentCustom6(component::Type(), &component::Create); }

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the component implementation that calls it. It simplifies adding new components, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param component The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type3 The third custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type4 The fourth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type5 The fifth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type6 The sixth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type7 The seventh custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_7(component, Custom_type1, Custom_type2, Custom_type3, Custom_type4, Custom_type5, Custom_type6, Custom_type7) \
			static T_String Type() { return T_String(#component); } \
			static Component *Create(Entity &owner, const T_String &name, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5, T_Any &custom6, T_Any &custom7) \
			{ \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				Custom_type3 *customC = NULL_PTR; \
				try { \
					customC = custom3.cast<Custom_type3*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom3 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type3)).c_str()); \
				} \
				Custom_type4 *customD = NULL_PTR; \
				try { \
					customD = custom4.cast<Custom_type4*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom4 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type4)).c_str()); \
				} \
				Custom_type5 *customE = NULL_PTR; \
				try { \
					customE = custom5.cast<Custom_type5*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom5 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type5)).c_str()); \
				} \
				Custom_type6 *customF = NULL_PTR; \
				try { \
					customF = custom6.cast<Custom_type6*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom6 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type6)).c_str()); \
				} \
				Custom_type7 *customG = NULL_PTR; \
				try { \
					customG = custom7.cast<Custom_type7*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom7 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type7)).c_str()); \
				} \
				return new component(owner, name, *customA, *customB, *customC, *customD, *customE, *customF, *customG); \
			} \
			static void RegisterToFactory(ComponentFactory &factory) { factory.registerComponentCustom7(component::Type(), &component::Create); }

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the component implementation that calls it. It simplifies adding new components, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param component The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type3 The third custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type4 The fourth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type5 The fifth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type6 The sixth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type7 The seventh custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type8 The eight custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_8(component, Custom_type1, Custom_type2, Custom_type3, Custom_type4, Custom_type5, Custom_type6, Custom_type7, Custom_type8) \
			static T_String Type() { return T_String(#component); } \
			static Component *Create(Entity &owner, const T_String &name, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5, T_Any &custom6, T_Any &custom7, T_Any &custom8) \
			{ \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				Custom_type3 *customC = NULL_PTR; \
				try { \
					customC = custom3.cast<Custom_type3*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom3 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type3)).c_str()); \
				} \
				Custom_type4 *customD = NULL_PTR; \
				try { \
					customD = custom4.cast<Custom_type4*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom4 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type4)).c_str()); \
				} \
				Custom_type5 *customE = NULL_PTR; \
				try { \
					customE = custom5.cast<Custom_type5*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom5 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type5)).c_str()); \
				} \
				Custom_type6 *customF = NULL_PTR; \
				try { \
					customF = custom6.cast<Custom_type6*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom6 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type6)).c_str()); \
				} \
				Custom_type7 *customG = NULL_PTR; \
				try { \
					customG = custom7.cast<Custom_type7*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom7 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type7)).c_str()); \
				} \
				Custom_type8 *customH = NULL_PTR; \
				try { \
					customH = custom8.cast<Custom_type8*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom8 was bad when calling " + T_String(#component) + "::Create, expected " + T_String(#Custom_type8)).c_str()); \
				} \
				return new component(owner, name, *customA, *customB, *customC, *customD, *customE, *customF, *customG, *customH); \
			} \
			static void RegisterToFactory(ComponentFactory &factory) { factory.registerComponentCustom8(component::Type(), &component::Create); }
