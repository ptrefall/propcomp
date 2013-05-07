#pragma once

#include <memory>
#include <vector>

class Player;
class EntityContainer;
class Entity;
class Skill;

class TurnManager
{
public:
	TurnManager();
	~TurnManager();

	void invoke();
	void schedule(int time, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Skill> &skill);

private:
	struct ScheduleInfo
	{
		int TotalTime;
		int CurrentTime;
		std::shared_ptr<Entity> entity;
		std::shared_ptr<Skill> skill;
		ScheduleInfo(int time, const std::shared_ptr<Entity> &entity, const std::shared_ptr<Skill> &skill) : TotalTime(time), CurrentTime(time), entity(entity), skill(skill) {}
	};

	std::vector<ScheduleInfo*> _schedule;

	ScheduleInfo *_find(const std::shared_ptr<Entity> &entity);

	static bool ScheduleSorter(ScheduleInfo *a, ScheduleInfo *b)
	{
		return a->CurrentTime < b->CurrentTime;
	}
};
