import matplotlib.pyplot as plt
from matplotlib import animation

from AnimationLimits import AnimationLimits

class BuildAnimation ( AnimationLimits ):
	# This class inherits from a AnimationLimits
	# just to access the AnimationLimits functions.

	### Functions to handle with animation limits ###

	def build( simulationOutputData , paths , animationBools , animationTime , animationTypes ):

		### get simulation output data ###
		[simulationSettings , particleData , timeVectorForPlot , scalarMap ] = simulationOutputData.get()

		### get folder where the animation will be saved ###
		simulationAnimationsOutputFolder = paths.getSimulationAnimationsOutputFolder()

		# extracting information from 'simulationSettings'
		nParticles = int(simulationSettings["nParticles"])

		### Configure figure ###
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

		### Initial function to animation ###
		def init():
			ax.set_title(str(timeVectorForPlot[0]) + " s")
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

		### Animate function ###
		def animate_byTimeStep(t):
			for p in range(nParticles):
				xCenter, yCente = circles[p].center
				X = 0
				Y = 1
				xCenter = particleData[p]['position'][t,X]
				yCenter = particleData[p]['position'][t,Y]
				circles[p].center = (xCenter , yCenter)
			# set graph limits
			[ xmin , xmax , ymin , ymax ] = AnimationLimits.getLimits_byTimeStep( particleData , nParticles , t )
			ax.set_xlim( (xmin , xmax) )
			ax.set_ylim( (ymin , ymax) )
			ax.set_title(str(timeVectorForPlot[t]) + " s")
			return circles

		def animate_global(t):
			for p in range(nParticles):
				xCenter, yCente = circles[p].center
				X = 0
				Y = 1
				xCenter = particleData[p]['position'][t,X]
				yCenter = particleData[p]['position'][t,Y]
				circles[p].center = (xCenter , yCenter)
			# set graph limits
			[ xmin , xmax , ymin , ymax ] = AnimationLimits.getLimits_global( particleData , nParticles )
			ax.set_xlim( (xmin , xmax) )
			ax.set_ylim( (ymin , ymax) )
			ax.set_title(str(timeVectorForPlot[t]) + " s")
			return circles

		def animate_autoscale(t):
			for p in range(nParticles):
				xCenter, yCente = circles[p].center
				X = 0
				Y = 1
				xCenter = particleData[p]['position'][t,X]
				yCenter = particleData[p]['position'][t,Y]
				circles[p].center = (xCenter , yCenter)
			# set graph limits
			[ xmin , xmax , ymin , ymax ] = AnimationLimits.getLimits_autoscale( ax )
			ax.set_xlim( (xmin , xmax) )
			ax.set_ylim( (ymin , ymax) )
			ax.set_title(str(timeVectorForPlot[t]) + " s")
			return circles

		# define animate functions
		animateFunction = {}
		animateFunction["by_time_step"] = animate_byTimeStep
		animateFunction["global"] = animate_global
		animateFunction["autoscale"] = animate_autoscale

		### video settings ###
		frames = len(timeVectorForPlot)
		fps = frames/animationTime

		### build and save video ###
		for at in animationTypes:
			if( animationBools[at] ):
				anim = animation.FuncAnimation(fig, animateFunction[at], init_func=init, frames=frames , blit=True)
				extension = "_" + at + ".mp4"
				anim.save(simulationAnimationsOutputFolder + "Animation" + extension, fps=fps)