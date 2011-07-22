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

#include <iostream>
#include <stdio.h>
#include <time.h>

void printStartup();
void initFactory(ComponentFactory &factory);
void buildBomb(Entity &bomb, ComponentFactory &factory);
void buildCrate(Entity &crate, ComponentFactory &factory);
void printReady();
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

	Entity &crate = EntityManager::Instance().create(factory, "Crate");
	buildCrate(crate, factory);

	printReady();

	while(crate.getProperty<bool>("Alive").get())
	{
		F32 deltaTime = 0.016f;
		EntityManager::Instance().update(deltaTime);
		wait(16);
	}

	system("pause");

	//Clean up
	EntityManager::Shutdown();
}

void printStartup()
{
	std::cout << "Thank you for downloading and testing out the \nComponent-based entities using properties codebase!" << std::endl;
	std::cout << "In this test we'll demonstrate a ticking time-bomb \nthat explodes and kills a crate." << std::endl;
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
}

void buildBomb(Entity &bomb, ComponentFactory &factory)
{
	std::cout << "Build bomb entity..." << std::endl;

	std::cout << "- add Timer component" << std::endl;
	bomb.addComponent("Timer");
	std::cout << "- add Explosive component" << std::endl;
	bomb.addComponent("Explosive");
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

void wait(int ms)
{
  clock_t endwait;
  endwait = clock () + ms * (CLOCKS_PER_SEC/1000) ;
  while (clock() < endwait) {}
}
