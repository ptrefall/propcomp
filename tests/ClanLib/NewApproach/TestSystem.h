#pragma once
#include <ClanLib\core.h>

#include <iostream>

class TestSystem;
typedef CL_SharedPtr<TestSystem> TestSystemPtr;

class TestSystem
{
public:
	TestSystem() {}
	void test() { std::cout << "Testing!" << std::endl; }
};