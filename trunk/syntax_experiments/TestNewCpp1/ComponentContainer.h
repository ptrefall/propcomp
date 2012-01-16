/////////////////////////////////////////////////////
//
#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

class Component;
typedef std::shared_ptr<Component> ComponentPtr;

template<class EntityType, class ComponentFactoryTypePtr>
class ComponentContainer
{
public:
	ComponentContainer(EntityType *thisAsEntity, ComponentFactoryTypePtr factory) : thisAsEntity(thisAsEntity), factory(factory) {}

	template<class ComponentType>
	std::shared_ptr<ComponentType> addComponent()
	{
		auto component = factory->create<EntityType, ComponentType>(thisAsEntity);
		components.push_back(component);
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0)
	{
		auto component = factory->create<EntityType, ComponentType, CustomParam0>(thisAsEntity, param0);
		components.push_back(component);
		return component;
	}

protected:
	EntityType *thisAsEntity;
	ComponentFactoryTypePtr factory;
	std::vector<ComponentPtr> components;
};
//
/////////////////////////////////////////////////////////