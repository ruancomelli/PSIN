from processDataHistory import plotParticleDataHistory
from processDataHistory import plotParticleDataHistory3D

# generate the graphics and videos
def generateGraphics( timeVectorForPlot , particleData , pythonOutputFolder , scalarMap , simulationSettings , graphBools ):

	# Plot Energy
	thisKey = "energy"
	if( graphBools[thisKey] ):
		print(">> Plotting mechanical energy")

		plotParticleDataHistory( 
			timeVector = timeVectorForPlot, 
			particleData = particleData, 
			key = "energy", 
			title = "\nMechanical Energy\n", 
			outputFolder = pythonOutputFolder, 
			fileName = "mechanical_energy_plot", 
			extension = ".png", 
			xAxisLabel = "\nTime [s]\n", 
			yAxisLabel = "\nEnergy [J]\n", 
			scalarMap = scalarMap,  
			nParticles = simulationSettings["nParticles"])

		print("<< Done")
	
	# Plot Linear Momentum
	thisKey = "linear_momentum"
	if( graphBools[thisKey] ):
		print(">> Plotting linear momentum")

		plotParticleDataHistory3D( 
			timeVector = timeVectorForPlot, 
			particleData = particleData, 
			key = "linear_momentum", 
			title = "\nLinear Momentum", 
			outputFolder = pythonOutputFolder, 
			fileName = "linear_momentum_plot", 
			extension = ".png", 
			xAxisLabel = "\nTime [s]\n", 
			yAxisLabel = "\nLinear Momentum [kg*m/s]\n", 
			scalarMap = scalarMap,  
			nParticles = simulationSettings["nParticles"]
			)

		print("<< Done")
	
	# Plot Angular Momentum
	thisKey = "angular_momentum"
	if( graphBools[thisKey] ):
		print(">> Plotting angular momentum")

		plotParticleDataHistory3D( 
			timeVector = timeVectorForPlot, 
			particleData = particleData, 
			key = "angular_momentum", 
			title = "\nAngular Momentum", 
			outputFolder = pythonOutputFolder, 
			fileName = "angular_momentum_plot", 
			extension = ".png", 
			xAxisLabel = "\nTime [s]\n", 
			yAxisLabel = "\nAngular Momentum [kg*m^2/s]\n", 
			scalarMap = scalarMap,  
			nParticles = simulationSettings["nParticles"]
			)

		print("<< Done")
		
	# Plot Resulting Force
	thisKey = "force"
	if( graphBools[thisKey] ):
		print(">> Plotting force")

		plotParticleDataHistory3D( 
			timeVector = timeVectorForPlot, 
			particleData = particleData, 
			key = "force", 
			title = "\nResulting Force", 
			outputFolder = pythonOutputFolder, 
			fileName = "force_plot", 
			extension = ".png", 
			xAxisLabel = "\nTime [s]\n", 
			yAxisLabel = "\nResulting Force [N]\n", 
			scalarMap = scalarMap,  
			nParticles = simulationSettings["nParticles"]
			)

		print("<< Done")
	
	# Plot Resulting Torque
	thisKey = "torque"
	if( graphBools[thisKey] ):
		print(">> Plotting torque")

		plotParticleDataHistory3D( 
			timeVector = timeVectorForPlot, 
			particleData = particleData, 
			key = "torque", 
			title = "\nResulting Torque", 
			outputFolder = pythonOutputFolder, 
			fileName = "torque_plot", 
			extension = ".png", 
			xAxisLabel = "\nTime [s]\n", 
			yAxisLabel = "\nResulting Torque [N*m]\n", 
			scalarMap = scalarMap,  
			nParticles = simulationSettings["nParticles"]
			)

		print("<< Done")