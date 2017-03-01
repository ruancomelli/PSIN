from interfaceDefinitions import *
from simulate import *

class SimulateInterface( Frame ):
	
	def simulateCommand():
		pass

	def generateCommand( self ):
		# processing before call 'generateGraphics'
		graphBools = transformToBool( possibleGraph , graphType)
		videoBools = transformToBool( possibleVideo , videoType)
		print(videoBools)

		# if some king of video was chosen, then 'buildVideo'
		# is set True.
		if( True in videoBools.values() ):
			buildVideo = True
		else:
			buildVideo = False

		# generate everything the user choose
		generateGraphics(
			simulationName = simulationName ,
			programName = programName ,
			graphBools = graphBools ,
			buildVideo = buildVideo ,
			videoBools = videoBools
			)

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

		# choose video types
		row = 1
		for i in range( len(videoType) ):
			self.videoTypeOption = Checkbutton(self , text=videoType[i] , variable=possibleVideo[ videoType[i] ])
			# self.videoTypeOption = Radiobutton(self , text=videoTypes[i] , variable=videoTypeChoice , value=videoTypes[i])
			self.videoTypeOption.grid(row=row , column=i, sticky=W+E+N+S )
		
		# Generate graphs button
		row = 2
		column = int(len(graphType) / 2)
		text = 'Generate Graphics'
		self.generateGraph = Button(self , text=text , command=self.generateCommand)
		self.generateGraph.grid(row=row , column=column, sticky=W+E+N+S )
		
#		self.whatever = Whatever( self , width= , height= ,  )
#		self.whatever.grid(row= , column= , columnspan= , rowspan= , sticky=W+E+N+S , padx= , pady= )

def main():
	SimulateInterface().mainloop() # starts event loop

if __name__ == "__main__":
	main()