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

		[ self.programPath , self.mainInputFilePath ] = self.userInput.get()

		with open(self.mainInputFilePath.get()) as mainInputFile:    
			mainInput = json.load(mainInputFile)

		# Important data:
		# mainInput["mainOutputFolder"]: the path of mainOutputFolder. 
		# 	This folder contains a file named 'main.json' and a folder named 'input'
		# 	input/ contains the input files used to run the simulation
		# 	main.json is the main simulation file.
		# mainInput["particleOutputFolder"]: the path of particleOutputFolder. 
		# 	For each particle in the simulation, there is exactly one file in this folder,
		# 	named after the particle's name, of this particle's history.
		# mainInput["boundaryOutputFolder"]: the path of boundaryOutputFolder. 
		# 	For each boundary in the simulation, there is exactly one file in this folder,
		# 	named after the boundary's name, of this boundary's history.

		self.particleFilePaths = []
		for (_, _, filenames) in os.walk(mainInput["particleOutputFolder"]):
			for filename in filenames:
				particleFilePath = os.path.join(mainInput["particleOutputFolder"], filename)
				self.particleFilePaths.append( particleFilePath )
			break


		self.boundaryFilePaths = []
		for (_, _, filenames) in os.walk(mainInput["boundaryOutputFolder"]):
			for filename in filenames:
				boundaryFilePath = os.path.join(mainInput["boundaryOutputFolder"], filename)
				self.boundaryFilePaths.append( boundaryFilePath )
			break

		self.simulationPlotFolder = os.path.join(mainInput["mainOutputFolder"], "Plots")
		self.simulationAnimationFolder = os.path.join(mainInput["mainOutputFolder"], "Animations")

		# Create directories

		os.makedirs(self.simulationPlotFolder, exist_ok = True)
		os.makedirs(self.simulationAnimationFolder, exist_ok = True)


	def getSimulationProgramPath( self ):
		self.generate()

		return self.programPath

	def getSimulationMainInputFilePath( self ):
		self.generate()

		return self.mainInputFilePath

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