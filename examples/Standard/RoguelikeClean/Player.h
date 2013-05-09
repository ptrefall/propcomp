#pragma once

#include "Controller.h"

class Player : public Controller
{
public:
	Player();
	virtual ~Player();

protected:
	void _internalThink() override;

private:
	void _handleInput();
	void _handleActionKeyInput(int ascii);
};