/*Totem EDK
Copyright (c) 2009 Pål Trefall and Kenneth Gangstø

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Note: Some of the libraries Totem EDK may link to may have additional
requirements or restrictions.
*/

#include "../../../include/Totem/Component.h"
#include "../../../include/Totem/ComponentContainer.h"
#include "../../../include/Totem/Property.h"
#include "../../../include/Totem/PropertyContainer.h"
#include "../../../include/Totem/PropertyList.h"
#include "../../../include/Totem/PropertyListContainer.h"
#include "../../../include/Totem/HashedString.h"

#include "../../../include/Totem/Addons/EventSystem.h"
#include "../../../include/Totem/Addons/DelegateSystem.h"

#include "TestSystem.h"
#include "TestComponent.h"
#include "../Common/Entity.h"

#include <memory>
#include <algorithm>
#include <iostream>

class EntityCallback : public sigslot::has_slots<>
{
public:
	EntityCallback(){}

	void onComponentAdded(std::shared_ptr<Totem::IComponent<PropertyUserData>> component)
	{
		std::cout << "Component " + component->getName() + " added" << std::endl;
	}

	void onPropertyAdded(std::shared_ptr<Totem::IProperty> property, const PropertyUserData &userData)
	{
		std::cout << "Property " + property->getName() + " added to " + userData.component->getName() + " component in entity " + userData.entity.lock()->getName() << std::endl;
	}

	void onPropertyListAdded(std::shared_ptr<Totem::IPropertyList> propertyList, const PropertyUserData &userData)
	{
		std::cout << "PropertyList " + propertyList->getName() + " added to " + userData.component->getName() + " component in entity " + userData.entity.lock()->getName() << std::endl;
	}
};

class ListCallback : public sigslot::has_slots<>
{
public:
	ListCallback(){}
    void onValueAddedToList(unsigned int index, const int &newValue)
    {
            std::cout << "Added value " << newValue << " at index " << index << std::endl;
    }
    void onValueErasedFromList(unsigned int index, const int &valueErased)
    {
            std::cout << "Erased value " << valueErased << " from index " << index << std::endl;
    }
    void onValuesClearedFromList()
    {
            std::cout << "Values cleared!" << std::endl;
    }
	void onValueChanged(unsigned int index, const int &oldValue, const int &newValue)
    {
            std::cout << "Value changed from " << oldValue << " to " << newValue << " at index " << index << std::endl;
    }
};

void main()
{
        //We initialize some systems/managers for the engine here...
        TestSystemPtr sys = std::make_shared<TestSystem>();
        EntityPtr entity = std::make_shared<Entity>("TestEntity");
		{
			auto entityCallback = std::make_shared<EntityCallback>();
			entity->componentAdded().connect(entityCallback.get(), &EntityCallback::onComponentAdded);
			entity->propertyWithUserDataAdded().connect(entityCallback.get(), &EntityCallback::onPropertyAdded);
			entity->propertyListWithUserDataAdded().connect(entityCallback.get(), &EntityCallback::onPropertyListAdded);
		
			auto testComp0 = entity->addComponent(std::make_shared<TestComponent>(entity, "Test0", sys));
			auto testComp1 = entity->addComponent<TestComponent>(std::make_shared<TestComponent>(entity, "Test1", sys));

			if(Totem::Component<TestComponent, PropertyUserData>::isType(testComp0) == false)
				return; //This shouldn't happen

			if(entity->hasComponent<TestComponent>("Test1") == false)
				return; //This shouldn't happen
           
			//testComp0->test(); //<- this is a shared_ptr to an IComponent, so we can't call test() function.
			testComp1->test();
                        
			auto test_prop = testComp0->get<std::string>("TestProp");
			std::cout << test_prop.get() << " from " << testComp0->getName() << std::endl;
			auto test_prop2 = testComp1->get<std::string>("TestProp");
			std::cout << test_prop2.get() << " from " << testComp1->getName() << std::endl;
               
			auto test_shared_prop = entity->get<std::string>("TestSharedProp");
			std::cout << test_shared_prop.get() << std::endl;
			test_shared_prop = "Test Shared Property Value Changed";

			entity->sendEvent0("SomeEvent");
		
			auto list = entity->addList<int>("TestList");

			auto listCallback = std::make_shared<ListCallback>();
			list.valueAdded().connect(listCallback.get(), &ListCallback::onValueAddedToList);
			list.valueErased().connect(listCallback.get(), &ListCallback::onValueErasedFromList);
			list.valuesCleared().connect(listCallback.get(), &ListCallback::onValuesClearedFromList);
			list.valueChanged().connect(listCallback.get(), &ListCallback::onValueChanged);
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list[1] += 2;
			list.erase(1);
			list.erase(1);
			list.clear();
		}
		std::cout << "There's " << entity.use_count() << " references to entity alive!" << std::endl;
		entity.reset();
		std::cout << "There's " << entity.use_count() << " references to entity alive!" << std::endl;
		sys.reset();

        system("pause");
}