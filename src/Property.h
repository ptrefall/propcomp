/*Component-based Entity Engine
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

Note: Some of the libraries Component-based Entity Engine may link to may have additional
requirements or restrictions.
*/

#pragma once

#include "types_config.h"

#include "IProperty.h"

template<class T>
class PropertyData HAS_SIGNALSLOTS_INHERITANCE_TYPE
{
public:
	~PropertyData() {}
	T value;
	T_String name;
	typename T_Signal_v2<const T&, const T&>::Type valueChanged;
};

template<class T>
class Property : public IProperty
{
public:
	Property()
	{
	}

	Property(const Property& copy)
	: data(copy.data)
	{
	}

	Property(const T_String &name)
	: data(new PropertyData<T>())
	{	
		data->name = name; 
	}

	virtual ~Property() {}

	void set(const T& value) 
	{ 
		if(data->value != value)
		{
			T oldValue = data->value;
			data->value = value; 

			data->valueChanged.emit(oldValue, value);
		}
	}
	const T& get() const { return data->value; }

	IProperty *getInterface() { return static_cast<IProperty*>(this); }

	virtual const T_String &getName() const { return data->name; }

	virtual bool isNull() const { return data == NULL_PTR; }

	typename T_Signal_v2<const T&, const T&>::Type &valueChanged() { return data->valueChanged; }

	Property<T> operator= (const Property<T>& rhs);
	Property<T> operator= (const T& rhs);

	Property<T> operator+= (const Property<T>& rhs);
	Property<T> operator+= (const T& rhs);

	Property<T> operator-= (const Property<T>& rhs);
	Property<T> operator-= (const T& rhs);

	Property<T> operator*= (const Property<T>& rhs);
	Property<T> operator*= (const T& rhs);

	bool operator== (const Property<T>& rhs);
	bool operator== (const T& rhs);

	bool operator!= (const Property<T>& rhs);
	bool operator!= (const T& rhs);

	bool operator> (const Property<T>& rhs);
	bool operator> (const T& rhs);

	bool operator< (const Property<T>& rhs);
	bool operator< (const T& rhs);

	operator T() const { return data->value; }

private:
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
	typename T_Signal_v1<const T&>::Type valueAdded;
	typename T_Signal_v0<>::Type valueCleared;
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

	PropertyList(const T_String &name)
	: data(new PropertyListData<T>())
	{	
		data->name = name; 
	}

	virtual ~PropertyList() {}

	void add(const T& value, bool duplicationGuard = false) 
	{ 
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

	virtual void erase(U32 index, bool deleteData = false)
	{
		if(index >= data->value.size())
			return;

		if(deleteData)
			delete data->value[index];

		data->value.erase(data->value.begin()+index);
	}

	virtual void clear(bool deleteData = false)
	{
		if(deleteData)
		{
			for(U32 i = 0; i < data->value.size(); i++)
				delete data->value[i];
		}
		data->value.clear();
		data->valueCleared.emit();
	}

	virtual U32 size() const { return (U32)data->value.size(); }

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
