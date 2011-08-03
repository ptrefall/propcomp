/*Component-based Entity Engine
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

Note: Some of the libraries Component-based Entity Engine may link to may have additional
requirements or restrictions.
*/

#include <Entity.h>
#include <Component.h>
#include <ComponentFactory.h>

#include <iostream>
#include <stdio.h>
#include <time.h>

void printStartup();
void initFactory(ComponentFactory &factory);
void defineDog(Entity &dog, ComponentFactory &factory);
void defineMan(Entity &man, ComponentFactory &factory);
void printReady();
void wait(int ms);

class Voice : public Component
{
public:
	Voice(Entity &owner, const T_String &name)
	: Component(owner, name)
	{
		hello_property = owner.addProperty<T_String>("HelloWords", "Hello!");
		bye_property = owner.addProperty<T_String>("ByeWords", "Bye!");
		target_property = owner.addProperty<Entity*>("Target", NULL_PTR);
	}
	virtual ~Voice() {}
	
	virtual void onEvent(const T_Event &event)
	{
		if(event.type == "SPEAK")
		{
			T_String what = event.arg0.str;
			if(target_property.get() == NULL_PTR)
			{
				if(what == "HELLO")
					std::cout << owner.getName().c_str() << " the " << owner.getType().c_str() << " says: " 
					<< hello_property.get().c_str() << std::endl;
				else if(what == "BYE")
					std::cout << owner.getName().c_str() << " the " << owner.getType().c_str() << " says: " 
					<< bye_property.get().c_str() << std::endl;
			}
			else
			{
				if(what == "HELLO")
					std::cout << owner.getName().c_str() << " the " << owner.getType().c_str() << " says: " 
					<< hello_property.get().c_str() << " to " << target_property.get()->getName().c_str() << std::endl;
				else if(what == "BYE")
					std::cout << owner.getName().c_str() << " the " << owner.getType().c_str() << " says: " 
					<< bye_property.get().c_str() << " to " << target_property.get()->getName().c_str() << std::endl;
			}
		}
	}
	
	static T_String getType() { return "Voice"; }
	static Component* Create(Entity &owner, const T_String &name) { return new Voice(owner, name); }

protected:
	Property<T_String> hello_property;
	Property<T_String> bye_property;
	Property<Entity*> target_property;
};

class Targeter : public Component
{
public:
	Targeter(Entity &owner, const T_String &name)
	: Component(owner, name)
	{
		target_property = owner.addProperty<Entity*>("Target", NULL_PTR);
		target_property.valueChanged().connect(this, &Targeter::onTargetChanged);
	}
	virtual ~Targeter() {}
	
	static T_String getType() { return "Targeter"; }
	static Component* Create(Entity &owner, const T_String &name) { return new Targeter(owner, name); }

protected:
	Property<Entity*> target_property;

	void onTargetChanged(Entity * const &oldValue, Entity * const &newValue)
	{
		std::cout << owner.getName().c_str() << " the " << owner.getType().c_str() << " looks at " 
		<< target_property.get()->getName().c_str() << std::endl;
		wait(1000);
	}
};

void main()
{
	//Print out some startup text
	printStartup();

	//Create factory and register components
	ComponentFactory factory;
	initFactory(factory);

	Entity &dog = Entity(factory, "Dog", "Champ");
	defineDog(dog, factory);

	Entity &man = Entity(factory, "Man", "James");
	defineMan(man, factory);

	printReady();

	dog.getProperty<Entity*>("Target") = &man;
	man.getProperty<Entity*>("Target") = &dog;

	T_Event event("SPEAK");

	event.arg0.str = "HELLO";
	man.onEvent(event);
	wait(1000);
	dog.onEvent(event);
	wait(1000);
	
	event.arg0.str = "BYE";
	man.onEvent(event);
	wait(1000);
	dog.onEvent(event);
	wait(1000);

	system("pause");
}

void printStartup()
{
	std::cout << "Thank you for downloading and testing out the \nComponent-based entities using properties codebase!" << std::endl;
	std::cout << "In this test we'll demonstrate a man and a dog interacting in \"sophisticated\" conversation." << std::endl;
	std::cout << "\n";
	system("pause");
}

void initFactory(ComponentFactory &factory)
{
	std::cout << "Initialize components..." << std::endl;
	std::cout << "- register Voice" << std::endl;
	std::cout << "- register Targeter" << std::endl;

	factory.registerComponent(Voice::getType(), &Voice::Create);
	factory.registerComponent(Targeter::getType(), &Targeter::Create);
}

void defineDog(Entity &dog, ComponentFactory &factory)
{
	std::cout << "Define dog entity..." << std::endl;
	std::cout << "- add Voice component" << std::endl;
	std::cout << "- add Targeter component" << std::endl;
	std::cout << "- set HelloWords to Voff!" << std::endl;
	std::cout << "- set ByeWords to VoffVoff!" << std::endl;

	dog.addComponent("Voice");
	dog.addComponent("Targeter");

	dog.getProperty<T_String>("HelloWords") = "Voff!"; //Time out after 6 ticks
	dog.getProperty<T_String>("ByeWords") = "VoffVoff!"; //Seconds per tick
}

void defineMan(Entity &man, ComponentFactory &factory)
{
	std::cout << "Build man entity..." << std::endl;
	std::cout << "- add Voice component" << std::endl;
	std::cout << "- add Targeter component" << std::endl;
	std::cout << "- set HelloWords to Hi there" << std::endl;
	std::cout << "- set ByeWords to Good bye" << std::endl;

	man.addComponent("Voice");
	man.addComponent("Targeter");

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
