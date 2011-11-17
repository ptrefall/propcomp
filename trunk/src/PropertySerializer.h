#pragma once

/**
 * @file
 * @class Totem::PropertySerializer
 *
 * @author P�l Trefall
 * @author Kenneth Gangst�
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
 * Note: Some of the libraries Totem EDK may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * Property Serializer
 * RTTI implementation was originally contributed by 'zerotri'.
 * 
 */

#include "types_config.h"
#include "IPropertySerializer.h"
#include "IProperty.h"
#include "Property.h"
#include "IPropertyList.h"
#include "PropertyList.h"
#include <sstream>

namespace Totem {

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
	virtual T_String toString(const IProperty *const property)
	{
		if(property->getType() == IProperty::getType<bool>())
			return serialize<bool>(property);
		else if(property->getType() == IProperty::getType<char>())
			return serialize<char>(property);
		else if(property->getType() == IProperty::getType<unsigned char>())
			return serialize<unsigned char>(property);
		else if(property->getType() == IProperty::getType<S32>())
			return serialize<S32>(property);
		else if(property->getType() == IProperty::getType<U32>())
			return serialize<U32>(property);
		else if(property->getType() == IProperty::getType<F32>())
			return serialize<F32>(property);
		else if(property->getType() == IProperty::getType<D32>())
			return serialize<D32>(property);

		return "";
	}

	/**
	 * Serializes a property list to text string
	 *
	 * @param propertyList The property list to serialize
	 * @return Returns serialized property list
	 */
	virtual T_String toString(IPropertyList *const propertyList)
	{
		if(propertyList->getType() == IPropertyList::getType<bool>())
		{
#if USE_PROPERTY_LIST_BOOL_VECTOR_RTTI_WORKAROUND
			return serialize<bool>(propertyList);
#else
			throw T_Exception("Enable USE_PROPERTY_LIST_BOOL_VECTOR_RTTI_WORKAROUND in types_config.h in order to use bool with PropertyList, but read the comment thoroughly!");
#endif
		}
		else if(propertyList->getType() == IPropertyList::getType<char>())
			return serialize<char>(propertyList);
		else if(propertyList->getType() == IPropertyList::getType<unsigned char>())
			return serialize<unsigned char>(propertyList);
		else if(propertyList->getType() == IPropertyList::getType<S32>())
			return serialize<S32>(propertyList);
		else if(propertyList->getType() == IPropertyList::getType<U32>())
			return serialize<U32>(propertyList);
		else if(propertyList->getType() == IPropertyList::getType<F32>())
			return serialize<F32>(propertyList);
		else if(propertyList->getType() == IPropertyList::getType<D32>())
			return serialize<D32>(propertyList);

		return "";
	}

	/**
	 * Deserializes a property from string
	 *
	 * @param property The property to hold the serialized value
	 * @param serialized_property The string to deserialize
	 */
	virtual void fromString(IProperty *const property, const T_String &serialized_property)
	{
		if(property->getType() == IProperty::getType<bool>())
			deserialize<bool>(property, serialized_property);
		else if(property->getType() == IProperty::getType<char>())
			deserialize<char>(property, serialized_property);
		else if(property->getType() == IProperty::getType<unsigned char>())
			deserialize<unsigned char>(property, serialized_property);
		else if(property->getType() == IProperty::getType<S32>())
			deserialize<S32>(property, serialized_property);
		else if(property->getType() == IProperty::getType<U32>())
			deserialize<U32>(property, serialized_property);
		else if(property->getType() == IProperty::getType<F32>())
			deserialize<F32>(property, serialized_property);
		else if(property->getType() == IProperty::getType<D32>())
			deserialize<D32>(property, serialized_property);
	}

	/**
	 * Deserializes a property list from string
	 *
	 * @param propertyList The property list to hold the serialized value
	 * @param serialized_propertyList The string to deserialize
	 */
	virtual void fromString(IPropertyList *const propertyList, const T_String &serialized_propertyList)
	{
		if(propertyList->getType() == IPropertyList::getType<bool>())
		{
#if USE_PROPERTY_LIST_BOOL_VECTOR_RTTI_WORKAROUND
			deserialize<bool>(propertyList, serialized_propertyList);
#else
			throw T_Exception("Enable USE_PROPERTY_LIST_BOOL_VECTOR_RTTI_WORKAROUND in types_config.h in order to use bool with PropertyList, but read the comment thoroughly!");
#endif
		}
		else if(propertyList->getType() == IPropertyList::getType<char>())
			deserialize<char>(propertyList, serialized_propertyList);
		else if(propertyList->getType() == IPropertyList::getType<unsigned char>())
			deserialize<unsigned char>(propertyList, serialized_propertyList);
		else if(propertyList->getType() == IPropertyList::getType<S32>())
			deserialize<S32>(propertyList, serialized_propertyList);
		else if(propertyList->getType() == IPropertyList::getType<U32>())
			deserialize<U32>(propertyList, serialized_propertyList);
		else if(propertyList->getType() == IPropertyList::getType<F32>())
			deserialize<F32>(propertyList, serialized_propertyList);
		else if(propertyList->getType() == IPropertyList::getType<D32>())
			deserialize<D32>(propertyList, serialized_propertyList);
	}

private:
	/**
	 * Serializes any base C++ type into a string stream and returns the generated string
	 *
	 * @param property The property to serialize
	 * @return Returns serialized property
	 */
	template<typename T>
	T_String serialize(const IProperty *const property)
	{	
		const Property<T> *const prop = static_cast<const Property<T> *const>(property);
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
	T_String serialize(IPropertyList *const propertyList)
	{	
		PropertyList<T> *const prop = static_cast<PropertyList<T> *const>(propertyList);
		std::stringstream stream;
		stream << prop->size() << " ";
		for(U32 i = 0; i < prop->size(); i++)
#if USE_PROPERTY_LIST_BOOL_VECTOR_RTTI_WORKAROUND
		{
			if(prop->getId() == IPropertyList::getTypeId<bool>())
				stream << prop->at_bool(i).get() << " ";
			else
				stream << prop->at(i).get() << " ";
		}
#else
			stream << prop->at(i).get() << " ";
#endif
		return stream.str();
	}

	/**
	 * Deserializes any base C++ type property from string
	 *
	 * @param property The property to hold the serialized value
	 * @param serialized_property The string to deserialize
	 */
	template<typename T>
	void deserialize(IProperty *const property, const T_String &serialized_property)
	{	
		T value;
		std::stringstream stream(serialized_property);
		stream >> std::dec >> value;

		Property<T> *const prop = static_cast<Property<T> *const >(property);
		prop->set(value);
	}

	/**
	 * Deserializes any base C++ type property list from string
	 *
	 * @param propertyList The property list to hold the serialized value
	 * @param serialized_propertyList The string to deserialize
	 */
	template<typename T>
	void deserialize(IPropertyList *const propertyList, const T_String &serialized_propertyList)
	{	
		U32 size;
		std::stringstream stream(serialized_propertyList);
		stream >> std::dec >> size;

		PropertyList<T> *const prop = static_cast<PropertyList<T> *const>(propertyList);
		prop->resize(size);
		T value;
		for(U32 i = 0; i < size; i++)
		{
			stream >> value;
#if USE_PROPERTY_LIST_BOOL_VECTOR_RTTI_WORKAROUND
			if(prop->getId() == IPropertyList::getTypeId<bool>())
			{
				PropertyListIndexValueBool<T> index = prop->at_bool(i);
				index.set(value);
			}
			else
			{
				PropertyListIndexValue<T> index = prop->at(i);
				index.set(value);
			}
			
#else
			PropertyListIndexValue<T> index = prop->at(i);
			index.set(value);
#endif
		}
	}
};

} //namespace Totem
