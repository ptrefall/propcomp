#pragma once

/**
 * @file
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
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
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 
 * Note: Some of the libraries Component-based Entity Engine may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * Property, PropertyData, PropertyList and PropertyListData
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
	 * plus emit the valueChanged signal. This also enforces the readOnly flag, which
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

			data->valueChanged.emit(oldValue, value);
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
	 * @return Returns true if data does not exist, true if it does.
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

	///
	Property<T> operator= (const Property<T>& rhs);
	///
	Property<T> operator= (const T& rhs);

	///
	Property<T> operator+= (const Property<T>& rhs);
	///
	Property<T> operator+= (const T& rhs);

	///
	Property<T> operator-= (const Property<T>& rhs);
	///
	Property<T> operator-= (const T& rhs);

	///
	Property<T> operator*= (const Property<T>& rhs);
	///
	Property<T> operator*= (const T& rhs);

	///
	bool operator== (const Property<T>& rhs);
	///
	bool operator== (const T& rhs);

	///
	bool operator!= (const Property<T>& rhs);
	///
	bool operator!= (const T& rhs);

	///
	bool operator> (const Property<T>& rhs);
	///
	bool operator> (const T& rhs);

	///
	bool operator< (const Property<T>& rhs);
	///
	bool operator< (const T& rhs);

	/// Instead of property.get() one can also use the property() operator to get the real PropertyData value.
	operator T() const { return data->value; }

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

template<class T>
class PropertyListData HAS_SIGNALSLOTS_INHERITANCE_TYPE
{
public:
	~PropertyListData() {}
	typename T_Vector<T>::Type value;
	T_String name;
	bool readOnly;
	typename T_Signal_v1<const T&>::Type valueAdded;
	typename T_Signal_v0<>::Type valueErased;
	typename T_Signal_v0<>::Type valuesCleared;
};

template<class T>
class PropertyList : public IPropertyList
{
public:
	PropertyList()
	{
	}

	PropertyList(const PropertyList& copy)
	: data(copy.data)
	{
	}

	PropertyList(const T_String &name, bool readOnly = false)
	: data(new PropertyListData<T>())
	{	
		data->name = name;
		data->readOnly = readOnly;
	}

	virtual ~PropertyList() {}

	void add(const T& value, bool forced = false, bool duplicationGuard = false) 
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
		data->valueAdded.emit(value);
	}

	void erase(U32 index, bool deleteData = false, bool forced = false)
	{
		if(data->readOnly && !forced)
			throw T_Exception(("PropertyList " + data->name + " is read-only!").c_str());

		if(index >= data->value.size())
			return;

		if(deleteData)
			delete data->value[index];

		data->value.erase(data->value.begin()+index);
		data->valueErased.emit();
	}

	void clear(bool deleteData = false, bool forced = false)
	{
		if(data->readOnly && !forced)
			throw T_Exception(("PropertyList " + data->name + " is read-only!").c_str());

		if(deleteData)
		{
			//for(U32 i = 0; i < data->value.size(); i++)
			//	delete data->value[i];
		}
		data->value.clear();
		data->valuesCleared.emit();
	}

	U32 size() const { return (U32)data->value.size(); }

	bool empty() const { return data->value.empty(); }

	const typename T_Vector<T>::Type &get() const { return data->value; }

	IPropertyList *getInterface() { return static_cast<IPropertyList*>(this); }

	virtual const T_String &getName() const { return data->name; }

	virtual bool isNull() const { return data == NULL_PTR; }

	typename T_Signal_v1<const T&>::Type &valueAdded() { return data->valueAdded; }

	typename T_Signal_v0<>::Type &valueCleared() { return data->valueCleared; }

	operator typename T_Vector<T>::Type() const { return data->value; }

private:
	typename T_SharedPtr< PropertyListData<T> >::Type data;
};
