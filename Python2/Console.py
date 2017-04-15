from tkinter import *
import os

class Console:

	def __init__( self , frame ):

		# set console size
		self.height = 400
		self.width = 500
		frame.config(height=self.height , width=self.width)

		wid = frame.winfo_id() # Return identifier ID for this widget
		os.system('xterm -into %d -geometry 40x20 -sb &' % wid)