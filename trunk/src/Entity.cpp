/*Component-based Entity Engine
Copyright (c) 2009 Pål Trefall and Kenneth Gangstø

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Note: Some of the libraries Component-based Entity Engine may link to may have additional
requirements or restrictions.
*/

#include "Entity.h"
#include "Component.h"
#include "ComponentFactory.h"
#include "Property.h"

Entity::Entity(ComponentFactory& componentFactory, const T_String &type, const T_String &name)
: componentFactory(componentFactory), type(type)
{
	if(name.empty())
		this->name = type;
	else
		this->name = name;
}

Entity::~Entity()
{
	for(unsigned int i = 0; i < components.size(); i++)
		delete components[i];
	components.clear();

	removeAllProperties();
}

Component &Entity::addComponent(const T_String& componentType, const T_String& componentName)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component *component = components[i];
		if(componentName.length() == 0)
		{
			if(component->getName() == componentType)
				return *component;
		}
		else
		{
			if(component->getName() == componentName)
				return *component;
		}
	}

	Component* component = componentFactory.createComponent(*this, componentType, componentName);
	components.push_back(component);
	return *component;
}

bool Entity::hasComponent(const T_String& componentName)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component *component = components[i];
		if(component->getName() == componentName)
			return true;
	}
	return false;
}

Component &Entity::getComponent(const T_String& componentName)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component *component = components[i];
		if(component->getName() == componentName)
		{
			return *component;
		}
	}
	throw T_Exception(("Unable to get component " + componentName).c_str());
}

void Entity::updateComponents(F32 deltaTime)
{
	for(unsigned int i = 0; i < components.size(); i++)
		components[i]->update(deltaTime);
}

void Entity::onEvent(const T_Event &event)
{
	for(unsigned int i = 0; i < components.size(); i++)
		components[i]->onEvent(event);
}
