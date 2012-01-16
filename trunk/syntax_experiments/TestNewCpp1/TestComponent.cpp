#include "TestComponent.h"
#include "TestSystem.h"

TestComponent::TestComponent(Entity *owner, TestSystemPtr sys) 
: Component(Type()), owner(owner), sys(sys) 
{ 
}

void TestComponent::reset(Entity *owner, TestSystemPtr sys)
{
	this->owner = owner;
	this->sys = sys;

	test_prop = addProperty<std::string>("TestProp", "Testing Property");
	test_shared_prop = owner->addSharedProperty<std::string>("TestSharedProp", "Testing Shared Property");
}

void TestComponent::test() 
{ 
	sys->test(); 
}
