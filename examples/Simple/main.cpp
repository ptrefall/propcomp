/*Totem EDK
Copyright (c) 2009 P�l Trefall and Kenneth Gangst�

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

#include "../Common/Entity.h"
#include <Totem/Component.h>
#include <Totem/ComponentFactory.h>

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace Totem;

void printStartup();
void initFactory(ComponentFactory &factory);
void defineDog(Entity &dog, const T_String &name);
void defineMan(Entity &man, const T_String &name);
void printReady();
void wait(int ms);

class Voice : public Component
{
public:
	COMPONENT_0(Entity, Voice)
	Voice(Entity &owner, const T_String &name)
	: Component(name), owner(owner), speakEventId("SPEAK")
	{
		type_property = owner.addProperty<T_String>("Type", "");
		hello_property = owner.addProperty<T_String>("HelloWords", "Hello!");
		bye_property = owner.addProperty<T_String>("ByeWords", "Bye!");
		target_property = owner.addProperty<Entity*>("Target", NULL_PTR);

		owner.registerToEvent1<const T_String&>(speakEventId).connect(this, &Voice::onSpeakEvent);

	}
	virtual ~Voice() {}

private:
	Property<T_String> type_property;
	Property<T_String> hello_property;
	Property<T_String> bye_property;
	Property<Entity*> target_property;
	T_HashedString speakEventId;

	void onSpeakEvent(const T_String &what)
	{
		const T_String &owner_name = owner.getProperty<T_String>("Name").get();
		if(target_property.get() == NULL_PTR)
		{
			if(what == "HELLO")
				std::cout << owner_name.c_str() << " the " << type_property.get().c_str() << " says: " 
				<< hello_property.get().c_str() << std::endl;
			else if(what == "BYE")
				std::cout << owner_name.c_str() << " the " << type_property.get().c_str() << " says: " 
				<< bye_property.get().c_str() << std::endl;
		}
		else
		{
			const T_String &target_name = target_property.get()->getProperty<T_String>("Name").get();

			if(what == "HELLO")
				std::cout << owner_name.c_str() << " the " << type_property.get().c_str() << " says: " 
				<< hello_property.get().c_str() << " to " << target_name.c_str() << std::endl;
			else if(what == "BYE")
				std::cout << owner_name.c_str() << " the " << type_property.get().c_str() << " says: " 
				<< bye_property.get().c_str() << " to " << target_name.c_str() << std::endl;
		}
	}
};

class Targeter : public Component
{
public:
	COMPONENT_0(Entity, Targeter)
	Targeter(Entity &owner, const T_String &name)
	: Component(name), owner(owner)
	{
		type_property = owner.addProperty<T_String>("Type", "");
		name_property = owner.addProperty<T_String>("Name", "");
		target_property = owner.addProperty<Entity*>("Target", NULL_PTR);
		target_property.valueChanged().connect(this, &Targeter::onTargetChanged);
	}
	virtual ~Targeter() {}

private:
	Property<T_String> type_property;
	Property<T_String> name_property;
	Property<Entity*> target_property;

	void onTargetChanged(Entity * const &/*oldValue*/, Entity * const &/*newValue*/)
	{
		std::cout << name_property.get().c_str() << " the " << type_property.get().c_str() << " looks at " 
		<< target_property.get()->getProperty<T_String>("Name").get().c_str() << std::endl;
		wait(1000);
	}
};

class CustomParamsHolder : public Component
{
public:
	COMPONENT_6(Entity, CustomParamsHolder, int, int, int, int, int, int)
	CustomParamsHolder(Entity &owner, const T_String &name, int &a, int &b, int &c, int &d, int &e, int &f)
	: Component(name), owner(owner), a(a), b(b), c(c), d(d), e(e), f(f)
	{
		std::cout << "CustomParamsHolder: " << a << " " << b << " " << c << " " << d << " " << e << " " << f << std::endl;
	}
	virtual ~CustomParamsHolder() {}
	int a,b,c,d,e,f;
};

int main()
{
	//Print out some startup text
	printStartup();

	//Create factory and register components
	ComponentFactory factory;
	initFactory(factory);

	Entity dog = Entity(factory); //, 0, "Dog");
	defineDog(dog, "Champ");

	Entity man = Entity(factory); //, 1, "Man");
	defineMan(man, "James");

	Entity custom_test = Entity(factory); //, 2, "CustomTest");
	int a = 0; int b = 1; int c = 2; int d = 3; int e = 4; int f = 5;
	custom_test.addComponent<int,int,int,int,int,int>("CustomParamsHolder", a,b,c,d,e,f);

	printReady();

	dog.getProperty<Entity*>("Target") = &man;
	man.getProperty<Entity*>("Target") = &dog;

	T_HashedString speakEventId("SPEAK");

	man.sendEvent1<const T_String&>(speakEventId, "HELLO");
	wait(1000);
	dog.sendEvent1<const T_String&>(speakEventId, "HELLO");
	wait(1000);

	man.sendEvent1<const T_String&>(speakEventId, "BYE");
	wait(1000);
	dog.sendEvent1<const T_String&>(speakEventId, "BYE");
	wait(1000);

	system("pause");
	return 0;
}

void printStartup()
{
	std::cout << "Thank you for downloading and testing out Totem EDK!" << std::endl;
	std::cout << "In this test we'll demonstrate a man and a dog interacting in \"sophisticated\" conversation." << std::endl;
	std::cout << "\n";
	system("pause");
}

void initFactory(ComponentFactory &factory)
{
	std::cout << "Initialize components..." << std::endl;
	std::cout << "- register Voice" << std::endl;
	std::cout << "- register Targeter" << std::endl;
	std::cout << "- register CustomParamsHolder" << std::endl;

	Voice::RegisterToFactory(factory);
	Targeter::RegisterToFactory(factory);
	CustomParamsHolder::RegisterToFactory(factory);
}

void defineDog(Entity &dog, const T_String &name)
{
	std::cout << "Define dog Entity..." << std::endl;
	std::cout << "- add Voice component" << std::endl;
	std::cout << "- add Targeter component" << std::endl;
	std::cout << "- set Name to " << name.c_str() << std::endl;
	std::cout << "- set HelloWords to Voff!" << std::endl;
	std::cout << "- set ByeWords to VoffVoff!" << std::endl;

	dog.addComponent("Voice");
	dog.addComponent("Targeter");

	dog.getProperty<T_String>("Type") = "Dog";
	dog.getProperty<T_String>("Name") = name;
	dog.getProperty<T_String>("HelloWords") = "Voff!"; //Time out after 6 ticks
	dog.getProperty<T_String>("ByeWords") = "VoffVoff!"; //Seconds per tick
}

void defineMan(Entity &man, const T_String &name)
{
	std::cout << "Build man Entity..." << std::endl;
	std::cout << "- add Voice component" << std::endl;
	std::cout << "- add Targeter component" << std::endl;
	std::cout << "- set Name to " << name.c_str() << std::endl;
	std::cout << "- set HelloWords to Hi there" << std::endl;
	std::cout << "- set ByeWords to Good bye" << std::endl;

	man.addComponent("Voice");
	man.addComponent("Targeter");

	man.getProperty<T_String>("Type") = "Man";
	man.getProperty<T_String>("Name") = name;
	man.getProperty<T_String>("HelloWords") = "Hi there"; //Time out after 6 ticks
	man.getProperty<T_String>("ByeWords") = "Good bye"; //Seconds per tick
}

void printReady()
{
	std::cout << "Initialization done." << std::endl;
	std::cout << "Press any key to start simulation." << std::endl;
	std::cout << "\n";
	system("pause");
}

void wait(int ms)
{
  clock_t endwait;
  endwait = clock () + ms * (CLOCKS_PER_SEC/1000) ;
  while (clock() < endwait) {}
}