import os
from getSimulationData import getSimulationData
from tkinter import *
root = Tk()

########## Simulation definitions ##########

# General
simulationName = 'Simulation1'
programName ='CollidingSpheres.exe'
videoType = ["by_time_step" , "global" , "autoscale"]
graphType = [ 'energy' , 'linear_momentum' , 'angular_momentum' , 'force' , 'torque' ]

# Paths
simulationInputPath = "../_input/input.txt"
simulationOutputFolder = "../_output/" + simulationName + "/"
pythonOutputFolder = "../_output/" + simulationName + "/Python_output/"
programFolder = "../_build/apps/Release/"

os.makedirs(pythonOutputFolder, exist_ok=True)

########## GUI utilities ##########

# getData
[	simulationSettings,
	particleData,
	timeVectorForPlot,
	scalarMap
] = getSimulationData(
	simulationName,
	simulationInputPath,
	simulationOutputFolder
	)

# simulate GUI - Simulation name
simulationNameOption = StringVar()
simulationNameOption.set( simulationName )

# simulate GUI - Program name
programNameOption = StringVar()
programNameOption.set( programName )

# graphs bools
graphBooleanVars = {}
for i in range( len(graphType) ):
	graphBooleanVars[ graphType[i] ] = BooleanVar()
	graphBooleanVars[ graphType[i] ].set(True)
	# use: graphBooleanVars[ graphType ].get()

# video bools
buildVideo = BooleanVar()
videoBooleanVars = {}
for i in range( len(videoType) ):
	videoBooleanVars[ videoType[i] ] = BooleanVar()
	videoBooleanVars[ videoType[i] ].set(False)
	# use: graphBooleanVars[ graphType ].get()

# transform a 'BooleanVar' in a 'bool'
def transformToBool( booleanVars , types ):
	bools = {}
	for i in range( len(booleanVars) ):
		bools[ types[i] ] = booleanVars[ types[i] ].get()
		# use : bools[ type ]

	return bools

# video time
videoTime = StringVar()
videoTime.set("1")