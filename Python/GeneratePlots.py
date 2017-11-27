from tkinter import *
import os
import numpy
import matplotlib.pyplot as plt
from matplotlib import font_manager

### Auxilliary function to get color ###
def getColor(color):
	if color[1] == "":
		return (color[0][0], color[0][1], color[0][2])
	else:
		return color[1]

class GeneratePlots:
	def __init__( self , frame , simulationOutputData , paths , display ):

		### Store references to objects ###
		self.simulationOutputData = simulationOutputData
		self.paths = paths
		self.display = display

		particleDataEntry = 1
		self.particleData = self.simulationOutputData.get()[particleDataEntry]
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


	def plotParticleDataHistory( self, propertyName, title, outputFolder, filename,
	    extension, xAxisLabel, yAxisLabel, component = 0 ):

		timeVector = list(self.time.values())
		particleData = self.particleData

		if component == 'X':
			component = 0
		elif component == 'Y':
			component = 1
		elif component == 'Z':
			component = 2
			
		fig = plt.figure(
			figsize=(18, 14),
			facecolor='w',
			edgecolor='k')

		ax = fig.add_subplot(111)

		xMinimum = min(timeVector)
		xMaximum = max(timeVector)

		yMinimum = min( [propertyValue
			for particleType in particleData.values()
			for particle in particleType.values()
			for propertyValue in particle[propertyName].values()
			])

		yMaximum = max( [propertyValue
			for particleType in particleData.values()
			for particle in particleType.values()
			for propertyValue in particle[propertyName].values()
			])

		total = [ sum(history) for history in zip(
			*[
				particle[propertyName].values()
				for particleType in particleData.values()
				for particle in particleType.values()
			])
		]

		print("property name: ", propertyName)

		yMinimum = min( min(total), yMinimum )
		yMaximum = max( max(total), yMaximum )
		
		xWidth = xMaximum - xMinimum
		yWidth = yMaximum - yMinimum
		
		# Set labels

		ax.set_xlabel(xAxisLabel, size=24, weight='normal', family='sans-serif')
		ax.set_ylabel(yAxisLabel, size=24, weight='normal', family='sans-serif')
		
		# ax.set_title(title, size=30, weight='normal', family='sans-serif')
		
		# Set plot limits
		
		xMinimumLim = xMinimum# - 0.1*xWidth
		xMaximumLim = xMaximum# + 0.1*xWidth
		
		yMinimumLim = yMinimum - 0.1*yWidth
		yMaximumLim = yMaximum + 0.1*yWidth
		
		plt.xlim( xMinimumLim, xMaximumLim )
		plt.ylim( yMinimumLim, yMaximumLim )
		
		# Set plot ticks
		
		ax.tick_params()
		ax.minorticks_on()
		
	#	rangeStep = numpy.round(xWidth , int( numpy.abs(numpy.log10(xWidth)) + 1  ) )
	#	xTicks = numpy.linspace(start=xMinimum , stop=xMaximum , num=10)
	#	yTicks = numpy.linspace(start=yMinimum , stop=yMaximum , num=20)
	#	
	#	ax.set_xticks( xTicks )
	#	ax.set_yticks( yTicks )

		# Add grid
		
		ax.grid(visible=True , which='major')
		ax.grid(visible=True , which='minor' , color=[0.5 , 0.5 , 0.5])
		
		ax.title.set_fontsize(25)
		for label in (ax.get_xticklabels() + ax.get_yticklabels()):
		    label.set_fontproperties( font_manager.FontProperties(family='sans-serif', style='normal',
	    size=15, weight='normal') )
						
		# Plot total propertyName-property
		ax.plot( 
			timeVector, 
			total,
			'k-',
			linewidth = 2.0,
			label = "Total"
			)
						
		# Plot each particle's property
		for particleTypename, particleType in particleData.items():
			for particleName, particle in particleType.items():
				ax.plot(
					[self.time[t] for t in self.time.keys()],
					[particle[propertyName][t] for t in self.time.keys()],
					color = getColor(particle["Color"][next(iter(particle["Color"]))]),
					label = particleName,
					marker = '.'
					)
		
		
		handles, labels = ax.get_legend_handles_labels()
		handle_list, label_list = [], []
		for handle, label in zip(handles, labels):
		    if label not in label_list:
		        handle_list.append(handle)
		        label_list.append(label)
		
		lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': 15, 'family': 'sans-serif', 'weight': 'normal'})
		lgd.set_title("Legenda", prop={'size': 18, 'family': 'sans-serif', 'weight': 'normal'})
		plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")
		plt.close(fig)
	
	def plotParticleDataHistory3D( self, propertyName, title, outputFolder, filename,
		extension, xAxisLabel, yAxisLabel ):

		self.plotParticleDataHistory( 
			propertyName = propertyName, 
			title = title + " - X Direction\n", 
			outputFolder = outputFolder, 
			filename = filename + "_X_plot",
			extension = extension, 
			xAxisLabel = xAxisLabel, 
			yAxisLabel = yAxisLabel + " - X Direction",
			nParticles = nParticles, 
			component = 'X' )

		self.plotParticleDataHistory( 
			propertyName = propertyName, 
			title = title + " - Y Direction\n", 
			outputFolder = outputFolder, 
			filename = filename + "_Y_plot",
			extension = extension, 
			xAxisLabel = xAxisLabel, 
			yAxisLabel = yAxisLabel + " - Y Direction", 
			nParticles = nParticles, 
			component = 'Y' )

		self.plotParticleDataHistory( 
			propertyName = propertyName, 
			title = title + " - Z Direction\n", 
			outputFolder = outputFolder, 
			filename = filename + "_Z_plot",
			extension = extension, 
			xAxisLabel = xAxisLabel, 
			yAxisLabel = yAxisLabel + " - Z Direction", 
			nParticles = nParticles, 
			component = 'Z' )

	def plot( self ):

		# get plotBools
		self.plotBools = self.toBool(self.plotsBooleanVars)

		# if( True in self.plotBools.values() ):
		if True:
			# Verify if the user selected some plot
			# if it selected some, generate plots
			# else, warn the user.

			### Get external infomation ###

			# get folder to save plots
			plotOutputFolder = self.paths.getSimulationPlotsOutputFolder()

			# get simulation data
			[simulationSettings, self.particleData, boundaryData, self.time] = self.simulationOutputData.get()


			### Plots ###
			for particleType in self.particleData.values():	# For every type: SphericalParticle, SquareParticle...
				for particle in particleType.values():	# For every particle of this type: BlueSphere, RedSphere
					for propertyName, propertyHistory in particle.items():
						if isinstance(list(propertyHistory.values())[0], float) or isinstance(list(propertyHistory.values())[0], int):
							self.plotParticleDataHistory( 
								propertyName=propertyName, 
								title=propertyName, 
								outputFolder=plotOutputFolder, 
								filename=propertyName, 
								extension=".png", 
								xAxisLabel="Time [s]", 
								yAxisLabel=propertyName
								)
						elif isinstance(list(propertyHistory.values())[0], list):
							pass
							# self.plotParticleDataHistory3D(
							# 	propertyName=propertyName,
							# 	title=propertyName,
							# 	outputFolder=plotOutputFolder,
							# 	filename=propertyName,
							# 	extension=".png",
							# 	xAxisLabel="Time [s]", 
							# 	yAxisLabel=propertyName
							# 	)
						else:
							print("Ooops!\nFirst value of propertyHistory: ", list(propertyHistory)[0])

			# finish
			self.display.message("Plots done")

		else:
			self.display.message("No plot selected. Nothing to be done.")

			# # Plot Energy
			# thisKey = "energy"
			# if( self.plotBools[thisKey] ):
			# 	self.display.message("Plotting " + thisKey)
			# 	plotParticleDataHistory( 
			# 		timeVector = timeVectorForPlot, 
			# 		particleData = self.particleData, 
			# 		propertyName = "energy", 
			# 		title = "\nMechanical Energy\n", 
			# 		outputFolder = plotOutputFolder, 
			# 		filename = "mechanical_energy_plot", 
			# 		extension = ".png", 
			# 		xAxisLabel = "\nTime [s]\n", 
			# 		yAxisLabel = "\nEnergy [J]\n", 
			# 		scalarMap = scalarMap,  
			# 		nParticles = simulationSettings["nParticles"])
			
			# # Plot Linear Momentum
			# thisKey = "linear_momentum"
			# if( self.plotBools[thisKey] ):
			# 	self.display.message("Plotting " + thisKey)
			# 	plotParticleDataHistory3D( 
			# 		timeVector = timeVectorForPlot, 
			# 		particleData = self.particleData, 
			# 		propertyName = "linear_momentum", 
			# 		title = "\nLinear Momentum", 
			# 		outputFolder = plotOutputFolder, 
			# 		filename = "linear_momentum_plot", 
			# 		extension = ".png", 
			# 		xAxisLabel = "\nTime [s]\n", 
			# 		yAxisLabel = "\nLinear Momentum [kg*m/s]\n", 
			# 		scalarMap = scalarMap,  
			# 		nParticles = simulationSettings["nParticles"]
			# 		)
			
			# # Plot Angular Momentum
			# thisKey = "angular_momentum"
			# if( self.plotBools[thisKey] ):
			# 	self.display.message("Plotting " + thisKey)
			# 	plotParticleDataHistory3D( 
			# 		timeVector = timeVectorForPlot, 
			# 		particleData = self.particleData, 
			# 		propertyName = "angular_momentum", 
			# 		title = "\nAngular Momentum", 
			# 		outputFolder = plotOutputFolder, 
			# 		filename = "angular_momentum_plot", 
			# 		extension = ".png", 
			# 		xAxisLabel = "\nTime [s]\n", 
			# 		yAxisLabel = "\nAngular Momentum [kg*m^2/s]\n", 
			# 		scalarMap = scalarMap,  
			# 		nParticles = simulationSettings["nParticles"]
			# 		)
				
			# # Plot Resulting Force
			# thisKey = "force"
			# if( self.plotBools[thisKey] ):
			# 	self.display.message("Plotting " + thisKey)
			# 	plotParticleDataHistory3D( 
			# 		timeVector = timeVectorForPlot, 
			# 		particleData = self.particleData, 
			# 		propertyName = "force", 
			# 		title = "\nResulting Force", 
			# 		outputFolder = plotOutputFolder, 
			# 		filename = "force_plot", 
			# 		extension = ".png", 
			# 		xAxisLabel = "\nTime [s]\n", 
			# 		yAxisLabel = "\nResulting Force [N]\n", 
			# 		scalarMap = scalarMap,  
			# 		nParticles = simulationSettings["nParticles"]
			# 		)
			
			# # Plot Resulting Torque
			# thisKey = "torque"
			# if( self.plotBools[thisKey] ):
			# 	self.display.message("Plotting " + thisKey)
			# 	plotParticleDataHistory3D( 
			# 		timeVector = timeVectorForPlot, 
			# 		particleData = self.particleData, 
			# 		propertyName = "torque", 
			# 		title = "\nResulting Torque", 
			# 		outputFolder = plotOutputFolder, 
			# 		filename = "torque_plot", 
			# 		extension = ".png", 
			# 		xAxisLabel = "\nTime [s]\n", 
			# 		yAxisLabel = "\nResulting Torque [N*m]\n", 
			# 		scalarMap = scalarMap,  
			# 		nParticles = simulationSettings["nParticles"]
			# 		)

	def toBool( self , plotsBooleanVars ):
		plotBools = {}
		for i in range( len(plotsBooleanVars) ):
			plotBools[ self.plotTypes[i] ] = plotsBooleanVars[ self.plotTypes[i] ].get()
			# use : bools[ type ]

		return plotBools