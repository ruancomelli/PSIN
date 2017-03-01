def setSquare(xmin , xmax , ymin , ymax):
	xWidth = xmax - xmin
	middleX = (xmax + xmin) / 2

	yWidth = ymax - ymin
	middleY = (ymax + ymin) / 2

	width = max( xWidth , yWidth )
	
	xmin = middleX - width/2
	xmax = middleX + width/2
	
	ymin = middleY - width/2
	ymax = middleY + width/2
	
	return [ xmin , xmax , ymin , ymax ]
	

def getMinAndMax(particleData , nParticles , t , coor):
	# t : time step
	# coor : coordinete ; X=0 , Y=1 and Z=2

	coorMin = particleData[0]['position'][t,coor] - float( particleData[0]['main']['Radius'] )
	for p in range(nParticles):
		coorMin = min( coorMin , particleData[p]['position'][t,coor] - float(particleData[p]['main']['Radius']) )

	# max
	coorMax = particleData[0]['position'][t,coor] + float( particleData[0]['main']['Radius'] )
	for p in range(nParticles):
		coorMax = max( coorMax , particleData[p]['position'][t,coor] - float(particleData[p]['main']['Radius']) )

	return [coorMin , coorMax]

def getLimits_byTimeStep(particleData , nParticles , t):
	# Define a limit for each time instant
	X = 0
	Y = 1
	Z = 2

	# X
	[xmin , xmax] = getMinAndMax(particleData , nParticles , t , X)

	# Y
	[ymin , ymax] = getMinAndMax(particleData , nParticles , t , Y)
	
	[ xmin , xmax , ymin , ymax ] = setSquare(xmin , xmax , ymin , ymax)

	return [ xmin , xmax , ymin , ymax ]

def getLimits_global( particleData , nParticles ):
	#Set limits
	p = 0
	xmin = min(particleData[p]['position'][:,0] - float(particleData[p]['main']['Radius']))
	xmax = max(particleData[p]['position'][:,0] + float(particleData[p]['main']['Radius']))
	ymin = min(particleData[p]['position'][:,1] - float(particleData[p]['main']['Radius']))
	ymax = max(particleData[p]['position'][:,1] + float(particleData[p]['main']['Radius']))
	for p in range(nParticles): # for each particle
		# X
		xLocalMin = min(particleData[p]['position'][:,0] - float(particleData[p]['main']['Radius']))
		xLocalMax = max(particleData[p]['position'][:,0] + float(particleData[p]['main']['Radius']))
		if(xLocalMin < xmin):
			xmin = xLocalMin
		if(xLocalMax > xmax):
			xmax = xLocalMax
		# Y
		yLocalMin = min(particleData[p]['position'][:,1] - float(particleData[p]['main']['Radius']))
		yLocalMax = max(particleData[p]['position'][:,1] + float(particleData[p]['main']['Radius']))
		if(yLocalMin < ymin):
			ymin = yLocalMin
		if(yLocalMax > ymax):
			ymax = yLocalMax
	
	[ xmin , xmax , ymin , ymax ] = setSquare(xmin , xmax , ymin , ymax)

	return [ xmin , xmax , ymin , ymax ]

def getLimits_autoscale( ax ):

	ax.autoscale(enable=True , axis='both')

	[xmin , xmax] = ax.get_xlim()
	[ymin , ymax] = ax.get_ylim()
	
	[ xmin , xmax , ymin , ymax ] = setSquare(xmin , xmax , ymin , ymax)

	return [ xmin , xmax , ymin , ymax ]

