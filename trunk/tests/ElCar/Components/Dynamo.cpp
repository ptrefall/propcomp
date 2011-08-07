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

#include "types_config.h"
#include "Dynamo.h"
#include "../EntityManager.h"

#include <iostream>

using namespace Components;

Dynamo::Dynamo(Entity &owner, const T_String &name)
: Component(owner, name), addEffectEventId("ADD_EFFECT")
{
    car_property = owner.addProperty<Entity*>("Car", NULL_PTR);
	angularVelocity_property = owner.addProperty<F32>("AngularVelocity", 0.0f);
	generationFactor_property = owner.addProperty<F32>("GenerationFactor", 1.0f);
	dynamoEfficiency_property = owner.addProperty<F32>("DynamoEfficiency", 1.0f);
}

Dynamo::~Dynamo()
{
}

void Dynamo::update(F32 deltaTime)
{
	if(car_property.get() == NULL_PTR)
		return;

	if(owner.hasProperty("Name"))
		std::cout << "Dynamo of " << owner.getProperty<T_String>("Name").get().c_str() << " turnes with velocity " << angularVelocity_property.get() << std::endl;
	else
		std::cout << "Dynamo of " << owner.getType().c_str() << " turnes with velocity " << angularVelocity_property.get() << std::endl;

	F32 factor = generationFactor_property.get() * dynamoEfficiency_property.get();
	F32 effect = angularVelocity_property.get() * factor;

	car_property.get()->onEvent1<F32>(addEffectEventId, effect);
}
