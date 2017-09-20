#ifndef COMMAND_LINE_PARSER_CPP
#define COMMAND_LINE_PARSER_CPP

#include <CommandLineParser.hpp>

// UtilsLib
#include <FileSystem.hpp>
#include <ProgramOptions.hpp>
#include <string.hpp>

// Standard
#include <iostream>

namespace psin {

// Parse command line
string CommandLineParser::parseArgvIntoSimulationName(int argc, char * argv[])
{
	return CommandLineParser::parseArgvIntoSimulationNameAndRootPath(argc, argv).first;
}

string CommandLineParser::parseArgvIntoSimulationRootPath(int argc, char * argv[])
{
	return CommandLineParser::parseArgvIntoSimulationNameAndRootPath(argc, argv).second;
}

std::pair<string, string> CommandLineParser::parseArgvIntoSimulationNameAndRootPath(int argc, char * argv[])
{
	string simulationName = "Simulation1";
	string rootPath = parentDirectory( parentDirectory( currentDirectory() ) );

	program_options::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("simulation", program_options::value<string>(), "simulation's name")
		("root", program_options::value<string>(), "simulation's root folder")
	;

	program_options::variables_map vm = psin::parseCommandLine(argc, argv, desc);

	if(vm.count("help"))
	{
		std::cout << desc << "\n";
		exit(0);
	}

	if(vm.count("simulation"))
	{
		simulationName = vm["simulation"].as<string>();
	}

	if(vm.count("root"))
	{
		rootPath = vm["root"].as<string>();
	}

	return std::pair<string, string>( simulationName, rootPath );
}

string CommandLineParser::parseArgvIntoSimulationPath(int argc, char * argv[])
{
	string simulationPath = parentDirectory( parentDirectory( currentDirectory() ) );

	program_options::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("path", program_options::value<string>(), "Configuration filepath")
	;

	program_options::variables_map vm = psin::parseCommandLine(argc, argv, desc);

	if(vm.count("help"))
	{
		std::cout << desc << "\n";
		exit(0);
	}

	if(vm.count("path"))
	{
		simulationPath = vm["path"].as<string>();
	}

	return simulationPath;
}

} // psin

#endif // COMMAND_LINE_PARSER_CPP
