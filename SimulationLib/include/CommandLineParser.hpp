#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include <string>

namespace psin {

struct CommandLineParser
{
	static std::pair<std::string, std::string> parseArgvIntoSimulationNameAndRootPath(int argc, char * argv[]);
	static std::string parseArgvIntoSimulationName(int argc, char * argv[]);
	static std::string parseArgvIntoSimulationRootPath(int argc, char * argv[]);
};

} // psin

#endif // COMMAND_LINE_PARSER_HPP
