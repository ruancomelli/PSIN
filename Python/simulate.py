# -*- coding: utf-8 -*-
"""
@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import os
import subprocess
from getTagValuePairsFromFile import getTagValuePairsFromFile
from readCSVmatrix import readCSVmatrix

def simulate( simulationName, programName ):
	
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
	programFolder = "../_tests/"
	
	simulationInputFileString = "<simulationName> " + simulationName
	simulationInputFile = open(simulationInputPath, 'w');
	simulationInputFile.write( simulationInputFileString )

	simulationInputFile.close()
	
	os.makedirs(pythonOutputFolder, exist_ok=True)
	
	print( "< Done" )
	
	#
	# SIMULATING
	#
	
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

	timeVector = readCSVmatrix( simulationOutputFolder + "timeVector.txt" )

	print("< Done")
	
	# Read particles' files
	print("> Reading particle files")

	particleData = []
	radiusList = []

	simulationSettings["nParticles"] = int(simulationSettings["nParticles"])
	for counter in range( simulationSettings["nParticles"] ):
		thisParticleName = "Particle" + str(counter)

		print( ">> Inputing ", thisParticleName )

		thisParticleOutputFolder = simulationOutputFolder + thisParticleName + "/"

		thisParticleData = {}

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
		radiusList.append( float(thisParticleData["main"]["Radius"]) )

	print("< Done")

	#
	# PROCESS DATA
	#

	print("> Processing data")
	
	pass
	

	return (particleData, radiusList)

p = simulate('Simulation1', 'collidingspheres_x64.exe')