#include "GameManager.h"
#include "Parser.h"
#include "GameStateManager.h"
#include "TurnManager.h"
#include "EntityContainer.h"
#include "Player.h"
#include <libtcod.hpp>

std::shared_ptr<GameManager> GameManager::_instance;

std::shared_ptr<GameManager> GameManager::Get()
{
	if(_instance == nullptr)
		_instance = std::make_shared<GameManager>();

	return _instance;
}

void GameManager::Shutdown()
{
	if(_instance != nullptr)
		_instance.reset();
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

bool GameManager::initialize(const std::string &resourceDir)
{
	_parser = std::unique_ptr<Parser>(new Parser(resourceDir));
	_state = std::make_shared<GameStateManager>();
	_turn = std::make_shared<TurnManager>();
	_player = std::make_shared<Player>();
	_entities = std::make_shared<EntityContainer>();

	auto info = _parser->parseCfg("Config.cfg");
	
	TCODConsole::setCustomFont((resourceDir + info.Font).c_str());
	TCODConsole::initRoot(info.Width, info.Height, info.Title.c_str(), info.Fullscreen);

	return true;
}

void GameManager::run()
{
	_load();

	while( TCODConsole::isWindowClosed() == false )
	{
		_update();
		_render();
	}

	_save();
}

void GameManager::restart()
{
	_state->Set(GameStateManager::STARTUP);
}

void GameManager::terminate()
{
	_entities->clear();
}

void GameManager::_load()
{
}

void GameManager::_save()
{
}

void GameManager::_update()
{
	_state->update();
	_state->Set(GameStateManager::IDLE);

	_player->handleInput();
}

void GameManager::_render()
{
	TCODConsole::root->clear();
	TCODConsole::root->putChar(40,25,'@');
	TCODConsole::flush();
}
