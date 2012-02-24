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

template<class ComponentType, class PropertyFactoryType = DefaultPropertyFactory>
class Component : public IComponent<PropertyFactoryType>, public sigslot::has_slots<>
{
public:
	Component(const std::string &name) 
		: name(name)
	{
	}

	const std::string &getName() const override { return name; }

	Component &operator= (const Component &rhs)
	{
		if(this == &rhs)
			return *this;

		throw std::runtime_error("Assignment operation between ComponentTypes are not supported!");
	}
	
protected:
	unsigned int getInternalTypeId() const override { return IComponent::getInternalTypeId<ComponentType>(); }

	std::string name;
};

} // namespace Totem

#pragma warning(pop)

//
/////////////////////////////////////////////////////////
