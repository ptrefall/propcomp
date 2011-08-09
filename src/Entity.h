#pragma once

/**
 * @file
 * @class Entity
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Entity base class
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
 * The entity holds the means of containing components and properties and represents an object
 * in "the world", whether it's visible or purely functional. Only it's components restricts it's
 * functionality.
 * 
 */

#include "types_config.h"
#include "EventHandler.h"
#include "Property.h"

class Component;
class ComponentFactory;

class Entity : public EventHandler
{
public:
	/**
	 * Constructor
	 *
	 * @param componentFactory The componentFactory instance from which this entity will instanciate components.
	 * @param id The unique id of this entity instance, whos type and creation is specified by the engine implementation.
	 * @param type The type string associated with this entity instance.
	 */
	Entity(ComponentFactory& componentFactory, const T_EntityId &id, const T_String &type);
	/**
	 * Destructor
	 */
	virtual ~Entity();

	/**
	 * Get the unique id of this entity instance.
	 *
	 * @return Returns the unique id of this entity instance.
	 */
	const T_EntityId &getId() const { return id_property.get(); }
	
	/**
	 * Get the type that defines this entity instance.
	 *
	 * @return Returns the type of the entity instance.
	 */
	const T_String &getType() const { return type_property.get(); }

	//--------------------------------------------------------------

	/**
	 * Add a component of specified type to this entity.
	 *
	 * @param type The type of the component.
	 * @return Returns a reference to the component that was added to the entity.
	 */
	Component &addComponent(const T_String& type);

	/**
	 * Add a component of specified type to this entity with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @return Returns a reference to the component that was added to the entity.
	 */
	template<class T>
	Component &addComponent(const T_String& type, T &custom1);

	/**
	 * Add a component of specified type to this entity with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @return Returns a reference to the component that was added to the entity.
	 */
	template<class T, class U>
	Component &addComponent(const T_String& type, T &custom1, U &custom2);

	/**
	 * Add a component of specified type to this entity with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @param custom3 The custom parameter of type V
	 * @return Returns a reference to the component that was added to the entity.
	 */
	template<class T, class U, class V>
	Component &addComponent(const T_String& type, T &custom1, U &custom2, V &custom3);

	/**
	 * Add a component of specified type to this entity with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @param custom3 The custom parameter of type V
	 * @param custom4 The custom parameter of type W
	 * @return Returns a reference to the component that was added to the entity.
	 */
	template<class T, class U, class V, class W>
	Component &addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4);

	/**
	 * Add a component of specified type to this entity with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @param custom3 The custom parameter of type V
	 * @param custom4 The custom parameter of type W
	 * @param custom5 The custom parameter of type X
	 * @return Returns a reference to the component that was added to the entity.
	 */
	template<class T, class U, class V, class W, class X>
	Component &addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4, X &custom5);

	/**
	 * Add a component of specified type to this entity with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @param custom3 The custom parameter of type V
	 * @param custom4 The custom parameter of type W
	 * @param custom5 The custom parameter of type X
	 * @param custom6 The custom parameter of type Y
	 * @return Returns a reference to the component that was added to the entity.
	 */
	template<class T, class U, class V, class W, class X, class Y>
	Component &addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4, X &custom5, Y &custom6);

	/**
	 * Add a component of specified type to this entity with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @param custom3 The custom parameter of type V
	 * @param custom4 The custom parameter of type W
	 * @param custom5 The custom parameter of type X
	 * @param custom6 The custom parameter of type Y
	 * @param custom7 The custom parameter of type Z
	 * @return Returns a reference to the component that was added to the entity.
	 */
	template<class T, class U, class V, class W, class X, class Y, class Z>
	Component &addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4, X &custom5, Y &custom6, Z &custom7);

	/**
	 * Add a component of specified type to this entity with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @param custom3 The custom parameter of type V
	 * @param custom4 The custom parameter of type W
	 * @param custom5 The custom parameter of type X
	 * @param custom6 The custom parameter of type Y
	 * @param custom7 The custom parameter of type Z
	 * @param custom8 The custom parameter of type S
	 * @return Returns a reference to the component that was added to the entity.
	 */
	template<class T, class U, class V, class W, class X, class Y, class Z, class S>
	Component &addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4, X &custom5, Y &custom6, Z &custom7, S &custom8);

	//--------------------------------------------------------------
	
	/**
	 * Check whether the specified component type exist in this entity.
	 *
	 * @param type The type of the component.
	 * @return Returns true if the component exist in this entity, false if it doesn't.
	 */
	bool hasComponent(const T_String& type);

	/**
	 * Get a reference to a component of specified type from the entity.
	 *
	 * @param type The type of the component.
	 * @return Returns a reference to the component.
	 */
	Component &getComponent(const T_String& type);

	/**
	 * Get a reference to the entire list of components owned by the entity.
	 *
	 * @return Returns a reference to the entity's component list.
	 */
	T_Vector<Component*>::Type &getComponents() { return components; }
	
	//--------------------------------------------------------------

	/**
	 * Check whether the specified property name exist in this entity.
	 * This function works on the interface (IProperty) of the property,
	 * thus no type-casting is involved in it's usage.
	 *
	 * @param name The name of the property.
	 * @return Returns true if the property exist in this entity, false if it doesn't.
	 */
	bool hasProperty(const T_String& name);

	/**
	 * Add a property of specified type T and name to this entity with a default value.
	 * If readOnly is specified to true, one can only change the property by
	 * directly calling property.set(value, forced=true), all other pipes, like
	 * via operators, will throw an exception.
	 *
	 * @param name The name of the property used to store and associate the property in the entity.
	 * @param defaultValue The initial value this property should be set to when added to the entity.
	 * @param readOnly Flag this property as read-only if it should only be read. Defaults to false.
	 * @return Returns a shared_ptr (pimpl) reference to the property that was added to the entity.
	 */
	template<class T>Property<T> addProperty(const T_String& name, const T &defaultValue, bool readOnly = false);

	/**
	 * Add a property interface to this entity.
	 * There can be situations where this is required.
	 *
	 * @param property The interface of the property.
	 */
	void addProperty(IProperty *property);

	/**
	 * Get a shared_ptr (pimpl) reference to a property of specified name from the entity.
	 *
	 * @param name The name of the property.
	 * @return Returns a shared_ptr (pimpl) reference to the property.
	 */
	template<class T>Property<T> getProperty(const T_String& name);

	/**
	 * Get a property interface pointer to a property of specified name from the entity.
	 *
	 * @param name  The name of the property.
	 * @return The interface pointer to the property.
	 */
	IProperty *getIProperty(const T_String& name);

	/**
	 * Remove the property of specified name from entity with
	 * option to postpone deletion until the next time update
	 * is called on the entity.
	 *
	 * @param name The name of the property.
	 * @param postponeDelete Flag whether to postpone the deletion of this property (if true), or delete it immediately (if false). Defaults to false.
	 */
	void removeProperty(const T_String& name, bool postponeDelete = false);

	/**
	 * Remove all properties from entity.
	 *
	 */
	void removeAllProperties();

	/**
	 * Delete all properties that was deleted last time update was called
	 * and marked postponeDelete.
	 *
	 */
	void clearDeletedProperties();

	/**
	 * Get a reference to the entire map of properties owned by the entity.
	 *
	 * @return Returns a reference to the entity's property map.
	 */
	T_Map<T_String, IProperty*>::Type &getProperties() { return properties; }

	//--------------------------------------------------------------

	/**
	 * Check whether the specified property list name exist in this entity.
	 * This function works on the interface (IPropertyList) of the property list,
	 * thus no type-casting is involved in it's usage.
	 *
	 * @param name The name of the property list.
	 * @return Returns true if the property list exist in this entity, false if it doesn't.
	 */
	bool hasPropertyList(const T_String& name);

	/**
	 * Add a property list of specified type T and name to this entity.
	 * If readOnly is specified to true, one can only change the property list by
	 * directly calling propertyList.add(value, forced=true), all other pipes, like
	 * via operators, will throw an exception.
	 *
	 * @param name The name of the property list used to store and associate the property list in the entity.
	 * @param readOnly Flag this property list as read-only if it should only be read. Defaults to false.
	 * @return Returns a shared_ptr (pimpl) reference to the property list that was added to the entity.
	 */
	template<class T>PropertyList<T> addPropertyList(const T_String& name, bool readOnly = false);

	/**
	 * Add a property list interface to this entity.
	 * There can be situations where this is required.
	 *
	 * @param propertyList The interface of the property list.
	 */
	void addPropertyList(IPropertyList *propertyList);

	/**
	 * Get a shared_ptr (pimpl) reference to a property list of specified name from the entity.
	 *
	 * @param name The name of the property list.
	 * @return Returns a shared_ptr (pimpl) reference to the property list.
	 */
	template<class T>PropertyList<T> getPropertyList(const T_String& name);

	/**
	 * Get a property list interface pointer to a property list of specified name from the entity.
	 *
	 * @param name  The name of the property list.
	 * @return The interface pointer to the property list.
	 */
	IPropertyList *getIPropertyList(const T_String& name);

	/**
	 * Remove the property list of specified name from entity with
	 * option to postpone deletion until the next time update
	 * is called on the entity.
	 *
	 * @param name The name of the property list.
	 * @param postponeDelete Flag whether to postpone the deletion of this property list (if true), or delete it immediately (if false). Defaults to false.
	 */
	void removePropertyList(const T_String& name, bool postponeDelete = false);

	/**
	 * Remove all property lists from entity.
	 *
	 */
	void removeAllPropertyLists();

	/**
	 * Delete all property lists that was deleted last time update was called
	 * and marked postponeDelete.
	 *
	 */
	void clearDeletedPropertyLists();

	/**
	 * Get a reference to the entire map of property lists owned by the entity.
	 *
	 * @return Returns a reference to the entity's property list map.
	 */
	T_Map<T_String, IPropertyList*>::Type &getPropertyLists() { return propertyLists; }
	
	//--------------------------------------------------------------

	/**
	 * Call update function on all the components owned by this entity.
	 *
	 * @param deltaTime  Should be the time elapsed since update was called last time.
	 */
	void updateComponents(F32 deltaTime);
	
	/**
	 * Handles deletion of all properties pending for deletion in this entity.
	 *
	 * @param deltaTime  Should be the time elapsed since update was called last time.
	 */
	void updateProperties(F32 deltaTime);

	/**
	 * Handles deletion of all property lists pending for deletion in this entity.
	 *
	 * @param deltaTime  Should be the time elapsed since update was called last time.
	 */
	void updatePropertyLists(F32 deltaTime);

	//--------------------------------------------------------------

protected:
	/// The list of all components owned by this entity.
	T_Vector<Component*>::Type components;
	/// The map of all properties owned by this entity.
	T_Map<T_String, IProperty*>::Type properties;
	/// The list of all properties pending deletion in this entity.
	T_Vector<IProperty*>::Type deletedProperties;
	/// The map of all property lists owned by this entity.
	T_Map<T_String, IPropertyList*>::Type propertyLists;
	/// The list of all property lists pending deletion in this entity.
	T_Vector<IPropertyList*>::Type deletedPropertyLists;

	//--------------------------------------------------------------

	/// Reference to the component factory responsible for instancing components for this entity.
	ComponentFactory& componentFactory;
	/// Type property (read-only), holds the type string given in entity's constructor.
	Property<T_String> type_property;
	/// Id property (read-only), holds the id T_EntityId given in the entity's constructor.
	Property<T_EntityId> id_property;
};

//------------------------------------------------------

template<class T>
inline Component &Entity::addComponent(const T_String& type, T &custom1)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component &component = *components[i];
		if(component.getType() == type)
			return component;
	}

	T_Any any = &custom1;
	Component* component = componentFactory.createComponentCustom1(*this, type, any);
	components.push_back(component);
	return *component;
}

template<class T, class U>
inline Component &Entity::addComponent(const T_String& type, T &custom1, U &custom2)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component &component = *components[i];
		if(component.getType() == type)
			return component;
	}

	T_Any any = &custom1;
	T_Any any2 = &custom2;
	Component* component = componentFactory.createComponentCustom2(*this, type, any, any2);
	components.push_back(component);
	return *component;
}

template<class T, class U, class V>
inline Component &Entity::addComponent(const T_String& type, T &custom1, U &custom2, V &custom3)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component &component = *components[i];
		if(component.getType() == type)
			return component;
	}

	T_Any any = &custom1;
	T_Any any2 = &custom2;
	T_Any any3 = &custom3;
	Component* component = componentFactory.createComponentCustom3(*this, type, any, any2, any3);
	components.push_back(component);
	return *component;
}

template<class T, class U, class V, class W>
inline Component &Entity::addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component &component = *components[i];
		if(component.getType() == type)
			return component;
	}

	T_Any any = &custom1;
	T_Any any2 = &custom2;
	T_Any any3 = &custom3;
	T_Any any4 = &custom4;
	Component* component = componentFactory.createComponentCustom4(*this, type, any, any2, any3, any4);
	components.push_back(component);
	return *component;
}

template<class T, class U, class V, class W, class X>
inline Component &Entity::addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4, X &custom5)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component &component = *components[i];
		if(component.getType() == type)
			return component;
	}

	T_Any any = &custom1;
	T_Any any2 = &custom2;
	T_Any any3 = &custom3;
	T_Any any4 = &custom4;
	T_Any any5 = &custom5;
	Component* component = componentFactory.createComponentCustom5(*this, type, any, any2, any3, any4, any5);
	components.push_back(component);
	return *component;
}

template<class T, class U, class V, class W, class X, class Y>
inline Component &Entity::addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4, X &custom5, Y &custom6)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component &component = *components[i];
		if(component.getType() == type)
			return component;
	}

	T_Any any = &custom1;
	T_Any any2 = &custom2;
	T_Any any3 = &custom3;
	T_Any any4 = &custom4;
	T_Any any5 = &custom5;
	T_Any any6 = &custom6;
	Component* component = componentFactory.createComponentCustom6(*this, type, any, any2, any3, any4, any5, any6);
	components.push_back(component);
	return *component;
}

template<class T, class U, class V, class W, class X, class Y, class Z>
inline Component &Entity::addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4, X &custom5, Y &custom6, Z &custom7)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component &component = *components[i];
		if(component.getType() == type)
			return component;
	}

	T_Any any = &custom1;
	T_Any any2 = &custom2;
	T_Any any3 = &custom3;
	T_Any any4 = &custom4;
	T_Any any5 = &custom5;
	T_Any any6 = &custom6;
	T_Any any7 = &custom7;
	Component* component = componentFactory.createComponentCustom7(*this, type, any, any2, any3, any4, any5, any6, any7);
	components.push_back(component);
	return *component;
}

template<class T, class U, class V, class W, class X, class Y, class Z, class S>
inline Component &Entity::addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4, X &custom5, Y &custom6, Z &custom7, S &custom8)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component &component = *components[i];
		if(component.getType() == type)
			return component;
	}

	T_Any any = &custom1;
	T_Any any2 = &custom2;
	T_Any any3 = &custom3;
	T_Any any4 = &custom4;
	T_Any any5 = &custom5;
	T_Any any6 = &custom6;
	T_Any any7 = &custom7;
	T_Any any8 = &custom8;
	Component* component = componentFactory.createComponentCustom8(*this, type, any, any2, any3, any4, any5, any6, any7, any8);
	components.push_back(component);
	return *component;
}

//------------------------------------------------------

inline bool Entity::hasProperty(const T_String& name)
{
	if(properties.empty())
		return false;

	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(name);
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
inline Property<T> Entity::addProperty(const T_String& name, const T &defaultValue, bool readOnly)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(name);
	if(it != properties.end())
	{
		Property<T>* property;
#ifdef _DEBUG
		property = dynamic_cast< Property<T>* >(it->second);
		if(!property)
			throw T_Exception(("Property " + name + " already exists, but with another type!").c_str());
#else
		property = static_cast< Property<T>* >(it->second);
#endif
		return *property;
	}

	Property<T> *property = new Property<T>(name, readOnly);
	property->set(defaultValue, true);
	properties[property->getName()] = property;

	//return *property;
	return getProperty<T>(name);
}

template<class T>
inline Property<T> Entity::getProperty(const T_String& name)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(name);
	if(it != properties.end())
	{
		Property<T>* property;
#ifdef _DEBUG
		property = dynamic_cast< Property<T>* >(it->second);
		if(!property)
			throw T_Exception(("Tried to get property " + name + ", but the type was wrong!").c_str());
#else
		property = static_cast< Property<T>* >(it->second);
#endif
		return *property;
	}
	else
		throw T_Exception(("Unable to get property " + name).c_str());
}

inline IProperty *Entity::getIProperty(const T_String& name)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(name);
	if(it != properties.end())
		return it->second;
	else
		throw T_Exception(("Unable to get property " + name).c_str());
}

inline void Entity::removeProperty(const T_String& name, bool postponeDelete)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(name);
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

inline bool Entity::hasPropertyList(const T_String& name)
{
	if(propertyLists.empty())
		return false;

	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(name);
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
inline PropertyList<T> Entity::addPropertyList(const T_String& name, bool readOnly)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(name);
	if(it != propertyLists.end())
	{
		PropertyList<T>* propertyList;
#ifdef _DEBUG
		propertyList = dynamic_cast< PropertyList<T>* >(it->second);
		if(!propertyList)
			throw T_Exception(("PropertyList " + name + " already exists, but with another type!").c_str());
#else
		propertyList = static_cast< PropertyList<T>* >(it->second);
#endif
		return *propertyList;
	}

	PropertyList<T> *propertyList = new PropertyList<T>(name, readOnly);
	propertyLists[propertyList->getName()] = propertyList;

	//return *propertyList;
	return getPropertyList<T>(name);
}

template<class T>
inline PropertyList<T> Entity::getPropertyList(const T_String& name)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(name);
	if(it != propertyLists.end())
	{
		PropertyList<T>* propertyList;
#ifdef _DEBUG
		propertyList = dynamic_cast< PropertyList<T>* >(it->second);
		if(!propertyList)
			throw T_Exception(("Tried to get property list " + name + ", but the type was wrong!").c_str());
#else
		propertyList = static_cast< PropertyList<T>* >(it->second);
#endif
		return *propertyList;
	}
	else
		throw T_Exception(("Unable to get property list " + name).c_str());
}

inline IPropertyList *Entity::getIPropertyList(const T_String& name)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(name);
	if(it != propertyLists.end())
		return it->second;
	else
		throw T_Exception(("Unable to get property list " + name).c_str());
}

inline void Entity::removePropertyList(const T_String& name, bool postponeDelete)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(name);
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
