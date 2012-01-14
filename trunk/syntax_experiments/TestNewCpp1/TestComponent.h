#pragma once

#include "Component.h"

class TestSystem;

class TestComponent : public Component
{
public:
	TestComponent(std::shared_ptr<TestSystem> sys);
	static std::string Type() { return "Test"; }
	
	template<class CustomParam0>
	static std::shared_ptr<TestComponent> Create(CustomParam0 param0) { return std::make_shared<TestComponent>(param0); }

	void test();

private:
	std::shared_ptr<TestSystem> sys;
};
