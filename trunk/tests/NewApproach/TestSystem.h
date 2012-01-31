#pragma once

#include <memory>
#include <iostream>

class TestSystem;
typedef std::shared_ptr<TestSystem> TestSystemPtr;

class TestSystem
{
public:
	TestSystem() {}
	void test() { std::cout << "Testing!" << std::endl; }
};