/////////////////////////////////////////////////////
//
#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

class Component;
typedef std::shared_ptr<Component> ComponentPtr;
class ComponentFactory;
typedef std::shared_ptr<ComponentFactory> ComponentFactoryPtr;
class Entity;

class ComponentFactory
{
public:
	template<class ComponentType>
	std::shared_ptr<ComponentType> create(Entity *entity, unsigned int optionalParam)
	{
		return std::make_shared<ComponentType>(entity);
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> create(Entity *entity, CustomParam0 param0, unsigned int optionalParam)
	{
		return std::make_shared<ComponentType>(entity, param0);
	}

protected:
};
//
/////////////////////////////////////////////////////////