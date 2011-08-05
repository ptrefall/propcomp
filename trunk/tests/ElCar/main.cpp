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
#include "Components/AngularPhysics.h"
#include "Components/Dynamo.h"
#include "Components/EnergyCharger.h"
#include "Components/EnergyDecharger.h"
#include "Components/LinearPhysics.h"
#include "Components/Throttle.h"
#include "Components/Transformable.h"
#include "Components/WheelMount.h"

#include <iostream>
#include <stdio.h>
#include <time.h>

void printStartup();
void initFactory(ComponentFactory &factory);
void defineCar(Entity &car, ComponentFactory &factory);
void defineWheel(Entity &wheel, ComponentFactory &factory, const T_String &name);
void printReady();
void wait(int ms);

void main()
{
	//Print out some startup text
	printStartup();

	//Create factory and register components
	ComponentFactory factory;
	initFactory(factory);

	Entity &car = EntityManager::Instance().create(factory, "Car");
	defineCar(car, factory);

	printReady();

	T_Event event_throttle("THROTTLE");

	U32 num_iterations = 5;
	U32 curr_iteration = 0;
	while(curr_iteration < num_iterations)
	{
		F32 deltaTime = 0.016f;
		car.onEvent(event_throttle);
		EntityManager::Instance().update(deltaTime);
		wait(16);
		curr_iteration++;
	}

	system("pause");

	//Clean up
	EntityManager::Shutdown();
}

void printStartup()
{
	std::cout << "Thank you for downloading and testing out the \nComponent-based entities using properties codebase!" << std::endl;
	std::cout << "In this test we'll demonstrate an electric car." << std::endl;
	std::cout << "It's wheels will charge the battery, but rotating the wheels by force will spend energy too." << std::endl;
	std::cout << "\n";
	system("pause");
}

void initFactory(ComponentFactory &factory)
{
	std::cout << "Initialize components..." << std::endl;
	std::cout << "- register AngularPhysics" << std::endl;
	std::cout << "- register Dynamo" << std::endl;
	std::cout << "- register EnergyCharger" << std::endl;
	std::cout << "- register EnergyDecharger" << std::endl;
	std::cout << "- register LinearPhysics" << std::endl;
	std::cout << "- register Throttle" << std::endl;
	std::cout << "- register Transformable" << std::endl;
	std::cout << "- register WheelMount" << std::endl;

	factory.registerComponent(Components::AngularPhysics::getType(), &Components::AngularPhysics::Create);
	factory.registerComponent(Components::Dynamo::getType(), &Components::Dynamo::Create);
	factory.registerComponent(Components::EnergyCharger::getType(), &Components::EnergyCharger::Create);
	factory.registerComponent(Components::EnergyDecharger::getType(), &Components::EnergyDecharger::Create);
	factory.registerComponent(Components::LinearPhysics::getType(), &Components::LinearPhysics::Create);
	factory.registerComponent(Components::Throttle::getType(), &Components::Throttle::Create);
	factory.registerComponent(Components::Transformable::getType(), &Components::Transformable::Create);
	factory.registerComponent(Components::WheelMount::getType(), &Components::WheelMount::Create);
	
	
}

void defineCar(Entity &car, ComponentFactory &factory)
{
	std::cout << "Define car entity..." << std::endl;
	std::cout << "- add EnergyCharger component" << std::endl;
	std::cout << "- add EnergyDecharger component" << std::endl;
	std::cout << "- add LinearPhysics component" << std::endl;
	std::cout << "- add Throttle component" << std::endl;
	std::cout << "- add Transformable component" << std::endl;
	std::cout << "- add WheelMount component" << std::endl;
	std::cout << "- set EngineEffect to 0.5" << std::endl;

	car.addComponent("EnergyCharger");
	car.addComponent("EnergyDecharger");
	car.addComponent("LinearPhysics");
	car.addComponent("Throttle");
	car.addComponent("Transformable");
	car.addComponent("WheelMount");

	car.getProperty<F32>("EngineEffect") = 0.5f; //Spend this much energy to move car every time we throttle

	//Front Left
	{
		Entity &wheel = EntityManager::Instance().create(factory, "Wheel");
		defineWheel(wheel, factory, "WheelFrontLeft");
		car.getPropertyList<Entity*>("Wheels").add(&wheel);
		wheel.getProperty<Entity*>("Car") = &car;
	}

	//Front Right
	{
		Entity &wheel = EntityManager::Instance().create(factory, "Wheel");
		defineWheel(wheel, factory, "WheelFrontRight");
		car.getPropertyList<Entity*>("Wheels").add(&wheel);
		wheel.getProperty<Entity*>("Car") = &car;
	}

	//Back Left
	{
		Entity &wheel = EntityManager::Instance().create(factory, "Wheel");
		defineWheel(wheel, factory, "WheelBackLeft");
		car.getPropertyList<Entity*>("Wheels").add(&wheel);
		wheel.getProperty<Entity*>("Car") = &car;
	}

	//Back Right
	{
		Entity &wheel = EntityManager::Instance().create(factory, "Wheel");
		defineWheel(wheel, factory, "WheelBackRight");
		car.getPropertyList<Entity*>("Wheels").add(&wheel);
		wheel.getProperty<Entity*>("Car") = &car;
	}
}

void defineWheel(Entity &wheel, ComponentFactory &factory, const T_String &name)
{
	std::cout << "Define wheel entity..." << std::endl;
	std::cout << "- add AngularPhysics component" << std::endl;
	std::cout << "- add Dynamo component" << std::endl;
	std::cout << "- set Name to " << name.c_str() << std::endl;
	std::cout << "- set DynamoEfficiency to 4.0" << std::endl;
	std::cout << "- set GenerationFactor to 2.4" << std::endl;

	wheel.addComponent("AngularPhysics");
	wheel.addComponent("Dynamo");
	
	wheel.addProperty<T_String>("Name", name);
	wheel.getProperty<F32>("DynamoEfficiency") = 4.0f;
	wheel.getProperty<F32>("GenerationFactor") = 2.4f;
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
