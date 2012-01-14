#include "ComponentFactory.h"

void ComponentFactory::registerTypeId(const std::string &type, unsigned int typeId)
{
	component_type_ids[type] = typeId;
}

unsigned int ComponentFactory::getTypeId(const std::string &type)
{
	auto it = component_type_ids.find(type);
	if(it == component_type_ids.end())
		 return 0;
	else
		return it->second;
}
