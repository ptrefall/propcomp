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
	Entity *owner;
	TestSystemPtr sys;

	std::shared_ptr<Property<std::string>> test_prop;
	std::shared_ptr<SharedProperty<std::string>> test_shared_prop;
};
