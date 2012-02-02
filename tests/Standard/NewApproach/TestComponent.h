#pragma once

#include "../../../include/Totem/Component.h"
#include "../../../include/Totem/SharedProperty.h"
#include "../Common/Entity.h"

#include <memory>

class TestSystem;
typedef std::shared_ptr<TestSystem> TestSystemPtr;

class TestComponent : public Totem::Component<>
{
public:
	TestComponent(const std::string &name, EntityPtr owner, TestSystemPtr sys);
	static std::string Type() { return "Test"; }
        
	void test();

private:
	void OnSharedPropChanged(const std::string &old_value, const std::string &new_value);
	EntityPtr owner;
	TestSystemPtr sys;

	Totem::Property<std::string> test_prop;
	Totem::SharedProperty<std::string> test_shared_prop;
};