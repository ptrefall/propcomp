#pragma once

#include <memory>

class TestSystem;
typedef std::shared_ptr<TestSystem> TestSystemPtr;

class TestSystem
{
public:
	TestSystem();
	void test();
};
