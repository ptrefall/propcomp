/////////////////////////////////////////////////////
//
#pragma once

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
		checkComponentNamingHistory(ComponentType::getType(), ComponentType::getType());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType>(getComponentOwner(), ComponentType::getType());
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType>
	std::shared_ptr<ComponentType> addComponent(const std::string &name)
	{
		checkComponentNamingHistory(ComponentType::getType(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType>(getComponentOwner(), name);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0)
	{
		checkComponentNamingHistory(ComponentType::getType(), ComponentType::getType());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0>(getComponentOwner(), ComponentType::getType(), param0);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0)
	{
		checkComponentNamingHistory(ComponentType::getType(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0>(getComponentOwner(), name, param0);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, CustomParam1 param1)
	{
		checkComponentNamingHistory(ComponentType::getType(), ComponentType::getType());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1>(getComponentOwner(), ComponentType::getType(), param0, param1);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0, CustomParam1 param1)
	{
		checkComponentNamingHistory(ComponentType::getType(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1>(getComponentOwner(), name, param0, param1);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, CustomParam1 param1, CustomParam2 param2)
	{
		checkComponentNamingHistory(ComponentType::getType(), ComponentType::getType());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2>(getComponentOwner(), ComponentType::getType(), param0, param1, param2);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2)
	{
		checkComponentNamingHistory(ComponentType::getType(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2>(getComponentOwner(), name, param0, param1, param2);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3)
	{
		checkComponentNamingHistory(ComponentType::getType(), ComponentType::getType());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2, CustomParam3>(getComponentOwner(), ComponentType::getType(), param0, param1, param2, param3);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3)
	{
		checkComponentNamingHistory(ComponentType::getType(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2, CustomParam3>(getComponentOwner(), name, param0, param1, param2, param3);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3, class CustomParam4>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3, CustomParam4 param4)
	{
		checkComponentNamingHistory(ComponentType::getType(), ComponentType::getType());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2, CustomParam3, CustomParam4>(getComponentOwner(), ComponentType::getType(), param0, param1, param2, param3, param4);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3, class CustomParam4>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3, CustomParam4 param4)
	{
		checkComponentNamingHistory(ComponentType::getType(), name);
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2, CustomParam3, CustomParam4>(getComponentOwner(), name, param0, param1, param2, param3, param4);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3, class CustomParam4, class CustomParam5>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3, CustomParam4 param4, CustomParam5 param5)
	{
		checkComponentNamingHistory(ComponentType::getType(), ComponentType::getType());
		auto component = ComponentFactoryType::createComponent<EntityPtrType, ComponentType, CustomParam0, CustomParam1, CustomParam2, CustomParam3, CustomParam4, CustomParam5>(getComponentOwner(), ComponentType::getType(), param0, param1, param2, param3, param4, param5);
		components.push_back(component);

		sign_ComponentAdded.invoke(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1, class CustomParam2, class CustomParam3, class CustomParam4, class CustomParam5>
	std::shared_ptr<ComponentType> addComponent(const std::string &name, CustomParam0 param0, CustomParam1 param1, CustomParam2 param2, CustomParam3 param3, CustomParam4 param4, CustomParam5 param5)
	{
		checkComponentNamingHistory(ComponentType::getType(), name);
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
			if(components[i]->getType() == ComponentType::getType())
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
			if(components[i]->getType() == ComponentType::getType())
			{
				if(!name.empty())
				{
					if(components[i]->getName() == name)
						return std::static_pointer_cast<ComponentType>(components[i]);
				}
				else
				{
					return std::static_pointer_cast<ComponentType>(components[i]);
				}
			}
		}
		throw std::runtime_error(("Couldn't find component " + ComponentType::getType()).c_str());
	}

	std::shared_ptr<Component<PropertyFactoryType>> getComponent(const std::string &type, const std::string &name = std::string())
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			if(components[i]->getType() == type)
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
		throw std::runtime_error(("Couldn't find component " + type).c_str());
	}

	std::vector<std::shared_ptr<Component<PropertyFactoryType>>> &getComponents() { return components; }

	void updateComponents(const float &deltaTime)
	{
		for(unsigned int i = 0; i < components.size(); i++)
			components[i]->update(deltaTime);
	}

protected:
	void checkComponentNamingHistory(const std::string &type, const std::string &name)
	{
		auto it = component_naming_history.find(type);
		if(it != component_naming_history.end())
		{
			for(unsigned int i = 0; i < it->second.size(); i++)
			{
				if(it->second[i] == name)
					throw std::runtime_error("Found Component name duplicate for type " + type + " with name " + name);
			}
			it->second.push_back(name);
		}
		else
		{
			std::vector<std::string> list;
			list.push_back(name);
			component_naming_history[type] = list;
		}
	}

	virtual EntityPtrType getComponentOwner() = 0;

	std::vector<std::shared_ptr<Component<PropertyFactoryType>>> components;
	std::unordered_map<std::string, std::vector<std::string>> component_naming_history;

	/// Signal that's emitted when a component with added to the component container.
	sigslot::signal1<std::shared_ptr<Component<PropertyFactoryType>>> sign_ComponentAdded;
};

} //namespace Totem

//
/////////////////////////////////////////////////////////