/////////////////////////////////////////////////////
//
#pragma once

#include "Component.h"

#include <memory>
#include <vector>
#include <unordered_map>

namespace Totem
{

class DefaultComponentFactory
{
public:
	template<class EntityType, class ComponentType>
	static std::shared_ptr<ComponentType> createComponent(const std::string &name, EntityType *entity, unsigned int optionalParam)
	{
		return std::make_shared<ComponentType>(name, entity);
	}

	template<class EntityType, class ComponentType, class CustomParam0>
	static std::shared_ptr<ComponentType> createComponent(const std::string &name, EntityType *entity, CustomParam0 param0, unsigned int optionalParam)
	{
		return std::make_shared<ComponentType>(name, entity, param0);
	}

	template<class EntityType, class ComponentType, class CustomParam0, class CustomParam1>
	static std::shared_ptr<ComponentType> createComponent(const std::string &name, EntityType *entity, CustomParam0 param0, CustomParam1 param1, unsigned int optionalParam)
	{
		return std::make_shared<ComponentType>(name, entity, param0, param1);
	}
};

template<class EntityType, class ComponentFactoryType = DefaultComponentFactory>
class ComponentContainer
{
public:
	ComponentContainer(EntityType *thisAsEntity) : thisAsEntity(thisAsEntity) {}

	template<class ComponentType>
	std::shared_ptr<ComponentType> addComponent0(const std::string &name = std::string(), unsigned int optionalParam = 0)
	{
		auto component = ComponentFactoryType::createComponent<EntityType, ComponentType>(name, thisAsEntity, optionalParam);
		components.push_back(component);
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent1(CustomParam0 param0, const std::string &name = std::string(), unsigned int optionalParam = 0)
	{
		auto component = ComponentFactoryType::createComponent<EntityType, ComponentType, CustomParam0>(name, thisAsEntity, param0, optionalParam);
		components.push_back(component);
		return component;
	}

	template<class ComponentType, class CustomParam0, class CustomParam1>
	std::shared_ptr<ComponentType> addComponent2(CustomParam0 param0, CustomParam1 param1, const std::string &name = std::string(), unsigned int optionalParam = 0)
	{
		auto component = ComponentFactoryType::createComponent<EntityType, ComponentType, CustomParam0, CustomParam1>(name, thisAsEntity, param0, param1, optionalParam);
		components.push_back(component);
		return component;
	}

	//////////////////////////////////////////////////////////////////////////////

	template<class ComponentType>
	bool hasComponent(const std::string &name = std::string())
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			if(components[i]->getType() == ComponentType::Type())
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
			if(components[i]->getType() == ComponentType::Type())
			{
				if(!name.empty())
				{
					if(components[i]->getName() == name)
						return static_pointer_cast<ComponentType>(components[i]);
				}
				else
				{
					return static_pointer_cast<ComponentType>(components[i]);
				}
			}
		}
		throw std::runtime_error(("Couldn't find component " + ComponentType::Type()).c_str());
	}

	void updateComponents(const float &deltaTime)
	{
		for(unsigned int i = 0; i < components.size(); i++)
			components[i]->update(deltaTime);
	}

protected:
	EntityType *thisAsEntity;
	std::vector<std::shared_ptr<Component<>>> components;
};

} //namespace Totem

//
/////////////////////////////////////////////////////////