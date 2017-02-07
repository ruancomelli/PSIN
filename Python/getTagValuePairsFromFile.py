# -*- coding: utf-8 -*-
"""
Created at 06 feb. 2017

@author: ruancomelli
@email: ruancomelli@sinmec.ufsc.br
"""

import re

def getTagValuePairsFromFile( fileName, leftMarker, rightMarker = ""):

    regularExpression = leftMarker + r"(.*?)" + rightMarker + "(.*)"
    compiledInformation = re.compile(regularExpression)
    
    settings = {}
    fd = open(fileName, 'r')
    
    for line in fd:
            m = compiledInformation.match(line)
            if m is None: continue
            settings[m.group(1)] = m.group(2).strip()
    
    fd.close()
            
    return settings