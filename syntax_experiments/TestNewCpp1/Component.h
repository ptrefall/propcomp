/////////////////////////////////////////////////////
//
#pragma once

#include <string>
#include <memory>

class Component;
typedef std::shared_ptr<Component> ComponentPtr;

class Component
{
public:
	Component(const std::string &type);
	virtual ~Component();

	const std::string &getType() const { return type; }

protected:
	std::string type;
};
//
/////////////////////////////////////////////////////////
