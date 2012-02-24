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

	virtual unsigned int getRuntimeTypeId() const = 0;

	template<typename ComponentType>
	static unsigned int getRuntimeTypeId()
	{
		static unsigned int typeId(typeid(ComponentType).hash_code());
		return typeId;
	}
};

} //namespace Totem

