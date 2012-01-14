#include "TestComponent.h"
#include "TestSystem.h"

TestComponent::TestComponent(TestSystemPtr sys) 
: Component(Type()), sys(sys) 
{ 
}

void TestComponent::reset(TestSystemPtr sys)
{
	this->sys = sys;
}

void TestComponent::test() 
{ 
	sys->test(); 
}
