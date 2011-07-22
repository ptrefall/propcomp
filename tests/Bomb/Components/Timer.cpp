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
#include "Timer.h"

#include <iostream>

using namespace Components;

Timer::Timer(Entity &entity, const T_String &name)
: Component(entity, name)
{
    timeout_property = entity.addProperty<bool>("Timeout", false);
	timeoutValue_property = entity.addProperty<U32>("TimeoutValue", 5);
	tickInterval_property = entity.addProperty<F32>("TickInterval", 1.0f);
	time = 0.0f;
	ticks = 0;
}

Timer::~Timer()
{
}

void Timer::update(F32 deltaTime)
{
	if(timeout_property.get() == true)
		return;

	time += deltaTime;
	if(time < tickInterval_property.get())
		return;

	ticks++;
	time = 0.0f;

	if(ticks >= timeoutValue_property.get())
	{
		std::cout << "CLICK! (" << timeoutValue_property.get() - ticks << ")" << std::endl;
		timeout_property = true;
	}
	else if(ticks%2)
		std::cout << "tick (" << timeoutValue_property.get() - ticks << ")" << std::endl;
	else
		std::cout << "tack (" << timeoutValue_property.get() - ticks << ")" << std::endl;
}
