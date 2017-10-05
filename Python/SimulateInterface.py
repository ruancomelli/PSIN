from tkinter import *
root = Tk()

from config import *

from Display import Display
from UserInput import UserInput
from SimulationOutputData import SimulationOutputData
from Paths import Paths
from Simulate import Simulate
from GeneratePlots import GeneratePlots
from GenerateAnimations import GenerateAnimations
from Console import Console


#
# INITIALIZING
#

# The "Folder" suffix indicates that a variable holds a folder name, as in simulationFolder = "../simulation/"
# The "Path" suffix means that a variable holds a full file path, as in outputPath = "../simulation/output.txt"
# The "File" suffix is used to indicate that a variable is a file object, as in outputFile = open("../simulation/output.txt")
# In general, let X be a token. Then we should be able to write XFile = fopen(XPath) 
# The "Name" suffix, when applied in the context of files, is a filename, as in programName = "spyder.exe"

class SimulateInterface( Frame ):

	def __init__( self ):

		### Initialization ###
		Frame.__init__( self )
		self.currentRow = 0

		# Main window config
		self.master.title( "Particle Simulator" )
		self.grid( sticky=W+E+N+S )

		### Display ###

		# Initialize a frame
		self.displayFrame = Frame( self )
		self.displayFrame.grid( row=self.currentRow , sticky=N+S , padx=10 , pady=10)
		self.currentRow = self.currentRow + 1

		# Initialize display object
		self.display = Display( self.displayFrame , self )


		### User input ###

		# Initialize a frame
		self.userInputFrame = Frame( self )
		self.userInputFrame.grid( row=self.currentRow , sticky=N+S )
		self.currentRow = self.currentRow + 1

		# Initialize UserInput object
		self.userInput = UserInput( self.userInputFrame )


		### Paths ###
		self.paths = Paths(self.userInput)


		### Simulation output data ###
		self.simulationOutputData = SimulationOutputData( paths=self.paths , display=self.display )


		### Simulate ###

		# Initialize a frame
		self.simulateFrame = Frame( self )
		self.simulateFrame.grid( row=self.currentRow , sticky=N+S )
		self.currentRow = self.currentRow + 1

		# Initialize Simulate object
		self.simulate = Simulate( frame=self.simulateFrame , userInput=self.userInput , paths=self.paths , display=self.display )


		### Generate plots ###

		# Initialize a frame
		self.generatePlotsFrame = Frame( self )
		self.generatePlotsFrame.grid( row=self.currentRow , sticky=N+S )
		self.currentRow = self.currentRow + 1

		# Initialize generate plots object
		self.generatePlots = GeneratePlots( frame=self.generatePlotsFrame , simulationOutputData=self.simulationOutputData , paths=self.paths , display=self.display )


		### Generate animations ###

		# Initialize a frame
		self.generateAnimationsFrame = Frame( self )
		self.generateAnimationsFrame.grid( row=self.currentRow , sticky=N+S )
		self.currentRow = self.currentRow + 1

		# Initialize generate plots object
		self.generateAnimations = GenerateAnimations( frame=self.generateAnimationsFrame , simulationOutputData=self.simulationOutputData , paths=self.paths , display=self.display )


		# It will work just in linux...
		# ### Console ###

		# # Initialize a frame
		# self.consoleFrame = Frame( self )
		# self.consoleFrame.grid( row=self.currentRow , sticky=E+W+N+S )
		# self.currentRow = self.currentRow + 1

		# # Initialize Console object
		# self.console = Console( self.consoleFrame )


def main():
	SimulateInterface().mainloop() # starts event loop

if __name__ == "__main__":
	main()