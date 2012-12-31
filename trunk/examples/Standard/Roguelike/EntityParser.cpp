#include "EntityParser.h"
#include "Engine.h"
#include "Entity.h"

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
	std::string struct_name = str->getName();
	if(struct_name == "entity")
		entities.push_back(std::make_shared<Entity>(name));
    return true;
}
bool EntityParserListener::parserFlag(TCODParser *parser,const char *name)
{
	printf ("found new flag '%s'\n",name);
	if(entities.empty())
		return false;

	std::string flag_name = name;

	auto engine = Engine::getSingleton();
	auto render_system = engine->getRenderSystem();
	auto entity = entities.back();

	if(flag_name == "Actor")
	{
		entity->addComponent(std::make_shared<Actor>(entity, render_system));
	}
	else if(flag_name == "Ai")
	{
		//This component doesn't do anything yet... and might not ever do anything at all, 
		//since Player and Monster components takes care of that logic right now. Might
		//change that in the future though, as common behavior related to intelligence
		//could merge in this component.
	}
	else if(flag_name == "Attacker")
	{
		entity->addComponent(std::make_shared<Attacker>(entity));
	}
	else if(flag_name == "Consumable")
	{
		entity->addComponent(std::make_shared<Consumable>(entity));
	}
	else if(flag_name == "Container")
	{
		entity->addComponent(std::make_shared<Container>(entity));
	}
	else if(flag_name == "Destructible")
	{
		entity->addComponent(std::make_shared<Destructible>(entity, render_system));
	}
	else if(flag_name == "Monster")
	{
		entity->addComponent(std::make_shared<Monster>(entity));
	}
	else if(flag_name == "Pickable")
	{
		entity->addComponent(std::make_shared<Pickable>(entity, render_system));
	}
	else if(flag_name == "Player")
	{
		entity->addComponent(std::make_shared<Player>(entity, render_system));
	}
		//Magic
	else if(flag_name == "Effect")
	{
		entity->addComponent(std::make_shared<Effect>(entity));
	}
	else if(flag_name == "Healer")
	{
		entity->addComponent(std::make_shared<Healer>(entity));
	}
	else if(flag_name == "Weave")
	{
		entity->addComponent(std::make_shared<Weave>(entity));
	}
	return true;
}
bool EntityParserListener::parserProperty(TCODParser *parser,const char *name, TCOD_value_type_t type, TCOD_value_t value)
{
	printf ("found new property '%s'\n",name);
	if(entities.empty())
		return false;

	std::string prop_name = name;

	auto engine = Engine::getSingleton();
	auto entity = entities.back();

	if(prop_name == "Character")
	{
		entity->get<int>(prop_name) = (int)value.c;
	}
	else if(prop_name == "Color")
	{
		entity->get<TCODColor>(prop_name) = value.col;
	}
	else if(prop_name == "Defense")
	{
		entity->get<float>(prop_name) = value.f;
	}
	else if(prop_name == "MaxHP")
	{
		entity->get<float>(prop_name) = value.f;
	}
	else if(prop_name == "HP")
	{
		entity->get<float>(prop_name) = value.f;
	}
	else if(prop_name == "Power")
	{
		entity->get<float>(prop_name) = value.f;
	}
	else if(prop_name == "InventoryMaxSize")
	{
		entity->get<int>(prop_name) = value.i;
	}
	else if(prop_name == "CorpseName")
	{
		entity->get<std::string>(prop_name) = value.s;
	}

	else if(prop_name == "Blocks")
	{
		entity->get<float>(prop_name) = value.f;
	}
	else if(prop_name == "Amount")
	{
		entity->get<float>(prop_name) = value.f;
	}
	else if(prop_name == "Message")
	{
		entity->get<std::string>(prop_name) = value.s;
	}
	else if(prop_name == "TargetSelector")
	{
		//This property is slightly more advanced...
		if(entity->hasComponent<Effect>())
		{
			auto effect = entity->getComponent<Effect>();
			std::string selector_type = value.s;

			if(selector_type == "ClosestMonster")
				effect->setSelector(std::make_shared<TargetSelector>(TargetSelector::CLOSEST_MONSTER));
			else if(selector_type == "SelectedMonster")
				effect->setSelector(std::make_shared<TargetSelector>(TargetSelector::SELECTED_MONSTER));
			else if(selector_type == "SelectedRange")
				effect->setSelector(std::make_shared<TargetSelector>(TargetSelector::SELECTED_RANGE));
		}
	}
	else if(prop_name == "TargetRange")
	{
		//This property is slightly more advanced too...
		if(entity->hasComponent<Effect>())
		{
			auto effect = entity->getComponent<Effect>();

			//Note that TargetSelector property must have been defined before this property is set...
			if(effect->getSelector())
				effect->getSelector()->setRange(value.f);

			//else we should throw an exception, or at least print a warning about it!
		}
	}

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
