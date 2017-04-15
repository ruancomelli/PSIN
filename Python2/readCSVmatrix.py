# -*- coding: utf-8 -*-
"""
Created at 07 feb. 2017

@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import csv
import numpy

# This function will read a CSV file and it will
# return a array of read data. See the csv python
# package for more information.

def readCSVmatrix( filePath ):

	csvData = []

	# equivalent to csvFile = open(filePath)
	with open(filePath) as csvFile:

		readerObj = csv.reader(csvFile)

		for row in readerObj:
			csvData.append(row)
			
		csvData = numpy.array(csvData).astype(numpy.float)
		
	return numpy.array(csvData)
