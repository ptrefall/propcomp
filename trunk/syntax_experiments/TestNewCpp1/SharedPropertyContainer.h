#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "SharedProperty.h"

namespace Totem
{

class DefaultSharedPropertyFactory
{
public:
	template<class PropertyType>
	static std::shared_ptr<Totem::SharedProperty<PropertyType>> createSharedProperty(const std::string &name)
	{
		return std::make_shared<Totem::SharedProperty<PropertyType>>(name);
	}
};

template<class SharedPropertyFactoryType = DefaultSharedPropertyFactory, class UserData = void*>
class SharedPropertyContainer
{
public:
	/**
	 * Constructor
	 *
	 */
	SharedPropertyContainer() {}

	/**
	 * Destructor
	 */
	virtual ~SharedPropertyContainer()
	{
		removeAllSharedProperties();
	}

	//--------------------------------------------------------------
	
	/**
	 * Check whether the specified property name exist in this SharedPropertyContainer.
	 * This function works on the interface (IProperty) of the property,
	 * thus no type-casting is involved in it's usage.
	 *
	 * @param name The name of the property.
	 * @return Returns true if the property exist in this SharedPropertyContainer, false if it doesn't.
	 */
	bool hasSharedProperty(const std::string& name);

	/**
	 * Add a property of specified type T and name to this SharedPropertyContainer with a default value.
	 * If readOnly is specified to true, one can only change the property by
	 * directly calling property.set(value, ..., overrideReadonly=true), all other pipes, like
	 * via operators, will throw an exception.
	 *
	 * @param name The name of the property used to store and associate the property in the SharedPropertyContainer.
	 * @param defaultValue The initial value this property should be set to when added to the SharedPropertyContainer.
	 * @param readOnly Flag this property as read-only if it should only be read. Defaults to false.
	 * @return Returns a shared_ptr (pimpl) reference to the property that was added to the SharedPropertyContainer.
	 */
	template<class T>
	SharedProperty<T> addSharedProperty(const std::string& name, const T &defaultValue)
	{
		auto it = shared_properties.find(name);
		if(it != shared_properties.end())
		{
			std::shared_ptr<SharedProperty<T>> property;
	#ifdef _DEBUG
			property = std::dynamic_pointer_cast< SharedProperty<T> >(it->second);
			if(!property)
				throw std::runtime_error(("SharedProperty " + name + " already exists, but with another type!").c_str());
	#else
			property = std::static_pointer_cast< SharedProperty<T> >(it->second);
	#endif
			sign_sharedPropertyAdded.invoke(it->second);
			return *property.get();
		}

		auto property = SharedPropertyFactoryType::createSharedProperty<T>(name);
		property->set(defaultValue, true);
		shared_properties[property->getName()] = property;

		//return *property;
		sign_sharedPropertyAdded.invoke(std::static_pointer_cast<IProperty>(property));
		//return getProperty<T>(name);
		return *property.get();
	}

	/**
	 * Add a property of specified type T and name to this SharedPropertyContainer with a default value and userdata of type UserData.
	 * If readOnly is specified to true, one can only change the property by
	 * directly calling property.set(value, ..., overrideReadonly=true), all other pipes, like
	 * via operators, will throw an exception.
	 *
	 * @param name The name of the property used to store and associate the property in the SharedPropertyContainer.
	 * @param defaultValue The initial value this property should be set to when added to the SharedPropertyContainer.
	 * @param userData The userdata is of type specified for the SharedPropertyContainer's class template, and provides optional userdata description of the property.
	 * @param readOnly Flag this property as read-only if it should only be read. Defaults to false.
	 * @return Returns a shared_ptr (pimpl) reference to the property that was added to the SharedPropertyContainer.
	 */
	template<class T>
	SharedProperty<T> addSharedProperty(const std::string& name, const T &defaultValue, const UserData &userData)
	{
		auto it = shared_properties.find(name);
		if(it != shared_properties.end())
		{
			std::shared_ptr<SharedProperty<T>> property;
	#ifdef _DEBUG
			property = std::dynamic_pointer_cast< SharedProperty<T> >(it->second);
			if(!property)
				throw std::runtime_error(("SharedProperty " + name + " already exists, but with another type!").c_str());
	#else
			property = std::static_pointer_cast< SharedProperty<T> >(it->second);
	#endif
			sign_sharedPropertyWithUserDataAdded.invoke(it->second, userData);
			return *property.get();
		}

		auto property = SharedPropertyFactoryType::createSharedProperty<T>(name);
		property->set(defaultValue, true);
		shared_properties[property->getName()] = property;

		//return *property;
		sign_sharedPropertyWithUserDataAdded.invoke(std::static_pointer_cast<IProperty>(property), userData);
		//return getProperty<T>(name);
		return *property.get();
	}

	/**
	 * Add a property interface to this SharedPropertyContainer.
	 * There can be situations where this is required.
	 *
	 * @param property The interface of the property.
	 */
	void addSharedProperty(std::shared_ptr<IProperty> property);

	/**
	 * Get a shared_ptr (pimpl) reference to a property of specified name from the SharedPropertyContainer.
	 *
	 * @param name The name of the property.
	 * @return Returns a shared_ptr (pimpl) reference to the property.
	 */
	template<class T>
	SharedProperty<T> getSharedProperty(const std::string& name)
	{
		auto it = shared_properties.find(name);
		if(it != shared_properties.end())
		{
			std::shared_ptr<SharedProperty<T>> property;
	#ifdef _DEBUG
			property = std::dynamic_pointer_cast< SharedProperty<T> >(it->second);
			if(!property)
				throw std::runtime_error(("Tried to get shared property " + name + ", but the type was wrong!").c_str());
	#else
			property = std::static_pointer_cast< SharedProperty<T> >(it->second);
	#endif
			return *property.get();
		}
		else
			throw std::runtime_error(("Unable to get property " + name).c_str());
	}

	/**
	 * Get a property interface pointer to a property of specified name from the SharedPropertyContainer.
	 *
	 * @param name  The name of the property.
	 * @return The interface pointer to the property.
	 */
	std::shared_ptr<IProperty> getSharedPropertyInterface(const std::string& name);

	/**
	 * Remove the property of specified name from SharedPropertyContainer with
	 * option to postpone deletion until the next time update
	 * is called on the SharedPropertyContainer.
	 *
	 * @param name The name of the property.
	 * @param postponeDelete Flag whether to postpone the deletion of this property (if true), or delete it immediately (if false). Defaults to false.
	 */
	void removeSharedProperty(const std::string& name, bool postponeDelete = false);

	/**
	 * Remove all properties from SharedPropertyContainer.
	 *
	 */
	void removeAllSharedProperties();

	/**
	 * Delete all properties that was deleted last time update was called
	 * and marked postponeDelete.
	 *
	 */
	void clearDeletedSharedProperties();

	/**
	 * Get a reference to the entire map of properties owned by the SharedPropertyContainer.
	 *
	 * @return Returns a reference to the SharedPropertyContainer's property map.
	 */
	std::unordered_map<std::string, std::shared_ptr<IProperty>> &getSharedProperties() { return shared_properties; }

	//--------------------------------------------------------------
	
	/**
	 * Handles deletion of all properties pending for deletion in this SharedPropertyContainer.
	 *
	 */
	void updateSharedProperties();

	//--------------------------------------------------------------

	/// Provide an assignment operator to leviate level W4 warning
	SharedPropertyContainer &operator= (const SharedPropertyContainer &rhs)
	{
		if(this == &rhs)
			return *this;

		throw std::runtime_error("Assignment operation between SharedPropertyContainer are not supported!");
	}

	//--------------------------------------------------------------

	/**
	 * Function that gives the outside access to the SharedPropertyContainer's
	 * propertyAdded signal. It's through this function call we can
	 * register slots to the propertyAdded signal.
	 *
	 * @return Returns the propertyAdded signal of this property handler.
	 */
	sigslot::signal1<std::shared_ptr<IProperty>> sharedPropertyAdded() { return sign_sharedPropertyAdded; }

	/**
	 * Function that gives the outside access to the SharedPropertyContainer's
	 * propertyWithUserDataAdded signal. It's through this function call we can
	 * register slots to the propertyWithUserDataAdded signal.
	 *
	 * @return Returns the propertyWithUserDataAdded signal of this property handler.
	 */
	sigslot::signal2<std::shared_ptr<IProperty>, const UserData&> &sharedPropertyWithUserDataAdded() { return sign_sharedPropertyWithUserDataAdded; }

protected:
	/// The map of all properties owned by this SharedPropertyContainer.
	std::unordered_map<std::string, std::shared_ptr<IProperty>> shared_properties;
	/// The list of all properties pending deletion in this SharedPropertyContainer.
	std::vector<std::shared_ptr<IProperty>> deletedSharedProperties;
	/// Signal that's emitted when a property with NO userdata is added to the property handler.
	sigslot::signal1<std::shared_ptr<IProperty>> sign_sharedPropertyAdded;
	/// Signal that's emitted when a property with userdata is added to the property handler.
	sigslot::signal2<std::shared_ptr<IProperty>, const UserData&> sign_sharedPropertyWithUserDataAdded;
};

//------------------------------------------------------

template<class SharedPropertyFactoryType, class UserData>
inline bool SharedPropertyContainer<SharedPropertyFactoryType, UserData>::hasSharedProperty(const std::string& name)
{
	if(properties.empty())
		return false;

	auto it = shared_properties.find(name);
	if(it != shared_properties.end())
		return true;
	else
		return false;
}

template<class SharedPropertyFactoryType, class UserData>
inline void SharedPropertyContainer<SharedPropertyFactoryType, UserData>::addSharedProperty(std::shared_ptr<IProperty> property)
{
	auto it = shared_properties.find(property->getName());
	if(it == shared_properties.end())
		shared_properties[property->getName()] = property;
}

template<class SharedPropertyFactoryType, class UserData>
inline std::shared_ptr<IProperty> SharedPropertyContainer<SharedPropertyFactoryType, UserData>::getSharedPropertyInterface(const std::string& name)
{
	auto it = shared_properties.find(name);
	if(it != shared_properties.end())
		return it->second;
	else
		throw std::runtime_error(("Unable to get shared property " + name).c_str());
}

template<class SharedPropertyFactoryType, class UserData>
inline void SharedPropertyContainer<SharedPropertyFactoryType, UserData>::removeSharedProperty(const std::string& name, bool postponeDelete)
{
	auto it = shared_properties.find(name);
	if(it != shared_properties.end())
	{
		std::shared_ptr<IProperty> property = (*it).second;
		if(postponeDelete)
			deletedSharedProperties.push_back(property);
		shared_properties.erase(it);
	}
}

template<class SharedPropertyFactoryType, class UserData>
inline void SharedPropertyContainer<SharedPropertyFactoryType, UserData>::removeAllSharedProperties()
{
	shared_properties.clear();
	clearDeletedSharedProperties();
}

template<class SharedPropertyFactoryType, class UserData>
inline void SharedPropertyContainer<SharedPropertyFactoryType, UserData>::updateSharedProperties()
{
	clearDeletedSharedProperties();
}

template<class SharedPropertyFactoryType, class UserData>
inline void SharedPropertyContainer<SharedPropertyFactoryType, UserData>::clearDeletedSharedProperties()
{
	deletedSharedProperties.clear();
}

} //namespace Totem 
