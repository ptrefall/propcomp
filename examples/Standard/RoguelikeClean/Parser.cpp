#include "Parser.h"

Parser::Parser(const std::string &resourceDir)
	: resourceDir(resourceDir)
{
	parser = new TCODParser();
}

Parser::~Parser()
{
	delete parser;
}

Parser::CfgInfo Parser::parseCfg(const std::string &file)
{
	auto dataStruct = parser->newStructure("config");

	dataStruct
		->addProperty("width", TCOD_TYPE_INT, false)
		->addProperty("height", TCOD_TYPE_INT, false)
		->addProperty("fullscreen", TCOD_TYPE_BOOL, false)
		->addProperty("font", TCOD_TYPE_STRING, false)
		->addProperty("title", TCOD_TYPE_STRING, false)
		->addProperty("introMessage", TCOD_TYPE_STRING, false);

	Parser::CfgInfo info;
	auto tmp = resourceDir;
	parser->run(tmp.append(file).c_str(), new ParserListener(info));
	return info;
}

///////////////////////////////////////////////////
//
// ENTITY PARSER LISTENER
//
///////////////////////////////////////////////////
ParserListener::ParserListener(Parser::CfgInfo &info)
	: ITCODParserListener(), cfgInfo(&info)
{
}

ParserListener::~ParserListener()
{
}

bool ParserListener::parserNewStruct(TCODParser *parser,const TCODParserStruct *str,const char *name)
{
	std::string struct_name = str->getName();
	if(struct_name.compare("config") == 0)
	{
		
	}
    return true;
}
bool ParserListener::parserFlag(TCODParser *parser,const char *name)
{
	return true;
}
bool ParserListener::parserProperty(TCODParser *parser,const char *name, TCOD_value_type_t type, TCOD_value_t value)
{
	std::string propName = name;

	if(propName.compare("width") == 0 && type == TCOD_TYPE_INT)
	{
		if(cfgInfo != nullptr) cfgInfo->Width = value.i;
	}
	else if(propName.compare("height") == 0 && type == TCOD_TYPE_INT)
	{
		if(cfgInfo != nullptr) cfgInfo->Height = value.i;
	}
	else if(propName.compare("fullscreen") == 0 && type == TCOD_TYPE_BOOL)
	{
		if(cfgInfo != nullptr) cfgInfo->Fullscreen = value.b;
	}
	else if(propName.compare("font") == 0 && type == TCOD_TYPE_STRING)
	{
		if(cfgInfo != nullptr) cfgInfo->Font = value.s;
	}
	else if(propName.compare("title") == 0 && type == TCOD_TYPE_STRING)
	{
		if(cfgInfo != nullptr) cfgInfo->Title = value.s;
	}
	else if(propName.compare("introMessage") == 0 && type == TCOD_TYPE_STRING)
	{
		if(cfgInfo != nullptr) cfgInfo->IntroMessage = value.s;
	}
	else 
	{
		return false;
	}

	return true;
}
bool ParserListener::parserEndStruct(TCODParser *parser,const TCODParserStruct *str, const char *name)
{
	return true;
}
void ParserListener::error(const char *msg)
{
	fprintf(stderr,msg);
}
