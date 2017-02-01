# -*- coding: utf-8 -*-
"""
Created on Tue Jan 31 15:45:23 2017

@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

from tkinter import *

class WellcomeWindow( Frame ):
	
	def __init__(self):
		Frame.__init__(self)
		self.grid( sticky=W+E+N+S )
		
		self.inputButton = Button( self, text="Input", command=self.openInputWindow )
		self.inputButton.grid( row=2, column=1, padx=500, pady=6)
		pass
		
	def openInputWindow(self):
		pass

def main():
	WellcomeWindow().mainloop()

main()