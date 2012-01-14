/////////////////////////////////////////////////////
//
#pragma once

#include "ComponentFactory.h"
#include <memory>
#include <vector>
#include <unordered_map>

class Component;
typedef std::shared_ptr<Component> ComponentPtr;
class ComponentHandler;
typedef std::shared_ptr<ComponentHandler> ComponentHandlerPtr;

class ComponentHandler
{
public:
	ComponentHandler(ComponentFactoryPtr factory);

	template<class ComponentType>
	std::shared_ptr<ComponentType> addComponent()
	{
		auto component = factory->create<ComponentType>();
		components.push_back(component);
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0)
	{
		auto component = factory->create<ComponentType, CustomParam0>(param0);
		components.push_back(component);
		return component;
	}

protected:
	ComponentFactoryPtr factory;
	std::vector<ComponentPtr> components;
};
//
/////////////////////////////////////////////////////////