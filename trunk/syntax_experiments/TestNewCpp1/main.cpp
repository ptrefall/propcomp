
#include "ComponentContainer.h"
#include "TestSystem.h"
#include "TestComponent.h"
#include "Entity.h"
#include <memory>
#include <algorithm>
#include <iostream>

class ListCallback : public sigslot::has_slots<>
{
public:
	void onValueAddedToList(const unsigned int &index, const int &newValue)
	{
		std::cout << "Added value " << newValue << " at index " << index << std::endl;
	}
	void onValueErasedFromList(const unsigned int &index, const int &valueErased)
	{
		std::cout << "Erased value " << valueErased << " from index " << index << std::endl;
	}
	void onValuesClearedFromList()
	{
		std::cout << "Values cleared!" << std::endl;
	}
};

void main()
{
	//We initialize some systems/managers for the engine here...
	TestSystemPtr sys = std::make_shared<TestSystem>();

	EntityPtr entity = std::make_shared<Entity>();

	//We have loaded a list of serialized components that belong to this entity we're building
	std::vector<std::string> loaded_component_types;
	loaded_component_types.push_back("Test");

	//We iterate over serialized components and add one by one to the entity
	std::for_each(loaded_component_types.begin(), loaded_component_types.end(), [&](const std::string &component_type){
		if(component_type == TestComponent::Type())
		{
			auto testComp = entity->addComponent1<TestComponent, TestSystemPtr>(sys, "Test1");
			auto testComp2 = entity->addComponent1<TestComponent, TestSystemPtr>(sys, "Test2");
			
			testComp->test();
			testComp2->test();
			
			auto test_prop = testComp->getProperty<std::string>("TestProp");
			std::cout << test_prop.get() << " from " << testComp->getName() << std::endl;
			auto test_prop2 = testComp2->getProperty<std::string>("TestProp");
			std::cout << test_prop2.get() << " from " << testComp2->getName() << std::endl;
			
			auto test_shared_prop = entity->getSharedProperty<std::string>("TestSharedProp");
			std::cout << test_shared_prop.get() << std::endl;
			test_shared_prop = "Test Shared Property Value Changed";
		}
	});

	auto list = entity->addSharedPropertyList<int>("TestList");

	ListCallback listCallback;
	list.valueAdded().connect(&listCallback, &ListCallback::onValueAddedToList);
	list.valueErased().connect(&listCallback, &ListCallback::onValueErasedFromList);
	list.valuesCleared().connect(&listCallback, &ListCallback::onValuesClearedFromList);
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.erase(1);
	list.erase(1);
	list.clear();

	system("pause");
}
