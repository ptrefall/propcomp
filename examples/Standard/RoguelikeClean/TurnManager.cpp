#include "TurnManager.h"
#include "GameManager.h"
#include "Player.h"
#include "EntityContainer.h"
#include "Entity.h"

#include <algorithm>
#include <iostream>

TurnManager::TurnManager()
	: _turnCount(0)
{
}

TurnManager::~TurnManager()
{
}

void TurnManager::invoke()
{
	std::vector<std::pair<int, std::shared_ptr<Entity>>> turnList;
	int elapsedTime = GameManager::Get()->getPlayer()->moveOrInteract();
	
	GameManager::Get()->getEntities()->moveOrInteract(elapsedTime);

	sort( _schedule.begin(), _schedule.end(), TurnManager::ScheduleSorter );

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Schedule for turn " << _turnCount << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	for(auto info : _schedule)
	{
		std::cout << info->CurrentTime << " - " << info->entity->getName() << std::endl;
	}
	std::cout << "-----------------------------------" << std::endl;
	_turnCount++;
}

void TurnManager::schedule(int time, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Skill> &skill)
{
	auto info = _find(entity);
	if(info == nullptr)
	{
		info = new ScheduleInfo(time, entity, skill);
		_schedule.push_back(info);
	}
}

TurnManager::ScheduleInfo *TurnManager::_find(const std::shared_ptr<Entity> &entity)
{
	if(entity)
	{
		for(auto info : _schedule)
		{
			if(info->entity == entity)
				return info;
		}
	}

	return nullptr;
}
