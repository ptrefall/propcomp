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
	~TestSystem() { std::cout << "TestSystem is being destroyed!" << std::endl; }
	void test() { std::cout << "Testing!" << std::endl; }

	void add(TestComponent *component)
	{ 
		components.push_back(component); 
		std::cout << "Added component " << component->getName() << " to Test System!" << std::endl;
	}
	void remove(TestComponent *component)
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			if(components[i] == static_cast<TestComponent*>(component))
			{
				std::cout << "Removed component " << component->getName() << " from Test System!" << std::endl;
				components[i] = components.back();
				components.pop_back();
				return;
			}
		}
	}

private:
	std::vector<TestComponent*> components;
};