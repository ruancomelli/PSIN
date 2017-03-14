// Standard
#include <string>

// SimulationLib
#include <Simulation.h>

using namespace std;

const string project_root_path = PROJECT_PATH;

int main(int argc, char **argv){
	Simulation simulation(project_root_path);

	simulation.doItAll(project_root_path);
}
