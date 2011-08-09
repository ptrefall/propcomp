/*Component-based Entity Engine
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

Note: Some of the libraries Component-based Entity Engine may link to may have additional
requirements or restrictions.
*/

#include "MultiTargeter.h"
#include "../../Common/EntityManager.h"

#include <iostream>

using namespace Components;

MultiTargeter::MultiTargeter(Entity &owner, const T_String &name)
: Component(owner, name)
{
    target_property_list = owner.addPropertyList<Entity*>("Targets");

    target_property_list.valueAdded().connect(this, &MultiTargeter::onTargetAdded);
}

MultiTargeter::~MultiTargeter()
{
}

void MultiTargeter::onTargetAdded(Entity * const &/*newValue*/)
{
}
