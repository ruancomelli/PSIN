# -*- coding: utf-8 -*-
"""
Created at 06 feb. 2017

@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import re

def getTagValuePairsFromFile( fileName, leftMarker, rightMarker = ""):

	# It looks for expressions as: LEFTMARKER SOMETHIN_NOT_EMPTY RIGHTMARKER SOME_OTHER_THING_NOT_EMPTY
	# It will save the SOMETHIN_NOT_EMPTY int group(1) and SOME_OTHER_THING_NOT_EMPTY in group(2)
	#example: leftmarker = '<' , rightmarker = '>'
	#    <expression1> something
	# { group(1) == 'expression1' } is true
	# { group(2) == 'something' } is true
    regularExpression = leftMarker + r"(.*?)" + rightMarker + "(.*)"
    compiledInformation = re.compile(regularExpression)
    
    settings = {}
    fd = open(fileName, 'r')
    
    for line in fd:
		# It will iterate in all file lines looking for
		# some expression as defined above.
		# If some expression is found, it will save
		# in the dictionary "settings".
		# example:
		#    the expression "<expression1> something" if
		#    found in file will be saved as:
		#    setting[ r'expression1' ] = something
		# The "strip()" will process the string to eliminate
		# newline and whitespace
            m = compiledInformation.match(line)
            if m is None: continue
            settings[m.group(1)] = m.group(2).strip()
    
    fd.close()
            
    return settings