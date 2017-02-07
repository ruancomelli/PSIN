# -*- coding: utf-8 -*-
"""
Created at 07 feb. 2017

@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import csv

def readCSV( filePath ):

	csvData = []

	with open(filePath) as csvFile:

		readerObj = csv.reader(csvFile)

		for row in readerObj:
			csvData.append(row)

	return csvData
