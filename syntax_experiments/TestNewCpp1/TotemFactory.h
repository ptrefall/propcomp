/////////////////////////////////////////////////////
//
#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "SharedProperty.h"
#include "Property.h"

class Component;
typedef std::shared_ptr<Component> ComponentPtr;
class TotemFactory;
typedef std::shared_ptr<TotemFactory> TotemFactoryPtr;
class Entity;

class TotemFactory
{
public:
	template<class ComponentType>
	std::shared_ptr<ComponentType> createComponent(Entity *entity, unsigned int optionalParam)
	{
		return std::make_shared<ComponentType>(entity, this);
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> createComponent(Entity *entity, CustomParam0 param0, unsigned int optionalParam)
	{
		return std::make_shared<ComponentType>(entity, this, param0);
	}

	template<class PropertyType>
	std::shared_ptr<Totem::SharedProperty<PropertyType>> createSharedProperty(const std::string &name)
	{
		return std::make_shared<Totem::SharedProperty<PropertyType>>(name);
	}

	template<class PropertyType>
	std::shared_ptr<Totem::Property<PropertyType>> createProperty(const std::string &name)
	{
		return std::make_shared<Totem::Property<PropertyType>>(name);
	}

protected:
};
//
/////////////////////////////////////////////////////////