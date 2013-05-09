#include "Player.h"
#include "GameManager.h"
#include "GameStateManager.h"
#include "TurnManager.h"
#include "ActionManager.h"
#include "MapManager.h"
#include "Entity.h"
#include "PropertyDefinitions.h"
#include "Components/Actor.h"
#include "Math/vec2.h"
#include <libtcod.hpp>

using namespace clan;

Player::Player()
	: Controller()
{
}

Player::~Player()
{
}

void Player::Set(const std::shared_ptr<Entity> &pawn)
{
	Controller::Set(pawn);
	if(pawn && pawn->hasProperty(PROPERTY_POSITION) && pawn->hasProperty(PROPERTY_SIGHT_RADIUS))
		{
			GameManager::Get()->getMap()->computeFov(
				MapManager::LAYER_GROUND, 
				pawn->get<Vec2i>(PROPERTY_POSITION), 
				pawn->get<int>(PROPERTY_SIGHT_RADIUS));
		}
}

void Player::_internalThink()
{
	_handleInput();
}

void Player::_handleInput()
{
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&key,&mouse);

	if(key.vk == TCODK_ESCAPE)
	{
		GameManager::Get()->close();
		return;
	}

	if(_pawn == nullptr)
		return;

	bool waitTurn = false;
	Vec2i dir;
	switch(key.vk) 
	{
		case TCODK_UP : 
		case TCODK_KP8 :	dir.y=-1; break;
		case TCODK_KP7 :	dir.y=-1; dir.x=-1; break;
		case TCODK_KP9 :	dir.y=-1; dir.x=1; break;
		case TCODK_DOWN :	
		case TCODK_KP2 :	dir.y=1; break;
		case TCODK_KP1 :	dir.y=1; dir.x=-1; break;
		case TCODK_KP3 :	dir.y=1; dir.x=1; break;
		case TCODK_LEFT :	
		case TCODK_KP4 :	dir.x=-1; break;
		case TCODK_RIGHT :	
		case TCODK_KP6 :	dir.x=1; break;
		case TCODK_KP5 :	waitTurn = true;
		case TCODK_CHAR : _handleActionKeyInput(key.c); break;
		default:break;
	}

	if( dir.x != 0 || dir.y != 0)
	{
		_dir = dir;
		_dir.x = clan::clamp<int, int, int>(_dir.x, -1, 1);
		_dir.y = clan::clamp<int, int, int>(_dir.y, -1, 1);

		if(_pawn->hasProperty(PROPERTY_POSITION) && _pawn->hasProperty(PROPERTY_SIGHT_RADIUS))
		{
			GameManager::Get()->getMap()->computeFov(
				MapManager::LAYER_GROUND, 
				_pawn->get<Vec2i>(PROPERTY_POSITION), 
				_pawn->get<int>(PROPERTY_SIGHT_RADIUS));
		}

		auto result = GameManager::Get()->getAction()->testMove(_pawn, _dir);
		switch(result)
		{
		case ActionManager::RESULT_MOVE:
		case ActionManager::RESULT_MOVE_TO_ATTACK:
			_actionIntent[result] = true;
			GameManager::Get()->getState()->Set(GameStateManager::NEW_TURN);
			break;

		case ActionManager::RESULT_MOVE_BLOCKED:
		default:
			break;
		};
	}
	else if(waitTurn)
	{
		_actionIntent[ActionManager::WAIT] = true;
		GameManager::Get()->getState()->Set(GameStateManager::NEW_TURN);
	}
}

void Player::_handleActionKeyInput(int ascii)
{
}
