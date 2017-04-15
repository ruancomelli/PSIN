import os

class Paths:

	def __init__( self , userInput ):

		### Store references to objects ###
		self.userInput = userInput

	def generate( self ):
		# This class receives a UserInput class
		# reference and return the paths used by
		# the  interface

		# get user data
		[ simulationName , programPath , rootFolder ] = self.userInput.get()

		# General paths
		self.inputFolder = rootFolder + "_input/"
		self.outputFolder = rootFolder + "_output/"

		# Simulation specific paths
		self.simulationInputFolder = self.inputFolder + simulationName + "/"
		self.simulationOutputFolder = self.outputFolder + simulationName + "/"

		# Simulation output
		self.simulationNumericalOutputFolder = self.simulationOutputFolder + "Numerical/"
		self.simulationGraphicalOutputFolder = self.simulationOutputFolder + "Graphical/"

		# Simulation plot and animation folders
		self.simulationPlotFolder = self.simulationGraphicalOutputFolder + "Plots/"
		self.simulationAnimationFolder = self.simulationGraphicalOutputFolder + "Animations/"

		os.makedirs(self.simulationPlotFolder , exist_ok=True)
		os.makedirs(self.simulationAnimationFolder , exist_ok=True)

	def getSimulationNumericalOutput( self ):
		self.generate()

		return self.simulationNumericalOutputFolder

	def getSimulationPlotsOutputFolder( self ):
		self.generate()

		return self.simulationPlotFolder

	def getSimulationAnimationsOutputFolder( self ):
		self.generate()

		return self.simulationAnimationFolder