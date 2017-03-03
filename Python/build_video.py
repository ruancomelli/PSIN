from matplotlib import pyplot as plt
from matplotlib import animation
from graphLimitsFunctions import *
from interfaceDefinitions import *

# def build_video(particleData , nParticles , outputFolder , fileName , limitsType):
def build_video(particleData , nParticles , outputFolder , fileName , videoBools):

	# Config 
	fig_dpi = 100
	fig_x_size = 7
	fig_y_size = 6.5

	# create figure
	fig = plt.figure()
	fig.set_dpi(fig_dpi)
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
		circles.append( plt.Circle( (xCenter , yCenter), radius , fill=True ) )

	# Initial function to animation
	def init():
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

	# Generating video
	interval = 10
	frames = 100
	fps = 30

	print('interval = ' , interval)
	print('frames = ' , frames)
	print('fps = ' , fps)

	# define animate functions
	animateFunction = {}
	animateFunction["by time step"] = animate_byTimeStep
	animateFunction["global"] = animate_global
	animateFunction["autoscale"] = animate_autoscale

	for vt in videoType:
		if( videoBools[vt] ):
			anim = animation.FuncAnimation(fig, animateFunction[vt], init_func=init, frames=frames, interval=interval)
			extension = "_" + vt + ".mp4"
			anim.save(outputFolder + fileName + extension, fps=fps, extra_args=['-vcodec', 'h264', '-pix_fmt', 'yuv420p'])