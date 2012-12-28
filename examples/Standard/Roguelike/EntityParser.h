#pragma once

#include <libtcod.hpp>
#include <vector>

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;

class EntityParser
{
public:
	EntityParser();
	~EntityParser();

	EntityPtr getPlayer() const { return player; }
	const std::vector<EntityPtr> &getMonsters() const { return monsters; }
	const std::vector<EntityPtr> &getItems() const { return items; }

private:
	TCODParser *parser;

	EntityPtr player;
	std::vector<EntityPtr> monsters;
	std::vector<EntityPtr> items;
};

class EntityParserListener : public ITCODParserListener
{
public:
	EntityParserListener(std::vector<EntityPtr> &entities);

	bool parserNewStruct(TCODParser *parser,const TCODParserStruct *str,const char *name) override;
	bool parserFlag(TCODParser *parser,const char *name) override;
	bool parserProperty(TCODParser *parser,const char *name, TCOD_value_type_t type, TCOD_value_t value) override;
	bool parserEndStruct(TCODParser *parser,const TCODParserStruct *str, const char *name) override;
	void error(const char *msg) override;

private:
	std::vector<EntityPtr> &entities;
};
