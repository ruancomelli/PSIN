from tkinter import *
root = Tk()

from simulate import *
#from simulate import *

# Initialize all grph possible types

graphType = [ 'energy' , 'linear_momentum' , 'angular_momentum' , 'force' , 'torque' , 'video' ]

possibleGraph = {}
for i in range( len(graphType) ):
	possibleGraph[ graphType[i] ] = BooleanVar()
	possibleGraph[ graphType[i] ].set(True)
	# use: possibleGraph[ graphType ].get()

class SimulateInterface( Frame ):
	
	def simulateCommand():
		pass

	def __init__( self ):

		Frame.__init__( self ) # initializes Frame object

		# Main window config
		self.master.title( 'Particle Simulator' )
#		self.pack( expand=YES , fill=BOTH )
		self.grid( sticky=W+E+N+S )

		# choose which graphs will be build
		row = 0
		self.checkButton = []
		for i in range( len(graphType) ):
			print(i)
			cb = Checkbutton(self , text=graphType[i] , variable=possibleGraph[graphType[i]] )
			self.checkButton.append( cb )
			self.checkButton[i].grid(row=row , column=i, sticky=W+E+N+S )
		
		# Generate graphs button
		row = 1
		column = int(len(graphType) / 2) - 1
		text = 'Generate Graphics'
		self.generateGraph = Button(self , text=text)
		self.generateGraph.grid(row=row , column=column, sticky=W+E+N+S )
		
#		self.whatever = Whatever( self , width= , height= ,  )
#		self.whatever.grid(row= , column= , columnspan= , rowspan= , sticky=W+E+N+S , padx= , pady= )

def main():
	SimulateInterface().mainloop() # starts event loop

if __name__ == "__main__":
	main()