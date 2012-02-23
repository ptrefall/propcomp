#pragma once

#include <memory>
#include <string>

namespace Totem
{

class IProperty
{
public:
	virtual const unsigned int &getTypeId() const = 0;
	virtual const std::string &getName() const = 0;
	virtual bool isNull() const = 0;
	virtual bool isDirty() const = 0;
	virtual void clearDirty() = 0;

	template<typename PropertyType>
	static const unsigned int &getTypeId()
	{
		static unsigned int typeId(typeid(PropertyType).hash_code());
		return typeId;
	}

	template<typename PropertyType>
	static const std::string &getType()
	{
		static std::string type;
		if(type.empty())
		{
			std::string temp_type(typeid(PropertyType).name());
			if(temp_type.find("class ") != std::string::npos)
				type = temp_type.substr(6, temp_type.size());
			else if(temp_type.find("struct ") != std::string::npos)
				type = temp_type.substr(7, temp_type.size());
			else
				type = temp_type;
		}
		return type;
	}
};

} //namespace Totem

