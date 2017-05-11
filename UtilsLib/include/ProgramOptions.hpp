#ifndef UTILS_PROGRAM_OPTIONS_H
#define UTILS_PROGRAM_OPTIONS_H

#include <boost/program_options.hpp>

namespace boost
{
	namespace program_options
	{
		using OptionsDescription = options_description;
		using VariablesMap = variables_map;
	}
}

namespace ProgramOptions = boost::program_options;

ProgramOptions::VariablesMap parseCommandLine(const int argc, const char ** argv, ProgramOptions::OptionsDescription options);

#endif //UTILS_PROGRAM_OPTIONS_H
