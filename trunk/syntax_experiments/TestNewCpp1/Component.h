/////////////////////////////////////////////////////
//
#pragma once

#include <string>
#include <memory>
#include "../../depends/Standard/sigslot.h"
#include "PropertyContainer.h"

namespace Totem
{

template<class PropertyFactoryType = DefaultPropertyFactory>
class Component : public PropertyContainer<PropertyFactoryType>, public sigslot::has_slots<>
{
public:
	Component(const std::string &type) : PropertyContainer<PropertyFactoryType>(), type(type) {}

	const std::string &getType() const { return type; }

	virtual void update(const float &/*deltaTime*/) {}

	Component &operator= (const Component &rhs)
	{
		if(this == &rhs)
			return *this;

		throw std::runtime_error("Assignment operation between ComponentTypes are not supported!");
	}
	
protected:
	std::string type;
};

} // namespace Totem

//
/////////////////////////////////////////////////////////
