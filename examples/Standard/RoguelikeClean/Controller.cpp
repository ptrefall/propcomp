#include "Controller.h"
#include "GameManager.h"
#include "GameStateManager.h"
#include "TurnManager.h"
#include "ActionManager.h"
#include "Entity.h"
#include "Components/Actor.h"
#include "Math/vec2.h"
#include <libtcod.hpp>

using namespace clan;

Controller::Controller()
	: _dir(Vec2i(0,0))
{
	_actionIntent.resize(ActionManager::ACTION_TYPE_COUNT, false);
}

Controller::~Controller()
{
}

void Controller::think()
{
	_resetActionIntent();
	_internalThink();
}

void Controller::_resetActionIntent()
{
	for(unsigned int i = 0; i < _actionIntent.size(); i++)
		_actionIntent[i] = false;
}

int Controller::estimateAction()
{
	int elapsedTime = 0;

	if(_pawn == nullptr)
		return elapsedTime;

	if(_actionIntent[ActionManager::MOVE])
		elapsedTime = GameManager::Get()->getAction()->estimateAction(ActionManager::MOVE, _pawn, _dir);
	else if(_actionIntent[ActionManager::ATTACK])
		elapsedTime = GameManager::Get()->getAction()->estimateAction(ActionManager::ATTACK, _pawn, _dir);
	else if(_actionIntent[ActionManager::WAIT])
		elapsedTime = GameManager::Get()->getAction()->estimateAction(ActionManager::WAIT, _pawn, _dir);
	else
		return elapsedTime;

	GameManager::Get()->getTurn()->schedule(elapsedTime, shared_from_this());
	return elapsedTime;
}

void Controller::takeAction()
{
	if(_pawn == nullptr)
		return;

	if(_actionIntent[ActionManager::MOVE])
		GameManager::Get()->getAction()->takeAction(ActionManager::MOVE, _pawn, _dir);
	else if(_actionIntent[ActionManager::ATTACK])
		GameManager::Get()->getAction()->takeAction(ActionManager::ATTACK, _pawn, _dir);
	
}