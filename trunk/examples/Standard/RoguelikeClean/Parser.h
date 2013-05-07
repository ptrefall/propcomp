#pragma once

#include <libtcod.hpp>
#include <vector>

class Parser
{
public:
	Parser(const std::string &resourceDir);
	~Parser();

	struct CfgInfo
	{
		int Width;
		int Height;
		bool Fullscreen;
		std::string Font;
		std::string Title;
		std::string IntroMessage;
	};
	CfgInfo parseCfg(const std::string &file);

private:
	TCODParser *parser;
	std::string resourceDir;
};

class ParserListener : public ITCODParserListener
{
public:
	ParserListener(Parser::CfgInfo &info);
	~ParserListener();

	bool parserNewStruct(TCODParser *parser,const TCODParserStruct *str,const char *name) override;
	bool parserFlag(TCODParser *parser,const char *name) override;
	bool parserProperty(TCODParser *parser,const char *name, TCOD_value_type_t type, TCOD_value_t value) override;
	bool parserEndStruct(TCODParser *parser,const TCODParserStruct *str, const char *name) override;
	void error(const char *msg) override;

	Parser::CfgInfo *cfgInfo;
};
