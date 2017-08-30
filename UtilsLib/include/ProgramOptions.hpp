#ifndef PROGRAM_OPTIONS_HPP
#define PROGRAM_OPTIONS_HPP

#include <boost/program_options.hpp>

namespace psin {

namespace ProgramOptions
{
	using namespace boost::program_options;
	using OptionsDescription = options_description;
	using VariablesMap = variables_map;
}

ProgramOptions::VariablesMap parseCommandLine(int argc, char * argv[], ProgramOptions::OptionsDescription & options);

} // psin

#endif //PROGRAM_OPTIONS_HPP
