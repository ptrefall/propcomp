#pragma once

#include "../../../include/Totem/Component.h"
#include "../../../include/Totem/Property.h"
#include "../Common/Entity.h"

#include <memory>

class TestSystem;
typedef std::shared_ptr<TestSystem> TestSystemPtr;

class TestComponent : public Totem::Component<>
{
public:
	TestComponent(const EntityPtr &owner, const std::string &name, const TestSystemPtr &sys);
	static std::string getType() { return "Test"; }
        
	void test();

private:
	void OnSharedPropChanged(const std::string &old_value, const std::string &new_value);
	EntityWPtr owner;
	TestSystemPtr sys;

	void OnSomeEvent();

	Totem::Property<std::string> test_prop;
	Totem::Property<std::string> test_shared_prop;
};