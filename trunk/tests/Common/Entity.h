#pragma once

#include <ComponentHandler.h>
#include <PropertyHandler.h>
#include <PropertyListHandler.h>
#include <EventHandler.h>
class Entity :	public ComponentHandler, 
				public PropertyHandler, 
				public PropertyListHandler, 
				public EventHandler
{
public:
	Entity(ComponentFactory &factory, const T_EntityId &id, const T_String &type)
		: ComponentHandler(factory)
	{
		id_property = addProperty<T_EntityId>("Id", id, true); //read-only
        type_property = addProperty<T_String>("Type", type, true); //read-only
	}

	virtual ~Entity() {}

	const T_EntityId &getId() const { return id_property.get(); }
	const T_String &getType() const { return type_property.get(); }

private:
    Property<T_String> type_property;
    Property<T_EntityId> id_property;
};
