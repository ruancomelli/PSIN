class AnimationLimits:

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
		

	def getMinAndMax(particleData, t, coor):
		# t : time step
		# coor : coordinate ; X=0 , Y=1 and Z=2

		coorMin = min([
			particle["Position"][t][coor] - particle["Radius"][t] 
			for particle in particleData["SphericalParticle"].values()
			])

		coorMin = max([
			particle["Position"][t][coor] + particle["Radius"][t] 
			for particle in particleData["SphericalParticle"].values()
			])

		return [coorMin , coorMax]

	def getLimits_byTimeStep(particleData, t):
		# Define a limit for each time instant
		X = 0
		Y = 1
		Z = 2

		# X
		[xmin , xmax] = AnimationLimits.getMinAndMax(particleData, t, X)

		# Y
		[ymin , ymax] = AnimationLimits.getMinAndMax(particleData, t, Y)
		
		[ xmin , xmax , ymin , ymax ] = AnimationLimits.setSquare(xmin , xmax , ymin , ymax)

		return [ xmin , xmax , ymin , ymax ]

	def getLimits_global( particleData ):
		#Set limits

		X = 0
		Y = 1
		Z = 2

		xmin = min([
				min(particle["Position"][:][X] - particle["Radius"])
				for particle in particleData["SphericalParticle"].values()
			])

		xmax = max([
				max(particle["Position"][:][X] + particle["Radius"])
				for particle in particleData["SphericalParticle"].values()
			])

		ymin = min([
				min(particle["Position"][:][Y] - particle["Radius"])
				for particle in particleData["SphericalParticle"].values()
			])

		ymax = max([
				max(particle["Position"][:][Y] + particle["Radius"])
				for particle in particleData["SphericalParticle"].values()
			])
		
		[ xmin , xmax , ymin , ymax ] = AnimationLimits.setSquare(xmin , xmax , ymin , ymax)

		return [ xmin , xmax , ymin , ymax ]

	def getLimits_autoscale( ax ):

		ax.autoscale(enable=True , axis='both')

		[xmin , xmax] = ax.get_xlim()
		[ymin , ymax] = ax.get_ylim()
		
		[ xmin , xmax , ymin , ymax ] = AnimationLimits.setSquare(xmin , xmax , ymin , ymax)

		return [ xmin , xmax , ymin , ymax ]