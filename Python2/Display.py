from tkinter import *

class Display:

	def __init__(self , frame , mainWindow):

		### Store a reference to main window ###
		self.mainWindow = mainWindow

		### Create label ###
		self.infoLabelMessage = "Insert your simulation configuration"
		self.infoLabel = Label(frame , text=self.infoLabelMessage , font="Arial 15")
		self.infoLabel.grid( sticky=N+S )

	def message(self , text):
		self.infoLabel["text"] = text
		self.mainWindow.update()