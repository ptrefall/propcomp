
#pragma once

#include "Engine/Common/GameWorld/gameobject.h"

enum GameObjectVisual
{
	GOV_CHARACTER = 0,
	GOV_ORC,
	GOV_TROLL,
	GOV_ITEM,
	GOV_SCROLL,
	GOV_POTION,
	GOV_CORPSE
};

class Visual : public Totem::Component<Visual>
{
public:
	Visual(GameObject *owner, const std::string &name = std::string());
	virtual ~Visual();

	static std::string getType() { return "Visual"; }

protected:
	Totem::Property<int> looks_property;
};
