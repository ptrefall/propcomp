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
	
protected:
	std::string type;
};

} // namespace Totem

//
/////////////////////////////////////////////////////////
