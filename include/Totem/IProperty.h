#pragma once

#include <memory>
#include <string>

namespace Totem
{

class IProperty
{
public:
	virtual const unsigned int &getType() const = 0;
	virtual const std::string &getName() const = 0;
	virtual bool isNull() const = 0;
	virtual bool isDirty() const = 0;
	virtual void clearDirty() = 0;

	template<typename PropertyType>
	static unsigned int getType()
	{
		static unsigned int typeId(typeid(PropertyType).hash_code());
		return typeId;
	}
};

} //namespace Totem

