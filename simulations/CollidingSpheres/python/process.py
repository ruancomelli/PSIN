import sys

sys.path.insert(0, '/home/ruancomelli/GitProjects/ParticleSimulator/Python/Pseudo')

from PseudoInterface import *

import operator
import numpy as np
from numpy import array
from numpy.linalg import norm
import matplotlib
import matplotlib.pyplot as plt
from math import ceil

programPath = "/home/ruancomelli/GitProjects/ParticleSimulator/build_sublime/bin/Release/psinApp"
mainInputFilePath = "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/FallingSphere/input/main.json"

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

initialPosition = array(propertyValue["Position"][0])
initialVelocity = array(propertyValue["Velocity"][0])
gravity = array([0.0, -9.81, 0.0])

instantaneousSolution = lambda t: initialPosition + initialVelocity * t + gravity * t**2 / 2
solution = array([instantaneousSolution(t) for t in timeInstant])

listDifference = lambda a, b: list(map(operator.sub, a, b))
error = array( list(map(listDifference, propertyValue["Position"], solution)) )
maxError = max([norm(x) for x in error])
print("Maximum error: ", maxError)

solution_x = list(map(list, zip(*solution)))[0]
solution_y = list(map(list, zip(*solution)))[1]
solution_z = list(map(list, zip(*solution)))[2]

normalsize = 1
smallsize = 4/9 * normalsize
family = 'serif'
weight = 'light'

fig = plt.figure(
	figsize=(10*normalsize, 8*normalsize),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

ax.plot(
	timeInstant,
	solution_y,
	color = 'black',
	label = 'Solução Analítica',
	# marker = '.',
	linewidth = 1*normalsize
	)

ax.plot(
	timeInstant,
	propertyValue["Position - Y"],
	color = 'red',
	label = 'Simulação',
	marker = '.',
	linestyle="None",
	markersize = 3*normalsize
	)

ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "y_position"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )

ax.tick_params(axis='both', which='major', labelsize=12*normalsize)
ax.tick_params(axis='both', which='minor', labelsize=10*normalsize)

handles, labels = ax.get_legend_handles_labels()
handle_list, label_list = [], []
for handle, label in zip(handles, labels):
    if label not in label_list:
        handle_list.append(handle)
        label_list.append(label)
lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': 14*normalsize, 'family': family, 'weight': weight})
ax.set_xlabel('Tempo [s]', fontdict={'size': 16*normalsize, 'family': family, 'weight': weight})
ax.set_ylabel('Altura [m]', fontdict={'size': 16*normalsize, 'family': family, 'weight': weight})
# lgd.set_title("Legenda", prop={'size': 16*normalsize, 'family': family, 'weight': weight})
lgd.set_title("Legenda", prop={'size': 16*normalsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)



mainInputFilePath = "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/FallingSphere/python/main.json"

null = None

mainData = {
	"initialTime": 0.0,
	"timeStep": 1e-3,
	"finalTime": 1,
	"timeStepsForOutput": 100,
	"outputsForExporting": 1,
	"mainOutputFolder": "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/FallingSphere/output",
	"particleOutputFolder": "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/FallingSphere/output/particles",
	"boundaryOutputFolder": "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/FallingSphere/output/boundaries",
	"looper": "GearLooper",
	"seeker": "BlindSeeker",

	"interactions":
	{
		"GravityForce": null
	},

	"particles":
	{
		"SphericalParticle": 
		[
			"/home/ruancomelli/GitProjects/ParticleSimulator/simulations/FallingSphere/input/particle.json"
		]
	},

	"boundaries":
	{
		"GravityField": 
		[
			"/home/ruancomelli/GitProjects/ParticleSimulator/simulations/FallingSphere/input/gravity.json"
		]
	}
}

# for Dt in [1e-3, 2e-3, 4e-3, 8e-3, 16e-3, 32e-3, 64e-3, 128e-3, 256e-3, 512e-3]:
# maxError = []
# Dt_vec = [2**(i/2)*1e-5 for i in range(20)]
# outputs = 1000
# for i in range(len(Dt_vec)):
# 	Dt = Dt_vec[i]
# 	mainData["timeStep"] = Dt
# 	mainData["timeStepsForOutput"] = ceil((mainData["finalTime"] - mainData["initialTime"]) / (mainData["timeStep"] * outputs))
# 	with open(mainInputFilePath, 'w') as mainFile:
# 		json.dump(mainData, mainFile)
# 	userInput = PseudoUserInput(programPath, mainInputFilePath)
# 	paths = PseudoPaths(userInput)
# 	simulate = PseudoSimulate(userInput, paths)
# 	simulate.execute()
# 	simulationOutputData = PseudoSimulationOutputData(paths)
# 	particleData = simulationOutputData.get()[1]
# 	particle = particleData["SphericalParticle"]["Particle"]

# 	propertyValue = {}
# 	for propertyName, propertyHistory in particle.items():
# 		propertyValue[propertyName] = list(propertyHistory.values())

# 	time = simulationOutputData.get()[3]
# 	timeIndex = list(time.keys())
# 	timeInstant = list(time.values())

# 	initialPosition = array(propertyValue["Position"][0])
# 	initialVelocity = array(propertyValue["Velocity"][0])
# 	gravity = array([0.0, -9.81, 0.0])

# 	instantaneousSolution = lambda t: initialPosition + initialVelocity * t + gravity * t**2 / 2
# 	solution = array([instantaneousSolution(t) for t in timeInstant])

# 	listDifference = lambda a, b: list(map(operator.sub, a, b))
# 	error = array( list(map(listDifference, propertyValue["Position"], solution)) )
# 	maxError.append(max([norm(x) for x in error]))


# fig = plt.figure(
# 	figsize=(10*normalsize, 8*normalsize),
# 	facecolor='w',
# 	edgecolor='k')

# ax = fig.add_subplot(111)

# ax.plot(
# 	Dt_vec,
# 	maxError,
# 	color = 'red',
# 	label = 'Erro Máximo',
# 	marker = '.'
# 	)
	
# outputFolder = paths.getSimulationPlotsOutputFolder()
# filename = "maximum_error"
# extension = ".pdf"
# ax.set_xscale('linear')
# ax.set_yscale('linear')

# ax.tick_params(axis='both', which='major', labelsize=12*normalsize)
# ax.tick_params(axis='both', which='minor', labelsize=10*normalsize)

# handles, labels = ax.get_legend_handles_labels()
# handle_list, label_list = [], []
# for handle, label in zip(handles, labels):
#     if label not in label_list:
#         handle_list.append(handle)
#         label_list.append(label)
# lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': 14*normalsize, 'family': family, 'weight': 'normal'})
# ax.set_xlabel('Tempo [s]', fontdict={'size': 16*normalsize, 'family': family})
# ax.set_ylabel('Altura [m]', fontdict={'size': 16*normalsize, 'family': family})
# lgd.set_title("Legenda", prop={'size': 16*normalsize, 'family': family, 'weight': 'normal'})

# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# ax.set_xscale('log')
# ax.set_yscale('linear')
# filename = "maximum_error_logx"
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# ax.set_xscale('linear')
# ax.set_yscale('log')
# filename = "maximum_error_logy"
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# ax.set_xscale('log')
# ax.set_yscale('log')
# filename = "maximum_error_logx_logy"
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# plt.close(fig)

# fig = plt.figure(
# 	figsize=(18, 14),
# 	facecolor='w',
# 	edgecolor='k')

# ax = fig.add_subplot(111)

# ax.plot(
# 	[time[t] for t in time.keys()],
# 	[particle[propertyName][t] for t in time.keys()],
# 	color = getColor(particle["Color"][next(iter(particle["Color"]))]),
# 	label = particleName,
# 	marker = '.'
# 	)

# plt.close(fig)