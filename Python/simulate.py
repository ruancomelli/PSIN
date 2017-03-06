import subprocess

# run the simulation program, C++
def simulate(programFolder , programName):
	#
	# SIMULATING
	#
	# It executes the C++ compiled program
	print( "> Simulating" )
	subprocess.Popen( programFolder + programName )
	print( "< Simulation finished" )