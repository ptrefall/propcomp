#include "TestComponent.h"
#include "TestSystem.h"

#include <iostream>

TestComponent::TestComponent(const EntityPtr &owner, const CL_String &name, const TestSystemPtr &sys) 
: Totem::Component<TestComponent>(name), owner(owner), sys(sys) 
{
	test_prop = add<CL_String>("TestProp", "Testing Property");
	test_shared_prop = owner->add<CL_String>("TestSharedProp", "Testing Shared Property");
	slots.connect(test_shared_prop.valueChanged(), this, &TestComponent::OnSharedPropChanged);
	slots.connect(owner->registerToEvent0("SomeEvent"), this, &TestComponent::OnSomeEvent);
}

void TestComponent::test() 
{ 
	sys->test(); 
}

void TestComponent::OnSharedPropChanged(const CL_String &/*old_value*/, const CL_String &new_value)
{
	if(name != CL_String())
		std::cout << new_value.c_str() << " from " << name.c_str() << std::endl;
	else
		std::cout << new_value.c_str() << std::endl;
}

void TestComponent::OnSomeEvent()
{
	std::cout << "Some Event Fired for " << name.c_str() << "!" << std::endl;
}
