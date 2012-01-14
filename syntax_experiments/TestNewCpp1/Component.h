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

	template<class ComponentType>
	static ComponentPtr InternalCreate()
	{
		return std::make_shared<ComponentType>();
	}

	template<class ComponentType, class CustomParam0>
	static ComponentPtr InternalCreate(CustomParam0 param0)
	{
		return std::make_shared<ComponentType>(param0);
	}
};
//
/////////////////////////////////////////////////////////