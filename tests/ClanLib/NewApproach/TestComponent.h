#pragma once
#include <ClanLib\core.h>

#include "../../../editions/ClanLib/include/Totem/Component.h"
#include "../../../editions/ClanLib/include/Totem/Property.h"
#include "../Common/Entity.h"

class TestSystem;
typedef std::shared_ptr<TestSystem> TestSystemPtr;

class TestComponent : public Totem::Component<>
{
public:
	TestComponent(EntityPtr owner, const CL_String &name, TestSystemPtr sys);
	static CL_String Type() { return "Test"; }
        
	void test();

private:
	void OnSharedPropChanged(const CL_String &old_value, const CL_String &new_value);
	CL_Slot sharedPropChangedSlot;

	EntityPtr owner;
	TestSystemPtr sys;

	Totem::Property<CL_String> test_prop;
	Totem::Property<CL_String> test_shared_prop;
};