from matplotlib import pyplot as plt
from matplotlib import animation
from graphLimitsFunctions import *

def build_video(particleData , nParticles):

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
		circles.append( plt.Circle( (xCenter , yCenter), radius , fill=True , facecolor='b' ) )

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
	def animate(t):
		for p in range(nParticles):
			xCenter, yCente = circles[p].center
			X = 0
			Y = 1
			xCenter = particleData[p]['position'][t,X]
			yCenter = particleData[p]['position'][t,Y]
			circles[p].center = (xCenter , yCenter)
		print('t = ' , t)
		# set graph limits
#		[ xmin , xmax , ymin , ymax ] = getLimits_byTimeStep( particleData , nParticles , t )
#		[ xmin , xmax , ymin , ymax ] = getLimits_global( particleData , nParticles )
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

	anim = animation.FuncAnimation(fig, animate, init_func=init, frames=frames, interval=interval)

	anim.save('CollidingSpheres.mp4', fps=fps, extra_args=['-vcodec', 'h264', '-pix_fmt', 'yuv420p'])
