# Class used to run simulations.

from config import *
from tkinter import *
import subprocess

class Simulate():

	def execute( self ):
		# After: add pos processing, get the progrma return code

		[ simulationName , programPath , rootFolder ] = self.userInput.get()

		self.display.message("Simulating")

		self.simulationNameToProgram = " --simulation=" + simulationName + " "
		self.rootFolderToProgram = " --root=" + rootFolder + " "

		# Handle with errors
		# Possible errors:
		#	executable not found
		try:
			subprocess.run( programPath + self.rootFolderToProgram + self.simulationNameToProgram )
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
