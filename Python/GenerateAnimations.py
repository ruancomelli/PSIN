from tkinter import *
from BuildVideo import BuildAnimation

class GenerateAnimations:

	def toBool( self , animationBooleanVars ):
		animationBools = {}
		for i in range( len(animationBooleanVars) ):
			animationBools[ self.animationTypes[i] ] = animationBooleanVars[ self.animationTypes[i] ].get()

		return animationBools

	def generateAnimation( self ):

		# Function BuildVideo.build is called if at least
		# one type of animation was chose

		animationBools = self.toBool( self.animationBooleanVars )

		# Verify animation time
		if( float(self.animationTime.get()) <= 0 ):
			self.display.message("Animation time must be positive!")
			return
		
		if( True in animationBools.values() ):
			self.display.message("Animating...")
			
			BuildAnimation.build(
				simulationOutputData = self.simulationOutputData,
				paths = self.paths,
				animationBools = animationBools,
				animationTime = float( self.animationTime.get() ),
				animationTypes = self.animationTypes
				)
			
			self.display.message("Animation done")
		else:
			self.display.message("No animation selected. Nothing to be done")

	def __init__( self , frame , simulationOutputData , paths , display ):

		### variables ###

		# Provide to class access to "simulation output data" and "paths"
		# These data are used by class BuildVideo
		self.simulationOutputData = simulationOutputData
		self.paths = paths
		self.display = display

		# Define if a animation will be built
		self.buildAnimation = BooleanVar()

		# Set witch animation types will be built
		self.animationTypes = ["by_time_step" , "global" , "autoscale"]
		self.animationBooleanVars = {}
		for i in range( len(self.animationTypes) ):
			self.animationBooleanVars[ self.animationTypes[i] ] = BooleanVar()
			self.animationBooleanVars[ self.animationTypes[i] ].set(False)

		# Set animation duration
		self.animationTime = StringVar()
		self.animationTime.set("1")

		### Choose animation types to be build - checkbuttons ###
		row = 0
		self.animationCheckbutton = []
		for i in range( len(self.animationTypes) ):
			cb = Checkbutton(frame , text=self.animationTypes[i] , variable=self.animationBooleanVars[ self.animationTypes[i] ])
			self.animationCheckbutton.append(cb)
			self.animationCheckbutton[i].grid(row=row , column=i, sticky=W+E+N+S )


		### Animation duration ###

		# Label
		row = 1
		column = 0
		self.animationTimeText = "Animation Time: "
		self.animationTimeLabel = Label(frame , text=self.animationTimeText)
		self.animationTimeLabel.grid(row=row , column=column, sticky=W+E+N+S )
		
		# Animation time entry
		row = 1
		column = 1
		self.animationTimeEntry = Entry( frame , width=40 , font="Arial 10" , textvariable=self.animationTime )
		self.animationTimeEntry.grid(row=row , column=column, sticky=W+E+N+S )


		### Generate animations - button ###
		row = 2
		column = 1
		self.generateAnimationsText = "Animate"
		self.generateAnimations = Button(frame , text=self.generateAnimationsText , command=self.generateAnimation) # it needs a command
		self.generateAnimations.grid(row=row , column=column, sticky=N+S )