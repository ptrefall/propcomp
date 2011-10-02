#pragma once

/**
 * @file
 * @class Factotum::IPropertyList
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property List Interface base class
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
 * Note: Some of the libraries Factotum EDK may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * PropertyList Interface
 * RTTI implementation was originally contributed by 'zerotri'.
 * 
 */

#include "types_config.h"

namespace Factotum {

class IPropertyList
{
public:
	/**
	 * Destructor
	 */
	virtual ~IPropertyList() {}

	/**
	 * Get the name of this property list.
	 *
	 * @return Returns the name of the property list.
	 */
	virtual const T_String &getName() const = 0;

	/**
	 * Check if PropertyListData exist in this PropertyList.
	 *
	 * @return Returns whether the PropertyListData of this property list has been initialized.
	 */
	virtual bool isNull() const = 0;

	/**
	 *
	 */
	template<typename PropertyType>
	static T_PropertyTypeId getTypeId()
	{
		static T_PropertyTypeId typeId(newPropertyTypeId());
		return typeId;
	}

	/**
	 *
	 */
	const T_PropertyTypeId &getId() const { return id; }

	/**
	 *
	 */
	virtual T_String toString() = 0;
	/**
	 *
	 */
	virtual void fromString(const T_String &serialized_propertyList) = 0;

protected:
	///
	T_PropertyTypeId id;
	
	/**
	 *
	 */
	static T_PropertyTypeId newPropertyTypeId()
	{
		static T_PropertyTypeId next_id(0);
		return next_id++;
	}
};

} //namespace Factotum
