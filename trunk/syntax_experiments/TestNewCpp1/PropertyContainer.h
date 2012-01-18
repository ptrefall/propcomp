#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Property.h"

namespace Totem
{

template<class TotemFactoryType, class UserData = void*>
class PropertyContainer
{
public:
	/**
	 * Constructor
	 *
	 */
	PropertyContainer(TotemFactoryType *factory) : factory(factory) {}

	/**
	 * Destructor
	 */
	virtual ~PropertyContainer()
	{
		removeAllProperties();
	}

	//--------------------------------------------------------------
	
	/**
	 * Check whether the specified property name exist in this PropertyContainer.
	 * This function works on the interface (IProperty) of the property,
	 * thus no type-casting is involved in it's usage.
	 *
	 * @param name The name of the property.
	 * @return Returns true if the property exist in this PropertyContainer, false if it doesn't.
	 */
	bool hasProperty(const std::string& name);

	/**
	 * Add a property of specified type T and name to this PropertyContainer with a default value.
	 * If readOnly is specified to true, one can only change the property by
	 * directly calling property.set(value, ..., overrideReadonly=true), all other pipes, like
	 * via operators, will throw an exception.
	 *
	 * @param name The name of the property used to store and associate the property in the PropertyContainer.
	 * @param defaultValue The initial value this property should be set to when added to the PropertyContainer.
	 * @param readOnly Flag this property as read-only if it should only be read. Defaults to false.
	 * @return Returns a shared_ptr (pimpl) reference to the property that was added to the PropertyContainer.
	 */
	template<class T>
	Property<T> addProperty(const std::string& name, const T &defaultValue)
	{
		auto it = properties.find(name);
		if(it != properties.end())
		{
			std::shared_ptr<Property<T>> property;
	#ifdef _DEBUG
			property = std::dynamic_pointer_cast< Property<T> >(it->second);
			if(!property)
				throw std::runtime_error(("Property " + name + " already exists, but with another type!").c_str());
	#else
			property = std::static_pointer_cast< Property<T> >(it->second);
	#endif
			sign_propertyAdded.invoke(it->second);
			return *property.get();
		}

		auto property = factory->createProperty<T>(name);
		property->set(defaultValue);
		properties[property->getName()] = property;

		//return *property;
		sign_propertyAdded.invoke(std::static_pointer_cast<IProperty>(property));
		//return getProperty<T>(name);
		return *property.get();
	}

	/**
	 * Add a property of specified type T and name to this PropertyContainer with a default value and userdata of type UserData.
	 * If readOnly is specified to true, one can only change the property by
	 * directly calling property.set(value, ..., overrideReadonly=true), all other pipes, like
	 * via operators, will throw an exception.
	 *
	 * @param name The name of the property used to store and associate the property in the PropertyContainer.
	 * @param defaultValue The initial value this property should be set to when added to the PropertyContainer.
	 * @param userData The userdata is of type specified for the PropertyContainer's class template, and provides optional userdata description of the property.
	 * @param readOnly Flag this property as read-only if it should only be read. Defaults to false.
	 * @return Returns a shared_ptr (pimpl) reference to the property that was added to the PropertyContainer.
	 */
	template<class T>
	Property<T> addProperty(const std::string& name, const T &defaultValue, const UserData &userData)
	{
		auto it = properties.find(name);
		if(it != properties.end())
		{
			std::shared_ptr<Property<T>> property;
	#ifdef _DEBUG
			property = std::dynamic_pointer_cast< Property<T> >(it->second);
			if(!property)
				throw std::runtime_error(("Property " + name + " already exists, but with another type!").c_str());
	#else
			property = std::static_pointer_cast< Property<T> >(it->second);
	#endif
			sign_propertyWithUserDataAdded.invoke(it->second, userData);
			return *property.get();
		}

		auto property = factory->createProperty<T>(name);
		property->set(defaultValue);
		properties[property->getName()] = property;

		//return *property;
		sign_propertyWithUserDataAdded.invoke(std::static_pointer_cast<IProperty>(property), userData);
		//return getProperty<T>(name);
		return *property.get();
	}

	/**
	 * Add a property interface to this PropertyContainer.
	 * There can be situations where this is required.
	 *
	 * @param property The interface of the property.
	 */
	void addProperty(std::shared_ptr<IProperty> property);

	/**
	 * Get a shared_ptr (pimpl) reference to a property of specified name from the PropertyContainer.
	 *
	 * @param name The name of the property.
	 * @return Returns a shared_ptr (pimpl) reference to the property.
	 */
	template<class T>
	Property<T> getProperty(const std::string& name)
	{
		auto it = properties.find(name);
		if(it != properties.end())
		{
			std::shared_ptr<Property<T>> property;
	#ifdef _DEBUG
			property = std::dynamic_pointer_cast< Property<T> >(it->second);
			if(!property)
				throw std::runtime_error(("Tried to get property " + name + ", but the type was wrong!").c_str());
	#else
			property = std::static_pointer_cast< Property<T> >(it->second);
	#endif
			return *property.get();
		}
		else
			throw std::runtime_error(("Unable to get property " + name).c_str());
	}

	/**
	 * Get a property interface pointer to a property of specified name from the PropertyContainer.
	 *
	 * @param name  The name of the property.
	 * @return The interface pointer to the property.
	 */
	std::shared_ptr<IProperty> getPropertyInterface(const std::string& name);

	/**
	 * Remove the property of specified name from PropertyContainer with
	 * option to postpone deletion until the next time update
	 * is called on the PropertyContainer.
	 *
	 * @param name The name of the property.
	 * @param postponeDelete Flag whether to postpone the deletion of this property (if true), or delete it immediately (if false). Defaults to false.
	 */
	void removeProperty(const std::string& name, bool postponeDelete = false);

	/**
	 * Remove all properties from PropertyContainer.
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
	 * Get a reference to the entire map of properties owned by the PropertyContainer.
	 *
	 * @return Returns a reference to the PropertyContainer's property map.
	 */
	std::unordered_map<std::string, std::shared_ptr<IProperty>> &getProperties() { return properties; }

	//--------------------------------------------------------------
	
	/**
	 * Handles deletion of all properties pending for deletion in this PropertyContainer.
	 *
	 */
	void updateProperties();

	//--------------------------------------------------------------

	/// Provide an assignment operator to leviate level W4 warning
	PropertyContainer &operator= (const PropertyContainer &rhs)
	{
		if(this == &rhs)
			return *this;

		throw std::runtime_error("Assignment operation between PropertyContainer are not supported!");
	}

	//--------------------------------------------------------------

	/**
	 * Function that gives the outside access to the PropertyContainer's
	 * propertyAdded signal. It's through this function call we can
	 * register slots to the propertyAdded signal.
	 *
	 * @return Returns the propertyAdded signal of this property handler.
	 */
	sigslot::signal1<std::shared_ptr<IProperty>> propertyAdded() { return sign_propertyAdded; }

	/**
	 * Function that gives the outside access to the PropertyContainer's
	 * propertyWithUserDataAdded signal. It's through this function call we can
	 * register slots to the propertyWithUserDataAdded signal.
	 *
	 * @return Returns the propertyWithUserDataAdded signal of this property handler.
	 */
	sigslot::signal2<std::shared_ptr<IProperty>, const UserData&> &propertyWithUserDataAdded() { return sign_propertyWithUserDataAdded; }

protected:
	///
	TotemFactoryType *factory;
	/// The map of all properties owned by this PropertyContainer.
	std::unordered_map<std::string, std::shared_ptr<IProperty>> properties;
	/// The list of all properties pending deletion in this PropertyContainer.
	std::vector<std::shared_ptr<IProperty>> deletedProperties;
	/// Signal that's emitted when a property with NO userdata is added to the property handler.
	sigslot::signal1<std::shared_ptr<IProperty>> sign_propertyAdded;
	/// Signal that's emitted when a property with userdata is added to the property handler.
	sigslot::signal2<std::shared_ptr<IProperty>, const UserData&> sign_propertyWithUserDataAdded;
};

//------------------------------------------------------

template<class TotemFactoryType, class UserData>
inline bool PropertyContainer<TotemFactoryType, UserData>::hasProperty(const std::string& name)
{
	if(properties.empty())
		return false;

	auto it = properties.find(name);
	if(it != properties.end())
		return true;
	else
		return false;
}

template<class TotemFactoryType, class UserData>
inline void PropertyContainer<TotemFactoryType, UserData>::addProperty(std::shared_ptr<IProperty> property)
{
	auto it = properties.find(property->getName());
	if(it == properties.end())
		properties[property->getName()] = property;
}

template<class TotemFactoryType, class UserData>
inline std::shared_ptr<IProperty> PropertyContainer<TotemFactoryType, UserData>::getPropertyInterface(const std::string& name)
{
	auto it = properties.find(name);
	if(it != properties.end())
		return it->second;
	else
		throw std::runtime_error(("Unable to get property " + name).c_str());
}

template<class TotemFactoryType, class UserData>
inline void PropertyContainer<TotemFactoryType, UserData>::removeProperty(const std::string& name, bool postponeDelete)
{
	auto it = properties.find(name);
	if(it != properties.end())
	{
		std::shared_ptr<IProperty> property = (*it).second;
		if(postponeDelete)
			deletedProperties.push_back(property);
		properties.erase(it);
	}
}

template<class TotemFactoryType, class UserData>
inline void PropertyContainer<TotemFactoryType, UserData>::removeAllProperties()
{
	properties.clear();
	clearDeletedProperties();
}

template<class TotemFactoryType, class UserData>
inline void PropertyContainer<TotemFactoryType, UserData>::updateProperties()
{
	clearDeletedProperties();
}

template<class TotemFactoryType, class UserData>
inline void PropertyContainer<TotemFactoryType, UserData>::clearDeletedProperties()
{
	deletedProperties.clear();
}

} //namespace Totem

