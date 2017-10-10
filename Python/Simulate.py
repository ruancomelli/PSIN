# Class used to run simulations.

from config import *
from tkinter import *
import subprocess

class Simulate():

	def execute( self ):
		# After: add pos processing, get the progrma return code

		programPath = self.paths.getSimulationProgramPath()
		mainInputFilePath = self.paths.getSimulationMainInputFilePath()

		self.display.message("Simulating")

		programArg = "-- path=\"" + mainInputFilePath + "\" "

		# Handle errors
		# Possible errors:
		#	executable not found
		try:
			subprocess.run( [programPath, programArg] )
		except FileNotFoundError:
			self.display.message("Simulation program not found")
			return

		self.display.message("Simulation done")

	def __init__( self , frame , userInput , paths , display ):

		### Store references to objects ###
		self.userInput = userInput
		self.paths = paths
		self.display = display

		### Simulate ###
		row = 0
		column = 0
		self.simulateButtonText = "Simulate"
		self.simulateButton = Button( frame , text=self.simulateButtonText , command=self.execute)
		self.simulateButton.grid(row=row , column=column, sticky=N+S )
