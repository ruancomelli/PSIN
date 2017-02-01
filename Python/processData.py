# -*- coding: utf-8 -*-
"""
@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import os
import errno

def simulate( simulationName ):
	
	print( "> Initializing Program" )
	print( "==== ", simulationName, " ====" )
	
	simulationInputPath = "../../_input/input.txt"
	simulationOutputPath = "../../_output/" + simulationName + "/"
	pythonOutputPath = "../../_output/" + simulationName + "/MATLAB_output/"
	programPath = "../../_tests/"
	programName = "collidingspheres.exe"
	
	simulationInputFileString = "<simulationName> " + simulationName
	simulationInputFile = open(simulationInputPath, 'w');
	simulationInputFile.write()

	simulationInputFile.close()
	
	os.makedirs(pythonOutputPath, exist_ok=True)

