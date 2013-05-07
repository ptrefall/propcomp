#pragma once

#include <memory>
#include <string>

class Parser;
class GameStateManager;
class TurnManager;
class Player;
class EntityContainer;

class GameManager
{
public:
	~GameManager();
	static std::shared_ptr<GameManager> Get();
	static void Shutdown();

private:
#if(_MSC_VER >= 1700)
	friend class std::_Ref_count_obj<GameManager>;
#else
	friend class std::tr1::_Ref_count_obj<GameManager>;
#endif
	GameManager();
	static std::shared_ptr<GameManager> _instance;

public:
	bool initialize(const std::string &resourceDir);
	void run();
	void restart();
	void terminate();

public:
	const std::shared_ptr<GameStateManager> &getState() { return _state; }
	const std::shared_ptr<TurnManager> &getTurn() { return _turn; }
	const std::shared_ptr<Player> &getPlayer() { return _player; }
	const std::shared_ptr<EntityContainer> &getEntities() { return _entities; }

private:
	void _load();
	void _save();

	void _update();
	void _render();

private:
	std::unique_ptr<Parser> _parser;

	std::shared_ptr<GameStateManager> _state;
	std::shared_ptr<TurnManager> _turn;
	std::shared_ptr<Player> _player;
	std::shared_ptr<EntityContainer> _entities;
};