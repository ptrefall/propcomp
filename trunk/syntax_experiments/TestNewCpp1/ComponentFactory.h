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
	unsigned int getTypeId(const std::string &type);

	template<class ComponentType>
	void registerTypeId()
	{
		internalRegisterTypeId(ComponentType::Type(), Component::getTypeId<ComponentType>());
	}

	template<class ComponentType>
	std::shared_ptr<ComponentType> create()
	{
		return std::make_shared<ComponentType>();
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> create(CustomParam0 param0)
	{
		return std::make_shared<ComponentType>(param0);
	}

protected:
	void internalRegisterTypeId(const std::string &type, unsigned int typeId);
	std::unordered_map<std::string, unsigned int> component_type_ids;
};
//
/////////////////////////////////////////////////////////