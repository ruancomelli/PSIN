import os
import json
import subprocess

class PseudoSimulationOutputData:

	def __init__( self , paths ):

		### Store references to objects ###
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
			print("An output file wasn't found. Please, rerun simulation." )

			return

		# Return requested data
		return [self.simulationSettings, self.particleData, self.boundaryData, self.time]

class PseudoUserInput:
	def __init__(self, programPath, mainInputFilePath):
		self.programPath = programPath
		self.mainInputFilePath = mainInputFilePath

	def get(self):
		return [ self.programPath , self.mainInputFilePath ]

class PseudoSimulate:
	def execute( self ):
		# After: add pos processing, get the progrma return code

		programPath = self.paths.getSimulationProgramPath()
		mainInputFilePath = self.paths.getSimulationMainInputFilePath()

		print("Simulating")

		programArg = "--path=" + mainInputFilePath + ""

		# Handle errors
		# Possible errors:
		#	executable not found
		try:
			subprocess.run( [programPath, programArg] )
		except FileNotFoundError:
			print("Simulation program not found")
			return

		print("Simulation done")

	def __init__( self , userInput , paths ):

		### Store references to objects ###
		self.userInput = userInput
		self.paths = paths

class PseudoPaths:

	def __init__( self , userInput ):

		### Store references to objects ###
		self.userInput = userInput

	def generate( self ):
		# This class receives a UserInput class
		# reference and returns the paths used by
		# the interface

		[ self.programPath , self.mainInputFilePath ] = self.userInput.get()

		with open(self.mainInputFilePath) as mainInputFile:    
			mainInput = json.load(mainInputFile)

		# Important data:
		# mainInput["MainOutputFolder"]: the path of mainOutputFolder. 
		# 	This folder contains a file named 'main.json' and a folder named 'input'
		# 	input/ contains the input files used to run the simulation
		# 	main.json is the main simulation file.
		# mainInput["ParticleOutputFolder"]: the path of particleOutputFolder. 
		# 	For each particle in the simulation, there is exactly one file in this folder,
		# 	named after the particle's name, of this particle's history.
		# mainInput["BoundaryOutputFolder"]: the path of boundaryOutputFolder. 
		# 	For each boundary in the simulation, there is exactly one file in this folder,
		# 	named after the boundary's name, of this boundary's history.

		self.particleFilePaths = []
		for (_, _, filenames) in os.walk(mainInput["ParticleOutputFolder"]):
			for filename in filenames:
				particleFilePath = os.path.join(mainInput["ParticleOutputFolder"], filename)
				self.particleFilePaths.append( particleFilePath )
			break


		self.boundaryFilePaths = []
		for (_, _, filenames) in os.walk(mainInput["BoundaryOutputFolder"]):
			for filename in filenames:
				boundaryFilePath = os.path.join(mainInput["BoundaryOutputFolder"], filename)
				self.boundaryFilePaths.append( boundaryFilePath )
			break

		self.mainOutputFolder = mainInput["MainOutputFolder"]
		self.simulationPlotFolder = os.path.join(mainInput["MainOutputFolder"], "Plots")
		self.simulationAnimationFolder = os.path.join(mainInput["MainOutputFolder"], "Animations")
		self.timeVectorPath = os.path.join(mainInput["MainOutputFolder"], "timeVector.json")
		self.mainOutputFilePath = os.path.join(mainInput["MainOutputFolder"], "main.json")

		# Create directories

		os.makedirs(self.simulationPlotFolder, exist_ok = True)
		os.makedirs(self.simulationAnimationFolder, exist_ok = True)


	def getSimulationProgramPath( self ):
		self.generate()

		return self.programPath

	def getSimulationTimeVectorPath( self ):
		self.generate()

		return self.timeVectorPath

	def getSimulationMainInputFilePath( self ):
		self.generate()

		return self.mainInputFilePath

	def getSimulationMainOutputFolder( self ):
		self.generate()

		return self.mainOutputFolder

	def getSimulationMainOutputFilePath( self ):
		self.generate()

		return self.mainOutputFilePath

	def getSimulationParticleFilePaths( self ):
		self.generate()

		return self.particleFilePaths

	def getSimulationBoundaryFilePaths( self ):
		self.generate()

		return self.boundaryFilePaths

	def getSimulationPlotsOutputFolder( self ):
		self.generate()

		return self.simulationPlotFolder

	def getSimulationAnimationsOutputFolder( self ):
		self.generate()

		return self.simulationAnimationFolder