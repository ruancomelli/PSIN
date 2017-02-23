# -*- coding: utf-8 -*-
"""
@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import os
import subprocess

from getTagValuePairsFromFile import getTagValuePairsFromFile
from readCSVmatrix import readCSVmatrix
from processDataHistory import plotParticleDataHistory
from processDataHistory import plotParticleDataHistory3D

import matplotlib.colors as colors
import matplotlib.pyplot as plt
import matplotlib.cm as cmx

from matplotlib import animation
from build_video import build_video


def simulate( simulationName, programName, generateVideo=True ):
	
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
	
	simulationInputPath = "../_input/input.txt"
	simulationOutputFolder = "../_output/" + simulationName + "/"
	pythonOutputFolder = "../_output/" + simulationName + "/Python_output/"
	programFolder = "../_build/apps/Release/"
	
	simulationInputFileString = "<simulationName> " + simulationName
	simulationInputFile = open(simulationInputPath, 'w');
	simulationInputFile.write( simulationInputFileString )

	simulationInputFile.close()
	
	os.makedirs(pythonOutputFolder, exist_ok=True)
	
	print( "< Done" )
	
	#
	# SIMULATING
	#
	# It executes the C++ compiled program
	print( "> Simulating" )
	subprocess.Popen( programFolder + programName )
	print( "< Simulation finished" )
	
	#
	# READ DATA
	#
	
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

	#
	# PROCESS DATA
	#

	print("> Processing data")
	
	# Set colormap
	print(">> Setting colormap")
	
	cmap = plt.get_cmap('gist_rainbow')

	scalarMap = cmx.ScalarMappable( 
		cmap = cmap,
		norm = colors.Normalize( vmin=0 , vmax=simulationSettings["nParticles"]-1 ) )


	print("<< Done")
		
	
	# Plot Energy
	print(">> Plotting mechanical energy")

	plotParticleDataHistory( 
		timeVector = timeVectorForPlot, 
		particleData = particleData, 
		key = "energy", 
		title = "\nMechanical Energy\n", 
		outputFolder = pythonOutputFolder, 
		fileName = "mechanical_energy_plot", 
		extension = ".png", 
		xAxisLabel = "\nTime [s]\n", 
		yAxisLabel = "\nEnergy [J]\n", 
		scalarMap = scalarMap,  
		nParticles = simulationSettings["nParticles"])

	print("<< Done")
	
	# Plot Linear Momentum
	print(">> Plotting linear momentum")

	plotParticleDataHistory3D( 
		timeVector = timeVectorForPlot, 
		particleData = particleData, 
		key = "linear_momentum", 
		title = "\nLinear Momentum", 
		outputFolder = pythonOutputFolder, 
		fileName = "linear_momentum_plot", 
		extension = ".png", 
		xAxisLabel = "\nTime [s]\n", 
		yAxisLabel = "\nLinear Momentum [kg*m/s]\n", 
		scalarMap = scalarMap,  
		nParticles = simulationSettings["nParticles"]
		)

	print("<< Done")
	
	# Plot Angular Momentum
	print(">> Plotting angular momentum")

	plotParticleDataHistory3D( 
		timeVector = timeVectorForPlot, 
		particleData = particleData, 
		key = "angular_momentum", 
		title = "\nAngular Momentum", 
		outputFolder = pythonOutputFolder, 
		fileName = "angular_momentum_plot", 
		extension = ".png", 
		xAxisLabel = "\nTime [s]\n", 
		yAxisLabel = "\nAngular Momentum [kg*m^2/s]\n", 
		scalarMap = scalarMap,  
		nParticles = simulationSettings["nParticles"]
		)

	print("<< Done")
	
	# Plot Resulting Force
	print(">> Plotting force")

	plotParticleDataHistory3D( 
		timeVector = timeVectorForPlot, 
		particleData = particleData, 
		key = "force", 
		title = "\nResulting Force", 
		outputFolder = pythonOutputFolder, 
		fileName = "force_plot", 
		extension = ".png", 
		xAxisLabel = "\nTime [s]\n", 
		yAxisLabel = "\nResulting Force [N]\n", 
		scalarMap = scalarMap,  
		nParticles = simulationSettings["nParticles"]
		)

	print("<< Done")
	
	# Plot Resulting Torque
	print(">> Plotting torque")

	plotParticleDataHistory3D( 
		timeVector = timeVectorForPlot, 
		particleData = particleData, 
		key = "torque", 
		title = "\nResulting Torque", 
		outputFolder = pythonOutputFolder, 
		fileName = "torque_plot", 
		extension = ".png", 
		xAxisLabel = "\nTime [s]\n", 
		yAxisLabel = "\nResulting Torque [N*m]\n", 
		scalarMap = scalarMap,  
		nParticles = simulationSettings["nParticles"]
		)

	print("<< Done")

	# Generate Video

	if generateVideo:
		print(">> Generating video")

		nParticles = simulationSettings["nParticles"]
		build_video(particleData , nParticles)

		print("<< Done")
		

	return particleData

p = simulate('Simulation1', 'CollidingSpheres.exe')