#include "Player.h"
#include "GameManager.h"
#include "GameStateManager.h"
#include "TurnManager.h"
#include "Entity.h"
#include "Components/Actor.h"
#include "Math/vec2.h"
#include <libtcod.hpp>

using namespace clan;

Player::Player()
	: _dir(Vec2i(0,0))
{
	_intent.resize(INTENT_COUNT, false);
}

Player::~Player()
{
}

void Player::handleInput()
{
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&key,&mouse);

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
		case TCODK_CHAR : _handleActionKeyInput(key.c); break;
		default:break;
	}

	if( dir.x != 0 || dir.y != 0)
	{
		GameManager::Get()->getState()->Set(GameStateManager::NEW_TURN);
		_dir = dir;
		_dir.x = clan::clamp<int, int, int>(_dir.x, -1, 1);
		_dir.y = clan::clamp<int, int, int>(_dir.y, -1, 1);
		_intent[MOVE] = true;
	}
}

void Player::_handleActionKeyInput(int ascii)
{
}

int Player::moveOrInteract()
{
	int elapsedTime = 0;

	if(_intent[MOVE])
	{
		//TODO: THIS IS NOT FINISHED! :P
		if(_pawn)
		{
			auto actor = _pawn->getComponent<Actor>();
			if(actor)
			{
				auto walk = actor->GetSkill("walk");
				if(walk)
				{
					auto dex = actor->GetAttribute("dexterity");
					if(dex)
					{
						auto walkCost = (int)floor((walk->ActionCost() * walk->Value()) * 0.1f + 0.5f);
						elapsedTime = (int)floor((walkCost * dex->Value()) * 0.1f + 0.5f);
		
						GameManager::Get()->getTurn()->schedule(elapsedTime, _pawn, walk);
					}
				}
			}
		}
		return elapsedTime;
	}
	return elapsedTime;
}
