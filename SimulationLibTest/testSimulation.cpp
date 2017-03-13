#define BOOST_TEST_MODULE SimulationLibTest

// SimulationLib
#include <Simulation.h>

// UtilsLib
#include <Test.h>

TestCase( EmptyTest )
{
	Simulation("MakeSureThatThisFileDoesNotExist");
}