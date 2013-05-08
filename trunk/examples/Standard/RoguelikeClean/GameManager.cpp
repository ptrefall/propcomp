#include "GameManager.h"
#include "Parser.h"
#include "GameStateManager.h"
#include "TurnManager.h"
#include "RenderManager.h"
#include "EntityContainer.h"
#include "EntityFactory.h"
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
	_player.reset();
	_entities.reset();
	_renderer.reset();
}

bool GameManager::initialize(const std::string &resourceDir)
{
	_parser = std::unique_ptr<Parser>(new Parser(resourceDir));
	_state = std::make_shared<GameStateManager>();
	_turn = std::make_shared<TurnManager>();
	_renderer = std::make_shared<RenderManager>();
	_player = std::make_shared<Player>();
	_entities = std::make_shared<EntityContainer>();
	_factory = std::make_shared<EntityFactory>();

	auto cfg = _parser->parseCfg("Config.cfg");
	TCODConsole::setCustomFont((resourceDir + cfg.Font).c_str());
	TCODConsole::initRoot(cfg.Width, cfg.Height, cfg.Title.c_str(), cfg.Fullscreen);

	//TODO: Might want to add a loading screen here?

	if( !_factory->initialize(_entities, _parser->parseStats("Stats.cfg"), _parser->parseEntities("Entities.cfg")) )
		return false;

	_player->Set(_factory->instantiate("human"));

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
	//TCODConsole::root->putChar(40,25,'@');
	_renderer->render();
	TCODConsole::flush();
}
