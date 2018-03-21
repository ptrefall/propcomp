Totem EDK - a component based entity system using shared properties
Totem is an Entity Development Kit designed from the idea of writing an intuitive API for Entity behavior and property definition through aggregation. An Entity consist of multiple components that defines it's behavior, while referencing necessary properties of the Entity required for each behavior to function.

The approach originated from the realization that the most common relationship between components in an Entity, is the requirement to either read from or write to the same properties of an Entity, and the search for how to 100% decouple this relationship between components and at the same time avoid duplication of properties.

And so the Totem EDK was born. Properties add some extra logic on top of the data they represent, like a valueChanged signal that slots can be registered to. Thus several components can "react" when a property is changed in some component, or from outside the Entity system.

This adds a clean flow of events in the system, much more intuitive than in systems where the components own the properties, and where other components that need access to that data either has to go through an event pipeline chain, or through direct coupling with other components.

The realization is highly logical. A component simply reference the properties that exist in the Entity they belong to. Whether multiple components require access to the same property is irrelevant for the existence of each individual component of behavior.

What is a component based entity system?
A component based entity system is an entity system that relies on aggregation instead of inheritance to define entities. The most commonly referred to thorough explanation of component based entity systems in general can be found here: * http://cowboyprogramming.com/2007/01/05/evolve-your-heirachy/

#Overview
Open Source MIT license
No coupling between components.
No duplicate data.
No 3rd party dependencies
Comes bundled with three different type definition options
C++0x
Boost
ClanLib
Property, advanced data storage/management.
Properties support value changed signal.
Often used for components to react to each other's actions without knowing about each other.
PropertyData exist in a shared-pointer, Pimpl'ed by Property.
Properties are owned by Entity, referenced by Components.
No list lookups at runtime.
PropertyList, advanced list-data storage/management.
PropertyList support value added, value erased and values cleaned signals.
Can be used by components to react to changes occurring in a list in some other component.
PropertyListData exist in a shared-pointer, Pimpl'ed by PropertyList.
Optionally treats bool as a special case (due to std::vector bool implementation).
Event System
Registration based (Signal/Slots).
String Ids using string hashing for optimal look-up performance.
The "Any" implementation supports scheduled/delayed events.
Template implementation also provided.
Delegates
Can return value.
Registration based.
String Ids using string hashing for optimal look-up performance.
Support custom types to be inserted into component constructor typesafely via ComponentFactory.
Serialization
Property Serialization interface that's simple to overload with custom types
Totem comes bundled with a serializer for basic C++ types.
New in Version 2.0
No 3rd party dependencies
CMake project generation script
PropertyList
Registration-based Event System using signal/slots
Scheduled events
Registration-based Delegate System
Hashed string id's (unsigned int vs string compare)
Support custom types to be inserted into component constructor typesafely via ComponentFactory.
Serialization system that's easy to overload and extend.
Cleaned up classes and inheritance reduction
Less use of virtuals
Doxygen documentation in headers
Support for multiple component factories
New and improved examples
What does it look like?
Component
``` class TestComp : public Component { public: TestComp(Entity &owner, const T_String &name) : Component(owner, name), testEventId("TEST_EVT") { test_property = owner.addProperty("TestProp", "This is a test"); test_property.valueChanged().connect(this, &TestComp::onTestPropertyChanged); owner.registerToEvent1(testEventId).connect(this, &TestComp::onTestEvent); }

//This is optional virtual void update(float dt) overload { printf("Do something at %d", dt); }

//Preprocessor will add static functions: //Type(), Create(Entity&, const T_String &) and RegisterToFactory(ComponentFactory &) //to this component implementation. COMPONENT_0(TestComp)

private: Property test_property; T_StringId testEventId;

void onTestPropertyChanged(const T_String &oldValue, const T_String &newValue) { printf("Test property changed to %s\n", newValue.c_str()); }

void onTestEvent(const T_String &test) { printf("Test event: %s\n", test.c_str()); } };

//A demonstration of using custom parameters into the component constructor class CustomParamsComp : public Component { public: CustomParamsComp(Entity &owner, const T_String &name, CustomType1 &type1, CustomType2 &type2, CustomType3 &type3) : Component(owner, name), type1(type1), type2(type2), type3(type3) { }

//Preprocessor will add static functions: //Type(), Create(Entity&, const T_String &, CustomType1 &custom1, CustomType2 &custom2, CustomType3 &custom3) and RegisterToFactory(ComponentFactory &) //to this component implementation. COMPONENT_3(CustomParamsComp, CustomType1, CustomType2, CustomType3)

private: CustomType1 &type1; CustomType2 &type2; CustomType3 &type3; }; ```

Component Factory
ComponentFactory factory; TestComp::RegisterToFactory(factory); CustomParamsComp::RegisterToFactory(factory);

Entity
``` Entity test(factory);

test.addComponent("TestComp");

CustomType1 type1; CustomType2 type2; CustomType3 type3; test.addComponent("CustomParamsComp", type1, type2, type3);

test.getProperty("TestProp") = "This is an entity test!";

T_StringId testEventId("TEST_EVT"); test.onEvent1(testEventId, "Hello from test entity!");

test.updateComponents(0.016f); ```

Work in progress
Property (de)serialization
Make PropertyList more feature complete
Improve documentation
Design entity blueprint/template system
Stress-test example
Game example
Entity definition tool
Complete implementation of Boost and ClanLib dependency bundles
Authors
Pål Trefall
Kenneth 'sphair' Gangstø

Contributors
Jacob 'jacmoe' Moen

'savuporo'
'zerotri'
