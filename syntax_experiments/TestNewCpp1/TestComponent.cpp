#include "TestComponent.h"
#include "TestSystem.h"

TestComponent::TestComponent(TestSystemPtr sys) 
: Component(Type()), sys(sys) 
{ 
	typeId = Component::getTypeId<TestComponent>(); 
}

void TestComponent::test() 
{ 
	sys->test(); 
}
