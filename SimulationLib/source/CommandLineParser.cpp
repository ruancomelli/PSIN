#ifndef COMMAND_LINE_PARSER_CPP
#define COMMAND_LINE_PARSER_CPP

#include <CommandLineParser.hpp>

// UtilsLib
#include <FileSystem.hpp>
#include <ProgramOptions.hpp>

// Standard
#include <iostream>
#include <string>

namespace psin {

// Parse command line
std::string CommandLineParser::parseArgvIntoSimulationName(int argc, char * argv[])
{
	return CommandLineParser::parseArgvIntoSimulationNameAndRootPath(argc, argv).first;
}

std::string CommandLineParser::parseArgvIntoSimulationRootPath(int argc, char * argv[])
{
	return CommandLineParser::parseArgvIntoSimulationNameAndRootPath(argc, argv).second;
}

std::pair<std::string, std::string> CommandLineParser::parseArgvIntoSimulationNameAndRootPath(int argc, char * argv[])
{
	std::string simulationName = "Simulation1";
	std::string rootPath = parentDirectory( parentDirectory( currentDirectory() ) );

	ProgramOptions::OptionsDescription desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("simulation", ProgramOptions::value<std::string>(), "simulation's name")
		("root", ProgramOptions::value<std::string>(), "simulation's root folder")
	;

	ProgramOptions::VariablesMap vm = psin::parseCommandLine(argc, argv, desc);

	if(vm.count("help"))
	{
		std::cout << desc << "\n";
		exit(0);
	}

	if(vm.count("simulation"))
	{
		simulationName = vm["simulation"].as<std::string>();
	}

	if(vm.count("root"))
	{
		rootPath = vm["root"].as<std::string>();
	}

	return std::pair<std::string, std::string>( simulationName, rootPath );
}

std::string CommandLineParser::parseArgvIntoSimulationPath(int argc, char * argv[])
{
	std::string simulationPath = parentDirectory( parentDirectory( currentDirectory() ) );

	ProgramOptions::OptionsDescription desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("path", ProgramOptions::value<std::string>(), "Configuration filepath")
	;

	ProgramOptions::VariablesMap vm = psin::parseCommandLine(argc, argv, desc);

	if(vm.count("help"))
	{
		std::cout << desc << "\n";
		exit(0);
	}

	if(vm.count("path"))
	{
		simulationPath = vm["path"].as<std::string>();
	}

	return simulationPath;
}

} // psin

#endif // COMMAND_LINE_PARSER_CPP
