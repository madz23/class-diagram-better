///
/// \Authors Hunter, Patience, Austin Lyman
/// \file ClassParser.cpp
/// \note The implementation file for the class parser class. Only initializes the static regex fields for the header file.
///

#include "ClassParser.hh"

// Static Fields Initialization
std::regex ClassParser::classRegex = std::regex(R"(class\s+([A-z0-9_]+)\s*:?\s*((?:(?:private|public|protected)\s*\w+,?\s*)*)\{)");
std::regex ClassParser::methodRegex = std::regex(R"((?:static\s+)?((?:\w+::)*\w+(?:<.*>)? *&*\**) +(\w+) *(\(.*\)) *(?:const)*)");
std::regex ClassParser::fieldRegex = std::regex(R"((?:static\s+)?((?:\w+::)*\w+(?:<.*>)? *&*\**) +(\w+) *(?:const)*;)");
std::regex ClassParser::scopeRegex = std::regex(R"((private|public|protected):)");
std::regex ClassParser::typeRegex = std::regex(R"(((?:\w+::)*)(\w+)(?:<((?:\w+::)*(\w+).*)>)?)");
std::regex ClassParser::commentRegex = std::regex(R"((?:(\/\/.*\n)|(\/\*+\*+(?:[^\/\*][^\*]*\*+)*\/)))");
std::regex ClassParser::multiLineCommentRegex = std::regex(R"((?:\/\*\*+))");
std::regex ClassParser::inheritanceRegex = std::regex(R"((?:private|public|protected)\s*(\w+))");

std::set<std::string> ClassParser::collectionTypes = {
	"vector",
	"deque",
	"forward_list",
	"list",
	"stack",
	"queue",
	"priority_queue",
	"set",
	"multiset",
	"map",
	"multimap",
	"unordered_set",
	"unordered_multiset",
	"unordered_map",
	"unordered_multimap"
};
