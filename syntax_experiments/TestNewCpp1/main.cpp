
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
class ComponentFactory
{
public:
	ComponentFactory() {}
	
	template<class ComponenType>
	auto create() -> decltype(ComponenType::Create())
	{
		auto component = ComponenType::Create();
		return component;
	}

	template<class ComponenType, class CustomParam0>
	auto create() -> decltype(ComponenType::Create())
	{
		auto component = ComponenType::Create();
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
	
	/*auto addComponent(const std::string &type) -> std::shared_ptr<Component>
	{
		auto compFuncIt = components.find(type);
		if(compFuncIt == components.end())
			throw std::runtime_error("Component type not found!");
		const unsigned int &typeId = compFuncIt->second;
		if(typeId == Component::getTypeId<TestComp>())
			return TestComp::Create();

		throw std::runtime_error("Component type not found!");
	}*/

	template<class ComponenType>
	auto addComponent() -> decltype(ComponentType::Create())
	{
		auto component = ComponentType::Create();
		return component;
	}

	template<class ComponentType, class CustomParam0>
	std::shared_ptr<ComponentType> addComponent1(CustomParam0 param0)
	{
		auto component = ComponentType::Create<CustomParam0>(param0);
		return component;
	}
private:
	ComponentFactory &factory;
	//std::unordered_map<std::string, unsigned int> components;
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
	TestComp(TestSystem &sys) : Component(Type()), sys(sys) { typeId = Component::getTypeId<TestComp>(); }
	static std::string Type() { return "Test"; }
	template<class CustomParam0>
	static std::shared_ptr<TestComp> Create(CustomParam0 param0) { return std::make_shared<TestComp>(param0); }

	void test() { sys.test(); }

private:
	TestSystem &sys;
};
//
/////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////
//
void main()
{
	ComponentFactory factory;
	ComponentHandler entity(factory);
	TestSystem sys;
	auto testComp = entity.addComponent1<TestComp, TestSystem&>(sys);
	testComp->test();
	system("pause");
}
//
/////////////////////////////////////////////////////////
