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
#include <ComponentFactory.h>

#include "../Common/EntityManager.h"
#include "Components/Health.h"
#include "Components/Timer.h"
#include "Components/Explosive.h"
#include "Components/MultiTargeter.h"
#include "Components/RadiusTargetSeeker.h"
#include "Components/Transformable.h"

#include <iostream>
#include <stdio.h>
#include <time.h>

void printStartup();
void initFactory(ComponentFactory &factory);
void defineBomb(Entity &bomb, ComponentFactory &factory);
void defineCrate(Entity &crate, ComponentFactory &factory, const T_String &name);
void printReady();
void printResult(Entity &entity);
void wait(int ms);

void main()
{
	//Print out some startup text
	printStartup();

	//Create factory and register components
	ComponentFactory factory;
	initFactory(factory);

	Entity &bomb = EntityManager::Instance().create(factory, "Bomb");
	defineBomb(bomb, factory);

	Entity &crateA = EntityManager::Instance().create(factory, "Crate");
	defineCrate(crateA, factory, "CrateA");
	std::cout << "- set Position to (5.0, 0.0, 0.0)" << std::endl;
	crateA.getProperty<T_Vec3f>("Position") = T_Vec3f(5.0f, 0.0f, 0.0f);

	Entity &crateB = EntityManager::Instance().create(factory, "Crate");
	defineCrate(crateB, factory, "CrateB");
	std::cout << "- set Position to (0.0, 11.0, 0.0)" << std::endl;
	crateB.getProperty<T_Vec3f>("Position") = T_Vec3f(0.0f, 11.0f, 0.0f);

	Entity &crateC = EntityManager::Instance().create(factory, "Crate");
	defineCrate(crateC, factory, "CrateC");
	std::cout << "- set Position to (0.0, 0.0, 7.0)" << std::endl;
	crateC.getProperty<T_Vec3f>("Position") = T_Vec3f(5.0f, 7.0f, 2.0f);

	printReady();

	while(bomb.getProperty<bool>("Timeout").get() == false)
	{
		F32 deltaTime = 0.016f;
		EntityManager::Instance().update(deltaTime);
		wait(16);
	}

	system("pause");

	std::cout << "Result:" << std::endl;
	printResult(crateA);
	printResult(crateB);
	printResult(crateC);

	system("pause");

	//Clean up
	EntityManager::Shutdown();
}

void printStartup()
{
	std::cout << "Thank you for downloading and testing out the \nComponent-based entities using properties codebase!" << std::endl;
	std::cout << "In this test we'll demonstrate a ticking time-bomb \nthat explodes." << std::endl;
	std::cout << "It's blast radius will impact three crates placed in the scene." << std::endl;
	std::cout << "\n";
	system("pause");
}

void initFactory(ComponentFactory &factory)
{
	std::cout << "Initialize components..." << std::endl;
	std::cout << "- register Health" << std::endl;
	std::cout << "- register Timer" << std::endl;
	std::cout << "- register Explosive" << std::endl;
	std::cout << "- register MultiTargeter" << std::endl;
	std::cout << "- register RadiusTargetSeeker" << std::endl;
	std::cout << "- register Transformable" << std::endl;

	Components::Health::RegisterToFactory(factory);
	Components::Timer::RegisterToFactory(factory);
	Components::Explosive::RegisterToFactory(factory);
	Components::MultiTargeter::RegisterToFactory(factory);
	Components::RadiusTargetSeeker::RegisterToFactory(factory);
	Components::Transformable::RegisterToFactory(factory);
}

void defineBomb(Entity &bomb, ComponentFactory &factory)
{
	std::cout << "Define bomb entity..." << std::endl;
	std::cout << "- add Timer component" << std::endl;
	std::cout << "- add Explosive component" << std::endl;
	std::cout << "- add MultiTargeter component" << std::endl;
	std::cout << "- add RadiusTargetSeeker component" << std::endl;
	std::cout << "- add Transformable component" << std::endl;
	std::cout << "- set TimeoutValue to 6" << std::endl;
	std::cout << "- set TickInterval to 1.0" << std::endl;

	bomb.addComponent("Timer");
	bomb.addComponent("Explosive");
	bomb.addComponent("MultiTargeter");
	bomb.addComponent("RadiusTargetSeeker");
	bomb.addComponent("Transformable");
	
	bomb.getProperty<U32>("TimeoutValue") = 6; //Time out after 6 ticks
	bomb.getProperty<F32>("TickInterval") = 1.0f; //Seconds per tick
}

void defineCrate(Entity &crate, ComponentFactory &factory, const T_String &name)
{
	std::cout << "Define crate entity..." << std::endl;
	std::cout << "- add Health component" << std::endl;
	std::cout << "- add Transformable component" << std::endl;
	std::cout << "- set Name to " << name.c_str() << std::endl;
	std::cout << "- set Health to 100.0" << std::endl;

	crate.addComponent("Health");
	crate.addComponent("Transformable");
	
	crate.getProperty<T_String>("Name") = name;
	crate.getProperty<F32>("Health") = 100.0f;
}

void printReady()
{
	std::cout << "Initialization done." << std::endl;
	std::cout << "Press any key to start simulation." << std::endl;
	std::cout << "\n";
	system("pause");
}

void printResult(Entity &entity)
{
	const T_String &name = entity.getProperty<T_String>("Name").get();
	if(entity.hasProperty("Alive") && entity.getProperty<bool>("Alive").get() && entity.hasProperty("Health"))
	{
		F32 hp = entity.getProperty<F32>("Health").get();
		std::cout << name.c_str() << " HP:" << hp << "." << std::endl;
	}
	else
		std::cout << name.c_str() << " is dead." << std::endl;
}

void wait(int ms)
{
  clock_t endwait;
  endwait = clock () + ms * (CLOCKS_PER_SEC/1000) ;
  while (clock() < endwait) {}
}
