
#include "ComponentContainer.h"
#include "PoolComponentFactory.h"
#include "TestSystem.h"
#include "TestComponent.h"
#include "Entity.h"
#include <memory>
#include <algorithm>
#include <iostream>

void main()
{
	//We initialize some systems/managers for the engine here...
	TestSystemPtr sys = std::make_shared<TestSystem>();

	//Set up the component factory that pools resources
	PoolComponentFactoryPtr pool_factory = std::make_shared<PoolComponentFactory>();
	pool_factory->pool<Entity, TestComponent, TestSystemPtr>(2, nullptr, nullptr);

	std::shared_ptr<Entity> entity = std::make_shared<Entity>(pool_factory);

	//We have loaded a list of serialized components that belong to this entity we're building
	std::vector<std::string> loaded_component_types;
	loaded_component_types.push_back("Test");

	//We iterate over serialized components and add one by one to the entity
	std::for_each(loaded_component_types.begin(), loaded_component_types.end(), [&](const std::string &component_type){
		if(component_type == TestComponent::Type())
		{
			auto testComp = entity->addComponent<TestComponent, TestSystemPtr>(sys);
			testComp->test();
			auto test_prop = testComp->getProperty<std::string>("TestProp");
			std::cout << test_prop->get().c_str() << std::endl;
			auto test_shared_prop = entity->getSharedProperty<std::string>("TestSharedProp");
			std::cout << test_shared_prop->get().c_str() << std::endl;
		}
	});
	system("pause");
}
