
#include "ComponentHandler.h"
#include "TestSystem.h"
#include "TestComponent.h"
#include <memory>

void main()
{
	std::shared_ptr<ComponentHandler> entity = std::make_shared<ComponentHandler>();
	std::shared_ptr<TestSystem> sys = std::make_shared<TestSystem>();
	auto testComp = entity->addComponent<TestComponent, std::shared_ptr<TestSystem>>(sys);
	testComp->test();
	system("pause");
}
