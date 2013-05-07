#pragma once

#include "ModifiedStat.h"

class Skill : public ModifiedStat
{
public:
	Skill(const std::string &name, const std::string &description, int experienceToLevelUp, float levelModifier, int actionCost) 
		: ModifiedStat(name, description)
	{
		setExperienceToLevelUp(experienceToLevelUp);
		setLevelModifier(levelModifier);
		_active = false;
		_actionCost = actionCost;
	}
	virtual ~Skill() {}

	bool Active() const { return _active; }
	int ActionCost() const { return _actionCost; }
	
	int Cost() const { return ActionCost() * (10/Value()); }
	int ElapsedTime(int dexterity) const { return Cost() * (10/dexterity); }
	int CooldownTime(int stamina) const { return Cost() * (10/stamina); }

	void setActive(bool value) { _active = value; }
	void setActionCost(int value) { _actionCost = value; }

private:
	bool _active;
	int _actionCost;
};
