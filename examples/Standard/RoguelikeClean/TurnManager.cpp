#include "TurnManager.h"
#include "GameManager.h"
#include "ActionManager.h"
#include "Player.h"
#include "EntityContainer.h"
#include "Entity.h"
#include "EventDefinitions.h"

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
	int elapsedTime = GameManager::Get()->getPlayer()->estimateAction();
	GameManager::Get()->getEntities()->think(elapsedTime);

	sort( _schedule.begin(), _schedule.end(), TurnManager::ScheduleSorter );

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Schedule for turn " << _turnCount << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	for(unsigned int i = 0; i < _schedule.size(); i++)
	{
		auto info = _schedule[i];

		//Make sure the controller still has a pawn
		if(info->controller->Get())
		{
			std::cout << info->CurrentTime << " - " << info->controller->Get()->getName() << std::endl;
			if(info->Activated == false)
			{
				info->controller->takeAction();
				info->Activated = true;
			}
			info->controller->Get()->sendEvent1<int>(EVENT_NewTurn, elapsedTime);
			info->CurrentTime -= elapsedTime;
			if(info->CurrentTime <= 0)
			{
				_schedule.erase(_schedule.begin()+i);
			}
		}
		else
		{
			_schedule.erase(_schedule.begin()+i);
		}
	}
	std::cout << "-----------------------------------" << std::endl;
	_turnCount++;
}

void TurnManager::schedule(int time, const std::shared_ptr<Controller> &controller)
{
	auto info = _find(controller);
	if(info == nullptr)
	{
		info = new ScheduleInfo(time, controller);
		_schedule.push_back(info);
	}
}

TurnManager::ScheduleInfo *TurnManager::_find(const std::shared_ptr<Controller> &controller)
{
	if(controller)
	{
		for(auto info : _schedule)
		{
			if(info->controller == controller)
				return info;
		}
	}

	return nullptr;
}
