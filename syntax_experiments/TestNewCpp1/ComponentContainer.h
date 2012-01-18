/////////////////////////////////////////////////////
//
#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "Component.h"

namespace Totem
{

template<class EntityType, class TotemFactoryType>
class ComponentContainer
{
public:
	ComponentContainer(EntityType *thisAsEntity, TotemFactoryType *factory) : thisAsEntity(thisAsEntity), factory(factory) {}

	template<class ComponentType>
	std::shared_ptr<ComponentType> addComponent(unsigned int optionalParam = 0)
	{
		auto component = factory->createComponent<ComponentType>(thisAsEntity, optionalParam);
		components.push_back(component);
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0, unsigned int optionalParam = 0)
	{
		auto component = factory->createComponent<ComponentType, CustomParam0>(thisAsEntity, param0, optionalParam);
		components.push_back(component);
		return component;
	}

protected:
	EntityType *thisAsEntity;
	TotemFactoryType *factory;
	std::vector<std::shared_ptr<Component<TotemFactoryType>>> components;
};

} //namespace Totem

//
/////////////////////////////////////////////////////////