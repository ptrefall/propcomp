#pragma once

#include "IProperty.h"

#include "../../depends/Standard/sigslot.h"
#include <memory>
#include <sstream>

namespace Totem
{

template<class PropertyType>
class SharedProperty;

class DefaultSharedPropertySerializer
{
public:
	template<class PropertyType>
	static std::string toString(const SharedProperty<PropertyType> * const property)
	{
		std::stringstream stream;
		stream << property->get();
		return stream.str();
	}

	template<class PropertyType>
	static void fromString(const std::string &serialized_property, SharedProperty<PropertyType> * property)
	{
		PropertyType value;
		std::stringstream stream(serialized_property);
		stream >> std::dec >> value;
		property->set(value);
	}
};

template<class PropertyType>
class SharedPropertyData
{
public:
	PropertyType value;
	unsigned int type;
	std::string name;
	sigslot::signal2<const PropertyType &, const PropertyType &> valueChanged;
};

template<class PropertyType>
class SharedProperty : public IProperty
{
public:
	SharedProperty() {}
	SharedProperty(const SharedProperty &copy)
		: data(copy.data)
	{
	}
	SharedProperty(const std::string &name)
		: data(std::make_shared<SharedPropertyData<PropertyType>>())
	{
		data->type = IProperty::getType<PropertyType>();
		data->name = name;
	}

	void set(const PropertyType& value, bool invokeValueChanged = true) 
	{ 
		if(data->value != value)
		{
			PropertyType oldValue = data->value;
			data->value = value; 

			if(invokeValueChanged)
				data->valueChanged.invoke(oldValue, value);
		}
	}

	const PropertyType &get() const { return data->value; }
	const unsigned int &getType() const override { return data->type; }
	const std::string &getName() const override { return data->name; }
	bool isNull() const override { return data == nullptr; }

	template<class PropertySerializer>
	std::string toString() const { return PropertySerializer::toString<PropertyType>(this); }
	std::string toString() const override { return toString<DefaultSharedPropertySerializer>(); }
	template<class PropertySerializer>
	void fromString(const std::string &serialized_property) { return PropertySerializer::fromString<PropertyType>(serialized_property, this); }
	void fromString(const std::string &serialized_property) override { return fromString<DefaultSharedPropertySerializer>(serialized_property); }

	sigslot::signal2<const PropertyType &, const PropertyType &> &valueChanged() { return data->valueChanged; }

	/// Set's property's data to rhs' shared pointer data.
	SharedProperty<PropertyType> operator= (const SharedProperty<PropertyType>& rhs);
	/// Set's property's data to rhs' value.
	SharedProperty<PropertyType> operator= (const PropertyType& rhs);

	/// Adds rhs' data value to property's data value
	SharedProperty<PropertyType> operator+= (const SharedProperty<PropertyType>& rhs);
	/// Adds rhs' value to property's data value
	SharedProperty<PropertyType> operator+= (const PropertyType& rhs);

	/// Subtracts rhs' data value from property's data value
	SharedProperty<PropertyType> operator-= (const SharedProperty<PropertyType>& rhs);
	/// Subtracts rhs' value from property's data value
	SharedProperty<PropertyType> operator-= (const PropertyType& rhs);

	/// Multiplies rhs' data value with property's data value
	SharedProperty<PropertyType> operator*= (const SharedProperty<PropertyType>& rhs);
	/// Multiplies rhs' value with property's data value
	SharedProperty<PropertyType> operator*= (const PropertyType& rhs);

	/// Check whether the shared pointer data of rhs is same as property's
	bool operator== (const SharedProperty<PropertyType>& rhs);
	/// Check whether the value of rhs equals that of property's data value
	bool operator== (const PropertyType& rhs);

	/// Check whether the shared pointer data of rhs is not the same as property's
	bool operator!= (const SharedProperty<PropertyType>& rhs);
	/// Check whether the value of rhs is not equals that of property's data value
	bool operator!= (const PropertyType& rhs);

	/// Check whether the data value of rhs is less than property's data value
	bool operator> (const SharedProperty<PropertyType>& rhs);
	/// Check whether the value of rhs is less than property's data value
	bool operator> (const PropertyType& rhs);

	/// Check whether the data value of rhs is greater than property's data value
	bool operator< (const SharedProperty<PropertyType>& rhs);
	/// Check whether the value of rhs is greater than property's data value
	bool operator< (const PropertyType& rhs);

	/// Instead of property.get() this operator exist for convenience.
	operator const PropertyType &() const { return data->value; }

private:
	std::shared_ptr<SharedPropertyData<PropertyType>> data;
};

template<class PropertyType>
inline SharedProperty<PropertyType> SharedProperty<PropertyType>::operator =(const SharedProperty<PropertyType> &rhs)
{
	data = rhs.data;
	return *this;
}

template<class PropertyType>
inline SharedProperty<PropertyType> SharedProperty<PropertyType>::operator =(const PropertyType &rhs)
{
	set(rhs);
	return *this;
}

template<class PropertyType>
inline SharedProperty<PropertyType> SharedProperty<PropertyType>::operator +=(const SharedProperty<PropertyType> &rhs)
{
	set(data->value + rhs.data->value);
	return *this;
}

template<class PropertyType>
inline SharedProperty<PropertyType> SharedProperty<PropertyType>::operator +=(const PropertyType &rhs)
{
	set(data->value + rhs);
	return *this;
}

template<class PropertyType>
inline SharedProperty<PropertyType> SharedProperty<PropertyType>::operator -=(const SharedProperty<PropertyType> &rhs)
{
	set(data->value - rhs.data->value);
	return *this;
}

template<class PropertyType>
inline SharedProperty<PropertyType> SharedProperty<PropertyType>::operator -=(const PropertyType &rhs)
{
	set(data->value - rhs);
	return *this;
}

template<class PropertyType>
inline SharedProperty<PropertyType> SharedProperty<PropertyType>::operator *=(const SharedProperty<PropertyType> &rhs)
{
	set(data->value * rhs.data->value);
	return *this;
}

template<class PropertyType>
inline SharedProperty<PropertyType> SharedProperty<PropertyType>::operator *=(const PropertyType &rhs)
{
	set(data->value * rhs);
	return *this;
}

template<class PropertyType>
inline bool SharedProperty<PropertyType>::operator ==(const SharedProperty<PropertyType> &rhs)
{
	return data == rhs.data;
}

template<class PropertyType>
inline bool SharedProperty<PropertyType>::operator ==(const PropertyType &rhs)
{
	return (data->value == rhs);
}

template<class PropertyType>
inline bool SharedProperty<PropertyType>::operator !=(const SharedProperty<PropertyType> &rhs)
{
	return data != rhs.data;
}

template<class PropertyType>
inline bool SharedProperty<PropertyType>::operator !=(const PropertyType &rhs)
{
	return (data->value != rhs);
}

template<class PropertyType>
inline bool SharedProperty<PropertyType>::operator >(const SharedProperty<PropertyType> &rhs)
{
	return (data->value > rhs.data->value);
}

template<class PropertyType>
inline bool SharedProperty<PropertyType>::operator >(const PropertyType &rhs)
{
	return (data->value > rhs);
}

template<class PropertyType>
inline bool SharedProperty<PropertyType>::operator <(const SharedProperty<PropertyType> &rhs)
{
	return (data->value < rhs.data->value);
}

template<class PropertyType>
inline bool SharedProperty<PropertyType>::operator <(const PropertyType &rhs)
{
	return (data->value < rhs);
}

} //namespace Totem
