
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

	template<typename ComponentType>
	static unsigned int getTypeId()
	{
		static unsigned int id(newPropertyTypeId());
		return id;
	}

protected:
	std::string type;
	unsigned int typeId;
	static unsigned int newPropertyTypeId()
	{
		static unsigned int nextId(0);
		return nextId++;
	}

	template<class ComponentType>
	static std::shared_ptr<ComponentType> InternalCreate()
	{
		return std::make_shared<ComponentType>();
	}

	template<class ComponentType, class CustomParam0>
	static std::shared_ptr<ComponentType> InternalCreate(CustomParam0 param0)
	{
		return std::make_shared<ComponentType>(param0);
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
class ComponentHandler
{
public:
	template<class ComponentType>
	std::shared_ptr<ComponentType> addComponent()
	{
		auto component = ComponentType::Create();
		components.push_back(component);
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent(CustomParam0 param0)
	{
		auto component = ComponentType::Create<CustomParam0>(param0);
		components.push_back(component);
		return component;
	}

protected:
	std::vector<std::shared_ptr<Component>> components;
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
	TestComp(std::shared_ptr<TestSystem> sys) : Component(Type()), sys(sys) { typeId = Component::getTypeId<TestComp>(); }
	static std::string Type() { return "Test"; }
	template<class CustomParam0>
	static std::shared_ptr<TestComp> Create(CustomParam0 param0) { return std::make_shared<TestComp>(param0); }

	void test() { sys->test(); }

private:
	std::shared_ptr<TestSystem> sys;
};
//
/////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////
//
void main()
{
	std::shared_ptr<ComponentHandler> entity = std::make_shared<ComponentHandler>();
	std::shared_ptr<TestSystem> sys = std::make_shared<TestSystem>();
	auto testComp = entity->addComponent<TestComp, std::shared_ptr<TestSystem>>(sys);
	testComp->test();
	system("pause");
}
//
/////////////////////////////////////////////////////////
