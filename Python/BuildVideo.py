import matplotlib.pyplot as plt
import os
from matplotlib import animation
from math import floor
from numpy import log10
from Geometry import getIntersectPoints

from AnimationLimits import AnimationLimits

### Auxilliary function to get color ###
def getColor(color):
	if color[1] == "":
		return (color[0][0], color[0][1], color[0][2])
	else:
		return color[1]

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

		if "SphericalParticle" in particleData:
			for particleName, particle in particleData["SphericalParticle"].items():
				t = beginning
				X = 0
				Y = 1
				xCenter = float(particle["Position"][t][X])
				yCenter = float(particle["Position"][t][Y])
				radius = float(particle["Radius"][t])
				color = getColor(particle["Color"][t])
				circles[particleName] = plt.Circle( (xCenter , yCenter), radius , fill=True, fc=color )

		limits = AnimationLimits.getLimits_global( particleData )
		lines = {}
		if "FixedInfinitePlane" in boundaryData:
			for boundaryName, boundary in boundaryData["FixedInfinitePlane"].items():
				t = beginning
				X = 0
				Y = 0
				normalVersor = float(boundary[""])
				(boolReturn, begin, end) = getIntersectPoints(boundary[""])

		round_to_n = lambda x, n: round(x, -int(floor(log10(x))) + (n - 1)) if x != 0 else 0

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
				color = getColor(particle["Color"][t])

				circles[name] = plt.Circle( (xCenter, yCenter), radius, fill=True, fc=color )
				ax.add_patch(circles[name])

			return circles.values()

		def setAxisLimits(limits):
			[ xmin , xmax , ymin , ymax ] = limits
			ax.set_xlim( (xmin , xmax) )
			ax.set_ylim( (ymin , ymax) )

		def updateCircles(t):
			if "SphericalParticle" in particleData:
				for name, particle in particleData["SphericalParticle"].items():
					X = 0
					Y = 1
					xCenter = float(particle["Position"][t][X])
					yCenter = float(particle["Position"][t][Y])
					radius = float(particle["Radius"][t])
					circles[name].center = (xCenter , yCenter)
					circles[name].radius = radius

			return circles

		### Animate function ###
		def animate_byTimeStep(t):
			t = timeIndices[t]
			# set graph limits
			limits = AnimationLimits.getLimits_byTimeStep( particleData, t )
			setAxisLimits(limits)
			ax.set_title(str(round_to_n(time[t], 2)) + " s")
			circles = updateCircles(t)
			return circles.values()

		def animate_global(t):
			t = timeIndices[t]
			# set graph limits
			limits = AnimationLimits.getLimits_global( particleData )
			setAxisLimits(limits)
			ax.set_title(str(round_to_n(time[t], 2)) + " s")
			circles = updateCircles(t)
			return circles.values()

		def animate_autoscale(t):
			t = timeIndices[t]
			# set graph limits
			limits = AnimationLimits.getLimits_autoscale( ax )
			setAxisLimits(limits)
			ax.set_title(str(round_to_n(time[t], 2)) + " s")
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
				filename = "Animation" + extension
				filepath = os.path.join(simulationAnimationsOutputFolder, filename)
				anim.save(filepath, fps=fps)