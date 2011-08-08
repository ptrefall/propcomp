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

#include "types_config.h"

class Component;
class Entity;

class ComponentFactory
{
public:
	/**
	 * Constructor
	 */
	ComponentFactory();

	/**
	 * Destructor
	 */
	~ComponentFactory();

	/**
	 * Function pointer definition, forces a component implementation to provide
	 * a function that supports the format. Meant for a component implementation
	 * to instanciate itself within it's function, and then provide it, along with
	 * a type identifier, to the component factory for registration.
	 *
	 * @param entity Reference to the entity that will own this component instance.
	 * @param type The type identifier assigned to this component instance.
	 */
	typedef Component*(* ComponentCreator)(Entity &entity, const T_String &type);

	/**
	 * Registers a component with the factory. This has to be done before the component
	 * can be instanciated.
	 *
	 * @param type The identifier assigned to this component type.
	 * @param functor The function pointer to the component's create function.
	 */
    void registerComponent(const T_String &type, ComponentCreator functor);

	/**
	 * Create an instance of a component of type, owned by entity.
	 *
	 * @param entity The owner of the component instance.
	 * @param type The registered component type identifier associated with the component.
	 */
	Component* createComponent(Entity &entity, const T_String &type);

private:
	/// The container of component createor function pointers registered to the factory, each associated with a string key.
	T_Map<T_String, ComponentCreator>::Type* creators;
};
