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

class ComponentFactory
{
public:
	template<class EntityType, class ComponentType>
	std::shared_ptr<ComponentType> create(EntityType *entity)
	{
		return std::make_shared<ComponentType>(entity);
	}

	template<class EntityType, class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> create(EntityType *entity, CustomParam0 param0)
	{
		return std::make_shared<ComponentType>(entity, param0);
	}

protected:
};
//
/////////////////////////////////////////////////////////