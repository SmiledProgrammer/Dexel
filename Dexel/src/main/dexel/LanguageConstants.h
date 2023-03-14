#ifndef LANGUAGE_CONSTANTS_H
#define LANGUAGE_CONSTANTS_H

#include <map>
#include <set>
#include <string>
#include "Token.h"

namespace dexel {

	const map<char, Token::Type> SYMBOL_TOKENS{
		{'=', Token::TYPE_EQUALS_OPERATOR},
		{'+', Token::TYPE_PLUS_OPERATOR},
		{'-', Token::TYPE_HYPHEN_OPERATOR},
		{'*', Token::TYPE_ASTERISK_OPERATOR},
		{'/', Token::TYPE_FORWARD_SLASH_OPERATOR},
		{';', Token::TYPE_SEMICOLON_SEPARATOR},
		{'(', Token::TYPE_LEFT_PARENTHESES_SEPARATOR},
		{')', Token::TYPE_RIGHT_PARENTHESES_SEPARATOR},
		{'{', Token::TYPE_LEFT_BRACES_SEPARATOR},
		{'}', Token::TYPE_RIGHT_BRACES_SEPARATOR}
	};

	const map<string, Token::Type> DEXEL_KEYWORD_TOKENS{
		{"function", Token::TYPE_FUNCTION_KEYWORD},
		{"if", Token::TYPE_IF_KEYWORD},
		{"else", Token::TYPE_ELSE_KEYWORD},
		{"int", Token::TYPE_INT_KEYWORD}
	};

	const set<string> COMMAND_KEYWORDS{
		"advancement",
		"attribute",
		"ban",
		"ban-ip",
		"banlist",
		"bossbar",
		"clear",
		"clone",
		"damage",
		"data",
		"datapack",
		"debug",
		"defaultgamemode",
		"deop",
		"difficulty",
		"effect",
		"enchant",
		"execute",
		"experience",
		"fill",
		"fillbiome",
		"forceload",
		// "function", // overriden by Dexel language
		"gamemode",
		"gamerule",
		"give",
		"help",
		"item",
		"jfr",
		"kick",
		"kill",
		"list",
		"locate",
		"loot",
		"me",
		"msg",
		"op",
		"pardon",
		"pardon-ip",
		"particle",
		"perf",
		"place",
		"playsound",
		"publish",
		"recipe",
		"reload",
		"ride",
		"save-all",
		"save-off",
		"save-on",
		"say",
		"schedule",
		"scoreboard",
		"seed",
		"setblock",
		"setidletimeout",
		"setworldspawn",
		"spawnpoint",
		"spectate",
		"spreadplayers",
		"stop",
		"stopsound",
		"summon",
		"tag",
		"team",
		"teammsg",
		"teleport",
		"tell",
		"tellraw",
		"time",
		"title",
		"tm",
		"tp",
		"trigger",
		"w",
		"weather",
		"whitelist",
		"worldborder",
		"xp"
	};
}

#endif
