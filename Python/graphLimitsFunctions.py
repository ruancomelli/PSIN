def getMinAndMax(particleData , nParticles , t , coor)
	# t : time step
	# coor : coordinete ; X=0 , Y=1 and Z=2

	coorMin = particleData[0]['position'][t,coor] - float( particleData[0]['main']['Radius'] )
	for p in range(nParticles):
		coorMin = min( coorMin , particleData[p]['position'][t,coor] - float(particleData[p]['main']['Radius']) )

	# max
	coorMax = particleData[0]['position'][t,coor] + float( particleData[0]['main']['Radius'] )
	for p in range(nParticles):
		coorMax = min( coorMax , particleData[p]['position'][t,coor] - float(particleData[p]['main']['Radius']) )

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

	return [ xmin , xmax , ymin , ymax ]

def getLimits_global( particleData , nParticles ):
	#Set limits
	xMin = min(particleData[0]['position'][:,0])
	xMax = max(particleData[0]['position'][:,0])
	yMin = min(particleData[0]['position'][:,1])
	yMax = max(particleData[0]['position'][:,1])
	for p in range(nParticles): # for each particle
		# X
		xLocalMin = min(particleData[p]['position'][:,0])
		xLocalMax = max(particleData[p]['position'][:,0])
		if(xLocalMin < xMin):
			xMin = xLocalMin
		if(xLocalMax > xMax):
			xMax = xLocalMax
		# Y
		yLocalMin = min(particleData[p]['position'][:,0])
		yLocalMax = max(particleData[p]['position'][:,0])
		if(xLocalMin < xMin):
			yMin = yLocalMin
		if(xLocalMax > xMax):
			yMax = yLocalMax

	return [ xmin , xmax , ymin , ymax ]

def getLimits_autoscale( ax )

	ax.autoscale(enable=True , axis='both')

	[xmin , xmax] = ax.get_xlim()
	[ymin , ymax] = ax.get_ylim()

	return [ xmin , xmax , ymin , ymax ]

