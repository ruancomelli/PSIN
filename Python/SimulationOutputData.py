import matplotlib.colors as colors
import matplotlib.pyplot as plt
import matplotlib.cm as cmx
import json
import os
from collections import defaultdict

class SimulationOutputData:

	def __init__( self , display , paths ):

		### Store references to objects ###
		self.display = display
		self.paths = paths

	def get( self ):
		try:
			# Read particle and boundary histories
			self.particleHistoryArray = {}
			for particleFilePath in self.paths.getSimulationParticleFilePaths():
				filename = os.path.basename(particleFilePath)
				particleName = os.path.splitext(filename)[0]
				with open(particleFilePath) as particleFile:    
					self.particleHistoryArray[particleName] = json.load(particleFile)

			self.boundaryHistoryArray = {}
			for boundaryFilePath in self.paths.getSimulationBoundaryFilePaths():
				filename = os.path.basename(boundaryFilePath)
				boundaryName = os.path.splitext(filename)[0]
				with open(boundaryFilePath) as boundaryFile:    
					self.boundaryHistoryArray[boundaryName] = json.load(boundaryFile)

			with open(self.paths.getSimulationMainOutputFilePath()) as mainOutputFile:
				self.simulationSettings = json.load(mainOutputFile)
			
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
			simulationSettingsFilePath = self.paths.getSimulationMainOutputFilePath()
			with open(simulationSettingsFilePath) as simulationSettingsFile:
				self.simulationSettings = json.load(simulationSettingsFile)

			# Read particles
			for particleHistoryKey, particleHistory in self.particleHistoryArray.items():
				for particleHistoryElement in particleHistory:
					timeIndex = particleHistoryElement["timeIndex"]
					particleType = particleHistoryElement["particleType"]
					particle = particleHistoryElement["particle"]
					particleName = particle["Name"]

					for key in particle.keys():
						if particleType not in self.particleData:
							self.particleData[particleType] = {}

						if particleName not in self.particleData[particleType]:
							self.particleData[particleType][particleName] = {}

						if key not in self.particleData[particleType][particleName]:
							self.particleData[particleType][particleName][key] = {}

						self.particleData[particleType][particleName][key][timeIndex] = particle[key]
				
			# Read boundaries
			for boundaryHistoryKey, boundaryHistory in self.boundaryHistoryArray.items():
				for boundaryHistoryElement in boundaryHistory:
					timeIndex = boundaryHistoryElement["timeIndex"]
					boundaryType = boundaryHistoryElement["boundaryType"]
					boundary = boundaryHistoryElement["boundary"]
					boundaryName = boundary["Name"]

					for key in boundary.keys():
						if boundaryType not in self.boundaryData:
							self.boundaryData[boundaryType] = {}

						if boundaryName not in self.boundaryData[boundaryType]:
							self.boundaryData[boundaryType][boundaryName] = {}

						if key not in self.boundaryData[boundaryType][boundaryName]:
							self.boundaryData[boundaryType][boundaryName][key] = {}

						self.boundaryData[boundaryType][boundaryName][key][timeIndex] = boundary[key]

			# Read time
			with open(self.paths.getSimulationTimeVectorPath()) as timeVectorFile:
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
			norm = colors.Normalize( vmin=0 , vmax=len(self.particleHistoryArray) + len(self.boundaryHistoryArray) ) )

		# Return requested data
		return [self.simulationSettings, self.particleData, self.boundaryData, self.time, scalarMap]
