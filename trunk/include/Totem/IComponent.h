#pragma once

#include <memory>
#include <string>

namespace Totem
{

class IComponent
{
public:
	virtual const unsigned int &getTypeId() const = 0;
	virtual const std::string &getType() const = 0;
	virtual const std::string &getName() const = 0;

	template<typename ComponentType>
	static const unsigned int &getTypeId()
	{
		static unsigned int typeId(typeid(ComponentType).hash_code());
		return typeId;
	}

	template<typename ComponentType>
	static const std::string &getType()
	{
		static std::string type;
		if(type.empty())
		{
			std::string temp_type(typeid(ComponentType).name());
			type = temp_type.substr(6, temp_type.size());
		}
		return type;
	}
};

} //namespace Totem

