import SimulateInterface

interface = SimulateInterface.main()

pd = interface.simulationOutputData.get()[1]
time = interface.simulationOutputData.get()[3]

timeIndex = [t for t in time.keys()]
timeInstant = [t for t in time.values()]