#include "TestComponent.h"
#include "TestSystem.h"

#include <iostream>

TestComponent::TestComponent(const EntityPtr &owner, const std::string &name, const TestSystemPtr &sys) 
: Totem::Component<TestComponent>(name), owner(owner), sys(sys) 
{
	test_prop = add<std::string>("TestProp", "Testing Property");
	test_shared_prop = owner->add<std::string>("TestSharedProp", "Testing Shared Property");
	test_shared_prop.valueChanged().connect(this, &TestComponent::OnSharedPropChanged);

	owner->registerToEvent0("SomeEvent").connect(this, &TestComponent::OnSomeEvent);
}

void TestComponent::test() 
{ 
	sys->test(); 
}

void TestComponent::OnSharedPropChanged(const std::string &/*old_value*/, const std::string &new_value)
{
	if(name != std::string())
		std::cout << new_value << " from " << name << std::endl;
	else
		std::cout << new_value << std::endl;
}

void TestComponent::OnSomeEvent()
{
	std::cout << "Some Event Fired " << name.c_str() << "!" << std::endl;
}
