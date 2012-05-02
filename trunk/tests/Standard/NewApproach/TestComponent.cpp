#include "TestComponent.h"
#include "TestSystem.h"

#include <iostream>

TestComponent::TestComponent(const EntityWPtr &owner, const std::string &name, const TestSystemPtr &sys) 
: Totem::Component<TestComponent, PropertyUserData>(name), owner(owner), sys(sys) 
{
	user_data.entity = owner;
	user_data.component = this;

	test_prop = add<std::string>("TestProp", "Testing Property", user_data);
	test_shared_prop = owner.lock()->add<std::string>("TestSharedProp", "Testing Shared Property", user_data);
	test_shared_prop.valueChanged().connect(this, &TestComponent::OnSharedPropChanged);

	owner.lock()->registerToEvent0("SomeEvent").connect(this, &TestComponent::OnSomeEvent);
}

TestComponent::~TestComponent()
{
	std::cout << "Component " << name << "destructed!" << std::endl;
}

void TestComponent::initialize()
{
	//Register with TestSystem
	sys->add(shared_from_this());
	this->removed().connect(sys.get(), &TestSystem::remove);
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
