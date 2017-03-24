from tkinter import *
from processDataHistory import plotParticleDataHistory
from processDataHistory import plotParticleDataHistory3D

class GeneratePlots:

	def plot( self ):

		# get plotBools
		self.plotBools = self.toBool(self.plotsBooleanVars)

		if( True in self.plotBools.values() ):
			# Verify if the user selected some plot
			# if it selected some, generate plots
			# else, warn the user.

			### Get external infomation ###

			# get folder to save plots
			plotOutputFolder = self.paths.getSimulationPlotsOutputFolder()

			# get simulation data
			[simulationSettings, particleData , timeVectorForPlot , scalarMap ] = self.simulationOutputData.get()


			### Plots ###

			# Plot Energy
			thisKey = "energy"
			if( self.plotBools[thisKey] ):
				self.display.message("Plotting " + thisKey)
				plotParticleDataHistory( 
					timeVector = timeVectorForPlot, 
					particleData = particleData, 
					key = "energy", 
					title = "\nMechanical Energy\n", 
					outputFolder = plotOutputFolder, 
					fileName = "mechanical_energy_plot", 
					extension = ".png", 
					xAxisLabel = "\nTime [s]\n", 
					yAxisLabel = "\nEnergy [J]\n", 
					scalarMap = scalarMap,  
					nParticles = simulationSettings["nParticles"])
			
			# Plot Linear Momentum
			thisKey = "linear_momentum"
			if( self.plotBools[thisKey] ):
				self.display.message("Plotting " + thisKey)
				plotParticleDataHistory3D( 
					timeVector = timeVectorForPlot, 
					particleData = particleData, 
					key = "linear_momentum", 
					title = "\nLinear Momentum", 
					outputFolder = plotOutputFolder, 
					fileName = "linear_momentum_plot", 
					extension = ".png", 
					xAxisLabel = "\nTime [s]\n", 
					yAxisLabel = "\nLinear Momentum [kg*m/s]\n", 
					scalarMap = scalarMap,  
					nParticles = simulationSettings["nParticles"]
					)
			
			# Plot Angular Momentum
			thisKey = "angular_momentum"
			if( self.plotBools[thisKey] ):
				self.display.message("Plotting " + thisKey)
				plotParticleDataHistory3D( 
					timeVector = timeVectorForPlot, 
					particleData = particleData, 
					key = "angular_momentum", 
					title = "\nAngular Momentum", 
					outputFolder = plotOutputFolder, 
					fileName = "angular_momentum_plot", 
					extension = ".png", 
					xAxisLabel = "\nTime [s]\n", 
					yAxisLabel = "\nAngular Momentum [kg*m^2/s]\n", 
					scalarMap = scalarMap,  
					nParticles = simulationSettings["nParticles"]
					)
				
			# Plot Resulting Force
			thisKey = "force"
			if( self.plotBools[thisKey] ):
				self.display.message("Plotting " + thisKey)
				plotParticleDataHistory3D( 
					timeVector = timeVectorForPlot, 
					particleData = particleData, 
					key = "force", 
					title = "\nResulting Force", 
					outputFolder = plotOutputFolder, 
					fileName = "force_plot", 
					extension = ".png", 
					xAxisLabel = "\nTime [s]\n", 
					yAxisLabel = "\nResulting Force [N]\n", 
					scalarMap = scalarMap,  
					nParticles = simulationSettings["nParticles"]
					)
			
			# Plot Resulting Torque
			thisKey = "torque"
			if( self.plotBools[thisKey] ):
				self.display.message("Plotting " + thisKey)
				plotParticleDataHistory3D( 
					timeVector = timeVectorForPlot, 
					particleData = particleData, 
					key = "torque", 
					title = "\nResulting Torque", 
					outputFolder = plotOutputFolder, 
					fileName = "torque_plot", 
					extension = ".png", 
					xAxisLabel = "\nTime [s]\n", 
					yAxisLabel = "\nResulting Torque [N*m]\n", 
					scalarMap = scalarMap,  
					nParticles = simulationSettings["nParticles"]
					)
			
			# finish
			self.display.message("Plots done")

		else:
			self.display.message("No plot selected. Nothing to be done.")

		

	def toBool( self , plotsBooleanVars ):
		plotBools = {}
		for i in range( len(plotsBooleanVars) ):
			plotBools[ self.plotTypes[i] ] = plotsBooleanVars[ self.plotTypes[i] ].get()
			# use : bools[ type ]

		return plotBools

	def __init__( self , frame , simulationOutputData , paths , display ):


		### Store references to objects ###
		self.simulationOutputData = simulationOutputData
		self.paths = paths
		self.display = display


		### Create two frames ###
		
		# plot types frame
		row = 0
		self.plotTypesFrame = Frame( frame )
		self.plotTypesFrame.grid(row=row , sticky=N+S )

		# button frame
		row = 1
		self.plotButtonFrame = Frame( frame )
		self.plotButtonFrame.grid(row=row , sticky=N+S )


		### Possible plots type ###
		self.plotTypes = [ 'energy' , 'linear_momentum' , 'angular_momentum' , 'force' , 'torque' ]

		self.plotsBooleanVars = {}
		for i in range( len(self.plotTypes) ):
			self.plotsBooleanVars[ self.plotTypes[i] ] = BooleanVar()
			self.plotsBooleanVars[ self.plotTypes[i] ].set(False)
			# use: graphBooleanVars[ plotType ].get()

		### Choose plots - checkbuttons ###
		row = 0
		self.checkButtons = []
		for i in range( len(self.plotTypes) ):
			cb = Checkbutton(self.plotTypesFrame , text=self.plotTypes[i] , variable=self.plotsBooleanVars[self.plotTypes[i]] )
			self.checkButtons.append( cb )
			self.checkButtons[i].grid(row=row , column=i, sticky=W+E+N+S )


		### Plot button ###
		row = 1
		column = len(self.plotTypes)
		text = 'Plot'
		self.plotButton = Button(self.plotButtonFrame , text=text , command=self.plot)
		self.plotButton.grid(row=row , column=column, sticky=W+E+N+S )