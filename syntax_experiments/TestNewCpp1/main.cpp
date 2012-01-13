
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <memory>

/////////////////////////////////////////////////////
//
class Component
{
public:
	Component(const std::string &type);
	virtual ~Component();

protected:
	std::string type;

	template<class ComponentType>
	static std::shared_ptr<ComponentType> InternalCreate()
	{
		return std::make_shared<ComponentType>();
	}
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
	
	template<class T>
	auto create() -> decltype(T::Create())
	{
		auto component = T::Create();
		return component;
	}
};
//
/////////////////////////////////////////////////////////





/////////////////////////////////////////////////////
//
class ComponentHandler
{
public:
	ComponentHandler(ComponentFactory &factory) : factory(factory) {}
	
	template<class T>
	auto addComponent() -> decltype(T::Create())
	{
		auto component = T::Create();
		return component;
	}
private:
	ComponentFactory &factory;
};
//
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////
//
// USER SPECIFIC CODE FOLLOWING THIS COMMENT
//
/////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//
class TestSystem
{
public:
	void test() { std::cout << "Testing!" << std::endl; }
};

class TestComp : public Component
{
public:
	TestComp() : Component(Type()) {}
	static std::string Type() { return "Test"; }
	static auto Create() -> decltype(Component::InternalCreate<TestComp>()) { return Component::InternalCreate<TestComp>(); }

	void test() { std::cout << "Testing!" << std::endl; }
};
//
/////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////
//
void main()
{
	ComponentFactory factory;
	ComponentHandler entity(factory);
	auto testComp = entity.addComponent<TestComp>();
	testComp->test();
	system("pause");
}
//
/////////////////////////////////////////////////////////
