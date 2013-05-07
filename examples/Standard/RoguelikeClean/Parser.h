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

	struct StatsInfo
	{
		struct AttributeInfo
		{
			std::string Description;
			int ExperienceToLevelUp;
			float LevelModifier;
			int BaseValue;
		};

		struct VitalInfo
		{
			std::string Description;
			int ExperienceToLevelUp;
			float LevelModifier;
			int BaseValue;
			std::vector<std::string> ModifierNames;
			std::vector<float> ModifierValues;
		};

		struct SkillInfo
		{
			std::string Description;
			int ExperienceToLevelUp;
			float LevelModifier;
			int BaseValue;
			std::vector<std::string> ModifierNames;
			std::vector<float> ModifierValues;
			int ExperienceAwardedForUse;
			int Cost;
			int Cooldown;
			bool Activated;
		};

		std::vector<AttributeInfo*> Attributes;
		std::vector<VitalInfo*> Vitals;
		std::vector<SkillInfo*> Skills;
	};
	StatsInfo parseStats(const std::string &file);

	struct EntityInfo
	{
		std::string Name;
		std::vector<std::string> Components;
		std::vector<int> AttributeValues;
		std::vector<int> VitalValues;
		std::vector<int> SkillValues;
	};
	EntityInfo parseEntities(const std::string &file);

private:
	TCODParser *parser;
	std::string resourceDir;
};

class ParserListener : public ITCODParserListener
{
public:
	ParserListener(Parser::CfgInfo &info);
	ParserListener(Parser::StatsInfo &info);
	ParserListener(Parser::EntityInfo &info);
	~ParserListener();

	bool parserNewStruct(TCODParser *parser,const TCODParserStruct *str,const char *name) override;
	bool parserFlag(TCODParser *parser,const char *name) override;
	bool parserProperty(TCODParser *parser,const char *name, TCOD_value_type_t type, TCOD_value_t value) override;
	bool parserEndStruct(TCODParser *parser,const TCODParserStruct *str, const char *name) override;
	void error(const char *msg) override;

	Parser::CfgInfo *cfgInfo;
	Parser::StatsInfo *statsInfo;
	Parser::EntityInfo *entityInfo;
};
