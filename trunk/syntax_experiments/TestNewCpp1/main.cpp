
#include "ComponentContainer.h"
#include "PoolComponentFactory.h"
#include "ComponentFactory.h"
#include "TestSystem.h"
#include "TestComponent.h"
#include <memory>
#include <algorithm>

void main()
{
	//We initialize some systems/managers for the engine here...
	TestSystemPtr sys = std::make_shared<TestSystem>();

	//Set up the component factory that pools resources
	PoolComponentFactoryPtr pool_factory = std::make_shared<PoolComponentFactory>();
	pool_factory->pool<TestComponent, TestSystemPtr>(2, nullptr);

	//Set up an ordinary component factory
	ComponentFactoryPtr factory = std::make_shared<ComponentFactory>();


	//Then we make a new entity definition that uses pooled component factory
	std::shared_ptr<ComponentContainer<PoolComponentFactoryPtr>> entity = std::make_shared<ComponentContainer<PoolComponentFactoryPtr>>(pool_factory);

	//And another entity that uses an ordinary component factory
	std::shared_ptr<ComponentContainer<ComponentFactoryPtr>> entity2 = std::make_shared<ComponentContainer<ComponentFactoryPtr>>(factory);

	//We have loaded a list of serialized components that belong to this entity we're building
	std::vector<std::string> loaded_component_types;
	loaded_component_types.push_back("Test");

	//We iterate over serialized components and add one by one to the entity
	std::for_each(loaded_component_types.begin(), loaded_component_types.end(), [&](const std::string &component_type){
		if(component_type == TestComponent::Type())
		{
			auto testComp = entity->addComponent<TestComponent, TestSystemPtr>(sys);
			testComp->test();

			auto testComp2 = entity2->addComponent<TestComponent, TestSystemPtr>(sys);
			testComp2->test();
		}
	});
	system("pause");
}
