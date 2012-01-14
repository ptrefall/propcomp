
#include "ComponentHandler.h"
#include "TestSystem.h"
#include "TestComponent.h"
#include <memory>
#include <algorithm>

void main()
{
	//We initialize some systems/managers for the engine here...
	std::shared_ptr<TestSystem> sys = std::make_shared<TestSystem>();

	//Then we make a new entity definition
	std::shared_ptr<ComponentHandler> entity = std::make_shared<ComponentHandler>();
	entity->registerTypeId(TestComponent::Type(), Component::getTypeId<TestComponent>());

	//We have loaded a list of serialized components that belong to this entity we're building
	std::vector<std::string> loaded_component_types;
	loaded_component_types.push_back("Test");

	//We iterate over serialized components and add one by one to the entity
	std::for_each(loaded_component_types.begin(), loaded_component_types.end(), [&](const std::string component_type){
		if(entity->getTypeId(component_type) == Component::getTypeId<TestComponent>())
		{
			auto testComp = entity->addComponent<TestComponent, std::shared_ptr<TestSystem>>(sys);
			testComp->test();
		}
	});
	system("pause");
}
