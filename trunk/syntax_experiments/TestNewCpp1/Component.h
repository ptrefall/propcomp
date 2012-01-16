/////////////////////////////////////////////////////
//
#pragma once

#include <string>
#include <memory>
#include "PropertyContainer.h"

class Component;
typedef std::shared_ptr<Component> ComponentPtr;

class Component : public PropertyContainer<>
{
public:
	Component(const std::string &type) : PropertyContainer<>(), type(type) {}

	const std::string &getType() const { return type; }

protected:
	std::string type;
};
//
/////////////////////////////////////////////////////////
