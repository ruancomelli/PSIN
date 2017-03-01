

# Animate function
def animate_byTimeStep(t):
	for p in range(nParticles):
		xCenter, yCente = circles[p].center
		X = 0
		Y = 1
		xCenter = particleData[p]['position'][t,X]
		yCenter = particleData[p]['position'][t,Y]
		circles[p].center = (xCenter , yCenter)
	print('t = ' , t)
	# set graph limits
	[ xmin , xmax , ymin , ymax ] = getLimits_byTimeStep( particleData , nParticles , t )
	ax.set_xlim( (xmin , xmax) )
	ax.set_ylim( (ymin , ymax) )
	return circles

def animate_global(t):
	for p in range(nParticles):
		xCenter, yCente = circles[p].center
		X = 0
		Y = 1
		xCenter = particleData[p]['position'][t,X]
		yCenter = particleData[p]['position'][t,Y]
		circles[p].center = (xCenter , yCenter)
	print('t = ' , t)
	# set graph limits
	[ xmin , xmax , ymin , ymax ] = getLimits_global( particleData , nParticles )
	ax.set_xlim( (xmin , xmax) )
	ax.set_ylim( (ymin , ymax) )
	return circles

def animate_autoscale(t):
	for p in range(nParticles):
		xCenter, yCente = circles[p].center
		X = 0
		Y = 1
		xCenter = particleData[p]['position'][t,X]
		yCenter = particleData[p]['position'][t,Y]
		circles[p].center = (xCenter , yCenter)
	print('t = ' , t)
	# set graph limits
	[ xmin , xmax , ymin , ymax ] = getLimits_autoscale( ax )
	ax.set_xlim( (xmin , xmax) )
	ax.set_ylim( (ymin , ymax) )
	return circles