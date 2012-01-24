#pragma once

#include "IProperty.h"

#include "../../depends/Standard/sigslot.h"
#include <memory>
#include <sstream>

namespace Totem
{

template<class PropertyType, class PropertySerializer>
class Property;

class DefaultPropertySerializer
{
public:
	template<class PropertyType, class PropertySerializer>
	static std::string toString(const Property<PropertyType, PropertySerializer> * const property)
	{
		std::stringstream stream;
		stream << property->get();
		return stream.str();
	}

	template<class PropertyType, class PropertySerializer>
	static void fromString(const std::string &serialized_property, Property<PropertyType, PropertySerializer> * property)
	{
		PropertyType value;
		std::stringstream stream(serialized_property);
		stream >> std::dec >> value;
		property->set(value);
	}
};

template<class PropertyType>
class PropertyData
{
public:
	PropertyType value;
	unsigned int type;
	std::string name;
};

template<class PropertyType, class PropertySerializer = DefaultPropertySerializer>
class Property : public IProperty
{
public:
	Property() {}
	Property(const Property &copy)
		: data(copy.data)
	{
	}
	Property(const std::string &name)
		: data(std::make_shared<PropertyData<PropertyType>>())
	{
		data->type = IProperty::getType<PropertyType>();
		data->name = name;
	}

	void set(const PropertyType& value) 
	{ 
		if(data->value != value)
		{
			PropertyType oldValue = data->value;
			data->value = value; 
		}
	}

	const PropertyType &get() const { return data->value; }
	const unsigned int &getType() const override { return data->type; }
	const std::string &getName() const override { return data->name; }
	bool isNull() const override { return data == nullptr; }

	std::string toString(IPropertySerializerPtr serializer) const override { return PropertySerializer::toString<PropertyType, PropertySerializer>(this); }
	void fromString(const std::string &serialized_property, IPropertySerializerPtr serializer) override { return PropertySerializer::fromString<PropertyType, PropertySerializer>(serialized_property, this); }

	/// Set's property's data to rhs' shared pointer data.
	Property<PropertyType> operator= (const Property<PropertyType>& rhs);
	/// Set's property's data to rhs' value.
	Property<PropertyType> operator= (const PropertyType& rhs);

	/// Adds rhs' data value to property's data value
	Property<PropertyType> operator+= (const Property<PropertyType>& rhs);
	/// Adds rhs' value to property's data value
	Property<PropertyType> operator+= (const PropertyType& rhs);

	/// Subtracts rhs' data value from property's data value
	Property<PropertyType> operator-= (const Property<PropertyType>& rhs);
	/// Subtracts rhs' value from property's data value
	Property<PropertyType> operator-= (const PropertyType& rhs);

	/// Multiplies rhs' data value with property's data value
	Property<PropertyType> operator*= (const Property<PropertyType>& rhs);
	/// Multiplies rhs' value with property's data value
	Property<PropertyType> operator*= (const PropertyType& rhs);

	/// Check whether the shared pointer data of rhs is same as property's
	bool operator== (const Property<PropertyType>& rhs);
	/// Check whether the value of rhs equals that of property's data value
	bool operator== (const PropertyType& rhs);

	/// Check whether the shared pointer data of rhs is not the same as property's
	bool operator!= (const Property<PropertyType>& rhs);
	/// Check whether the value of rhs is not equals that of property's data value
	bool operator!= (const PropertyType& rhs);

	/// Check whether the data value of rhs is less than property's data value
	bool operator> (const Property<PropertyType>& rhs);
	/// Check whether the value of rhs is less than property's data value
	bool operator> (const PropertyType& rhs);

	/// Check whether the data value of rhs is greater than property's data value
	bool operator< (const Property<PropertyType>& rhs);
	/// Check whether the value of rhs is greater than property's data value
	bool operator< (const PropertyType& rhs);

	/// Instead of property.get() this operator exist for convenience.
	operator const PropertyType &() const { return data->value; }

private:
	std::shared_ptr<PropertyData<PropertyType>> data;
};

template<class PropertyType, class PropertySerializer>
inline Property<PropertyType> Property<PropertyType, PropertySerializer>::operator =(const Property<PropertyType> &rhs)
{
	data = rhs.data;
	return *this;
}

template<class PropertyType, class PropertySerializer>
inline Property<PropertyType> Property<PropertyType, PropertySerializer>::operator =(const PropertyType &rhs)
{
	set(rhs);
	return *this;
}

template<class PropertyType, class PropertySerializer>
inline Property<PropertyType> Property<PropertyType, PropertySerializer>::operator +=(const Property<PropertyType> &rhs)
{
	set(data->value + rhs.data->value);
	return *this;
}

template<class PropertyType, class PropertySerializer>
inline Property<PropertyType> Property<PropertyType, PropertySerializer>::operator +=(const PropertyType &rhs)
{
	set(data->value + rhs);
	return *this;
}

template<class PropertyType, class PropertySerializer>
inline Property<PropertyType> Property<PropertyType, PropertySerializer>::operator -=(const Property<PropertyType> &rhs)
{
	set(data->value - rhs.data->value);
	return *this;
}

template<class PropertyType, class PropertySerializer>
inline Property<PropertyType> Property<PropertyType, PropertySerializer>::operator -=(const PropertyType &rhs)
{
	set(data->value - rhs);
	return *this;
}

template<class PropertyType, class PropertySerializer>
inline Property<PropertyType> Property<PropertyType, PropertySerializer>::operator *=(const Property<PropertyType> &rhs)
{
	set(data->value * rhs.data->value);
	return *this;
}

template<class PropertyType, class PropertySerializer>
inline Property<PropertyType> Property<PropertyType, PropertySerializer>::operator *=(const PropertyType &rhs)
{
	set(data->value * rhs);
	return *this;
}

template<class PropertyType, class PropertySerializer>
inline bool Property<PropertyType, PropertySerializer>::operator ==(const Property<PropertyType> &rhs)
{
	return data == rhs.data;
}

template<class PropertyType, class PropertySerializer>
inline bool Property<PropertyType, PropertySerializer>::operator ==(const PropertyType &rhs)
{
	return (data->value == rhs);
}

template<class PropertyType, class PropertySerializer>
inline bool Property<PropertyType, PropertySerializer>::operator !=(const Property<PropertyType> &rhs)
{
	return data != rhs.data;
}

template<class PropertyType, class PropertySerializer>
inline bool Property<PropertyType, PropertySerializer>::operator !=(const PropertyType &rhs)
{
	return (data->value != rhs);
}

template<class PropertyType, class PropertySerializer>
inline bool Property<PropertyType, PropertySerializer>::operator >(const Property<PropertyType> &rhs)
{
	return (data->value > rhs.data->value);
}

template<class PropertyType, class PropertySerializer>
inline bool Property<PropertyType, PropertySerializer>::operator >(const PropertyType &rhs)
{
	return (data->value > rhs);
}

template<class PropertyType, class PropertySerializer>
inline bool Property<PropertyType, PropertySerializer>::operator <(const Property<PropertyType> &rhs)
{
	return (data->value < rhs.data->value);
}

template<class PropertyType, class PropertySerializer>
inline bool Property<PropertyType, PropertySerializer>::operator <(const PropertyType &rhs)
{
	return (data->value < rhs);
}

} //namespace Totem

