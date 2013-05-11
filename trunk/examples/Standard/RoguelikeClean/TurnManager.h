#pragma once

#include "Entity.h"
#include <memory>
#include <vector>

class Controller;
class EntityContainer;
class Skill;

class TurnManager
{
public:
	TurnManager();
	~TurnManager();

	void invoke();
	void schedule(int time, const std::shared_ptr<Controller> &controller);

private:
	unsigned long _turnCount;

	struct ScheduleInfo
	{
		bool Activated;
		int TotalTime;
		int CurrentTime;
		std::shared_ptr<Controller> controller;
		ScheduleInfo(int time, const std::shared_ptr<Controller> &controller) : Activated(false), TotalTime(time), CurrentTime(time), controller(controller) {}
	};

	std::vector<std::shared_ptr<ScheduleInfo>> _schedule;

	std::shared_ptr<ScheduleInfo> _find(const std::shared_ptr<Controller> &controller);

	static bool ScheduleSorter(const std::shared_ptr<ScheduleInfo> &a, const std::shared_ptr<ScheduleInfo> &b)
	{
		return a->CurrentTime < b->CurrentTime;
	}
};
