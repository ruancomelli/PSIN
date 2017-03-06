from matplotlib import pyplot as plt
from matplotlib import animation
from graphLimitsFunctions import *
from interfaceDefinitions import *

# def build_video(particleData , nParticles , outputFolder , fileName , limitsType):
def build_video(simulationSettings , particleData , timeVector , scalarMap , outputFolder , fileName , videoBools , videoTime):

	# extracting information from 'simulationSettings'
	nParticles = int(simulationSettings["nParticles"])
	initialTime = float(simulationSettings["initialTime"])
	finalTime = float(simulationSettings["finalTime"])
	timeStep = float(simulationSettings["timeStep"])


	# Config 
	fig_x_size = 8
	fig_y_size = 8

	# create figure
	fig = plt.figure()
	fig.set_size_inches(fig_x_size, fig_y_size)
	ax = fig.add_subplot(111)
	ax.grid(visible=True)

	# Set axes limits
	ax.autoscale(enable=True , axis='both')

	# Create several circles, one for each particle
	circles = []
	for p in range(nParticles):
		radius = float( particleData[p]['main']['Radius'] )
		timeStep = 0
		X = 0
		Y = 1
		xCenter = particleData[p]['position'][timeStep,X]
		yCenter = particleData[p]['position'][timeStep,Y]
		circles.append( plt.Circle( (xCenter , yCenter), radius , fill=True , fc=scalarMap.to_rgba(p) ) )

	# Initial function to animation
	def init():
		ax.set_title(str(timeVector[0]) + " s")
		for p in range(nParticles):
			radius = float( particleData[p]['main']['Radius'] )
			timeStep = 0
			X = 0
			Y = 1
			xCenter = particleData[p]['position'][timeStep,X]
			yCenter = particleData[p]['position'][timeStep,Y]
			circles[p].center = (xCenter , yCenter)
			ax.add_patch(circles[p])

		return circles

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
		ax.set_title(str(timeVector[t]) + " s")
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
		ax.set_title(str(timeVector[t]) + " s")
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
		ax.set_title(str(timeVector[t]) + " s")
		return circles

	# Generating video
	totalTime = finalTime - initialTime
	frames = len(timeVector)
	fps = frames/videoTime

	# define animate functions
	animateFunction = {}
	animateFunction["by_time_step"] = animate_byTimeStep
	animateFunction["global"] = animate_global
	animateFunction["autoscale"] = animate_autoscale

	for vt in videoType:
		if( videoBools[vt] ):
			anim = animation.FuncAnimation(fig, animateFunction[vt], init_func=init, frames=frames , blit=True)
			extension = "_" + vt + ".mp4"
			anim.save(outputFolder + fileName + extension, fps=fps)