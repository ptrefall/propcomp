#include "EntityParser.h"
#include "Engine.h"
#include "Entity.h"

EntityParser::EntityParser()
{
	parser = new TCODParser();
	auto entity_struct = parser->newStructure("entity");

	//Available components
	entity_struct
		->addFlag("Actor")
		->addFlag("Ai")
		->addFlag("Attacker")
		->addFlag("Consumable")
		->addFlag("Container")
		->addFlag("Destructible")
		->addFlag("Monster")
		->addFlag("Pickable")
		->addFlag("Player")
		//Magic
		->addFlag("Effect")
		->addFlag("Healer")
		->addFlag("Weave");

	//Available properties
	entity_struct
		->addProperty("Character", TCOD_TYPE_CHAR, false)
		->addProperty("Color", TCOD_TYPE_STRING, false)
		->addProperty("Defense", TCOD_TYPE_FLOAT, false)
		->addProperty("MaxHP", TCOD_TYPE_FLOAT, false)
		->addProperty("HP", TCOD_TYPE_FLOAT, false)
		->addProperty("Power", TCOD_TYPE_FLOAT, false)
		->addProperty("InventorySpace", TCOD_TYPE_INT, false)
		->addProperty("CorpseName", TCOD_TYPE_STRING, false)

		->addProperty("Blocks", TCOD_TYPE_BOOL, false)
		->addProperty("Amount", TCOD_TYPE_FLOAT, false)
		->addProperty("Message", TCOD_TYPE_STRING, false)
		->addProperty("TargetSelector", TCOD_TYPE_STRING, false)
		->addProperty("TargetRange", TCOD_TYPE_FLOAT, false);

	//Allow inheritance of x num levels
	int INHERITANCE_DEPTH = 4;
	std::vector<TCODParserStruct*> inheritanceDepth;
	inheritanceDepth.push_back(entity_struct);
	for(int i = 0; i < INHERITANCE_DEPTH; i++)
	{
		inheritanceDepth.push_back(inheritanceDepth[i]->addStructure(inheritanceDepth[i]));
	}

	std::vector<EntityPtr> player_list;
	parser->run((Engine::getSingleton()->getResourceDir() + "Entities/Player.cfg").c_str(), new EntityParserListener(player_list));
	if( !player_list.empty() )
		player = player_list[0];
	parser->run((Engine::getSingleton()->getResourceDir() + "Entities/Monsters.cfg").c_str(), new EntityParserListener(monsters));
	parser->run((Engine::getSingleton()->getResourceDir() + "Entities/Items.cfg").c_str(), new EntityParserListener(items));
}

EntityParser::~EntityParser()
{
	delete parser;
}

///////////////////////////////////////////////////
//
// ENTITY PARSER LISTENER
//
///////////////////////////////////////////////////
EntityParserListener::EntityParserListener(std::vector<EntityPtr> &entities)
	: ITCODParserListener(), entities(entities)
{
}

bool EntityParserListener::parserNewStruct(TCODParser *parser,const TCODParserStruct *str,const char *name)
{
	printf ("new structure type '%s' with name '%s'\n", str->getName(), name ? name : "NULL");
    return true;
}
bool EntityParserListener::parserFlag(TCODParser *parser,const char *name)
{
	printf ("found new flag '%s'\n",name);
	return true;
}
bool EntityParserListener::parserProperty(TCODParser *parser,const char *name, TCOD_value_type_t type, TCOD_value_t value)
{
	printf ("found new property '%s'\n",name);
	return true;
}
bool EntityParserListener::parserEndStruct(TCODParser *parser,const TCODParserStruct *str, const char *name)
{
	printf ("end of structure type '%s'\n",name);
	return true;
}
void EntityParserListener::error(const char *msg)
{
	fprintf(stderr,msg);
}
