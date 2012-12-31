#include "EntityParser.h"
#include "Engine.h"
#include "Entity.h"

#include "Systems/PrefabSystem.h"

#include "Components/Actor.h"
#include "Components/Map.h"
#include "Components/Destructible.h"
#include "Components/Attacker.h"
#include "Components/Player.h"
#include "Components/Monster.h"
#include "Components/Gui.h"
#include "Components/Container.h"
#include "Components/Consumable.h"
#include "Components/Pickable.h"
#include "Components/Magic/Effect.h"
#include "Components/Magic/Healer.h"
#include "Components/Magic/Weave.h"
#include "Utils/TargetSelector.h"

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
		->addProperty("Color", TCOD_TYPE_COLOR, false)
		->addProperty("Defense", TCOD_TYPE_FLOAT, false)
		->addProperty("MaxHP", TCOD_TYPE_FLOAT, false)
		->addProperty("HP", TCOD_TYPE_FLOAT, false)
		->addProperty("Power", TCOD_TYPE_FLOAT, false)
		->addProperty("InventoryMaxSize", TCOD_TYPE_INT, false)
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

	parser->run((Engine::getSingleton()->getResourceDir() + "Entities/Player.cfg").c_str(), new EntityParserListener());
	//parser->run((Engine::getSingleton()->getResourceDir() + "Entities/Monsters.cfg").c_str(), new EntityParserListener());
	//parser->run((Engine::getSingleton()->getResourceDir() + "Entities/Items.cfg").c_str(), new EntityParserListener());
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
EntityParserListener::EntityParserListener()
	: ITCODParserListener(), name(std::string())
{
}

bool EntityParserListener::parserNewStruct(TCODParser *parser,const TCODParserStruct *str,const char *name)
{
	printf ("new structure type '%s' with name '%s'\n", str->getName(), name ? name : "NULL");
	std::string struct_name = str->getName();
	if(struct_name == "entity")
	{
		this->name = name;
		components.clear();
		properties.clear();
		special_properties.clear();
	}
    return true;
}
bool EntityParserListener::parserFlag(TCODParser *parser,const char *name)
{
	printf ("found new flag '%s'\n",name);
	if(this->name.empty())
		return false;

	components.push_back(name);
	return true;
}
bool EntityParserListener::parserProperty(TCODParser *parser,const char *name, TCOD_value_type_t type, TCOD_value_t value)
{
	printf ("found new property '%s'\n",name);
	if(this->name.empty() || components.empty())
		return false;

	std::string prop_name = name;

	auto engine = Engine::getSingleton();

	//Check for special types of properties first...
	if(prop_name == "TargetSelector")
	{
		auto property = new Totem::Property<std::string>(prop_name);
		property->set(value.s, false);
		special_properties.push_back(property);
	}
	else if(prop_name == "TargetRange")
	{
		auto property = new Totem::Property<float>(prop_name);
		property->set(value.f, false);
		special_properties.push_back(property);
	}

	//Then we handle for generic types...
	if(type == TCOD_TYPE_BOOL)
	{
		auto property = new Totem::Property<bool>(prop_name);
		property->set(value.b, false);
		properties.push_back(property);
	}
	else if(type == TCOD_TYPE_INT)
	{
		auto property = new Totem::Property<int>(prop_name);
		property->set(value.i, false);
		properties.push_back(property);
	}
	else if(type == TCOD_TYPE_FLOAT)
	{
		auto property = new Totem::Property<float>(prop_name);
		property->set(value.f, false);
		properties.push_back(property);
	}
	else if(type == TCOD_TYPE_STRING)
	{
		auto property = new Totem::Property<std::string>(prop_name);
		property->set(value.s, false);
		properties.push_back(property);
	}
	else if(type == TCOD_TYPE_COLOR)
	{
		auto property = new Totem::Property<TCODColor>(prop_name);
		property->set(value.col, false);
		properties.push_back(property);
	}
	return true;
}
bool EntityParserListener::parserEndStruct(TCODParser *parser,const TCODParserStruct *str, const char *name)
{
	printf ("end of structure type '%s'\n",name);
	if( this->name.empty() || this->name != std::string(name) )
		return false;

	auto prefab_system = Engine::getSingleton()->getPrefabSystem();
	prefab_system->createPrefab(this->name, components, properties, special_properties);

	return true;
}
void EntityParserListener::error(const char *msg)
{
	fprintf(stderr,msg);
}
