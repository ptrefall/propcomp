/*Component-based Entity Engine
Copyright (c) 2009 P�l Trefall and Kenneth Gangst�

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
#include "Property.h"

class Component;
class ComponentFactory;

class Entity
{
public:
	Entity(ComponentFactory& componentFactory, const T_String &type, const T_String &name = T_String());
	virtual ~Entity();

	const T_String &getType() const { return type; }
	const T_String &getName() const { return name; }

	//-----------------------------------------------
	//Component Container specific logic
	Component &addComponent(const T_String& componentType, const T_String& componentName = T_String());
	bool hasComponent(const T_String& componentName);
	Component &getComponent(const T_String& componentName);
	T_Vector<Component*>::Type &getComponents() { return components; }
	//-----------------------------------------------

	//------------------------------------------------
	//Property Container specific logic
	bool hasProperty(const T_String& propName);
	template<class T>Property<T> addProperty(const T_String& propName, const T &defaultValue);
	void addProperty(IProperty *property);

	template<class T>Property<T> getProperty(const T_String& propName);
	IProperty *getIProperty(const T_String& propName);

	void removeProperty(const T_String& propName, bool postponeDelete = false);
	void removeAllProperties();
	void clearDeletedProperties();

	T_Map<T_String, IProperty*>::Type &getProperties() { return properties; }
	//-----------------------------------------------

	void updateComponents(F32 deltaTime);
	void updateProperties(F32 deltaTime);
	void onEvent(const T_Event &event);

protected:
	T_Vector<Component*>::Type components;
	T_Map<T_String, IProperty*>::Type properties;
	T_Vector<IProperty*>::Type deletedProperties;

	ComponentFactory& componentFactory;
	T_String type, name;
};

inline bool Entity::hasProperty(const T_String& propName)
{
	if(properties.empty())
		return false;

	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(propName);
	if(it != properties.end())
		return true;
	else
		return false;
}

inline void Entity::addProperty(IProperty *property)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(property->getName());
	if(it == properties.end())
		properties[property->getName()] = property;
}

template<class T>
inline Property<T> Entity::addProperty(const T_String& propName, const T &defaultValue)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(propName);
	if(it != properties.end())
	{
		Property<T>* property;
#ifdef _DEBUG
		property = dynamic_cast< Property<T>* >(it->second);
		if(!property)
			throw T_Exception(("Property " + propName + " already exists, but with another type!").c_str());
#else
		property = static_cast< Property<T>* >(it->second);
#endif
		return *property;
	}

	Property<T> *property = new Property<T>(propName);
	property->set(defaultValue);
	properties[property->getName()] = property;

	//return *property;
	return getProperty<T>(propName);
}

template<class T>
inline Property<T> Entity::getProperty(const T_String& propName)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(propName);
	if(it != properties.end())
	{
		Property<T>* property;
#ifdef _DEBUG
		property = dynamic_cast< Property<T>* >(it->second);
		if(!property)
			throw T_Exception(("Tried to get property " + propName + ", but the type was wrong!").c_str());
#else
		property = static_cast< Property<T>* >(it->second);
#endif
		return *property;
	}
	else
		throw T_Exception(("Unable to get property " + propName).c_str());
}

inline IProperty *Entity::getIProperty(const T_String& propName)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(propName);
	if(it != properties.end())
		return it->second;
	else
		throw T_Exception(("Unable to get property " + propName).c_str());
}

inline void Entity::removeProperty(const T_String& propName, bool postponeDelete)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(propName);
	if(it != properties.end())
	{
		IProperty* property = (*it).second;
		if(postponeDelete)
			deletedProperties.push_back(property);
		else
			delete property;
		properties.erase(it);
	}
}

inline void Entity::removeAllProperties()
{
	T_Map<T_String, IProperty*>::Type::iterator it;
	for(it = properties.begin(); it != properties.end(); ++it)
	{
		IProperty* property = (*it).second;
		delete property;
	}
	properties.clear();
	clearDeletedProperties();
}

inline void Entity::updateProperties(F32 deltaTime)
{
	clearDeletedProperties();
}

inline void Entity::clearDeletedProperties()
{
	for(unsigned int i = 0; i < deletedProperties.size(); i++)
		delete deletedProperties[i];
	deletedProperties.clear();
}