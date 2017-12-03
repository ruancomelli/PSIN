import os
import json

class Paths:

	def __init__( self , userInput ):

		### Store references to objects ###
		self.userInput = userInput

	def generate( self ):
		# This class receives a UserInput class
		# reference and returns the paths used by
		# the interface

		[ programPath , mainInputFilePath ] = self.userInput.get()
		self.programPath = programPath.get()
		self.mainInputFilePath = mainInputFilePath.get()

		with open(self.mainInputFilePath) as mainInputFile:    
			mainInput = json.load(mainInputFile)

		# Important data:
		# mainInput["MainOutputFolder"]: the path of mainOutputFolder. 
		# 	This folder contains a file named 'main.json' and a folder named 'input'
		# 	input/ contains the input files used to run the simulation
		# 	main.json is the main simulation file.
		# mainInput["ParticleOutputFolder"]: the path of particleOutputFolder. 
		# 	For each particle in the simulation, there is exactly one file in this folder,
		# 	named after the particle's name, of this particle's history.
		# mainInput["BoundaryOutputFolder"]: the path of boundaryOutputFolder. 
		# 	For each boundary in the simulation, there is exactly one file in this folder,
		# 	named after the boundary's name, of this boundary's history.

		self.particleFilePaths = []
		for (_, _, filenames) in os.walk(mainInput["ParticleOutputFolder"]):
			for filename in filenames:
				particleFilePath = os.path.join(mainInput["ParticleOutputFolder"], filename)
				self.particleFilePaths.append( particleFilePath )
			break


		self.boundaryFilePaths = []
		for (_, _, filenames) in os.walk(mainInput["BoundaryOutputFolder"]):
			for filename in filenames:
				boundaryFilePath = os.path.join(mainInput["BoundaryOutputFolder"], filename)
				self.boundaryFilePaths.append( boundaryFilePath )
			break

		self.simulationPlotFolder = os.path.join(mainInput["MainOutputFolder"], "Plots")
		self.simulationAnimationFolder = os.path.join(mainInput["MainOutputFolder"], "Animations")
		self.timeVectorPath = os.path.join(mainInput["MainOutputFolder"], "timeVector.json")
		self.mainOutputFilePath = os.path.join(mainInput["MainOutputFolder"], "main.json")

		# Create directories

		os.makedirs(self.simulationPlotFolder, exist_ok = True)
		os.makedirs(self.simulationAnimationFolder, exist_ok = True)


	def getSimulationProgramPath( self ):
		self.generate()

		return self.programPath

	def getSimulationTimeVectorPath( self ):
		self.generate()

		return self.timeVectorPath

	def getSimulationMainInputFilePath( self ):
		self.generate()

		return self.mainInputFilePath

	def getSimulationMainOutputFilePath( self ):
		self.generate()

		return self.mainOutputFilePath

	def getSimulationParticleFilePaths( self ):
		self.generate()

		return self.particleFilePaths

	def getSimulationBoundaryFilePaths( self ):
		self.generate()

		return self.boundaryFilePaths

	def getSimulationPlotsOutputFolder( self ):
		self.generate()

		return self.simulationPlotFolder

	def getSimulationAnimationsOutputFolder( self ):
		self.generate()

		return self.simulationAnimationFolder