#pragma once
#pragma warning(push)
#pragma warning(disable : 4481)

#include "IProperty.h"

#include <sigslot.h>
#include <memory>

namespace Totem
{

template<class PropertyType>
class PropertyData
{
public:
	PropertyType value;
	std::string name;
	bool dirty;
	sigslot::signal2<const PropertyType &, const PropertyType &> valueChanged;
};

template<class PropertyType>
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
		data->name = name;
		data->dirty = false; 
	}

	void set(const PropertyType& value, bool invokeValueChanged = true) 
	{ 
		if(data->value != value)
		{
			PropertyType oldValue = data->value;
			data->value = value; 
			data->dirty = true; 

			if(invokeValueChanged)
				data->valueChanged.invoke(oldValue, value);
		}
	}

	unsigned int getRuntimeTypeId() const override { return IProperty::getRuntimeTypeId<PropertyType>(); }

	const PropertyType &get() const { return data->value; }
	PropertyType &get() { return data->value; }
	const std::string &getName() const override { return data->name; }
	bool isNull() const override { return data == nullptr; }
	bool isDirty() const override { return data->dirty; }
	void clearDirty() override { data->dirty = false; }

	sigslot::signal2<const PropertyType &, const PropertyType &> &valueChanged() { return data->valueChanged; }

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
	/// Instead of property.get() this operator exist for convenience.
	operator PropertyType &() { return data->value; }

private:
	std::shared_ptr<PropertyData<PropertyType>> data;
};

template<class PropertyType>
inline Property<PropertyType> Property<PropertyType>::operator =(const Property<PropertyType> &rhs)
{
	data = rhs.data;
	return *this;
}

template<class PropertyType>
inline Property<PropertyType> Property<PropertyType>::operator =(const PropertyType &rhs)
{
	set(rhs);
	return *this;
}

template<class PropertyType>
inline Property<PropertyType> Property<PropertyType>::operator +=(const Property<PropertyType> &rhs)
{
	set(data->value + rhs.data->value);
	return *this;
}

template<class PropertyType>
inline Property<PropertyType> Property<PropertyType>::operator +=(const PropertyType &rhs)
{
	set(data->value + rhs);
	return *this;
}

template<class PropertyType>
inline Property<PropertyType> Property<PropertyType>::operator -=(const Property<PropertyType> &rhs)
{
	set(data->value - rhs.data->value);
	return *this;
}

template<class PropertyType>
inline Property<PropertyType> Property<PropertyType>::operator -=(const PropertyType &rhs)
{
	set(data->value - rhs);
	return *this;
}

template<class PropertyType>
inline Property<PropertyType> Property<PropertyType>::operator *=(const Property<PropertyType> &rhs)
{
	set(data->value * rhs.data->value);
	return *this;
}

template<class PropertyType>
inline Property<PropertyType> Property<PropertyType>::operator *=(const PropertyType &rhs)
{
	set(data->value * rhs);
	return *this;
}

template<class PropertyType>
inline bool Property<PropertyType>::operator ==(const Property<PropertyType> &rhs)
{
	return data == rhs.data;
}

template<class PropertyType>
inline bool Property<PropertyType>::operator ==(const PropertyType &rhs)
{
	return (data->value == rhs);
}

template<class PropertyType>
inline bool Property<PropertyType>::operator !=(const Property<PropertyType> &rhs)
{
	return data != rhs.data;
}

template<class PropertyType>
inline bool Property<PropertyType>::operator !=(const PropertyType &rhs)
{
	return (data->value != rhs);
}

template<class PropertyType>
inline bool Property<PropertyType>::operator >(const Property<PropertyType> &rhs)
{
	return (data->value > rhs.data->value);
}

template<class PropertyType>
inline bool Property<PropertyType>::operator >(const PropertyType &rhs)
{
	return (data->value > rhs);
}

template<class PropertyType>
inline bool Property<PropertyType>::operator <(const Property<PropertyType> &rhs)
{
	return (data->value < rhs.data->value);
}

template<class PropertyType>
inline bool Property<PropertyType>::operator <(const PropertyType &rhs)
{
	return (data->value < rhs);
}

} //namespace Totem

#pragma warning(pop)
