#pragma once

/*Factotum EDK
Copyright (c) 2009 Pål Trefall and Kenneth Gangstø

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Note: Some of the libraries Factotum EDK may link to may have additional
requirements or restrictions.
*/

#include "types_config.h"
#include "PropertySerializer.h"
#include "IProperty.h"
#include "Property.h"
#include <sstream>

#include "../Common/Vector3.h"

class CustomPropertySerializer : public Factotum::PropertySerializer
{
public: 
	CustomPropertySerializer() {}
	virtual ~CustomPropertySerializer() {}

	virtual T_String toString(const Factotum::IProperty *property)
	{
		if(property->getId() == Factotum::IProperty::getTypeId<Vector3<F32>>())
			return serializeVector3<F32>(property);
		else if(property->getId() == Factotum::IProperty::getTypeId<Vector3<S32>>())
			return serializeVector3<S32>(property);
		else if(property->getId() == Factotum::IProperty::getTypeId<Vector3<U32>>())
			return serializeVector3<U32>(property);
		else
			return Factotum::PropertySerializer::toString(property);
	}

	virtual T_String toString(Factotum::IPropertyList *propertyList)
	{
		if(propertyList->getId() == Factotum::IPropertyList::getTypeId<Vector3<F32>>())
			return serializeVector3<F32>(propertyList);
		else if(propertyList->getId() == Factotum::IPropertyList::getTypeId<Vector3<S32>>())
			return serializeVector3<S32>(propertyList);
		else if(propertyList->getId() == Factotum::IPropertyList::getTypeId<Vector3<U32>>())
			return serializeVector3<U32>(propertyList);
		else
			return Factotum::PropertySerializer::toString(propertyList);
	}

	virtual void fromString(Factotum::IProperty *property, const T_String &serialized_property)
	{
		if(property->getId() == Factotum::IProperty::getTypeId<Vector3<F32>>())
			deserializeVector3<F32>(property, serialized_property);
		else if(property->getId() == Factotum::IProperty::getTypeId<Vector3<S32>>())
			deserializeVector3<S32>(property, serialized_property);
		else if(property->getId() == Factotum::IProperty::getTypeId<Vector3<U32>>())
			deserializeVector3<U32>(property, serialized_property);
		else
			Factotum::PropertySerializer::fromString(property, serialized_property);

	}

	virtual void fromString(Factotum::IPropertyList *propertyList, const T_String &serialized_propertyList)
	{
		if(propertyList->getId() == Factotum::IPropertyList::getTypeId<Vector3<F32>>())
			deserializeVector3<F32>(propertyList, serialized_propertyList);
		else if(propertyList->getId() == Factotum::IPropertyList::getTypeId<Vector3<S32>>())
			deserializeVector3<S32>(propertyList, serialized_propertyList);
		else if(propertyList->getId() == Factotum::IPropertyList::getTypeId<Vector3<U32>>())
			deserializeVector3<U32>(propertyList, serialized_propertyList);
		else
			Factotum::PropertySerializer::fromString(propertyList, serialized_propertyList);
	}

private:
	template<typename T>
	T_String serializeVector3(const Factotum::IProperty *property)
	{	
		const Factotum::Property<Vector3<T>> *prop = static_cast<const Factotum::Property<Vector3<T>> *>(property);
		std::stringstream stream;
		stream << prop->get().x << " ";
		stream << prop->get().y << " ";
		stream << prop->get().z;
		return stream.str();
	}

	template<typename T>
	T_String serializeVector3(Factotum::IPropertyList *propertyList)
	{	
		Factotum::PropertyList<Vector3<T>> *prop = static_cast<Factotum::PropertyList<Vector3<T>> *>(propertyList);
		std::stringstream stream;
		stream << prop->size() << " ";
		for(U32 i = 0; i < prop->size(); i++)
		{
			stream << prop->get()[i].x << " ";
			stream << prop->get()[i].y << " ";
			stream << prop->get()[i].z << " ";
		}
		return stream.str();
	}

	template<typename T>
	void deserializeVector3(Factotum::IProperty *property, const T_String &serialized_property)
	{	
		Vector3<T> value;
		std::stringstream stream(serialized_property);
		stream >> std::dec >> value.x >> value.y >> value.z;

		Factotum::Property<Vector3<T>> *prop = static_cast<Factotum::Property<Vector3<T>> *>(property);
		prop->set(value);
	}

	template<typename T>
	void deserializeVector3(Factotum::IPropertyList *propertyList, const T_String &serialized_propertyList)
	{	
		U32 size;
		std::stringstream stream(serialized_propertyList);
		stream >> std::dec >> size;

		Factotum::PropertyList<Vector3<T>> *prop = static_cast<Factotum::PropertyList<Vector3<T>> *>(propertyList);
		prop->resize(size);
		Vector3<T> value;
		for(U32 i = 0; i < size; i++)
		{
			stream >> value.x >> value.y >> value.z;
			(*prop)[i] = value;
		}
	}
};
