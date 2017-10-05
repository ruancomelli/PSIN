# Class used to get the user input.

from config import *
from tkinter import *
import os

class UserInput:

	def __init__( self , frame ):
		
		### Data set by the user: ###
		#	programPath
		#	mainInputFilePath

		self.programPath = StringVar()
		self.programPath.set( programPath )

		self.mainInputFilePath = StringVar()
		self.mainInputFilePath.set( mainInputFilePath )

		
		### Get programPath ###

		# Label
		row = 0
		column = 0
		self.programPathLabelText = "Executable path:"
		self.programPathLabel = Label( frame , text=self.programPathLabelText )
		self.programPathLabel.grid(row=row , column=column, sticky=W+E+N+S )

		# Entry
		row = 0
		column = 1
		self.programPathEntry = Entry( frame , width=40 , font="Arial 10" , textvariable=self.programPath )
		self.programPathEntry.grid(row=row , column=column, sticky=W+E+N+S )


		### Get mainInputFilePath ###

		# Label
		row = 1
		column = 0
		self.mainInputFilePathLabelText = "Main input file path:"
		self.mainInputFilePathLabel = Label( frame , text=self.mainInputFilePathLabelText )
		self.mainInputFilePathLabel.grid(row=row , column=column, sticky=W+E+N+S )

		# Entry
		row = 1
		column = 1
		self.mainInputFilePathEntry = Entry( frame , width=40 , font="Arial 10" , textvariable=self.mainInputFilePath )
		self.mainInputFilePathEntry.grid(row=row , column=column, sticky=W+E+N+S )

	def get( self ):
		# Return the information we want.
		
		return [ self.programPath , self.mainInputFilePath ]
		# Use: [ programPath , mainInputFilePath ] = self.userInput.get()