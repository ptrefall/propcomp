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

	template<typename ComponentType>
	static unsigned int getTypeId()
	{
		static unsigned int id(newPropertyTypeId());
		return id;
	}

protected:
	std::string type;
	unsigned int typeId;
	static unsigned int newPropertyTypeId()
	{
		static unsigned int nextId(0);
		return nextId++;
	}
};
//
/////////////////////////////////////////////////////////
