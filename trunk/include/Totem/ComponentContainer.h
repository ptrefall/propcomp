/////////////////////////////////////////////////////
//
#pragma once

#include "IComponent.h"
#include "Component.h"

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace Totem
{

class DefaultComponentFactory
{
public:
	template<class EntityPtrType, class ComponentType>
	static std::shared_ptr<ComponentType> createComponent(EntityPtrType entity, const std::string &name)
	{
		return std::make_shared<ComponentType>(entity, name);
	}

	template<class EntityPtrType, class ComponentType, class CustomParam0>
	static std::shared_ptr<ComponentType> createComponent(EntityPtrType entity, const std::string &name, CustomParam0 param0)
	{
		return std::make_shared<ComponentType>(entity, name, param0);
	}

	template<class EntityPtrType, class ComponentType, class CustomParam0, class CustomParam1>
	static std::shared_ptr<ComponentType> createComponent(EntityPtrType entity, const std::string &name, CustomParam0 param0, CustomParam1 param1)
	{
		return std::make_shared<ComponentType>(entity, name, param0, param1);
	}

	template<class EntityPtrType, class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2>
	static std::shared_ptr<ComponentType> createComponent(EntityPtrType entity, const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2)
	{
		return std::make_shared<ComponentType>(entity, name, param0, param1, param2);
	}

	template<class EntityPtrType, class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3>
	static std::shared_ptr<ComponentType> createComponent(EntityPtrType entity, const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3)
	{
		return std::make_shared<ComponentType>(entity, name, param0, param1, param2, param3);
	}

	template<class EntityPtrType, class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3, class CustomParam4>
	static std::shared_ptr<ComponentType> createComponent(EntityPtrType entity, const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3, CustomParam4 param4)
	{
		return std::make_shared<ComponentType>(entity, name, param0, param1, param2, param3, param4);
	}

	template<class EntityPtrType, class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3, class CustomParam4, class CustomParam5>
	static std::shared_ptr<ComponentType> createComponent(EntityPtrType entity, const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3, CustomParam4 param4, CustomParam5 param5)
	{
		return std::make_shared<ComponentType>(entity, name, param0, param1, param2, param3, param4, param5);
	}
};

template<class EntityPtrType, class ComponentFactoryType = DefaultComponentFactory, class PropertyFactoryType = DefaultPropertyFactory>
class ComponentContainer
{
public:
	template<class ComponentType>
	std::shared_ptr<ComponentType> addComponent()
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), std::string());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType>(getComponentOwner(), std::string());
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType>
	std::shared_ptr<ComponentType> addComponent(const std::string &name)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType>(getComponentOwner(), name);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), std::string());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0>(getComponentOwner(), std::string(), param0);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0>(getComponentOwner(), name, param0);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, CustomParam1 param1)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), std::string());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1>(getComponentOwner(), std::string(), param0, param1);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0, CustomParam1 param1)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1>(getComponentOwner(), name, param0, param1);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, CustomParam1 param1, CustomParam2 param2)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), std::string());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2>(getComponentOwner(), std::string(), param0, param1, param2);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2>(getComponentOwner(), name, param0, param1, param2);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), std::string());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2, CustomParam3>(getComponentOwner(), std::string(), param0, param1, param2, param3);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2, CustomParam3>(getComponentOwner(), name, param0, param1, param2, param3);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3, class CustomParam4>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3, CustomParam4 param4)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), std::string());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2, CustomParam3, CustomParam4>(getComponentOwner(), std::string(), param0, param1, param2, param3, param4);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3, class CustomParam4>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3, CustomParam4 param4)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2, CustomParam3, CustomParam4>(getComponentOwner(), name, param0, param1, param2, param3, param4);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3, class CustomParam4, class CustomParam5>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3, CustomParam4 param4, CustomParam5 param5)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), std::string());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2, CustomParam3, CustomParam4, CustomParam5>(getComponentOwner(), std::string(), param0, param1, param2, param3, param4, param5);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3, class CustomParam4, class CustomParam5>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3, CustomParam4 param4, CustomParam5 param5)
	{
		checkDuplicationAndAdd(IComponent<PropertyFactoryType>::getRuntimeTypeId<ComponentType>(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2, CustomParam3, CustomParam4, CustomParam5>(getComponentOwner(), name, param0, param1, param2, param3, param4, param5);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	//////////////////////////////////////////////////////////////////////////////

	template<class ComponentType>
	bool hasComponent(const std::string &name = std::string())
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			if(IComponent<PropertyFactoryType>::isType<ComponentType>(components[i]))
			{
				if(!name.empty())
				{
					if(components[i]->getName() == name)
						return true;
				}
				else
				{
					return true;
				}
			}
		}
		return false;
	}

	template<class ComponentType>
	std::shared_ptr<ComponentType> getComponent(const std::string &name = std::string())
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			if(IComponent<PropertyFactoryType>::isType<ComponentType>(components[i]))
			{
				if(!name.empty())
				{
					if(components[i]->getName() == name)
						return components[i];
				}
				else
				{
					return components[i];
				}
			}
		}
		throw std::runtime_error(("Couldn't find component with name " + name).c_str());
	}

	std::vector<std::shared_ptr<IComponent<PropertyFactoryType>>> &getComponents() { return components; }

	void updateComponents(const float &deltaTime)
	{
		for(unsigned int i = 0; i < components.size(); i++)
			components[i]->update(deltaTime);
	}

	template<class ComponentType>
	void removeComponent(const std::string &name = std::string(), bool upholdOrderInList = false)
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			if(IComponent<PropertyFactoryType>::isType<ComponentType>(components[i]))
			{
				if(!name.empty())
				{
					if(components[i]->getName() == name)
					{
						sign_ComponentRemoved.invoke(components[i]);
						if(upholdOrderInList)
						{
							components.erase(components.begin()+i);
						}
						else
						{
							components[i] = components.back();
							components.pop_back();
						}
						return;
					}
				}
				else
				{
					sign_ComponentRemoved.invoke(components[i]);
					if(upholdOrderInList)
					{
						components.erase(components.begin()+i);
					}
					else
					{
						components[i] = components.back();
						components.pop_back();
					}
					return;
				}
			}
		}
		throw std::runtime_error(("Couldn't find component with name " + name).c_str());
	}

	sigslot::signal1<std::shared_ptr<IComponent<PropertyFactoryType>>> &componentAdded() { return sign_ComponentAdded; }
	sigslot::signal1<std::shared_ptr<IComponent<PropertyFactoryType>>> &componentRemoved() { return sign_ComponentRemoved; }

protected:
	virtual EntityPtrType getComponentOwner() = 0;

	void checkDuplicationAndAdd(unsigned int typeId, const std::string &name)
	{
		auto it = namesForComponentTypes.find(typeId);
		if(it != namesForComponentTypes.end())
		{
			const std::vector<std::string> &names = it->second;
			for(unsigned int i = 0; i < names.size(); i++)
				if(names[i] == name)
					throw std::runtime_error("Found duplicate component name: " + name);
			it->second.push_back(name);
		}
		else
		{
			std::vector<std::string> new_list;
			new_list.push_back(name);
			namesForComponentTypes[typeId] = new_list;
		}
	}

	std::unordered_map<unsigned int, std::vector<std::string>> namesForComponentTypes;
	std::vector<std::shared_ptr<IComponent<PropertyFactoryType>>> components;

	/// Signal that's emitted when a component was added to the component container.
	sigslot::signal1<std::shared_ptr<IComponent<PropertyFactoryType>>> sign_ComponentAdded;
	/// Signal that's emitted when a component was removed from the component container.
	sigslot::signal1<std::shared_ptr<IComponent<PropertyFactoryType>>> sign_ComponentRemoved;
};

} //namespace Totem

//
/////////////////////////////////////////////////////////