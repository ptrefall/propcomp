
#pragma once

#include "Engine/Common/GameWorld/gameobject.h"

enum GameObjectLooks
{
	GOL_CHARACTER = 0,
	GOL_ORC,
	GOL_TROLL,
	GOL_ITEM,
	GOL_SCROLL,
	GOL_POTION,
	GOL_CORPSE
};

class Looks : public Totem::Component<Looks>
{
public:
	Looks(GameObject &owner, const std::string &name = std::string());
	virtual ~Looks();

	static std::string getType() { return "Looks"; }

protected:
	Totem::Property<int> looks_property;
};
