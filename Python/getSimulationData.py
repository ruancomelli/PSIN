from getTagValuePairsFromFile import getTagValuePairsFromFile
from readCSVmatrix import readCSVmatrix
from processDataHistory import plotParticleDataHistory
from processDataHistory import plotParticleDataHistory3D

import matplotlib.colors as colors
import matplotlib.pyplot as plt
import matplotlib.cm as cmx

def getSimulationData(simulationName , simulationInputPath , simulationOutputFolder ):
	#
	# INITIALIZING
	#
	
	# The "Folder" suffix indicates that a variable holds a folder name, as in simulationFolder = "../simulation/"
	# The "Path" suffix means that a variable holds a full file path, as in outputPath = "../simulation/output.txt"
	# The "File" suffix is used to indicate that a variable is a file object, as in outputFile = open("../simulation/output.txt")
	# In general, let X be a token. Then we should be able to write XFile = fopen(XPath) 
	# The "Name" suffix, when applied in the context of files, is a filename, as in programName = "spyder.exe"

	print( "> Initializing Program" )
	print( "==== ", simulationName, " ====" )
	
	simulationInputFileString = "<simulationName> " + simulationName
	simulationInputFile = open(simulationInputPath, 'w');
	simulationInputFile.write( simulationInputFileString )

	simulationInputFile.close()

	# Read main output file
	print("> Reading main output file")
	mainSimulationOutputPath = simulationOutputFolder + "output.txt"
	
	simulationSettings = getTagValuePairsFromFile(mainSimulationOutputPath, "<", ">")
	
	print("< Done")

	# Read time vector
	print("> Reading time vector")
	
	timeVectorForPlot = readCSVmatrix( simulationOutputFolder + "timeVectorForPlot.txt" )

	print("< Done")
	
	# Read particles' files
	print("> Reading particle files")

	particleData = []

	# particleData is accessed using particleData[particleIndex][key][timeIndex][coordinate]
	# For instance, if one wishes to access the Z coordinate, in timeStep number 5, 
	# of the second particle's velocity, one should write:
	# particleData[ 2 - 1 ][ "velocity" ][ 5 - 1 ][ 3 - 1 ], or
	# particleData[ 1 ][ "velocity" ][ 4 ][ 2 ] which stands for
	# particleData["second particle"]["velocity"]["5th timeStep"]["Z coordinate"]
		

	simulationSettings["nParticles"] = int(simulationSettings["nParticles"])
	for counter in range( simulationSettings["nParticles"] ):
		thisParticleName = "Particle" + str(counter)

		print( ">> Inputing ", thisParticleName )

		thisParticleOutputFolder = simulationOutputFolder + thisParticleName + "/"

		thisParticleData = {}

		# It is bad. If we add soemthing different in our main program,
		# we will need to change everything above. It could be interesting
		# to put a 'listdir' and, with its return, create the plots.
		# Plans to future.

		thisParticleData["main"] = getTagValuePairsFromFile( thisParticleOutputFolder + "data.txt", "<", ">" )
		thisParticleData["energy"] = readCSVmatrix( thisParticleOutputFolder + "energy.txt" )
		thisParticleData["position"] = readCSVmatrix( thisParticleOutputFolder + "position.txt" )
		thisParticleData["velocity"] = readCSVmatrix( thisParticleOutputFolder + "velocity.txt" )
		thisParticleData["linear_momentum"] = readCSVmatrix( thisParticleOutputFolder + "linear_momentum.txt" )
		thisParticleData["orientation"] = readCSVmatrix( thisParticleOutputFolder + "orientation.txt" )
		thisParticleData["rotational_velocity"] = readCSVmatrix( thisParticleOutputFolder + "rotational_velocity.txt" )
		thisParticleData["angular_momentum"] = readCSVmatrix( thisParticleOutputFolder + "angular_momentum.txt" )
		thisParticleData["force"] = readCSVmatrix( thisParticleOutputFolder + "force.txt" )
		thisParticleData["torque"] = readCSVmatrix( thisParticleOutputFolder + "torque.txt" )

		particleData.append(thisParticleData)

	print("< Done")

	print("> Processing data")
	
	# Set colormap
	print(">> Setting colormap")
	
	cmap = plt.get_cmap('gist_rainbow')

	scalarMap = cmx.ScalarMappable( 
		cmap = cmap,
		norm = colors.Normalize( vmin=0 , vmax=simulationSettings["nParticles"]-1 ) )

	print("<< Done")

	return [simulationSettings , particleData , timeVectorForPlot , scalarMap]