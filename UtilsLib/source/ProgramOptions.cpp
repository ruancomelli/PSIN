#include <ProgramOptions.h>

ProgramOptions::VariablesMap parseCommandLine(int argc, char ** argv, ProgramOptions::OptionsDescription options)
{
	ProgramOptions::VariablesMap vm;

	ProgramOptions::store( 
		ProgramOptions::parse_command_line(argc, argv, options), 
		vm );

	ProgramOptions::notify(vm);

	return vm;
}