from getTagValuePairsFromFile import getTagValuePairsFromFile
from readCSVmatrix import readCSVmatrix

import matplotlib.colors as colors
import matplotlib.pyplot as plt
import matplotlib.cm as cmx

class SimulationOutputData:

	def __init__( self , display , paths ):

		### Store references to objects ###
		self.display = display
		self.paths = paths

	def get( self ):
		try:
			# get paths
			simulationNumericalOutputFolder = self.paths.getSimulationNumericalOutput()

			# Read main output file
			mainSimulationOutputPath = simulationNumericalOutputFolder + "mainInfoOutput.txt"
			simulationSettings = getTagValuePairsFromFile(mainSimulationOutputPath, "<", ">")

			# Read time vector
			timeVectorForPlot = readCSVmatrix( simulationNumericalOutputFolder + "timeVectorForPlot.txt" )
			
			# Read particles' files
			particleData = []

			# particleData is accessed using particleData[particleIndex][key][timeIndex][coordinate]
			# For instance, if one wishes to access the Z coordinate, in timeStep number 5, 
			# of the second particle's velocity, one should write:
			# particleData[ 2 - 1 ][ "velocity" ][ 5 - 1 ][ 3 - 1 ], or
			# particleData[ 1 ][ "velocity" ][ 4 ][ 2 ] which stands for
			# particleData["second particle"]["velocity"]["5th timeStep"]["Z coordinate"]
				

			simulationSettings["nParticles"] = int(simulationSettings["nParticles"])
			for counter in range( simulationSettings["nParticles"] ):
				thisParticleName = "Particle" + str(counter)

				thisParticleOutputFolder = simulationNumericalOutputFolder + thisParticleName + "/"

				thisParticleData = {}

				# It is bad. If we add soemthing different in our main program,
				# we will need to change everything above. It could be interesting
				# to put a 'listdir' and, with its return, create the plots.
				# Plans to future.

				thisParticleData["main"] = getTagValuePairsFromFile( thisParticleOutputFolder + "data.txt", "<", ">" )
				thisParticleData["energy"] = readCSVmatrix( thisParticleOutputFolder + "energy.txt" )
				thisParticleData["position"] = readCSVmatrix( thisParticleOutputFolder + "position.txt" )
				thisParticleData["velocity"] = readCSVmatrix( thisParticleOutputFolder + "velocity.txt" )
				thisParticleData["linear_momentum"] = readCSVmatrix( thisParticleOutputFolder + "linear_momentum.txt" )
				thisParticleData["orientation"] = readCSVmatrix( thisParticleOutputFolder + "orientation.txt" )
				thisParticleData["rotational_velocity"] = readCSVmatrix( thisParticleOutputFolder + "rotational_velocity.txt" )
				thisParticleData["angular_momentum"] = readCSVmatrix( thisParticleOutputFolder + "angular_momentum.txt" )
				thisParticleData["force"] = readCSVmatrix( thisParticleOutputFolder + "force.txt" )
				thisParticleData["torque"] = readCSVmatrix( thisParticleOutputFolder + "torque.txt" )

				particleData.append(thisParticleData)
		except FileNotFoundError:
			self.display.message("An output file wasn't found. Please, rerun simulation." )

			return
			
		# Set colormap
		cmap = plt.get_cmap('gist_rainbow')
		scalarMap = cmx.ScalarMappable( 
			cmap = cmap,
			norm = colors.Normalize( vmin=0 , vmax=simulationSettings["nParticles"]-1 ) )

		# Return requested data
		return [simulationSettings , particleData , timeVectorForPlot , scalarMap]
