#pragma once

#include "Component.h"

class TestSystem;
typedef std::shared_ptr<TestSystem> TestSystemPtr;

class TestComponent : public Component
{
public:
	TestComponent(TestSystemPtr sys);
	static std::string Type() { return "Test"; }

	void test();

private:
	TestSystemPtr sys;
};
