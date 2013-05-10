#pragma once

#include "Controller.h"

class Player : public Controller
{
public:
	Player();
	virtual ~Player();

	void Set(const std::shared_ptr<Entity> &pawn) override;

	void FOV();

protected:
	void _internalThink() override;

private:
	void _handleInput();
	void _handleActionKeyInput(int ascii);
};