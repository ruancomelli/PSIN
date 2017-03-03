from tkinter import *
root = Tk()

# Simulation definitions
simulationName = 'Simulation1'
programName ='CollidingSpheres.exe'
videoType = ["by time step" , "global" , "autoscale"]
graphType = [ 'energy' , 'linear_momentum' , 'angular_momentum' , 'force' , 'torque' ]

# simulate GUI
programNameOption = StringVar()
programNameOption.set( programName )

# graphs bools
possibleGraph = {}
for i in range( len(graphType) ):
	possibleGraph[ graphType[i] ] = BooleanVar()
	possibleGraph[ graphType[i] ].set(True)
	# use: possibleGraph[ graphType ].get()

# video bools
buildVideo = BooleanVar()
possibleVideo = {}
for i in range( len(videoType) ):
	possibleVideo[ videoType[i] ] = BooleanVar()
	possibleVideo[ videoType[i] ].set(False)
	# use: possibleGraph[ graphType ].get()

# transform a 'BooleanVar' in a 'bool'
def transformToBool( possibleSomething , somethingType ):
	bools = {}
	for i in range( len(possibleSomething) ):
		bools[ somethingType[i] ] = possibleSomething[ somethingType[i] ].get()
		# use : bools[ type ]

	return bools