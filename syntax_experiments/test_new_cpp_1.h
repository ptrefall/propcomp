
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <functional>

/////////////////////////////////////////////////////
//
class Component
{
public:
	Component(const std::string &type);
	virtual ~Component();
protected:
	std::string type;
};

Component::Component(const std::string &type)
: type(type)
{
}

Component::~Component()
{
}
//
/////////////////////////////////////////////////////////





/////////////////////////////////////////////////////
//
class ComponentFactory
{
public:
	ComponentFactory() {}
	
	template<class LambdaType>
	void register(const std::string &type, LambdaType lambda)
	{
		functors[type] = lambda;
	}
	
	auto create(const std::string &type) -> decltype(functors[type](type))
	{
		auto component = functors[type](type);
		return component;
	}
	
private:
	std::unordered_map<std::string, std::function> functors;
};
//
/////////////////////////////////////////////////////////





/////////////////////////////////////////////////////
//
class ComponentHandler
{
public:
	ComponentHandler(ComponentFactory &factory) : factory(factory) {}
	
	auto addComponent(const std::string &type) -> decltype(factory.create(type))
	{
		auto component = factory.create(type);
		return component;
	}
private:
	ComponentFactory &factory;
};
//
/////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////
//
class TestSystem
{
public:
	void test() { std::cout << "Testing!" std::endl; }
};

class TestComp : public Component
{
public:
	TestComp(const std::string &type/*, TestSystem &sys*/) /*: sys(sys)*/ { /*sys.test();*/ }
	static std::string getType() { return "Test"; }
	static auto getCreate() -> decltype(create) { return create; }
	
private:
	//TestSystem &sys;
	static auto create = [](const std::string &type) { return std::make_shared<TestComp>(type); } //return shared_ptr... thus no longer needed  to manage new/delete...
};
//
/////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////
//
void main()
{
	ComponentFactory factory;
	factory.register<decltype(TestComp::getCreate())>(TestComp::getType(), TestComp::getCreate());
	ComponentHandler entity(factory);
	auto testComp = entity.addComponent("Test"); //Should return actual TestComp type directly, not Component... 
}
//
/////////////////////////////////////////////////////////
