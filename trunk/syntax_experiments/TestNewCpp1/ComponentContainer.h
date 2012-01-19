/////////////////////////////////////////////////////
//
#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "Component.h"

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
};

template<class EntityType, class ComponentFactoryType = DefaultComponentFactory>
class ComponentContainer
{
public:
	ComponentContainer(EntityType *thisAsEntity) : thisAsEntity(thisAsEntity) {}

	template<class ComponentType>
	std::shared_ptr<ComponentType> addComponent(const std::string &name = std::string(), unsigned int optionalParam = 0)
	{
		auto component = ComponentFactoryType::createComponent<EntityType, ComponentType>(name, thisAsEntity, optionalParam);
		components.push_back(component);
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, const std::string &name = std::string(), unsigned int optionalParam = 0)
	{
		auto component = ComponentFactoryType::createComponent<EntityType, ComponentType, CustomParam0>(name, thisAsEntity, param0, optionalParam);
		components.push_back(component);
		return component;
	}



protected:
	EntityType *thisAsEntity;
	std::vector<std::shared_ptr<Component<>>> components;
};

} //namespace Totem

//
/////////////////////////////////////////////////////////