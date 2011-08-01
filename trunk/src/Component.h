/*Component-based Entity Engine
Copyright (c) 2009 P�l Trefall and Kenneth Gangst�

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

#pragma once

#include "types_config.h"

#include "Entity.h"
#include "Property.h"

class Component HAS_SIGNALSLOTS_INHERITANCE_TYPE
{
public:
	virtual ~Component() {}

	T_String getName() const { return name; }

    virtual void update(F32 deltaTime) {};
	virtual void onEvent(const T_Event &event) {};

	template<class T>Property<T> addProperty(const T_String &propName, const T &defaultValue);
	template<class T>Property<T> getProperty(const T_String &propName);
	void removeProperty(const T_String &propName);

protected:
	Component(Entity &owner, const T_String &name) : owner(owner), name(name) {};

	Entity &owner;
    T_String name;
};

template<class T>
inline Property<T> Component::addProperty(const T_String &propName, const T &defaultValue)
{
	T_String compPropName = name + ":" + propName;
	return owner.addProperty<T>(compPropName, defaultValue);
}

template<class T>
inline Property<T> Component::getProperty(const T_String &propName)
{
	T_String compPropName = name + ":" + propName;
	return owner.getProperty<T>(compPropName);
}

inline void Component::removeProperty(const T_String &propName)
{
	T_String compPropName = name + ":" + propName;
	owner.removeProperty(compPropName);
}