#pragma once

#include "../Common/Entity.h"
#include "TestComponent.h"

#include <memory>
#include <iostream>
#include <vector>

class TestSystem;
typedef std::shared_ptr<TestSystem> TestSystemPtr;

class TestSystem : public sigslot::has_slots<>
{
public:
	TestSystem() {}
	~TestSystem() { std::cout << "TestSystem destroyed!" << std::endl; }
	void test() { std::cout << "Testing!" << std::endl; }

	void add(std::shared_ptr<Totem::IComponent<PropertyUserData>> component)
	{ 
		components.push_back(component); 
		std::cout << "Added component " << component->getName() << " to Test System!" << std::endl;
	}
	void remove(std::shared_ptr<Totem::IComponent<PropertyUserData>> component)
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			if(components[i].get() == static_cast<TestComponent*>(component.get()))
			{
				std::cout << "Removed component " << component->getName() << " from Test System!" << std::endl;
				components[i] = components.back();
				components.pop_back();
				return;
			}
		}
	}

private:
	std::vector<std::shared_ptr<Totem::IComponent<PropertyUserData>>> components;
};