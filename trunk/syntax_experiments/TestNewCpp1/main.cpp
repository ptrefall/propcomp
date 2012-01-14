
#include "ComponentHandler.h"
#include "PoolComponentFactory.h"
#include "TestSystem.h"
#include "TestComponent.h"
#include <memory>
#include <algorithm>

void main()
{
	//We initialize some systems/managers for the engine here...
	TestSystemPtr sys = std::make_shared<TestSystem>();

	//Set up the component factory
	PoolComponentFactoryPtr factory = std::make_shared<PoolComponentFactory>();
	factory->registerTypeId<TestComponent>();
	factory->pool<TestComponent, TestSystemPtr>(2, nullptr);

	//Then we make a new entity definition
	std::shared_ptr<ComponentHandler<PoolComponentFactoryPtr>> entity = std::make_shared<ComponentHandler<PoolComponentFactoryPtr>>(factory);

	//We have loaded a list of serialized components that belong to this entity we're building
	std::vector<std::string> loaded_component_types;
	loaded_component_types.push_back("Test");

	//We iterate over serialized components and add one by one to the entity
	std::for_each(loaded_component_types.begin(), loaded_component_types.end(), [&](const std::string &component_type){
		if(factory->getTypeId(component_type) == Component::getTypeId<TestComponent>())
		{
			auto testComp = entity->addComponent<TestComponent, TestSystemPtr>(sys);
			testComp->test();
		}
	});
	system("pause");
}
