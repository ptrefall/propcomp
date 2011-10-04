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

#include "Transformable.h"

using namespace Components;
using namespace Totem;

Transformable::Transformable(Entity &owner, const T_String &name)
: Component(owner, name)
{
	position_property = owner.addProperty<T_Vec3f>("Position", T_Vec3f(0.0f, 0.0f, 0.0f));
}

Transformable::~Transformable()
{
}
