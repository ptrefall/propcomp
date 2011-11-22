#pragma once

/**
 * @file
 * @class Totem::Entity
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Entity class
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
 * The entity is defined through the composition of components, properties and
 * handlers it's made from.
 * 
 */

#include <ComponentHandler.h>
#include <PropertyHandler.h>
#include <PropertyListHandler.h>
#if USE_TEMPLATE_EVENT_HANDLER
#include <TemplateEventHandler.h>
#elif USE_ANY_EVENT_HANDLER
#include <AnyEventHandler.h>
#endif
#include <DelegateHandler.h>

namespace Totem {

class Entity :	public ComponentHandler<Entity>, 
				public PropertyHandler, 
				public PropertyListHandler, 
#if USE_TEMPLATE_EVENT_HANDLER
				public TemplateEventHandler,
#elif USE_ANY_EVENT_HANDLER
				public AnyEventHandler,
#endif
				public DelegateHandler
{
public:
	/// Constructor
	Entity(ComponentFactory &factory)
#pragma warning(suppress: 4355)
		: ComponentHandler(*this, factory)
	{
	}

	/// Constructor
	Entity(ComponentFactory &factory, IPropertySerializer *serializer)
#pragma warning(suppress: 4355)
		: ComponentHandler(*this, factory), PropertyHandler(serializer), PropertyListHandler(serializer)
	{
	}

	/// Destructor
	virtual ~Entity() {}
};

} //namespace Totem
