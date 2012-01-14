/////////////////////////////////////////////////////
//
#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

class Component;

class ComponentHandler
{
public:
	void registerTypeId(const std::string &type, unsigned int typeId);
	unsigned int getTypeId(const std::string &type);

	template<class ComponentType>
	std::shared_ptr<ComponentType> addComponent()
	{
		auto component = ComponentType::Create();
		components.push_back(component);
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0)
	{
		auto component = ComponentType::Create<CustomParam0>(param0);
		components.push_back(component);
		return component;
	}

protected:
	std::vector<std::shared_ptr<Component>> components;
	std::unordered_map<std::string, unsigned int> component_type_ids;
};
//
/////////////////////////////////////////////////////////