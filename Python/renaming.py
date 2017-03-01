# -*- coding: utf-8 -*-
"""
Created on Thu Feb 16 12:52:31 2017

@author: ruancomelli
"""

import glob, os, re

def renameBoostFiles():

	os.chdir("C:/Users/ruanc.LAPTOP-8F2K1OUJ/GitProjects/boost_1_63_0/stage/lib")

	for file in glob.glob("*.lib"):
		
		regularExpression = r"(.*?)-vc140-(.*)"
		compiledInformation = re.compile(regularExpression)
		
		x = os.listdir()
		
		for filename in x:
			matches = compiledInformation.match(filename)
			if matches is None: continue
			newFilename = matches.group(1).strip() + "-vc100-" + matches.group(2).strip()
			os.rename(filename, newFilename)