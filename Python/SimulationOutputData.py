import matplotlib.colors as colors
import matplotlib.pyplot as plt
import matplotlib.cm as cmx
import json

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
					self.boundaryHistoryArray[boundaryName] = json.load(boundaryFile)

			self.simulationSettings = json.load(boundaryFile)
			
			self.particleData = {}
			self.boundaryData = {}
			self.time = {}

			# particleData is accessed using particleData[particleIndex][key][timeIndex][coordinate]
			# For instance, if one wishes to access the Z coordinate, in the 5th time instant (which corresponds to 4), 
			# of the BlueParticles's velocity, where BlueParticle is a SphericalParticle, one should write:
			# particleData["SphericalParticle"]["BlueParticle"]["velocity"][ 4 ][ 2 ], which stands for
			# particleData["SphericalParticle"]["BlueParticle"]["velocity"]["5th timeStep"]["Z coordinate"]
			# Similarly for boundaryData
			# (time[i]["timeIndex"], time[i]["timeInstant"]) is the i-th timepair
			
			# Read simulation settings
			simulationSettingsFilePath = paths.getSimulationMainOutputFilePath()
			with open(simulationSettingsFilePath) as simulationSettingsFile:
				self.simulationSettings = json.load(simulationSettingsFile)

			# Read particles
			for particleHistory in self.particleHistoryArray:
				for particleHistoryElement in particleHistory:
					timeIndex = particleHistoryElement["timeIndex"]
					particleType = particleHistoryElement["particleType"]
					particle = particleHistoryElement["particle"]
					particleName = particle["Name"]

					for key in particle.keys():
						self.particleData[particleType][particleName][key][timeIndex] = particle[key]
				
			# Read boundaries
			for boundaryHistory in self.boundaryHistoryArray:
				for boundaryHistoryElement in boundaryHistory:
					timeIndex = boundaryHistoryElement["timeIndex"]
					boundaryType = boundaryHistoryElement["boundaryType"]
					boundary = boundaryHistoryElement["boundary"]
					boundaryName = boundary["Name"]

					for key in boundary.keys():
						self.boundaryData[boundaryType][boundaryName][key][timeIndex] = boundary[key]

			# Read time
			with open(paths.getSimulationTimeVectorPath()) as timeVectorFile:    
				timeHistory = json.load(timeVectorFile)

				for timeHistoryElement in timeHistory:
					timeIndex = timeHistoryElement["timeIndex"]
					timeInstant = timeHistoryElement["timeInstant"]
					self.time[timeIndex] = timeInstant

		except FileNotFoundError:
			self.display.message("An output file wasn't found. Please, rerun simulation." )

			return
			
		# Set colormap
		cmap = plt.get_cmap('gist_rainbow')
		scalarMap = cmx.ScalarMappable( 
			cmap = cmap,
			norm = colors.Normalize( vmin=0 , vmax=len(particleHistoryArray) + len(boundaryHistoryArray) ) )

		# Return requested data
		return [self.simulationSettings, self.particleData, self.boundaryData, self.time, scalarMap]
