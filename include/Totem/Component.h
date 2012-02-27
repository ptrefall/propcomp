/////////////////////////////////////////////////////
//
#pragma once
#pragma warning(push)
#pragma warning(disable : 4481)

#include "IComponent.h"

#include <sigslot.h>
#include <string>
#include <memory>

namespace Totem
{

template<class ComponentType, class UserData = void*>
class Component : public IComponent<UserData>, public sigslot::has_slots<>
{
public:
	Component(const std::string &name) 
		: name(name)
	{
	}

	static bool isType(std::shared_ptr<IComponent> component)
	{
		return (component->getRuntimeTypeId() == getRuntimeTypeId<ComponentType());
	}

	unsigned int getRuntimeTypeId() const override { return IComponent::getRuntimeTypeId<ComponentType>(); }
	const std::string &getName() const override { return name; }

	Component &operator= (const Component &rhs)
	{
		if(this == &rhs)
			return *this;

		throw std::runtime_error("Assignment operation between ComponentTypes are not supported!");
	}
	
protected:
	std::string name;
};

} // namespace Totem

#pragma warning(pop)

//
/////////////////////////////////////////////////////////
