# -*- coding: utf-8 -*-
"""
Created on Sun Feb  5 18:04:28 2017

@author: ruanc
"""

import re

line = "<Steve> Rohan \n <Uhuuu> uhuuu"

searchObj = re.search( r"<(.*?)> (.*)", line, re.M|re.I)

if searchObj:
   print("searchObj.group() : ", searchObj.group())
   print("searchObj.group(1) : ", searchObj.group(1))
   print("searchObj.group(2) : ", searchObj.group(2))
else:
   print("Nothing found!!")