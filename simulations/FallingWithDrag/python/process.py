import sys

sys.path.insert(0, '/home/ruancomelli/GitProjects/ParticleSimulator/Python/Pseudo')

from PseudoInterface import *

import operator
import numpy as np
from numpy import array
from numpy import dot
from numpy.linalg import norm
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
from math import ceil
from math import sqrt, log, exp, atan2, pi

def consecute_diff(x):
	return [j-i for i, j in zip(x[:-1], x[1:])]

programPath = "/home/ruancomelli/GitProjects/ParticleSimulator/build_sublime/bin/Release/psinApp"
mainInputFilePath = "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/FallingWithDrag/input/main.json"

userInput = PseudoUserInput(programPath, mainInputFilePath)
paths = PseudoPaths(userInput)
simulationOutputData = PseudoSimulationOutputData(paths)
simulate = PseudoSimulate(userInput, paths)

simulate.execute()

particleData = simulationOutputData.get()[1]
particle = particleData["SphericalParticle"]["Particle"]

propertyValue = {}
for propertyName, propertyHistory in particle.items():
	propertyValue[propertyName] = list(propertyHistory.values())

time = simulationOutputData.get()[3]
timeIndex = list(time.keys())
timeInstant = list(time.values())
gravity = array([0.0, -9.81, 0.0])

normalwidth = 6
normalheight = 4
smallwidth = 7 * 4/10
smallheight = 5 * 4/10
# smallsize = 4/9 * normalsize
normalfontsize = 11
smallfontsize = 9
majorTickLabelSize = 10
minorTickLabelSize = 10
normalmarkersize = 3
normallinewidth = 1
family = 'serif'
weight = 'light'
dgray = [0.4, 0.4, 0.4]
lgray = [0.8, 0.8, 0.8]
llgray = [0.9, 0.9, 0.9]

radius = propertyValue["Radius"][0]
mass = propertyValue["Mass"][0]
area = pi * radius**2
g = norm(gravity)
dragCoefficient = 0.5
airSpecificMass = 1

analyticalTerminalVelocity = - sqrt(2*mass*g/(airSpecificMass*area*dragCoefficient))
analyticalTerminalVelocityVector = [analyticalTerminalVelocity] * len(timeInstant)

particleHeight = propertyValue["Position-Y"]
particleHeightForPlot = [x/1000 for x in propertyValue["Position-Y"]]
heightLabel = "Altura [km]"

potentialEnergy = [mass * norm(gravity) * h for h in particleHeight]
kineticEnergy = propertyValue["kineticEnergy"]
mechanicalEnergy = [p + k for p, k in zip(potentialEnergy, kineticEnergy)]

########################### Y POSITION
# normal size
fig = plt.figure(
	figsize=(normalwidth, normalheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

ax.plot(
	timeInstant,
	particleHeightForPlot,
	color = 'red',
	label = 'Simulação',
	marker = '.',
	linestyle="None",
	markersize = normalmarkersize
	)

ax.grid(visible=True , which='major' , color=lgray)

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "y_position_normal"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel(heightLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

# small size

fig = plt.figure(
	figsize=(smallwidth, smallheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

ax.plot(
	timeInstant,
	particleHeightForPlot,
	color = 'red',
	label = 'Simulação',
	marker = '.',
	linestyle="None",
	markersize = normalmarkersize
	)

ax.grid(visible=True , which='major' , color=lgray)

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "y_position_small"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel(heightLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

########################### Y VELOCITY
# normal size
fig = plt.figure(
	figsize=(normalwidth, normalheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

ax.plot(
	timeInstant,
	analyticalTerminalVelocityVector,
	color = 'black',
	label = 'Velocidade Terminal Analítica',
	# marker = '.',
	linewidth = normallinewidth
	)

ax.plot(
	timeInstant,
	propertyValue["Velocity-Y"],
	color = 'red',
	label = 'Simulação',
	marker = '.',
	linestyle="None",
	markersize = normalmarkersize
	)

ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "y_velocity_normal"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

handles, labels = ax.get_legend_handles_labels()
handle_list, label_list = [], []
for handle, label in zip(handles, labels):
    if label not in label_list:
        handle_list.append(handle)
        label_list.append(label)
lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
lgd.get_frame().set_facecolor(llgray)
lgd.get_frame().set_edgecolor(dgray)
ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel('Velocidade Vertical [m/s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

# small size
fig = plt.figure(
	figsize=(smallwidth, smallheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

ax.plot(
	timeInstant,
	analyticalTerminalVelocityVector,
	color = 'black',
	label = 'Velocidade Terminal\nAnalítica',
	# marker = '.',
	linewidth = normallinewidth
	)

ax.plot(
	timeInstant,
	propertyValue["Velocity-Y"],
	color = 'red',
	label = 'Simulação',
	marker = '.',
	linestyle="None",
	markersize = normalmarkersize
	)

ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "y_velocity_small"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

handles, labels = ax.get_legend_handles_labels()
handle_list, label_list = [], []
for handle, label in zip(handles, labels):
    if label not in label_list:
        handle_list.append(handle)
        label_list.append(label)
lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
lgd.get_frame().set_facecolor(llgray)
lgd.get_frame().set_edgecolor(dgray)
ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel('Velocidade Vertical [m/s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

# ########################### KINETIC ENERGY
# normal size
fig = plt.figure(
	figsize=(normalwidth, normalheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

if len(timeInstant) > 100:
	ax.plot(
		timeInstant,
		kineticEnergy,
		color = 'red',
		label = 'Energia cinética da partícula',
		# marker = '.',
		linewidth = normallinewidth
		)
else:
	ax.plot(
		timeInstant,
		kineticEnergy,
		color = 'red',
		label = 'Energia cinética da partícula',
		marker = '.',
		linestyle="None",
		# linewidth = normallinewidth,
		markersize = normalmarkersize
		)

ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "kinetic_energy_normal"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
lgd.get_frame().set_facecolor(llgray)
lgd.get_frame().set_edgecolor(dgray)
ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel('Energia cinética da partícula [J]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

# small size
fig = plt.figure(
	figsize=(smallwidth, smallheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

if len(timeInstant) > 100:
	ax.plot(
		timeInstant,
		kineticEnergy,
		color = 'red',
		label = 'Energia cinética da partícula',
		# marker = '.',
		linewidth = normallinewidth
		)
else:
	ax.plot(
		timeInstant,
		kineticEnergy,
		color = 'red',
		label = 'Energia cinética da partícula',
		marker = '.',
		linestyle="None",
		# linewidth = normallinewidth,
		markersize = normalmarkersize
		)

ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "kinetic_energy_small"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
lgd.get_frame().set_facecolor(llgray)
lgd.get_frame().set_edgecolor(dgray)
ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel('Energia cinética da partícula [J]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

# ########################### MECHANICAL ENERGY
# normal size 
fig = plt.figure(
	figsize=(normalwidth, normalheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

if len(timeInstant) > 100:
	ax.plot(
		timeInstant,
		mechanicalEnergy,
		color = 'red',
		label = 'Energia mecânica da partícula',
		# marker = '.',
		linewidth = normallinewidth
		)
else:
	ax.plot(
		timeInstant,
		mechanicalEnergy,
		color = 'red',
		label = 'Energia mecânica da partícula',
		marker = '.',
		linestyle="None",
		# linewidth = normallinewidth,
		markersize = normalmarkersize
		)

ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "mechanical_energy_normal"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )
plt.ylim( 0, 8000 )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
lgd.get_frame().set_facecolor(llgray)
lgd.get_frame().set_edgecolor(dgray)
ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel('Energia mecânica da partícula [J]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

# small size 
fig = plt.figure(
	figsize=(smallwidth, smallheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

if len(timeInstant) > 100:
	ax.plot(
		timeInstant,
		mechanicalEnergy,
		color = 'red',
		label = 'Energia mecânica da partícula',
		# marker = '.',
		linewidth = normallinewidth
		)
else:
	ax.plot(
		timeInstant,
		mechanicalEnergy,
		color = 'red',
		label = 'Energia mecânica da partícula',
		marker = '.',
		linestyle="None",
		# linewidth = normallinewidth,
		markersize = normalmarkersize
		)

ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "mechanical_energy_small"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )
plt.ylim( 0, 8000 )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
lgd.get_frame().set_facecolor(llgray)
lgd.get_frame().set_edgecolor(dgray)
ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel('Energia mecânica da partícula [J]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

airKinematicViscosity = 1.5e-5
Rmin = 1000
Rmax = 300000
vmin = Rmin * airKinematicViscosity / (2 * radius)
vmax = Rmax * airKinematicViscosity / (2 * radius)

print("Velocity limits: (", vmin, ",", vmax, ") m/s")
print("Terminal velocity: ", analyticalTerminalVelocity, "m/s")
particleDensity = 7639
particleTheoreticalMass = particleDensity * 4/3 * pi * radius**3
terminalVelocity = sqrt(2 * particleTheoreticalMass * g / (dragCoefficient * area * airSpecificMass))
print("Theoretical terminal velocity: ", terminalVelocity, "m/s")
print("Final velocity: ", propertyValue["Velocity-Y"][1], "m/s")