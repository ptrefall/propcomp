#pragma once

#include <ComponentHandler.h>
#include <PropertyHandler.h>
#include <PropertyListHandler.h>
#include <EventHandler.h>
#include <DelegateHandler.h>
class Entity :	public ComponentHandler, 
				public PropertyHandler, 
				public PropertyListHandler, 
				public EventHandler,
				public DelegateHandler
{
public:
	Entity(ComponentFactory &factory)
		: ComponentHandler(factory)
	{
	}

	virtual ~Entity() {}
};
