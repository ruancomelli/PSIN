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
			# Read particle and boundary histories
			self.particleHistoryArray = {}
			for particleFilePath in paths.getSimulationParticleFilePaths():
				filename = os.path.basename(particleFilePath)
				particleName = os.path.splitext(filename)[0]
				with open(particleFilePath) as particleFile:    
					self.particleHistoryArray[particleName] = json.load(particleFile)

			self.boundaryHistoryArray = []
			for boundaryFilePath in paths.getSimulationBoundaryFilePaths():
				filename = os.path.basename(boundaryFilePath)
				boundaryName = os.path.splitext(filename)[0]
				with open(boundaryFilePath) as boundaryFile:    
					self.boundaryHistoryArray[particleName] = json.load(particleFile)
			
			particleData = {}
			boundaryData = {}

			# particleData is accessed using particleData[particleIndex][key][timeIndex][coordinate]
			# For instance, if one wishes to access the Z coordinate, in the 5th time instant (which corresponds to 4), 
			# of the BlueParticles's velocity, where BlueParticle is a SphericalParticle, one should write:
			# particleData["SphericalParticle"]["BlueParticle"]["velocity"][ 4 ][ 2 ], which stands for
			# particleData["SphericalParticle"]["BlueParticle"]["velocity"]["5th timeStep"]["Z coordinate"]
				
			for particleHistory in self.particleHistoryArray:
				for particleHistoryElement in particleHistory:
					timeIndex = particleHistoryElement["TimeIndex"]

					thisParticleName = "Particle" + str(counter)

					thisParticleOutputFolder = simulationNumericalOutputFolder + thisParticleName + "/"

					thisParticleData = {}

					# It is bad. If we add anything different in our main program,
					# we will need to change everything above. It could be interesting
					# to put a 'listdir' and, with its return, create the plots.
					# Plans for the future.

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
