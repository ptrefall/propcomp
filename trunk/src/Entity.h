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
#include "Property.h"

class Component;
class ComponentFactory;

class Entity
{
public:
	Entity(ComponentFactory& componentFactory, const T_EntityId &id, const T_String &type, const T_String &name = T_String());
	virtual ~Entity();

	const T_EntityId &getId() const { return id_property.get(); }
	const T_String &getType() const { return type_property.get(); }
	const T_String &getName() const { return name_property.get(); }

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
	template<class T>Property<T> addProperty(const T_String& propName, const T &defaultValue, bool readOnly = false);
	void addProperty(IProperty *property);

	template<class T>Property<T> getProperty(const T_String& propName);
	IProperty *getIProperty(const T_String& propName);

	void removeProperty(const T_String& propName, bool postponeDelete = false);
	void removeAllProperties();
	void clearDeletedProperties();

	T_Map<T_String, IProperty*>::Type &getProperties() { return properties; }
	//-----------------------------------------------

	//------------------------------------------------
	//PropertyList Container specific logic
	bool hasPropertyList(const T_String& propListName);
	template<class T>PropertyList<T> addPropertyList(const T_String& propListName, bool readOnly = false);
	void addPropertyList(IPropertyList *propertyList);

	template<class T>PropertyList<T> getPropertyList(const T_String& propListName);
	IPropertyList *getIPropertyList(const T_String& propListName);

	void removePropertyList(const T_String& propListName, bool postponeDelete = false);
	void removeAllPropertyLists();
	void clearDeletedPropertyLists();

	T_Map<T_String, IPropertyList*>::Type &getPropertyLists() { return propertyLists; }
	//-----------------------------------------------

	void updateComponents(F32 deltaTime);
	void updateProperties(F32 deltaTime);
	void updatePropertyLists(F32 deltaTime);
	void onEvent(const T_Event &event);

protected:
	T_Vector<Component*>::Type components;
	T_Map<T_String, IProperty*>::Type properties;
	T_Vector<IProperty*>::Type deletedProperties;
	T_Map<T_String, IPropertyList*>::Type propertyLists;
	T_Vector<IPropertyList*>::Type deletedPropertyLists;

	ComponentFactory& componentFactory;
	Property<T_String> type_property, name_property;
	Property<T_EntityId> id_property;
};

//------------------------------------------------------

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
inline Property<T> Entity::addProperty(const T_String& propName, const T &defaultValue, bool readOnly)
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

	Property<T> *property = new Property<T>(propName, readOnly);
	property->set(defaultValue, true);
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

//----------------------------------------------

inline bool Entity::hasPropertyList(const T_String& propListName)
{
	if(propertyLists.empty())
		return false;

	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(propListName);
	if(it != propertyLists.end())
		return true;
	else
		return false;
}

inline void Entity::addPropertyList(IPropertyList *propertyList)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(propertyList->getName());
	if(it == propertyLists.end())
		propertyLists[propertyList->getName()] = propertyList;
}

template<class T>
inline PropertyList<T> Entity::addPropertyList(const T_String& propListName, bool readOnly)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(propListName);
	if(it != propertyLists.end())
	{
		PropertyList<T>* propertyList;
#ifdef _DEBUG
		propertyList = dynamic_cast< PropertyList<T>* >(it->second);
		if(!propertyList)
			throw T_Exception(("PropertyList " + propListName + " already exists, but with another type!").c_str());
#else
		propertyList = static_cast< PropertyList<T>* >(it->second);
#endif
		return *propertyList;
	}

	PropertyList<T> *propertyList = new PropertyList<T>(propListName, readOnly);
	propertyLists[propertyList->getName()] = propertyList;

	//return *propertyList;
	return getPropertyList<T>(propListName);
}

template<class T>
inline PropertyList<T> Entity::getPropertyList(const T_String& propListName)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(propListName);
	if(it != propertyLists.end())
	{
		PropertyList<T>* propertyList;
#ifdef _DEBUG
		propertyList = dynamic_cast< PropertyList<T>* >(it->second);
		if(!propertyList)
			throw T_Exception(("Tried to get property list " + propListName + ", but the type was wrong!").c_str());
#else
		propertyList = static_cast< PropertyList<T>* >(it->second);
#endif
		return *propertyList;
	}
	else
		throw T_Exception(("Unable to get property list " + propListName).c_str());
}

inline IPropertyList *Entity::getIPropertyList(const T_String& propListName)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(propListName);
	if(it != propertyLists.end())
		return it->second;
	else
		throw T_Exception(("Unable to get property list " + propListName).c_str());
}

inline void Entity::removePropertyList(const T_String& propListName, bool postponeDelete)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(propListName);
	if(it != propertyLists.end())
	{
		IPropertyList* propertyList = (*it).second;
		if(postponeDelete)
			deletedPropertyLists.push_back(propertyList);
		else
			delete propertyList;
		propertyLists.erase(it);
	}
}

inline void Entity::removeAllPropertyLists()
{
	T_Map<T_String, IPropertyList*>::Type::iterator it;
	for(it = propertyLists.begin(); it != propertyLists.end(); ++it)
	{
		IPropertyList* propertyList = (*it).second;
		delete propertyList;
	}
	propertyLists.clear();
	clearDeletedPropertyLists();
}

inline void Entity::updatePropertyLists(F32 deltaTime)
{
	clearDeletedPropertyLists();
}

inline void Entity::clearDeletedPropertyLists()
{
	for(unsigned int i = 0; i < deletedPropertyLists.size(); i++)
		delete deletedPropertyLists[i];
	deletedPropertyLists.clear();
}
