#pragma once

#include "Math/vec2.h"
#include <memory>
#include <vector>

class Entity;

class Player
{
public:
	Player();
	virtual ~Player();

	void handleInput();

	void Set(const std::shared_ptr<Entity> &pawn) { _pawn = pawn; }
	const std::shared_ptr<Entity> &Get() { return _pawn; }

	int moveOrInteract();

private:
	void _handleActionKeyInput(int ascii);

private:
	std::shared_ptr<Entity> _pawn;
	clan::Vec2i _dir;

	enum Intent
	{
		MOVE,
		INTENT_COUNT
	};
	std::vector<bool> _intent;
};