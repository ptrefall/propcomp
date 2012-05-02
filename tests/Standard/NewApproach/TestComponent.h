#pragma once

#include "../../../include/Totem/Component.h"
#include "../../../include/Totem/Property.h"
#include "../Common/Entity.h"

#include <memory>

class TestSystem;
typedef std::shared_ptr<TestSystem> TestSystemPtr;

class TestComponent : public Totem::Component<TestComponent, PropertyUserData>
{
public:
	TestComponent(const EntityWPtr &owner, const std::string &name, const TestSystemPtr &sys);
    virtual ~TestComponent();
	void initialize();
	void test();

private:
	void OnSharedPropChanged(const std::string &old_value, const std::string &new_value);
	EntityWPtr owner;
	TestSystemPtr sys;

	void OnSomeEvent();

	PropertyUserData user_data;
	Totem::Property<std::string> test_prop;
	Totem::Property<std::string> test_shared_prop;
};