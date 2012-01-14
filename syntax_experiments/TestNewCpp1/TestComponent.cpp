#include "TestComponent.h"
#include "TestSystem.h"

TestComponent::TestComponent(std::shared_ptr<TestSystem> sys) 
: Component(Type()), sys(sys) 
{ 
	typeId = Component::getTypeId<TestComponent>(); 
}

void TestComponent::test() 
{ 
	sys->test(); 
}
