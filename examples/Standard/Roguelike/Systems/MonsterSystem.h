#pragma once

#include "../Components/Monster.h"
#include "../Entity.h"
#include "../Engine.h"

#include <memory>
#include <iostream>
#include <vector>

class MonsterSystem;
typedef std::shared_ptr<MonsterSystem> MonsterSystemPtr;

class MonsterSystem : public sigslot::has_slots<>
{
public:
	MonsterSystem() {}
	~MonsterSystem() { std::cout << "Monster System is being destroyed!" << std::endl; }

	void add(Monster *monster)
	{
		for(unsigned int i = 0; i < monsters.size(); i++)
		{
			if(monsters[i] == monster)
				return;
		}
		monsters.push_back(monster);
		std::cout << "Added monster " << monster->getOwner()->getName() << " to Monster System!" << std::endl;
	}
	void remove(Monster *monster)
	{
		for(unsigned int i = 0; i < monsters.size(); i++)
		{
			if(monsters[i] == monster)
			{
				//std::cout << "Removed monster from Monster System!" << std::endl;
				monsters[i] = monsters.back();
				monsters.pop_back();
				return;
			}
		}
	}

	void think()
	{
	}

private:
	std::vector<Monster*> monsters;
};