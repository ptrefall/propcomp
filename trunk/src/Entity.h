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
	Entity(ComponentFactory &factory)
		: ComponentHandler(factory)
	{
	}

	virtual ~Entity() {}
};
