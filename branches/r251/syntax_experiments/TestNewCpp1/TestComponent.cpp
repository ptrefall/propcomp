#include "TestComponent.h"
#include "TestSystem.h"
#include <iostream>

TestComponent::TestComponent(const std::string &name, Entity *owner, TestSystemPtr sys) 
: Totem::Component<>(Type(), name), owner(owner), sys(sys) 
{
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
	if(name != std::string())
		std::cout << new_value << " from " << name << std::endl;
	else
		std::cout << new_value << std::endl;
}
