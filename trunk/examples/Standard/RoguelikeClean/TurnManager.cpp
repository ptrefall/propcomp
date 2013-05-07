#include "TurnManager.h"
#include "GameManager.h"
#include "Player.h"
#include "EntityContainer.h"

#include <algorithm>
#include <iostream>

TurnManager::TurnManager()
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
	for(auto info : _schedule)
	{
		std::cout << info->CurrentTime << std::endl;
	}
}

void TurnManager::schedule(int time, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Skill> &skill)
{
	auto info = _find(entity);
	if(info == nullptr)
	{
		info = new ScheduleInfo(time, entity, skill);
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
