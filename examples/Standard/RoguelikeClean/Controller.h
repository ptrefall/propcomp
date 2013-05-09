#pragma once

#include "Math/vec2.h"
#include <memory>
#include <vector>

class Entity;

class Controller : public std::enable_shared_from_this<Controller>
{
public:
	Controller();
	virtual ~Controller();

	void think();

	virtual void Set(const std::shared_ptr<Entity> &pawn) { _pawn = pawn; }
	const std::shared_ptr<Entity> &Get() { return _pawn; }

	int estimateAction();
	void takeAction();

protected:
	virtual void _internalThink() = 0;
	void _resetActionIntent();

protected:
	std::shared_ptr<Entity> _pawn;
	clan::Vec2i _dir;
	std::vector<bool> _actionIntent;
};