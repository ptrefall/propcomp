#pragma once

/**
 * @file
 * @class IPropertyList
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
 * Note: Some of the libraries Component-based Entity Engine may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * Property Interface
 * 
 */

#include "types_config.h"

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
};
