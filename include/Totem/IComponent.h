#pragma once

#include "PropertyContainer.h"

#include <memory>
#include <string>

namespace Totem
{

template<class UserData = void*>
class IComponent : public PropertyContainer<UserData>
{
public:
	IComponent() {}
	virtual ~IComponent() {}
	virtual const std::string &getName() const = 0;
	virtual void update(float /*elapsedTime*/) {}

	template<typename ComponentType>
	static bool isType(const std::shared_ptr<IComponent> &component)
	{
		return (component->getRuntimeTypeId() == getRuntimeTypeId<ComponentType>());
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

