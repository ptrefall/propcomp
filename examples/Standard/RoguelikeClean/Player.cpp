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

	switch(key.vk) 
	{
		case TCODK_UP : 
		case TCODK_KP8 :	_dir.y=-1; break;
		case TCODK_KP7 :	_dir.y=-1; _dir.x=-1; break;
		case TCODK_KP9 :	_dir.y=-1; _dir.x=1; break;
		case TCODK_DOWN :	
		case TCODK_KP2 :	_dir.y=1; break;
		case TCODK_KP1 :	_dir.y=1; _dir.x=-1; break;
		case TCODK_KP3 :	_dir.y=1; _dir.x=1; break;
		case TCODK_LEFT :	
		case TCODK_KP4 :	_dir.x=-1; break;
		case TCODK_RIGHT :	
		case TCODK_KP6 :	_dir.x=1; break;
		case TCODK_CHAR : _handleActionKeyInput(key.c); break;
		default:break;
	}

	if( _dir.x != 0 || _dir.y != 0)
	{
		GameManager::Get()->getState()->Set(GameStateManager::NEW_TURN);
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
				auto walk = actor->GetSkill("Walk");
				if(walk)
				{
					auto dex = actor->GetAttribute("Dexterity");
					if(dex)
					{
						elapsedTime = walk->ElapsedTime( dex->Value() );
		
						GameManager::Get()->getTurn()->schedule(elapsedTime, _pawn, walk);
					}
				}
			}
		}
		return elapsedTime;
	}
	return elapsedTime;
}
