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

#include "EntityManager.h"
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
void buildBomb(Entity &bomb, ComponentFactory &factory);
void buildCrate(Entity &crate, ComponentFactory &factory);
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
	buildBomb(bomb, factory);

	Entity &crateA = EntityManager::Instance().create(factory, "Crate", "CrateA");
	buildCrate(crateA, factory);
	std::cout << "- set Position to (5.0, 0.0, 0.0)" << std::endl;
	crateA.getProperty<T_Vec3f>("Position") = T_Vec3f(5.0f, 0.0f, 0.0f);

	Entity &crateB = EntityManager::Instance().create(factory, "Crate", "CrateB");
	buildCrate(crateB, factory);
	std::cout << "- set Position to (0.0, 11.0, 0.0)" << std::endl;
	crateB.getProperty<T_Vec3f>("Position") = T_Vec3f(0.0f, 11.0f, 0.0f);

	Entity &crateC = EntityManager::Instance().create(factory, "Crate", "CrateC");
	buildCrate(crateC, factory);
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
	factory.registerComponent(Components::Health::getType(), &Components::Health::Create);
	std::cout << "- register Timer" << std::endl;
	factory.registerComponent(Components::Timer::getType(), &Components::Timer::Create);
	std::cout << "- register Explosive" << std::endl;
	factory.registerComponent(Components::Explosive::getType(), &Components::Explosive::Create);
	std::cout << "- register MultiTargeter" << std::endl;
	factory.registerComponent(Components::MultiTargeter::getType(), &Components::MultiTargeter::Create);
	std::cout << "- register RadiusTargetSeeker" << std::endl;
	factory.registerComponent(Components::RadiusTargetSeeker::getType(), &Components::RadiusTargetSeeker::Create);
	std::cout << "- register Transformable" << std::endl;
	factory.registerComponent(Components::Transformable::getType(), &Components::Transformable::Create);
}

void buildBomb(Entity &bomb, ComponentFactory &factory)
{
	std::cout << "Build bomb entity..." << std::endl;

	std::cout << "- add Timer component" << std::endl;
	bomb.addComponent("Timer");
	std::cout << "- add Explosive component" << std::endl;
	bomb.addComponent("Explosive");
	std::cout << "- add MultiTargeter component" << std::endl;
	bomb.addComponent("MultiTargeter");
	std::cout << "- add RadiusTargetSeeker component" << std::endl;
	bomb.addComponent("RadiusTargetSeeker");
	std::cout << "- add Transformable component" << std::endl;
	bomb.addComponent("Transformable");
	std::cout << "- set TimeoutValue to 6" << std::endl;
	bomb.getProperty<U32>("TimeoutValue") = 6; //Time out after 6 ticks
	std::cout << "- set TickInterval to 1.0" << std::endl;
	bomb.getProperty<F32>("TickInterval") = 1.0f; //Seconds per tick
}

void buildCrate(Entity &crate, ComponentFactory &factory)
{
	std::cout << "Build crate entity..." << std::endl;

	std::cout << "- add Health component" << std::endl;
	crate.addComponent("Health");
	std::cout << "- add Transformable component" << std::endl;
	crate.addComponent("Transformable");
	std::cout << "- set Health to 100.0" << std::endl;
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
	if(entity.hasProperty("Alive") && entity.getProperty<bool>("Alive").get() && entity.hasProperty("Health"))
	{
		F32 hp = entity.getProperty<F32>("Health").get();
		std::cout << entity.getName().c_str() << " HP:" << hp << "." << std::endl;
	}
	else
		std::cout << entity.getName().c_str() << " is dead." << std::endl;
}

void wait(int ms)
{
  clock_t endwait;
  endwait = clock () + ms * (CLOCKS_PER_SEC/1000) ;
  while (clock() < endwait) {}
}
