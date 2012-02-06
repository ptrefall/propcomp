#pragma once

#include "IPropertyList.h"

#include <sigslot.h>
#include <memory>
#include <vector>

namespace Totem
{

template<class PropertyType>
class SharedPropertyListData
{
public:
	std::vector<PropertyType> value;
	unsigned int type;
	std::string name;
	sigslot::signal3<const unsigned int &, const PropertyType &, const PropertyType &> valueChanged;
	sigslot::signal2<const unsigned int &, const PropertyType &> valueAdded;
	sigslot::signal2<const unsigned int &, const PropertyType &> valueErased;
	sigslot::signal0<> valuesCleared;
	sigslot::signal2<const unsigned int &, const unsigned int &> listResized;
};

template<class PropertyType>
class SharedPropertyListIndexValue
{
public:
	SharedPropertyListIndexValue(std::shared_ptr<SharedPropertyListData<PropertyType>> data, const unsigned int &index)
		: data(data), index(index)
	{
	}

	const PropertyType &get() const { return data->value[index]; }

	void set(const PropertyType &rhs, bool invokeValueChanged = true)
	{
		PropertyType oldValue = data->value[index];
		data->value[index] = rhs;
		if(invokeValueChanged)
			data->valueChanged.invoke(index, oldValue, rhs);
	}

	void operator= (const PropertyType &rhs) { set(rhs); }

	SharedPropertyListIndexValue<PropertyType> &operator= (const SharedPropertyListIndexValue<PropertyType> &rhs)
	{
		if(this == &rhs)
			return *this;
		throw std::runtime_error("Operation not supported!");
	}
	operator const PropertyType &() const { return get(); }

	SharedPropertyListIndexValue<PropertyType> &operator+= (const SharedPropertyListIndexValue<PropertyType>& rhs)
	{
		if(this == &rhs)
			return *this;

		set(get() + rhs.get());
		return *this;
	}

	SharedPropertyListIndexValue<PropertyType> &operator+= (const PropertyType& rhs)
	{
		set(get() + rhs);
		return *this;
	}

	SharedPropertyListIndexValue<PropertyType> &operator-= (const SharedPropertyListIndexValue<PropertyType>& rhs)
	{
		if(this == &rhs)
			return *this;

		set(get() - rhs.get());
		return *this;
	}

	SharedPropertyListIndexValue<PropertyType> &operator-= (const PropertyType& rhs)
	{
		set(get() - rhs);
		return *this;
	}

	SharedPropertyListIndexValue<PropertyType> &operator*= (const SharedPropertyListIndexValue<PropertyType>& rhs)
	{
		if(this == &rhs)
			return *this;

		set(get() * rhs.get());
		return *this;
	}

	SharedPropertyListIndexValue<PropertyType> &operator*= (const PropertyType& rhs)
	{
		set(get() * rhs);
		return *this;
	}

	SharedPropertyListIndexValue<PropertyType> &operator/= (const SharedPropertyListIndexValue<PropertyType>& rhs)
	{
		if(this == &rhs)
			return *this;

		set(get() / rhs.get());
		return *this;
	}

	SharedPropertyListIndexValue<PropertyType> &operator/= (const PropertyType& rhs)
	{
		set(get() / rhs);
		return *this;
	}

private:
	std::shared_ptr<SharedPropertyListData<PropertyType>> data;
	const unsigned int &index;
};

template<class PropertyType>
class SharedPropertyList : public IPropertyList
{
public:
	SharedPropertyList() {}
	SharedPropertyList(const SharedPropertyList &copy)
		: data(copy.data)
	{
	}
	SharedPropertyList(const std::string &name)
		: data(std::make_shared<SharedPropertyListData<PropertyType>>())
	{
		data->type = IProperty::getType<PropertyType>();
		data->name = name;
	}

	void push_back(const PropertyType& value, bool invokeValueAdded = true) 
	{ 
		data->value.push_back(value); 

		if(invokeValueAdded)
			data->valueAdded.invoke(data->value.size()-1, value);
	}

	void erase(const unsigned int &index, bool invokeValueErased = true)
	{
		PropertyType value = data->value[index];
		data->value.erase(data->value.begin()+index);
		if(invokeValueErased)
			data->valueErased.invoke(index, value);
	}

	void clear(bool invokeValuesCleared = true)
	{
		data->value.clear();
		if(invokeValuesCleared)
			data->valuesCleared.invoke();
	}

	unsigned int size() const { return data->value.size(); }
	bool empty() const { return data->value.empty(); }

	void resize(const unsigned int &size, bool invokeListResized = true)
	{
		unsigned int oldSize = data->value.size();
		data->value.resize(size);
		if(invokeListResized)
			data->listResized(oldSize, size);
	}

	void resize(const unsigned int &size, const PropertyType &value, bool invokeListResized = true)
	{
		unsigned int oldSize = data->value.size();
		data->value.resize(size, value);
		if(invokeListResized)
			data->listResized(oldSize, size);
	}

	SharedPropertyListIndexValue<PropertyType> at(const unsigned int &index)
	{
		if(index >= data->value.size())
			throw std::runtime_error("Index was out of bounds for shared property list");

		return SharedPropertyListIndexValue<PropertyType>(data, index);
	}

	const std::vector<PropertyType> &get() const { return data->value; }
	const unsigned int &getType() const override { return data->type; }
	const std::string &getName() const override { return data->name; }
	bool isNull() const override { return data == nullptr; }

	sigslot::signal3<const unsigned int &, const PropertyType &, const PropertyType &> &valueChanged() { return data->valueChanged; }
	sigslot::signal2<const unsigned int &, const PropertyType &> &valueAdded() {return data->valueAdded; }
	sigslot::signal2<const unsigned int &, const PropertyType &> &valueErased() { return data->valueErased; }
	sigslot::signal0<> &valuesCleared() { return data->valuesCleared; }
	sigslot::signal2<const unsigned int &, const unsigned int &> &listResized() { return data->listResized; }

	/// Set's property's data to rhs' shared pointer data.
	SharedPropertyList<PropertyType> operator= (const SharedPropertyList<PropertyType>& rhs)
	{
		data = rhs.data;
		return *this;
	}
	/// Get the value of list at given index.
	SharedPropertyListIndexValue<PropertyType> operator[] (const unsigned int& index)
	{
		return at(index);
	}
	/// Instead of propertyList.get() this operator exist for convenience.
	operator const std::vector<PropertyType> &() const { return data->value; }

private:
	std::shared_ptr<SharedPropertyListData<PropertyType>> data;
};

} //namespace Totem
