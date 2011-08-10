#pragma once

/**
 * @file
 * @class PropertyData
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief PropertyData implementation class
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
 * PropertyData
 * 
 */

#include "types_config.h"

#include "IProperty.h"

template<class T>
class PropertyData HAS_SIGNALSLOTS_INHERITANCE_TYPE
{
public:
	/**
	 * Destructor
	 */
	~PropertyData() {}
	/// Actual data of the property.
	T value;
	/// Name of the property.
	T_String name;
	/// Is the property read-only?
	bool readOnly;
	/// Signal that's emitted when the value of the property change, returning the old and new value.
	typename T_Signal_v2<const T&, const T&>::Type valueChanged;
};

/**
 * @file
 * @class Property
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property implementation class
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
 * Property
 * 
 */

template<class T>
class Property : public IProperty
{
public:
	/**
	 * Default Constructor, results in a Property with no data!
	 */
	Property()
	{
	}

	/**
	 * Copy Constructor
	 */
	Property(const Property& copy)
	: data(copy.data)
	{
	}

	/**
	 * Constructor
	 *
	 * @param name Name of the property.
	 * @param readOnly Should the property be read only? (Defaults to false).
	 */
	Property(const T_String &name, bool readOnly = false)
	: data(new PropertyData<T>())
	{	
		data->name = name;
		data->readOnly = readOnly;
	}

	/**
	 * Destructor
	 */
	virtual ~Property() {}

	/**
	 * Set the value of the property. Handles setting the actual PropertyData.value,
	 * plus invoke the valueChanged signal. This also enforces the readOnly flag, which
	 * can only be bypassed by passing in forced = true.
	 *
	 * @param value The new value of the property.
	 * @param forced If this property is read-only, setting this parameter to true will bypass the read-only rule.
	 */
	void set(const T& value, bool forced = false) 
	{ 
		if(data->readOnly && !forced)
			throw T_Exception(("Property " + data->name + " is read-only!").c_str());

		if(data->value != value)
		{
			T oldValue = data->value;
			data->value = value; 

			data->valueChanged.invoke(oldValue, value);
		}
	}

	/**
	 * Returns the real data of the PropertyData value
	 *
	 * @return Returns the real data of the PropertyData value.
	 */
	const T& get() const { return data->value; }

	/**
	 * Get the interface of this property.
	 * 
	 * @return Returns the property interface of this property.
	 */
	IProperty *getInterface() { return static_cast<IProperty*>(this); }

	/**
	 * Get the name of this property.
	 * 
	 * @return Returns the name of this property.
	 */
	virtual const T_String &getName() const { return data->name; }

	/**
	 * Check whether the PropertyData is valid.
	 *
	 * @return Returns true if data does not exist, false if it does.
	 */
	virtual bool isNull() const { return data == NULL_PTR; }

	/**
	 * Function that gives the outside access to the PropertyData's
	 * valueChanged signal. It's through this function call we can
	 * register slots to the valueChanged signal.
	 *
	 * @return Returns the valueChanged signal of this property's PropertyData.
	 */
	typename T_Signal_v2<const T&, const T&>::Type &valueChanged() { return data->valueChanged; }

	/// Set's property's data to rhs' shared pointer data.
	Property<T> operator= (const Property<T>& rhs);
	/// Set's property's data to rhs' value.
	Property<T> operator= (const T& rhs);

	/// Adds rhs' data value to property's data value
	Property<T> operator+= (const Property<T>& rhs);
	/// Adds rhs' value to property's data value
	Property<T> operator+= (const T& rhs);

	/// Subtracts rhs' data value from property's data value
	Property<T> operator-= (const Property<T>& rhs);
	/// Subtracts rhs' value from property's data value
	Property<T> operator-= (const T& rhs);

	/// Multiplies rhs' data value with property's data value
	Property<T> operator*= (const Property<T>& rhs);
	/// Multiplies rhs' value with property's data value
	Property<T> operator*= (const T& rhs);

	/// Check whether the shared pointer data of rhs is same as property's
	bool operator== (const Property<T>& rhs);
	/// Check whether the value of rhs equals that of property's data value
	bool operator== (const T& rhs);

	/// Check whether the shared pointer data of rhs is not the same as property's
	bool operator!= (const Property<T>& rhs);
	/// Check whether the value of rhs is not equals that of property's data value
	bool operator!= (const T& rhs);

	/// Check whether the data value of rhs is less than property's data value
	bool operator> (const Property<T>& rhs);
	/// Check whether the value of rhs is less than property's data value
	bool operator> (const T& rhs);

	/// Check whether the data value of rhs is greater than property's data value
	bool operator< (const Property<T>& rhs);
	/// Check whether the value of rhs is greater than property's data value
	bool operator< (const T& rhs);

	/// Instead of property.get() this operator exist for convenience.
	operator const T &() const { return data->value; }

private:
	/// PropertyData of the Property is stored inside a shared pointer.
	typename T_SharedPtr< PropertyData<T> >::Type data;
};

template<class T>
inline Property<T> Property<T>::operator =(const Property<T> &rhs)
{
	data = rhs.data;
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator =(const T &rhs)
{
	set(rhs);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator +=(const Property<T> &rhs)
{
	set(data->value + rhs.data->value);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator +=(const T &rhs)
{
	set(data->value + rhs);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator -=(const Property<T> &rhs)
{
	set(data->value - rhs.data->value);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator -=(const T &rhs)
{
	set(data->value - rhs);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator *=(const Property<T> &rhs)
{
	set(data->value * rhs.data->value);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator *=(const T &rhs)
{
	set(data->value * rhs);
	return *this;
}

template<class T>
inline bool Property<T>::operator ==(const Property<T> &rhs)
{
	return data == rhs.data;
}

template<class T>
inline bool Property<T>::operator ==(const T &rhs)
{
	return (data->value == rhs);
}

template<class T>
inline bool Property<T>::operator !=(const Property<T> &rhs)
{
	return data != rhs.data;
}

template<class T>
inline bool Property<T>::operator !=(const T &rhs)
{
	return (data->value != rhs);
}

template<class T>
inline bool Property<T>::operator >(const Property<T> &rhs)
{
	return (data->value > rhs.data->value);
}

template<class T>
inline bool Property<T>::operator >(const T &rhs)
{
	return (data->value > rhs);
}

template<class T>
inline bool Property<T>::operator <(const Property<T> &rhs)
{
	return (data->value < rhs.data->value);
}

template<class T>
inline bool Property<T>::operator <(const T &rhs)
{
	return (data->value < rhs);
}

/**
 * @file
 * @class PropertyListData
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property List Data implementation class
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
 * PropertyListData
 * 
 */

template<class T>
class PropertyListData HAS_SIGNALSLOTS_INHERITANCE_TYPE
{
public:
	/**
	 * Destructor
	 */
	~PropertyListData() {}
	/// Actual list data of the property list.
	typename T_Vector<T>::Type value;
	/// Name of the property list.
	T_String name;
	/// Is the property read-only?
	bool readOnly;
	/// Signal that's emitted when a value in the property list change, returning the index that was changed, plus the old and new value.
	typename T_Signal_v3<const U32&, const T&, const T&>::Type valueChanged;
	/// Signal that's emitted when a value is added to the property list, passing the new value with the signal along with the index.
	typename T_Signal_v2<const U32&, const T&>::Type valueAdded;
	/// Signal that's emitted when a value is erased from the property list, passing the erased value with the signal along with the index.
	typename T_Signal_v2<const U32&, const T&>::Type valueErased;
	/// Signal that's emitted when the values of the property list is cleared.
	typename T_Signal_v0<>::Type valuesCleared;
};

/**
 * @file
 * @class PropertyListValue
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property List Value, returned by list to allow changing an index in the list safely.
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
 * PropertyListValue
 * 
 */

template<class T>
class PropertyListValue
{
public:
	/**
	 * Constructor
	 */
	PropertyListValue(T &value, const U32 &index, typename T_Signal_v3<const U32 &, const T&, const T&>::Type &valueChanged)
		: value(value), index(index), valueChanged(valueChanged)
	{
	}

	/**
	 * Destructor
	 */
	~PropertyListValue() {}

	/**
	 * Returns the real value of the PropertyListValue
	 *
	 * @return Returns the real value of the PropertyListValue.
	 */
	const T &get() const { return value; }

	/// Set's property list value's data to rhs' shared pointer data.
	void operator= (const T& rhs);

	/// Provide an assignment operator to leviate level W4 warning
	PropertyListValue<T> &operator= (const PropertyListValue<T> &rhs);

	/// Instead of propertyListValue.get() this operator exist for convenience.
	operator const T &() const { return value; }

private:
	///
	T &value;
	///
	const U32 &index;
	///
	typename T_Signal_v3<const U32 &, const T&, const T&>::Type &valueChanged;
};

template<class T>
inline void PropertyListValue<T>::operator =(const T &rhs)
{
	T oldValue = value;
	value = rhs;
	valueChanged.invoke(index, oldValue, value);
}

template<class T>
inline PropertyListValue<T> &PropertyListValue<T>::operator= (const PropertyListValue<T> &rhs)
{
	if(this == &rhs)
		return *this;

	throw T_Exception("Assignment operation between property list values are not supported!");
}

/**
 * @file
 * @class PropertyList
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property List implementation class
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
 * PropertyList
 * 
 */

template<class T>
class PropertyList : public IPropertyList
{
public:
	/**
	 * Default Constructor, results in a PropertyList with no data!
	 */
	PropertyList()
	{
	}

	/**
	 * Copy Constructor
	 */
	PropertyList(const PropertyList& copy)
	: data(copy.data)
	{
	}

	/**
	 * Constructor
	 *
	 * @param name Name of the property list.
	 * @param readOnly Should the property list be read only? (Defaults to false).
	 */
	PropertyList(const T_String &name, bool readOnly = false)
	: data(new PropertyListData<T>())
	{	
		data->name = name;
		data->readOnly = readOnly;
	}

	/**
	 * Destructor
	 */
	virtual ~PropertyList() {}

	/**
	 * Push back a value to the property list. Handles pushing onto the actual PropertyData.value,
	 * plus invoke the valueAdded signal. This also enforces the readOnly flag, which
	 * can only be bypassed by passing in forced = true.
	 *
	 * @param value The new value to add to the property list.
	 * @param forced If this property list is read-only, setting this parameter to true will bypass the read-only rule.
	 * @param duplicationGuard Whether the PropertyList should make an effort to guard against duplicate entires, defaults to false.
	 */
	void push_back(const T& value, bool forced = false, bool duplicationGuard = false) 
	{ 
		if(data->readOnly && !forced)
			throw T_Exception(("PropertyList " + data->name + " is read-only!").c_str());

		if(duplicationGuard)
		{
			for(U32 i = 0; i < data->value.size(); i++)
			{
				if(value == data->value[i])
					return;
			}
		}

		data->value.push_back(value); 
		data->valueAdded.invoke((U32)data->value.size()-1, value);
	}

	/**
	 * Erase a value from the property list. Handles erasing from the actual PropertyData.value,
	 * plus invoke the valueErased signal. This also enforces the readOnly flag, which
	 * can only be bypassed by passing in forced = true.
	 *
	 * @param index The index to erase from the property list.
	 * @param forced If this property list is read-only, setting this parameter to true will bypass the read-only rule.
	 */
	void erase(const U32 &index, bool forced = false)
	{
		if(data->readOnly && !forced)
			throw T_Exception(("PropertyList " + data->name + " is read-only!").c_str());

		if(index >= data->value.size())
			return;

		T value = data->value[index];
		data->value.erase(data->value.begin()+index);
		data->valueErased.invoke(index, value);
	}

	/**
	 * Clear all values from the property list. Handles clearing all values from the actual PropertyData.value,
	 * plus invoke the valuesCleared signal. This also enforces the readOnly flag, which
	 * can only be bypassed by passing in forced = true.
	 *
	 * @param forced If this property list is read-only, setting this parameter to true will bypass the read-only rule.
	 */
	void clear(bool forced = false)
	{
		if(data->readOnly && !forced)
			throw T_Exception(("PropertyList " + data->name + " is read-only!").c_str());

		data->value.clear();
		data->valuesCleared.invoke();
	}

	/**
	 * Get the number of values in the property list.
	 *
	 * @return Returns the number of values in the property list.
	 */
	U32 size() const { return (U32)data->value.size(); }

	/**
	 * Check if the property list is empty.
	 *
	 * @return Returns true if list is empty, false if it has values.
	 */
	bool empty() const { return data->value.empty(); }

	/**
	 * Returns the real list data of the PropertyListData value
	 *
	 * @return Returns the real list data of the PropertyListData value.
	 */
	const typename T_Vector<T>::Type &get() const { return data->value; }

	/**
	 * Get the interface of this property list.
	 * 
	 * @return Returns the property list interface of this property list.
	 */
	IPropertyList *getInterface() { return static_cast<IPropertyList*>(this); }

	/**
	 * Get the name of this property list.
	 * 
	 * @return Returns the name of this property list.
	 */
	virtual const T_String &getName() const { return data->name; }

	/**
	 * Check whether the PropertyListData is valid.
	 *
	 * @return Returns true if data does not exist, false if it does.
	 */
	virtual bool isNull() const { return data == NULL_PTR; }

	/**
	 * Function that gives the outside access to the PropertyListData's
	 * valueChanged signal. It's through this function call we can
	 * register slots to the valueChanged signal.
	 *
	 * @return Returns the valueChanged signal of this property list's PropertyListData.
	 */
	typename T_Signal_v3<const U32&, const T&, const T&>::Type &valueChanged() { return data->valueChanged; }

	/**
	 * Function that gives the outside access to the PropertyListData's
	 * valueAdded signal. It's through this function call we can
	 * register slots to the valueAdded signal.
	 *
	 * @return Returns the valueAdded signal of this property list's PropertyListData.
	 */
	typename T_Signal_v2<const U32&, const T&>::Type &valueAdded() { return data->valueAdded; }

	/**
	 * Function that gives the outside access to the PropertyListData's
	 * valueErased signal. It's through this function call we can
	 * register slots to the valueErased signal.
	 *
	 * @return Returns the valueErased signal of this property list's PropertyListData.
	 */
	typename T_Signal_v2<const U32&, const T&>::Type &valueErased() { return data->valueErased; }

	/**
	 * Function that gives the outside access to the PropertyListData's
	 * valuesCleared signal. It's through this function call we can
	 * register slots to the valuesCleared signal.
	 *
	 * @return Returns the valueCleared signal of this property list's PropertyListData.
	 */
	typename T_Signal_v0<>::Type &valuesCleared() { return data->valuesCleared; }

	/// Set's property list's data to rhs' shared pointer data.
	PropertyList<T> operator= (const PropertyList<T>& rhs);

	/// Get the value of list at given index.
	PropertyListValue<T> operator[] (const U32& index);

	/// Instead of propertyList.get() this operator exist for convenience.
	operator const typename T_Vector<T>::Type &() const { return data->value; }

private:
	/// PropertyListData of the Property list is stored inside a shared pointer.
	typename T_SharedPtr< PropertyListData<T> >::Type data;
};

template<class T>
inline PropertyList<T> PropertyList<T>::operator =(const PropertyList<T> &rhs)
{
	data = rhs.data;
	return *this;
}

template<class T>
inline PropertyListValue<T> PropertyList<T>::operator [](const U32 &index)
{
	if(index >= data->value.size())
		throw T_Exception(("Index was out of bounds for property list " + data->name).c_str());

	return PropertyListValue<T>(data->value[index], index, data->valueChanged);
}
