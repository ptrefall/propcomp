/////////////////////////////////////////////////////
//
#pragma once
#pragma warning(push)
#pragma warning(disable : 4481)

#include "IComponent.h"
#include "PropertyContainer.h"

#include <sigslot.h>
#include <string>
#include <memory>

namespace Totem
{

template<class ComponentType, class PropertyFactoryType = DefaultPropertyFactory>
class Component : public IComponent, public PropertyContainer<PropertyFactoryType>, public sigslot::has_slots<>
{
public:
	Component(const std::string &name) 
		: PropertyContainer<PropertyFactoryType>(), name(name)
	{
		typeId = IComponent::getTypeId<ComponentType>();
		type = IComponent::getType<ComponentType>();
	}

	const std::string &getType() const override { return type; }
	const unsigned int &getTypeId() const override { return typeId; }
	const std::string &getName() const { return name; }
	virtual void update(const float &/*deltaTime*/) {}

	Component &operator= (const Component &rhs)
	{
		if(this == &rhs)
			return *this;

		throw std::runtime_error("Assignment operation between ComponentTypes are not supported!");
	}
	
protected:
	unsigned int typeId;
	std::string type;
	std::string name;
};

} // namespace Totem

#pragma warning(pop)

//
/////////////////////////////////////////////////////////
