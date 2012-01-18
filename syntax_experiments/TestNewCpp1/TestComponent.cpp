#include "TestComponent.h"
#include "TestSystem.h"
#include <iostream>

TestComponent::TestComponent(Entity *owner, TotemFactory *factory, TestSystemPtr sys) 
: Totem::Component<TotemFactory>(factory, Type()), owner(owner), sys(sys) 
{
	if(owner && sys)
		reset(owner, sys);
}

void TestComponent::reset(Entity *owner, TestSystemPtr sys)
{
	this->owner = owner;
	this->sys = sys;

	test_prop = addProperty<std::string>("TestProp", "Testing Property");
	test_shared_prop = owner->addSharedProperty<std::string>("TestSharedProp", "Testing Shared Property");
	test_shared_prop.valueChanged().connect(this, &TestComponent::OnSharedPropChanged);
}

void TestComponent::test() 
{ 
	sys->test(); 
}

void TestComponent::OnSharedPropChanged(const std::string &old_value, const std::string &new_value)
{
	std::cout << new_value.c_str() << std::endl;
}
