#pragma once

#include "PropertyList.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace Totem
{

class DefaultPropertyListFactory
{
public:
	template<class PropertyType>
	static std::shared_ptr<Totem::PropertyList<PropertyType>> createPropertyList(const std::string &name)
	{
		return std::make_shared<Totem::PropertyList<PropertyType>>(name);
	}
};

template<class PropertyListFactoryType = DefaultPropertyListFactory, class UserData = void*>
class PropertyListContainer
{
public:
	/**
	 * Constructor
	 *
	 */
	PropertyListContainer() {}

	/**
	 * Destructor
	 */
	virtual ~PropertyListContainer()
	{
		removeAllPropertyLists();
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
	bool hasPropertyList(const std::string& name);

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
	PropertyList<T> addList(const std::string& name)
	{
		auto it = shared_property_lists.find(name);
		if(it != shared_property_lists.end())
		{
			std::shared_ptr<PropertyList<T>> property;
	#ifdef _DEBUG
			property = std::dynamic_pointer_cast< PropertyList<T> >(it->second);
			if(!property)
				throw std::runtime_error(("PropertyList " + name + " already exists, but with another type!").c_str());
	#else
			property = std::static_pointer_cast< PropertyList<T> >(it->second);
	#endif
			sign_PropertyListAdded.invoke(it->second);
			return *property.get();
		}

		auto property = PropertyListFactoryType::createPropertyList<T>(name);
		shared_property_lists[property->getName()] = property;

		//return *property;
		sign_PropertyListAdded.invoke(std::static_pointer_cast<IPropertyList>(property));
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
	PropertyList<T> addList(const std::string& name, const UserData &userData)
	{
		auto it = shared_property_lists.find(name);
		if(it != shared_property_lists.end())
		{
			std::shared_ptr<PropertyList<T>> property;
	#ifdef _DEBUG
			property = std::dynamic_pointer_cast< PropertyList<T> >(it->second);
			if(!property)
				throw std::runtime_error(("PropertyList " + name + " already exists, but with another type!").c_str());
	#else
			property = std::static_pointer_cast< Property<T> >(it->second);
	#endif
			sign_PropertyListWithUserDataAdded.invoke(it->second, userData);
			return *property.get();
		}

		auto property = PropertyListFactoryType::createPropertyList<T>(name);
		shared_property_lists[property->getName()] = property;

		//return *property;
		sign_PropertyListWithUserDataAdded.invoke(std::static_pointer_cast<IPropertyList>(property), userData);
		//return getProperty<T>(name);
		return *property.get();
	}

	/**
	 * Add a property interface to this PropertyContainer.
	 * There can be situations where this is required.
	 *
	 * @param property The interface of the property.
	 */
	void addList(std::shared_ptr<IPropertyList> property);

	/**
	 * Get a shared_ptr (pimpl) reference to a property of specified name from the PropertyContainer.
	 *
	 * @param name The name of the property.
	 * @return Returns a shared_ptr (pimpl) reference to the property.
	 */
	template<class T>
	PropertyList<T> getList(const std::string& name)
	{
		auto it = shared_property_lists.find(name);
		if(it != shared_property_lists.end())
		{
			std::shared_ptr<PropertyList<T>> property;
	#ifdef _DEBUG
			property = std::dynamic_pointer_cast< PropertyList<T> >(it->second);
			if(!property)
				throw std::runtime_error(("Tried to get shared property list " + name + ", but the type was wrong!").c_str());
	#else
			property = std::static_pointer_cast< PropertyList<T> >(it->second);
	#endif
			return *property.get();
		}
		else
			throw std::runtime_error(("Unable to get shared property list " + name).c_str());
	}

	/**
	 * Get a property interface pointer to a property of specified name from the PropertyContainer.
	 *
	 * @param name  The name of the property.
	 * @return The interface pointer to the property.
	 */
	std::shared_ptr<IPropertyList> getListInterface(const std::string& name);

	/**
	 * Remove the property of specified name from PropertyContainer with
	 * option to postpone deletion until the next time update
	 * is called on the PropertyContainer.
	 *
	 * @param name The name of the property.
	 * @param postponeDelete Flag whether to postpone the deletion of this property (if true), or delete it immediately (if false). Defaults to false.
	 */
	void removePropertyList(const std::string& name, bool postponeDelete = false);

	/**
	 * Remove all properties from PropertyContainer.
	 *
	 */
	void removeAllPropertyLists();

	/**
	 * Delete all properties that was deleted last time update was called
	 * and marked postponeDelete.
	 *
	 */
	void clearDeletedPropertyLists();

	/**
	 * Get a reference to the entire map of properties owned by the PropertyContainer.
	 *
	 * @return Returns a reference to the PropertyContainer's property map.
	 */
	std::unordered_map<std::string, std::shared_ptr<IPropertyList>> &getPropertyLists() { return shared_property_lists; }

	//--------------------------------------------------------------
	
	/**
	 * Handles deletion of all properties pending for deletion in this PropertyContainer.
	 *
	 */
	void updatePropertyLists();

	//--------------------------------------------------------------

	/// Provide an assignment operator to leviate level W4 warning
	PropertyListContainer &operator= (const PropertyListContainer &rhs)
	{
		if(this == &rhs)
			return *this;

		throw std::runtime_error("Assignment operation between PropertyListContainer are not supported!");
	}

	//--------------------------------------------------------------

	/**
	 * Function that gives the outside access to the PropertyContainer's
	 * propertyAdded signal. It's through this function call we can
	 * register slots to the propertyAdded signal.
	 *
	 * @return Returns the propertyAdded signal of this property handler.
	 */
	sigslot::signal1<std::shared_ptr<IPropertyList>> PropertyListAdded() { return sign_PropertyListAdded; }

	/**
	 * Function that gives the outside access to the PropertyContainer's
	 * propertyWithUserDataAdded signal. It's through this function call we can
	 * register slots to the propertyWithUserDataAdded signal.
	 *
	 * @return Returns the propertyWithUserDataAdded signal of this property handler.
	 */
	sigslot::signal2<std::shared_ptr<IPropertyList>, const UserData&> &PropertyListWithUserDataAdded() { return sign_PropertyListWithUserDataAdded; }

protected:
	/// The map of all properties owned by this PropertyContainer.
	std::unordered_map<std::string, std::shared_ptr<IPropertyList>> shared_property_lists;
	/// The list of all properties pending deletion in this PropertyContainer.
	std::vector<std::shared_ptr<IPropertyList>> deletedPropertyLists;
	/// Signal that's emitted when a property with NO userdata is added to the property handler.
	sigslot::signal1<std::shared_ptr<IPropertyList>> sign_PropertyListAdded;
	/// Signal that's emitted when a property with userdata is added to the property handler.
	sigslot::signal2<std::shared_ptr<IPropertyList>, const UserData&> sign_PropertyListWithUserDataAdded;
};

//------------------------------------------------------

template<class PropertyListFactoryType, class UserData>
inline bool PropertyListContainer<PropertyListFactoryType, UserData>::hasPropertyList(const std::string& name)
{
	if(shared_property_lists.empty())
		return false;

	auto it = shared_property_lists.find(name);
	if(it != shared_property_lists.end())
		return true;
	else
		return false;
}

template<class PropertyListFactoryType, class UserData>
inline void PropertyListContainer<PropertyListFactoryType, UserData>::addList(std::shared_ptr<IPropertyList> property)
{
	auto it = shared_property_lists.find(property->getName());
	if(it == shared_property_lists.end())
		shared_property_lists[property->getName()] = property;
}

template<class PropertyListFactoryType, class UserData>
inline std::shared_ptr<IPropertyList> PropertyListContainer<PropertyListFactoryType, UserData>::getListInterface(const std::string& name)
{
	auto it = shared_property_lists.find(name);
	if(it != shared_property_lists.end())
		return it->second;
	else
		throw std::runtime_error(("Unable to get shared property list " + name).c_str());
}

template<class PropertyListFactoryType, class UserData>
inline void PropertyListContainer<PropertyListFactoryType, UserData>::removePropertyList(const std::string& name, bool postponeDelete)
{
	auto it = shared_property_lists.find(name);
	if(it != shared_property_lists.end())
	{
		std::shared_ptr<IPropertyList> property = (*it).second;
		if(postponeDelete)
			deletedPropertyLists.push_back(property);
		shared_property_lists.erase(it);
	}
}

template<class PropertyListFactoryType, class UserData>
inline void PropertyListContainer<PropertyListFactoryType, UserData>::removeAllPropertyLists()
{
	shared_property_lists.clear();
	clearDeletedPropertyLists();
}

template<class PropertyListFactoryType, class UserData>
inline void PropertyListContainer<PropertyListFactoryType, UserData>::updatePropertyLists()
{
	clearDeletedPropertyLists();
}

template<class PropertyListFactoryType, class UserData>
inline void PropertyListContainer<PropertyListFactoryType, UserData>::clearDeletedPropertyLists()
{
	deletedPropertyLists.clear();
}

} //namespace Totem 
