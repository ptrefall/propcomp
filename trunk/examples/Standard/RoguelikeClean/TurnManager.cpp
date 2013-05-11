#include "TurnManager.h"
#include "GameManager.h"
#include "ActionManager.h"
#include "MapManager.h"
#include "Player.h"
#include "EntityContainer.h"
#include "Entity.h"
#include "EventDefinitions.h"
#include "PropertyDefinitions.h"
#include "AgentManager.h"

#include "Math/vec2.h"
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
	//GameManager::Get()->getEntities()->think(elapsedTime);
	GameManager::Get()->getAgent()->think(elapsedTime);

	sort( _schedule.begin(), _schedule.end(), TurnManager::ScheduleSorter );

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Schedule for turn " << _turnCount << " - lasts for " << elapsedTime << (elapsedTime == 1 ? " tick!" : " ticks!") << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::vector<std::shared_ptr<ScheduleInfo>> completedSchedules;
	for(unsigned int i = 0; i < _schedule.size(); i++)
	{
		auto info = _schedule[i];

		//Make sure the controller still has a pawn
		if(info->controller->Get())
		{
			std::cout << info->CurrentTime << (elapsedTime == 1 ? " tick - " : " ticks - ") << info->controller->Get()->getName() << std::endl;
			if(info->Activated == false)
			{
				info->controller->takeAction();
				info->Activated = true;
			}
			info->controller->Get()->sendEvent1<int>(EVENT_NewTurn, elapsedTime);
			info->CurrentTime -= elapsedTime;
			if(info->CurrentTime <= 0)
			{
				completedSchedules.push_back(info);
				//_schedule.erase(_schedule.begin()+i);
			}
		}
		else
		{
			completedSchedules.push_back(info);
			//_schedule.erase(_schedule.begin()+i);
		}
	}
	for(auto info : completedSchedules)
	{
		auto it = std::find(_schedule.begin(), _schedule.end(), info);
		if(it != _schedule.end())
			_schedule.erase(it);
	}
	completedSchedules.clear();
	std::cout << "-----------------------------------" << std::endl;
	for(unsigned int i = 0; i < _schedule.size(); i++)
	{
		auto info = _schedule[i];

		//Make sure the controller still has a pawn
		if(info->controller->Get())
		{
			if(info->CurrentTime == 0)
				completedSchedules.push_back(info);
			else
				std::cout << "- " << info->controller->Get()->getName() << " has " << info->CurrentTime << (info->CurrentTime == 1 ? " tick" : " ticks") << " time left on his action after the turn." << std::endl;
		}
	}
	for(auto info : completedSchedules)
	{
		auto it = std::find(_schedule.begin(), _schedule.end(), info);
		if(it != _schedule.end())
			_schedule.erase(it);
	}
	completedSchedules.clear();
	std::cout << "-----------------------------------" << std::endl;

	auto pawn = GameManager::Get()->getPlayer()->Get();
	if(pawn->hasProperty(PROPERTY_POSITION) && pawn->hasProperty(PROPERTY_SIGHT_RADIUS))
	{
		GameManager::Get()->getMap()->computeFov(
			MapManager::LAYER_GROUND, 
			pawn->get<clan::Vec2i>(PROPERTY_POSITION), 
			pawn->get<int>(PROPERTY_SIGHT_RADIUS));
	}

	_turnCount++;
}

void TurnManager::schedule(int time, const std::shared_ptr<Controller> &controller)
{
	/*auto info = _find(controller);
	if(info == nullptr)
	{*/
		auto info = std::make_shared<ScheduleInfo>(time, controller);
		_schedule.push_back(info);
	//}
}

std::shared_ptr<TurnManager::ScheduleInfo> TurnManager::_find(const std::shared_ptr<Controller> &controller)
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
