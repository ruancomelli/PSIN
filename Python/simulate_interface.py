from interfaceDefinitions import *
from simulate import *
from generateGraphics import *
from generateVideo import *

class SimulateInterface( Frame ):
	
	def simulateCommand( self ):
		simulate(
			programFolder = programFolder ,
			programName = programNameOption.get()
			)

	def generateCommand( self ):
		# processing before call 'generateGraphics'
		graphBools = transformToBool( graphBooleanVars , graphType)
		videoBools = transformToBool( videoBooleanVars , videoType)

		# if some king of video was chosen, then 'buildVideo'
		# is set True.
		if( True in videoBools.values() ):
			buildVideo = True
		else:
			buildVideo = False

		# generate everything the user choose

		# Graphics
		generateGraphics(
			timeVectorForPlot =  timeVectorForPlot,
			particleData =  particleData,
			pythonOutputFolder =  pythonOutputFolder,
			scalarMap =  scalarMap,
			simulationSettings =  simulationSettings,
			graphBools = graphBools
			)

		# Video
		generateVideo(
			timeVectorForPlot = timeVectorForPlot ,
			scalarMap = scalarMap ,
			pythonOutputFolder = pythonOutputFolder ,
			simulationSettings = simulationSettings ,
			particleData = particleData ,
			buildVideo = buildVideo ,
			videoBools = videoBools ,
			videoTime = float(videoTime.get()) )

	def __init__( self ):

		Frame.__init__( self ) # initializes Frame object

		# Main window config
		self.master.title( 'Particle Simulator' )
		self.grid( sticky=W+E+N+S )
		
		# Frame 0 : simulate options
		self.frame0 = Frame( self )
		self.frame0.grid( sticky=N+S )
		
		# simulation option
		row = 0
		column = 0
		self.simulationProgramEntry = Entry( self.frame0 , width=40 , font="Arial 10" , textvariable=programNameOption )
		self.simulationProgramEntry.grid(row=row , column=column, sticky=W+E+N+S )

		row = 0
		column = 2
		text = 'Simulate'
		self.simulateButton = Button(self.frame0 , text=text , command=self.simulateCommand)
		self.simulateButton.grid(row=row , column=column, sticky=W+E+N+S )
		
		# Frame 1 : graph generation option
		self.frame1 = Frame( self )
		self.frame1.grid(sticky=W+E+N+S )
		# choose which graphs will be build
		row = 1
		self.checkButton = []
		for i in range( len(graphType) ):
			cb = Checkbutton(self.frame1 , text=graphType[i] , variable=graphBooleanVars[graphType[i]] )
			self.checkButton.append( cb )
			self.checkButton[i].grid(row=row , column=i, sticky=W+E+N+S )
		
		# Frame 2 : video generation options
		self.frame2 = Frame( self )
		self.frame2.grid( sticky=N+S )
		# choose video types
		row = 0
		for i in range( len(videoType) ):
			self.videoTypeOption = Checkbutton(self.frame2 , text=videoType[i] , variable=videoBooleanVars[ videoType[i] ])
			# self.videoTypeOption = Radiobutton(self , text=videoTypes[i] , variable=videoTypeChoice , value=videoTypes[i])
			self.videoTypeOption.grid(row=row , column=i, sticky=W+E+N+S )


		# Frame 2 : video time option
		self.frame3 = Frame( self )
		self.frame3.grid( sticky=N+S )
		# label
		row = 0
		column = 0
		videoTimeText = "Video time: "
		self.videoTimeLabel = Label(self.frame3 , text=videoTimeText)
		self.videoTimeLabel.grid(row=row , column=column, sticky=W+E+N+S )
		# choose video time
		row = 0
		column = 1
		self.videoTimeEntry = Entry( self.frame3 , width=40 , font="Arial 10" , textvariable=videoTime )
		self.videoTimeEntry.grid(row=row , column=column, sticky=W+E+N+S )
		
		# Frame 3 : generate graphs button
		self.frame3 = Frame( self )
		self.frame3.grid( sticky=N+S )
		# Generate graphs button
		row = 0
		column = 0
		text = 'Generate Graphics'
		self.generateGraph = Button(self.frame3 , text=text , command=self.generateCommand)
		self.generateGraph.grid(row=row , column=column, sticky=W+E+N+S )

def main():
	SimulateInterface().mainloop() # starts event loop

if __name__ == "__main__":
	main()