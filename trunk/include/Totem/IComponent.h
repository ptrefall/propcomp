#pragma once

#include "PropertyContainer.h"

#include <memory>
#include <string>

namespace Totem
{

template<class PropertyFactoryType = DefaultPropertyFactory>
class IComponent : public PropertyContainer<PropertyFactoryType>
{
public:
	IComponent() : PropertyContainer<PropertyFactoryType>() {}
	virtual const std::string &getName() const = 0;
	virtual void update(const float &/*deltaTime*/) {}

	template<typename ComponentType>
	static bool isType(std::shared_ptr<IComponent<PropertyFactoryType>> component)
	{
		return (component->getInternalTypeId() == getInternalTypeId<ComponentType());
	}

	template<typename ComponentType>
	static void checkDuplicationAndAddName(const std::string &name)
	{
		static std::vector<std::string> names;
		for(unsigned int i = 0; i < names.size(); i++)
			if(names[i] == name)
				throw std::runtime_error("Component name duplication with name " + name);
		names.push_back(name);
	}

protected:
	virtual unsigned int getInternalTypeId() const = 0;

	template<typename ComponentType>
	static const unsigned int &getInternalTypeId()
	{
		static unsigned int typeId(typeid(ComponentType).hash_code());
		return typeId;
	}
};

} //namespace Totem

