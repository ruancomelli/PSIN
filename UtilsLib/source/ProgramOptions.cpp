#include <ProgramOptions.hpp>

namespace psin {
	
program_options::variables_map parseCommandLine(int argc, char * argv[], program_options::options_description & options)
{
	program_options::variables_map vm;

	program_options::store( 
		program_options::parse_command_line(argc, argv, options), 
		vm );

	program_options::notify(vm);

	return vm;
}

} // psin