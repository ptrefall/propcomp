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
 * The entity holds the means of containing components and properties and represents an object
 * in "the world", whether it's visible or purely functional. Only it's components restricts it's
 * functionality.
 * 
 */

#include "types_config.h"
#include "Property.h"

class Component;
class ComponentFactory;

class Entity
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

	/**
	 * Calls all slots registered to the argument-less event signal of type.
	 *
	 * @param type The type name of the event.
	 */
	void onEvent0(const T_StringId &type);

	/**
	 * Calls all slots registered to the event signal of type holding one argument.
	 *
	 * @param type The type name of the event.
	 * @param arg0 First argument of type T.
	 */
	template<class T> void onEvent1(const T_StringId &type, const T &arg0);

	/**
	 * Calls all slots registered to the event signal of type holding two arguments.
	 *
	 * @param type The type name of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 */
	template<class T, class U> void onEvent2(const T_StringId &type, const T &arg0, const U &arg1);

	/**
	 * Register a slot to the event signal of type holding two arguments.
	 *
	 * @param type The type name of the event.
	 * @return A signal that requires no arguments in the slot.
	 */
	T_Signal_v0<>::Type &registerToEvent0(const T_StringId &type);

	/**
	 * Register a slot to the event signal of type holding two arguments.
	 *
	 * @param type The type name of the event.
	 * @return A signal that requires one arguments in the slot.
	 */
	template<class T>typename T_Signal_v1<const T&>::Type &registerToEvent1(const T_StringId &type);

	/**
	 * Register a slot to the event signal of type holding two arguments.
	 *
	 * @param type The type name of the event.
	 * @return A signal that requires two arguments in the slot.
	 */
	template<class T, class U>typename T_Signal_v2<const T&, const U&>::Type &registerToEvent2(const T_StringId &type);

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

	/**
	 * In order to support multiple different types registered into the event maps
	 * we need to store them as interfaces, else we can only store one specific type
	 * into the map (must specify value of template classes).
	 */
	class IEventSignal
	{
	public:
		/// Constructor.
		IEventSignal() {}
		/// Destructor.
		virtual ~IEventSignal() {}
	};
	/// Event holding an argument-less signal.
	class EventSignal0 : public IEventSignal
	{
	public:
		T_Signal_v0<>::Type signal;
	};
	/// Event holding a signal that requires a single signal.
	template<class T> class EventSignal1 : public IEventSignal
	{
	public:
		typename T_Signal_v1<const T&>::Type signal;
	};
	/// Event holding a signal that requires two signals.
	template<class T, class U> class EventSignal2 : public IEventSignal
	{
	public:
		typename T_Signal_v2<const T&, const U&>::Type signal;
	};
	/// Map of argument-less event signals held by entity.
	T_Map<T_StringIdType, IEventSignal*>::Type events0;
	/// Map of event signals with one argument held by entity.
	T_Map<T_StringIdType, IEventSignal*>::Type events1;
	/// Map of event signals with two arguments held by entity.
	T_Map<T_StringIdType, IEventSignal*>::Type events2;

	//--------------------------------------------------------------

	/// Reference to the component factory responsible for instancing components for this entity.
	ComponentFactory& componentFactory;
	/// Type property (read-only), holds the type string given in entity's constructor.
	Property<T_String> type_property;
	/// Id property (read-only), holds the id T_EntityId given in the entity's constructor.
	Property<T_EntityId> id_property;
};

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

//----------------------------------------------

inline void Entity::onEvent0(const T_StringId &type)
{
	T_Map<T_StringIdType, IEventSignal*>::Type::iterator it = events0.find(type.getId());
	if(it == events0.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events0 registry!").c_str());

	static_cast<EventSignal0*>(it->second)->signal.emit();
}

template<class T>
inline void Entity::onEvent1(const T_StringId &type, const T &arg0)
{
	T_Map<T_StringIdType, IEventSignal*>::Type::iterator it = events1.find(type.getId());
	if(it == events1.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events1 registry!").c_str());

#ifdef _DEBUG
	EventSignal1<T> *signal = dynamic_cast<EventSignal1<T>*>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to emit event " + type.getStr() + ", but the argument type didn't match the registered type!").c_str());
	signal->signal.emit(arg0);
#else
	static_cast<EventSignal1<T>*>(it->second)->signal.emit(arg0);
#endif
}

template<class T, class U>
inline void Entity::onEvent2(const T_StringId &type, const T &arg0, const U &arg1)
{
	T_Map<T_StringIdType, IEventSignal*>::Type::iterator it = events2.find(type.getId());
	if(it == events2.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events2 registry!").c_str());

#ifdef _DEBUG
	EventSignal2<T,U> *signal = dynamic_cast<EventSignal2<T,U>*>(it->second);
	if(signal == NULL_PTR)
		throw T_Exception(("Tried to emit event " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
	signal->signal.emit(arg0, arg1);
#else
	static_cast<EventSignal1<T>*>(it->second)->signal.emit(arg0, arg1);
#endif
}

inline T_Signal_v0<>::Type &Entity::registerToEvent0(const T_StringId &type)
{
	EventSignal0 *signal = NULL_PTR;

	T_Map<T_StringIdType, IEventSignal*>::Type::iterator it = events0.find(type.getId());
	if(it == events0.end())
	{
		signal = new EventSignal0();
		events0[type.getId()] = signal;
	}
	else
	{
		signal = static_cast<EventSignal0*>(it->second);
	}

	return signal->signal;
}

template<class T>
inline typename T_Signal_v1<const T&>::Type &Entity::registerToEvent1(const T_StringId &type)
{
	EventSignal1<T> *signal = NULL_PTR;

	T_Map<T_StringIdType, IEventSignal*>::Type::iterator it = events1.find(type.getId());
	if(it == events1.end())
	{
		signal = new EventSignal1<T>();
		events1[type.getId()] = signal;
	}
	else
	{
#ifdef _DEBUG
		signal = dynamic_cast<EventSignal1<T>*>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried to return the event signal " + type.getStr() + ", but the argument type didn't match the registered type!").c_str());
#else
		signal = static_cast<EventSignal0*>(it->second);
#endif
	}

	return signal->signal;
}

template<class T, class U>
inline typename T_Signal_v2<const T&, const U&>::Type &Entity::registerToEvent2(const T_StringId &type)
{
	EventSignal2<T,U> *signal = NULL_PTR;

	T_Map<T_StringIdType, IEventSignal*>::Type::iterator it = events2.find(type.getId());
	if(it == events2.end())
	{
		signal = new EventSignal2<T,U>();
		events2[type.getId()] = signal;
	}
	else
	{
#ifdef _DEBUG
		signal = dynamic_cast<EventSignal2<T,U>*>(it->second);
		if(signal == NULL_PTR)
			throw T_Exception(("Tried toreturn the event signal " + type.getStr() + ", but one or both of the argument types didn't match the registered types!").c_str());
#else
		signal = static_cast<EventSignal0*>(it->second);
#endif
	}

	return signal->signal;
}
