/////////////////////////////////////////////////////
//
#pragma once

#include <string>
#include <memory>
#include "../../depends/Standard/sigslot.h"
#include "PropertyContainer.h"

namespace Totem
{

template<class TotemFactoryType>
class Component : public PropertyContainer<TotemFactoryType>, public sigslot::has_slots<>
{
public:
	Component(TotemFactoryType *factory, const std::string &type) : PropertyContainer<TotemFactoryType>(factory), type(type) {}

	const std::string &getType() const { return type; }
	
protected:
	std::string type;
};

} // namespace Totem

//
/////////////////////////////////////////////////////////
