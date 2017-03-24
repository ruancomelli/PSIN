# Class used to get the user input.

from config import *
from tkinter import *
import os

class UserInput:

	def __init__( self , frame ):
		
		### Data set by the user: ###
		#	simulationName
		#	buildType
		#	programName

		self.simulationName = StringVar()
		self.simulationName.set( simulationName )

		self.buildType = StringVar()
		self.buildType.set( buildType )

		self.programName = StringVar()
		self.programName.set( programName )

		# Getting PROJECT_PATH
		self.pythonPath = os.getcwd()
		self.rootFolder = self.pythonPath + "/../"

		
		### Get simulationName ###

		# Label
		row = 0
		column = 0
		self.simulationNameLabelText = "Simulation name:"
		self.simulationNameLabel = Label( frame , text=self.simulationNameLabelText )
		self.simulationNameLabel.grid(row=row , column=column, sticky=W+E+N+S )

		# Entry
		row = 0
		column = 1
		self.simulationNameEntry = Entry( frame , width=40 , font="Arial 10" , textvariable=self.simulationName )
		self.simulationNameEntry.grid(row=row , column=column, sticky=W+E+N+S )


		### Get programName ###

		# Label
		row = 1
		column = 0
		self.programNameLabelText = "Program name (insert \".exe\"):"
		self.programNameLabel = Label( frame , text=self.programNameLabelText )
		self.programNameLabel.grid(row=row , column=column, sticky=W+E+N+S )

		# Entry
		row = 1
		column = 1
		self.programNameEntry = Entry( frame , width=40 , font="Arial 10" , textvariable=self.programName )
		self.programNameEntry.grid(row=row , column=column, sticky=W+E+N+S )

		### Get build type ###

		# Label
		row = 2
		column = 0
		self.buildTypeLabelText = "Program build type:"
		self.buildTypeLabel = Label( frame , text=self.buildTypeLabelText )
		self.buildTypeLabel.grid(row=row , column=column, sticky=W+E+N+S )

		# Radiobuttons
		row = 2
		self.buildTypeRadioButtons = []
		for i in range( len(buildTypes) ):
			column = i+1
			rb = Radiobutton( frame , text=buildTypes[i] , variable=self.buildType , value=buildTypes[i] )
			self.buildTypeRadioButtons.append( rb )
			self.buildTypeRadioButtons[i].grid(row=row , column=column , sticky=W+E+N+S )

	def get( self ):
		# It returns the information we want.

		# pre-process program name
		self.programPath = self.rootFolder + "_build/apps/" + self.buildType.get() + "/" + self.programName.get()
		
		return [ self.simulationName.get() , self.programPath , self.rootFolder ]
		# Use: [ simulationName , programPath , rootFolder ] = self.userInput.get()