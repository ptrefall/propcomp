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

#include "../../../editions/ClanLib/include/Totem/ComponentContainer.h"
#include "../../../editions/ClanLib/include/Totem/Addons/EventSystem.h"
#include "TestSystem.h"
#include "TestComponent.h"
#include "../Common/Entity.h"

#include <algorithm>
#include <iostream>

class ListCallback
{
public:
        void onValueAddedToList(const unsigned int &index, const int &newValue)
        {
                std::cout << "Added value " << newValue << " at index " << index << std::endl;
        }
        void onValueErasedFromList(const unsigned int &index, const int &valueErased)
        {
                std::cout << "Erased value " << valueErased << " from index " << index << std::endl;
        }
        void onValuesClearedFromList()
        {
                std::cout << "Values cleared!" << std::endl;
        }
};

void main()
{
        //We initialize some systems/managers for the engine here...
        TestSystemPtr sys = std::make_shared<TestSystem>();

        EntityPtr entity = std::make_shared<Entity>();

        //We have loaded a list of serialized components that belong to this entity we're building
        std::vector<CL_String> loaded_component_types;
        loaded_component_types.push_back("Test");

        //We iterate over serialized components and add one by one to the entity
        std::for_each(loaded_component_types.begin(), loaded_component_types.end(), [&](const CL_String &component_type){
                if(component_type == TestComponent::Type())
                {
					try{
                        auto testComp = entity->addComponent1<TestComponent, TestSystemPtr>(sys, "Test1");
                        auto testComp2 = entity->addComponent1<TestComponent, TestSystemPtr>(sys, "Test2");
                        
                        testComp->test();
                        testComp2->test();
                        
                        auto test_prop = testComp->getProperty<CL_String>("TestProp");
                        std::cout << test_prop.get().c_str() << " from " << testComp->getName().c_str() << std::endl;
                        auto test_prop2 = testComp2->getProperty<CL_String>("TestProp");
                        std::cout << test_prop2.get().c_str() << " from " << testComp2->getName().c_str() << std::endl;
                        
                        auto test_shared_prop = entity->getSharedProperty<CL_String>("TestSharedProp");
                        std::cout << test_shared_prop.get().c_str() << std::endl;
                        test_shared_prop = "Test Shared Property Value Changed";
					} catch(CL_Exception &e) {
						std::cout << e.get_message_and_stack_trace().c_str() << std::endl;
					}
                }
        });

        auto list = entity->addSharedPropertyList<int>("TestList");

        ListCallback listCallback;
        list.valueAdded().connect(&listCallback, &ListCallback::onValueAddedToList);
        list.valueErased().connect(&listCallback, &ListCallback::onValueErasedFromList);
        list.valuesCleared().connect(&listCallback, &ListCallback::onValuesClearedFromList);
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.erase(1);
        list.erase(1);
        list.clear();

		

        system("pause");
}