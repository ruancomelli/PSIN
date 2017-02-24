from tkinter import *
root = Tk()

from simulate import *

simulationName = 'Simulation1'
programName ='CollidingSpheres.exe'

# possible graphs bools
possibleGraph = {}
for i in range( len(graphType) ):
	possibleGraph[ graphType[i] ] = BooleanVar()
	possibleGraph[ graphType[i] ].set(True)
	# use: possibleGraph[ graphType ].get()

# possible video types
videoTypes = ["by time step" , "global" , "autoscale"]
videoTypeChoice = StringVar()

def transformToBool( possibleGraph ):
	bools = {}
	for i in range( len(possibleGraph) ):
		bools[graphType[i]] = possibleGraph[ graphType[i] ].get()

	return bools

class SimulateInterface( Frame ):
	
	def simulateCommand():
		pass

	def generateCommand( self ):
		generateGraphics(simulationName , programName , videoTypeChoice.get() , transformToBool(possibleGraph))

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
			cb = Checkbutton(self , text=graphType[i] , variable=possibleGraph[graphType[i]] )
			self.checkButton.append( cb )
			self.checkButton[i].grid(row=row , column=i, sticky=W+E+N+S )

		# choose video type
		row = 1
		videoTypeChoice.set( videoTypes[0] )
		for i in range( len(videoTypes) ):
			self.videoTypeOption = Radiobutton(self , text=videoTypes[i] , variable=videoTypeChoice , value=videoTypes[i])
			self.videoTypeOption.grid(row=row , column=i, sticky=W+E+N+S )
		
		# Generate graphs button
		row = 2
		column = int(len(graphType) / 2) - 1
		text = 'Generate Graphics'
		self.generateGraph = Button(self , text=text , command=self.generateCommand)
		self.generateGraph.grid(row=row , column=column, sticky=W+E+N+S )
		
#		self.whatever = Whatever( self , width= , height= ,  )
#		self.whatever.grid(row= , column= , columnspan= , rowspan= , sticky=W+E+N+S , padx= , pady= )

def main():
	SimulateInterface().mainloop() # starts event loop

if __name__ == "__main__":
	main()