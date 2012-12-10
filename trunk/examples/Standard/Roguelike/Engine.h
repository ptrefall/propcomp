#pragma once

#include "Utils/Vec2i.h"

#include <libtcod.hpp>
#include <memory>
#include <string>
#include <vector>

class RenderSystem;
typedef std::shared_ptr<RenderSystem> RenderSystemPtr;

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

class Map;
typedef std::shared_ptr<Map> MapPtr;

class Player;
typedef std::shared_ptr<Player> PlayerPtr;

class Gui;
typedef std::shared_ptr<Gui> GuiPtr;

class Engine; typedef std::shared_ptr<Engine> EnginePtr;
class Engine 
{
public:
	enum GameStatus {
        STARTUP,
        IDLE,
        NEW_TURN,
        VICTORY,
        DEFEAT
    } gameStatus;

	static EnginePtr getSingleton();
    ~Engine();
 
	void init(const std::string &resource_dir, int screenWidth, int screenHeight);
    void update();
    void render();

	const std::string &getResourceDir() const { return resource_dir; }
	const RenderSystemPtr &getRenderSystem() const { return render_system; }

	const ActorPtr &getPlayer() const { return player; }
	const MapPtr &getMap() const { return map; }
	const GuiPtr &getGui() const { return gui; }

	EntityPtr createActor(const std::string &name, const Vec2i &pos, int characterID, TCODColor color);
	EntityPtr createMonster(EntityPtr actor, const std::string &corpse_name, float defense, float maxHp, float power);			

	int fovRadius;

	const std::vector<EntityPtr> &getEntities() const { return entities; }
	const std::vector<ActorPtr> &getActors() const { return actors; }

	void remove(const EntityPtr &entity);
	void remove(const ActorPtr &actor);

	const TCOD_key_t &getLastKey() const { return last_key; }
	const TCOD_mouse_t &getMouse() const { return mouse; }

	int getScreenWidth() const { return screenWidth; }
	int getScreenHeight() const { return screenHeight; }

	ActorPtr getClosestMonster(const Vec2i &pos, float range) const;

private:
#if(_MSC_VER >= 1700)
	friend class std::_Ref_count_obj<Engine>;
#else
	friend class std::tr1::_Ref_count_obj<Engine>;
#endif
	static void Shutdown();
	static EnginePtr singleton;
	Engine();

	std::string resource_dir;
	
	RenderSystemPtr render_system;

	std::vector<EntityPtr> entities;
	std::vector<ActorPtr> actors;

	ActorPtr player;
	PlayerPtr player_input;
	MapPtr map;
	GuiPtr gui;

	int screenWidth;
    int screenHeight;
	TCOD_key_t last_key;
	TCOD_mouse_t mouse;
};
