#pragma once

#include "Component.h"
#include "SharedProperty.h"
#include "Entity.h"

class TestSystem;
typedef std::shared_ptr<TestSystem> TestSystemPtr;

class TestComponent : public Component
{
public:
	TestComponent(Entity *owner, TestSystemPtr sys);
	static std::string Type() { return "Test"; }
	void reset(Entity *owner, TestSystemPtr sys);

	void test();

private:
	void OnSharedPropChanged(const std::string &old_value, const std::string &new_value);
	Entity *owner;
	TestSystemPtr sys;

	Property<std::string> test_prop;
	SharedProperty<std::string> test_shared_prop;
};
