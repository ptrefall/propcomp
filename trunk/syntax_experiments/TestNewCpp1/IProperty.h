#pragma once

#include <memory>
#include <string>

namespace Totem
{

class IPropertySerializer;
typedef std::shared_ptr<IPropertySerializer> IPropertySerializerPtr;

class IProperty
{
public:
	virtual const unsigned int &getType() const = 0;
	virtual const std::string &getName() const = 0;
	virtual bool isNull() const = 0;

	template<typename PropertyType>
	static unsigned int getType()
	{
		static unsigned int typeId(newPropertyTypeId());
		return typeId;
	}

private:
	static unsigned int newPropertyTypeId()
	{
		static unsigned int next_id(0);
		return next_id++;
	}
};

} //namespace Totem

