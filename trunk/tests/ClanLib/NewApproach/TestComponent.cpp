#include "TestComponent.h"
#include "TestSystem.h"

#include <iostream>

TestComponent::TestComponent(const CL_String &name, EntityPtr owner, TestSystemPtr sys) 
: Totem::Component<>(Type(), name), owner(owner), sys(sys) 
{
	test_prop = add<CL_String>("TestProp", "Testing Property");
	test_shared_prop = owner->add<CL_String>("TestSharedProp", "Testing Shared Property");
	sharedPropChangedSlot = test_shared_prop.valueChanged().connect(this, &TestComponent::OnSharedPropChanged);
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