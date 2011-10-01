#pragma once

/**
 * @file
 * @class Factotum::PropertySerializer
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property Serializer default implementation class
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
 * Property Serializer
 * 
 */

#include "types_config.h"
#include "IPropertySerializer.h"
#include "IProperty.h"
#include "Property.h"
#include "IPropertyList.h"
#include "PropertyList.h"
#include <sstream>

namespace Factotum {

class PropertySerializer : public IPropertySerializer
{
public: 
	/**
	 * Constructor
	 */
	PropertySerializer() {}

	/**
	 * Destructor
	 */
	virtual ~PropertySerializer() {}

	/**
	 * Serializes a property to text string
	 *
	 * @param property The property to serialize
	 * @return Returns serialized property
	 */
	virtual T_String toString(const IProperty *property)
	{
		if(property->getId() == IProperty::getTypeId<bool>())
			return serialize<bool>(property);
		else if(property->getId() == IProperty::getTypeId<S32>())
			return serialize<S32>(property);
		else if(property->getId() == IProperty::getTypeId<U32>())
			return serialize<U32>(property);
		else if(property->getId() == IProperty::getTypeId<F32>())
			return serialize<F32>(property);

		return "";
	}

	/**
	 * Serializes a property list to text string
	 *
	 * @param propertyList The property list to serialize
	 * @return Returns serialized property list
	 */
	virtual T_String toString(IPropertyList *propertyList)
	{
		if(propertyList->getId() == IPropertyList::getTypeId<bool>())
			return serialize<bool>(propertyList);
		else if(propertyList->getId() == IPropertyList::getTypeId<S32>())
			return serialize<S32>(propertyList);
		else if(propertyList->getId() == IPropertyList::getTypeId<U32>())
			return serialize<U32>(propertyList);
		else if(propertyList->getId() == IPropertyList::getTypeId<F32>())
			return serialize<F32>(propertyList);

		return "";
	}

	/**
	 * Deserializes a property from string
	 *
	 * @param property The property to hold the serialized value
	 * @param serialized_property The string to deserialize
	 */
	virtual void fromString(IProperty *property, const T_String &serialized_property)
	{
		if(property->getId() == IProperty::getTypeId<bool>())
			deserialize<bool>(property, serialized_property);
		else if(property->getId() == IProperty::getTypeId<S32>())
			deserialize<S32>(property, serialized_property);
		else if(property->getId() == IProperty::getTypeId<U32>())
			deserialize<U32>(property, serialized_property);
		else if(property->getId() == IProperty::getTypeId<F32>())
			deserialize<F32>(property, serialized_property);
	}

	/**
	 * Deserializes a property list from string
	 *
	 * @param propertyList The property list to hold the serialized value
	 * @param serialized_propertyList The string to deserialize
	 */
	virtual void fromString(IPropertyList *propertyList, const T_String &serialized_propertyList)
	{
		if(propertyList->getId() == IPropertyList::getTypeId<bool>())
			deserialize<bool>(propertyList, serialized_propertyList);
		else if(propertyList->getId() == IPropertyList::getTypeId<S32>())
			deserialize<S32>(propertyList, serialized_propertyList);
		else if(propertyList->getId() == IPropertyList::getTypeId<U32>())
			deserialize<U32>(propertyList, serialized_propertyList);
		else if(propertyList->getId() == IPropertyList::getTypeId<F32>())
			deserialize<F32>(propertyList, serialized_propertyList);
	}

private:
	/**
	 * Serializes any base C++ type into a string stream and returns the generated string
	 *
	 * @param property The property to serialize
	 * @return Returns serialized property
	 */
	template<typename T>
	T_String serialize(const IProperty *property)
	{	
		const Property<T> *prop = static_cast<const Property<T> *>(property);
		std::stringstream stream;
		stream << prop->get();
		return stream.str();
	}

	/**
	 * Serializes any base C++ type into a string stream and returns the generated string
	 *
	 * @param propertyList The property list to serialize
	 * @return Returns serialized property list
	 */
	template<typename T>
	T_String serialize(IPropertyList *propertyList)
	{	
		PropertyList<T> *prop = static_cast<PropertyList<T> *>(propertyList);
		std::stringstream stream;
		stream << prop->size() << " ";
		for(U32 i = 0; i < prop->size(); i++)
			stream << /*prop->at(i).get()*/ prop->get()[i] << " ";
		return stream.str();
	}

	/**
	 * Deserializes any base C++ type property from string
	 *
	 * @param property The property to hold the serialized value
	 * @param serialized_property The string to deserialize
	 */
	template<typename T>
	void deserialize(IProperty *property, const T_String &serialized_property)
	{	
		T value;
		std::stringstream stream(serialized_property);
		stream >> std::dec >> value;

		Property<T> *prop = static_cast<Property<T> *>(property);
		prop->set(value);
	}

	/**
	 * Deserializes any base C++ type property list from string
	 *
	 * @param propertyList The property list to hold the serialized value
	 * @param serialized_propertyList The string to deserialize
	 */
	template<typename T>
	void deserialize(IPropertyList *propertyList, const T_String &serialized_propertyList)
	{	
		/*U32 size;
		std::stringstream stream(serialized_propertyList);
		stream >> std::dec >> size;

		PropertyList<T> *prop = static_cast<PropertyList<T> *>(propertyList);
		prop->resize(size);
		T value;
		for(U32 i = 0; i < size; i++)
		{
			stream >> value;
			PropertyListIndexValue<T> index = prop->at(i);
			index.set(value);
		}*/
	}
};

} //namespace Factotum
