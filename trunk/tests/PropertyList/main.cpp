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

#include "../Common/Entity.h"
#include <Component.h>
#include <ComponentFactory.h>

#include <iostream>
#include <stdio.h>
#include <time.h>

void printStartup();
void initFactory(ComponentFactory &factory);
void printReady();

class ComponentA : public Component
{
public:
	COMPONENT_0(ComponentA)
	ComponentA(Entity &owner, const T_String &name)
	: Component(owner, name)
	{
		f32_property_list = owner.addPropertyList<F32>("F32List");
		f32_property_list.valueAdded().connect(this, &ComponentA::onValueAdded);
		f32_property_list.valueErased().connect(this, &ComponentA::onValueErased);
	}
	virtual ~ComponentA() {}

private:
	void onValueAdded(const U32 &index, const F32 &newValue)
	{
		std::cout << "Value added to " << f32_property_list.getName().c_str() << " at index " << index << ": " << newValue << std::endl;
	}
	void onValueErased(const U32 &index, const F32 &newValue)
	{
		std::cout << "Value erased from " << f32_property_list.getName().c_str() << " at index " << index << ": " << newValue << std::endl;
	}
	PropertyList<F32> f32_property_list;
};

class ComponentB : public Component
{
public:
	COMPONENT_0(ComponentB)
	ComponentB(Entity &owner, const T_String &name)
	: Component(owner, name)
	{
		f32_property_list = owner.addPropertyList<F32>("F32List");
		f32_property_list.valueChanged().connect(this, &ComponentB::onValueChanged);
		f32_property_list.valuesCleared().connect(this, &ComponentB::onValuesCleared);
	}
	virtual ~ComponentB() {}

private:
	void onValueChanged(const U32 &index, const F32 &oldValue, const F32 &newValue)
	{
		std::cout << "Value changed at index " << index << " in " <<  f32_property_list.getName().c_str() << " from " << oldValue << " to " << newValue << std::endl;
	}
	void onValuesCleared()
	{
		std::cout << "All values in " << f32_property_list.getName().c_str() << " was cleared!" << std::endl;
	}

	PropertyList<F32> f32_property_list;
};

void main()
{
	//Print out some startup text
	printStartup();

	//Create factory and register components
	ComponentFactory factory;
	initFactory(factory);

	std::cout << "Define test Entity..." << std::endl;
	std::cout << "- add ComponentA component" << std::endl;
	std::cout << "- add ComponentB component" << std::endl;

	Entity test = Entity(factory, 0, "Test");
	test.addComponent("ComponentA");
	test.addComponent("ComponentB");

	printReady();

	// When accessing a Property(List) externally from the Entity,
	// it's good practise to check that the property you're about to
	// work on actually exist. Software has living code, that might
	// change several times during it's lifetime, by different developers...
	if(test.hasPropertyList("F32List") == false)
	{
		std::cout << "Couldn't find property list F32List for Entity " << test.getType() << "!" << std::endl;
		system("pause");
		return;
	}

	PropertyList<F32> f32List = test.getPropertyList<F32>("F32List");

	for(U32 i = 0; i < 10; i++)
		f32List.push_back(i*i*0.1f);
	
	std::cout << "Size of F32List is " << f32List.size() << std::endl;

	f32List[0] = 0.5f;
	f32List[1] = 0.2f;

	for(U32 i = 0; i < 5; i++)
		f32List.erase(0);

	std::cout << "Size of F32List is " << f32List.size() << std::endl;

	const F32 &value0 = f32List[0];
	std::cout << "Real value of F32List's index 0 is " << value0 << std::endl;

	f32List.clear();

	if(f32List.empty())
		std::cout << "F32List is empty!" << std::endl;

	system("pause");
}

void printStartup()
{
	std::cout << "Thank you for downloading and testing out the \nComponent-based entities using properties codebase!" << std::endl;
	std::cout << "In this test we'll demonstrate the features of PropertyList." << std::endl;
	std::cout << "\n";
	system("pause");
}

void initFactory(ComponentFactory &factory)
{
	std::cout << "Initialize components..." << std::endl;
	std::cout << "- register ComponentA" << std::endl;
	std::cout << "- register ComponentB" << std::endl;

	ComponentA::RegisterToFactory(factory);
	ComponentB::RegisterToFactory(factory);
}

void printReady()
{
	std::cout << "Initialization done." << std::endl;
	std::cout << "Press any key to start simulation." << std::endl;
	std::cout << "\n";
	system("pause");
}
