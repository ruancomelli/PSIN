#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include <string>

namespace psin {

struct CommandLineParser
{
	using string = std::string;

	static std::pair<string, string> parseArgvIntoSimulationNameAndRootPath(int argc, char * argv[]);
	static string parseArgvIntoSimulationName(int argc, char * argv[]);
	static string parseArgvIntoSimulationRootPath(int argc, char * argv[]);
	static string parseArgvIntoSimulationPath(int argc, char * argv[]);
};

} // psin

#endif // COMMAND_LINE_PARSER_HPP
