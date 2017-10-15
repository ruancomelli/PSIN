import matplotlib.pyplot as plt
from matplotlib import animation

from AnimationLimits import AnimationLimits

class BuildAnimation ( AnimationLimits ):
	# This class inherits from a AnimationLimits
	# just to access the AnimationLimits functions.

	### Functions to handle with animation limits ###

	def build( simulationOutputData , paths , animationBools , animationTime , animationTypes ):

		### get simulation output data ###
		[simulationSettings, particleData, boundaryData, time] = simulationOutputData.get()

		### get folder where the animation will be saved ###
		simulationAnimationsOutputFolder = paths.getSimulationAnimationsOutputFolder()

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

		# Time indices
		timeIndices = [timeIndex for timeIndex in time.keys()]
			# Suppose that time = {5: 1.5, 8: 3.7}
			# 1.5 is the time instant indexed by number 5.
			# 5 is the first time index
			# So timeIndices[0] == 5 and time[5] == 1.5

		# Beginning of the simulation
		beginning = timeIndices[0]

		# Create several circles, one for each particle
		circles = {}

		for particleName, particle in particleData["SphericalParticle"].items():
			t = beginning
			X = 0
			Y = 1
			xCenter = float(particle["Position"][t][X])
			yCenter = float(particle["Position"][t][Y])
			radius = float(particle["Radius"][t])
			color = particle["Color"][t]
			# circles[particleName] = plt.Circle( (xCenter , yCenter), radius , fill=True, fc=color )
			circles[particleName] = plt.Circle( (xCenter , yCenter), radius , fill=True)

		### Initial function to animation ###
		def init():
			ax.set_title(str(time[0]) + " s")
			for name, particle in particleData["SphericalParticle"].items():
				t = beginning
				X = 0
				Y = 1
				xCenter = float(particle["Position"][t][X])
				yCenter = float(particle["Position"][t][Y])
				radius = float(particle["Radius"][t])
				color = particle["Color"][t]

				# circles[name] = plt.Circle( (xCenter, yCenter), radius, fill=True, fc=color )
				circles[name] = plt.Circle( (xCenter, yCenter), radius, fill=True)
				ax.add_patch(circles[name])

			return circles.values()

		def setAxisLimits(limits):
			[ xmin , xmax , ymin , ymax ] = limits
			ax.set_xlim( (xmin , xmax) )
			ax.set_ylim( (ymin , ymax) )

		def updateCircles(i):
			print("i: ", i, "\nlen: ", len(timeIndices), "\nt: ", timeIndices[i], "\n\n")
			for name, particle in particleData["SphericalParticle"].items():
				t = timeIndices[i]
				X = 0
				Y = 1
				xCenter = float(particle["Position"][t][X])
				yCenter = float(particle["Position"][t][Y])
				radius = float(particle["Radius"][t])
				circles[name].center = (xCenter , yCenter)
				circles[name].radius = radius

			return circles.values()

		### Animate function ###
		def animate_byTimeStep(i):
			t = timeIndices[i]
			# set graph limits
			limits = AnimationLimits.getLimits_byTimeStep( particleData, t )
			setAxisLimits(limits)
			ax.set_title(str(time[t]) + " s")
			circles = updateCircles(t)
			return circles

		def animate_global(i):
			t = timeIndices[i]

			# set graph limits
			limits = AnimationLimits.getLimits_global( particleData )
			setAxisLimits(limits)
			ax.set_title(str(time[t]) + " s")
			circles = updateCircles(t)
			return circles.values()

		def animate_autoscale(i):
			t = timeIndices[i]
			# set graph limits
			limits = AnimationLimits.getLimits_autoscale( ax )
			setAxisLimits(limits)
			ax.set_title(str(time[t]) + " s")
			circles = updateCircles(t)
			return circles.values()

		# define animate functions
		animateFunction = {}
		animateFunction["by_time_step"] = animate_byTimeStep
		animateFunction["global"] = animate_global
		animateFunction["autoscale"] = animate_autoscale

		### video settings ###
		frames = len(time)
		fps = frames/animationTime

		### build and save video ###
		for at in animationTypes:
			if( animationBools[at] ):
				anim = animation.FuncAnimation(fig, animateFunction[at], init_func=init, frames=frames , blit=True)
				extension = "_" + at + ".mp4"
				anim.save(simulationAnimationsOutputFolder + "Animation" + extension, fps=fps)