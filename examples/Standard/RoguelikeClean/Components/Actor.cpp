#include "Actor.h"

using namespace clan;
using namespace Totem;

Actor::Actor(Entity *owner)
	: Component<Actor>(GetType()), _owner(owner)
{
	_level = owner->add<int>("Level", 0);
	_experienceToSpend = owner->add<int>("ExperienceToSpend", 0);
}

Actor::~Actor() 
{
}

std::shared_ptr<Attribute> Actor::GetAttribute(const std::string &name) const
{
	for(auto value : _attributes)
	{
		if(value->Name() == name)
			return value;
	}

	return nullptr;
}

std::shared_ptr<Vital> Actor::GetVital(const std::string &name) const
{
	for(auto value : _vitals)
	{
		if(value->Name() == name)
			return value;
	}

	return nullptr;
}

std::shared_ptr<Skill> Actor::GetSkill(const std::string &name) const
{
	for(auto value : _skills)
	{
		if(value->Name() == name)
			return value;
	}

	return nullptr;
}

void Actor::AddExperience(int experience)
{
	_experienceToSpend += experience;
	_CalculateLevel();
}

//Take average of all of the actor's skills and assign that as the actor level
void Actor::_CalculateLevel()
{
}

void Actor::_UpdateStats()
{
	for(auto vital : _vitals)
		vital->Update();
	for(auto skill : _skills)
		skill->Update();
}