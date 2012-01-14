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
	void registerTypeId(const std::string &type, unsigned int typeId);
	unsigned int getTypeId(const std::string &type);

protected:
	std::unordered_map<std::string, unsigned int> component_type_ids;
};
//
/////////////////////////////////////////////////////////