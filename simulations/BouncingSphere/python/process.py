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

normalwidth = 7
normalheight = 5
smallwidth = 7 * 4/9
smallheight = 5 * 4/9
# smallsize = 4/9 * normalsize
normalfontsize = 11
smallfontsize = 9
majorTickLabelSize = 10
minorTickLabelSize = 10
normalmarkersize = 3
normallinewidth = 1
family = 'serif'
weight = 'light'

resistanceRule = lambda a,b: a*b/(a+b)

programPath = "/home/ruancomelli/GitProjects/ParticleSimulator/build_sublime/bin/Release/psinApp"
mainInputFilePath = "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/BouncingSphere/input/main.json"

userInput = PseudoUserInput(programPath, mainInputFilePath)
paths = PseudoPaths(userInput)
simulationOutputData = PseudoSimulationOutputData(paths)
simulate = PseudoSimulate(userInput, paths)

# simulate.execute()

particleData = simulationOutputData.get()[1]
boundaryData = simulationOutputData.get()[2]
time = simulationOutputData.get()[3]
timeIndex = list(time.keys())
timeInstant = list(time.values())
# timestep = time[timeIndex[1]] - time[timeIndex[0]]
timestep = 1e-5

particle = particleData["SphericalParticle"]["Particle"]
wall = boundaryData["FixedInfinitePlane"]["Wall"]
gravity = array(boundaryData["GravityField"]["Gravity"]["Gravity"][0])

particlePropertyValue = {}
for propertyName, propertyHistory in particle.items():
	particlePropertyValue[propertyName] = list(propertyHistory.values())

wallPropertyValue = {}
for propertyName, propertyHistory in particle.items():
	wallPropertyValue[propertyName] = list(propertyHistory.values())

effectiveMass = particlePropertyValue["Mass"][0]
effectiveElasticModulus = resistanceRule(particlePropertyValue["ElasticModulus"][0], wallPropertyValue["ElasticModulus"][0])
effectiveNormalDissipativeConstant = resistanceRule(particlePropertyValue["NormalDissipativeConstant"][0], wallPropertyValue["NormalDissipativeConstant"][0])
omegaStar = sqrt(effectiveElasticModulus / effectiveMass)
beta = effectiveNormalDissipativeConstant / effectiveMass

if beta < omegaStar / sqrt(2):
	omega = sqrt(omegaStar**2 - beta**2)
	analyticalCoefficientOfRestitution = exp(-beta/omega * (pi - atan2(2*beta*omega, omega**2 - beta**2)))
elif omegaStar / sqrt(2) <= beta and beta <= omegaStar:
	omega = sqrt(omegaStar**2 - beta**2)
	analyticalCoefficientOfRestitution = exp(-beta/omega * atan2(2*beta*omega, omega**2 - beta**2))
else:
	Omega = sqrt(beta**2 - omegaStar**2)
	analyticalCoefficientOfRestitution = exp(-beta/Omega * log((beta+Omega)/(beta-Omega)))

analyticalCoefficientOfRestitutionVector = [analyticalCoefficientOfRestitution] * len(timeIndex)

otherAnalyticalCoefficientOfRestitutionVector = [exp(-pi*effectiveNormalDissipativeConstant/(2*effectiveMass) / sqrt(effectiveElasticModulus/effectiveMass - (effectiveNormalDissipativeConstant/effectiveMass)**2))] * len(timeIndex)

outputPath = paths.getSimulationMainOutputFolder()

with open(os.path.join(outputPath, "coefficient_of_restitution.txt")) as coefficientOfRestitutionFile:
	coefficientOfRestitutionHistory = json.load(coefficientOfRestitutionFile)

coeffOfRestitutionTimeForPlot = []
coeffOfRestitutionHistoryForPlot = []
for j in coefficientOfRestitutionHistory:
	initialVelocity = j["velocities"][0]
	finalVelocity = j["velocities"][1]
	timeIndicesVector = list(range(j["timeIndices"][0], j["timeIndices"][1] + 1))
	coeffOfRestitutionTimeForPlot.append([x*timestep for x in timeIndicesVector])
	coeffOfRestitutionHistoryForPlot.append([- (finalVelocity + norm(gravity)*timestep) / initialVelocity] * len(timeIndicesVector))

# ########################### COEFFICIENT OF RESTITUTION

fig = plt.figure(
	figsize=(normalwidth, normalheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

ax.plot(
	timeInstant,
	analyticalCoefficientOfRestitutionVector,
	color = 'gray',
	label = 'Solução Analítica',
	# marker = '.',
	linewidth = normallinewidth
	)

ax.plot(
	timeInstant,
	otherAnalyticalCoefficientOfRestitutionVector,
	color = 'gray',
	label = 'Solução Analítica 2',
	# marker = '.',
	linewidth = normallinewidth
	)

print("Timestep: ", timestep)

for i in range(len(coeffOfRestitutionTimeForPlot)):
	ax.plot(
		coeffOfRestitutionTimeForPlot[i],
		coeffOfRestitutionHistoryForPlot[i],
		color = 'red',
		label = 'Simulação',
		marker = '.',
		linestyle="None",
		# linewidth = normallinewidth,
		markersize = normalmarkersize
		)

ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "coefficient_of_restitution"
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
ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel('Coeficiente de Restituição', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

# time = simulationOutputData.get()[3]
# timeIndex = list(time.keys())
# timeInstant = list(time.values())

# initialPosition = array(propertyValue["Position"][0])
# initialVelocity = array(propertyValue["Velocity"][0])
# gravity = array([0.0, -9.81, 0.0])

# instantaneousSolution = lambda t: initialPosition + initialVelocity * t + gravity * t**2 / 2
# instantaneousVelocitySolution = lambda t: initialVelocity + t*gravity
# instantaneousAccelerationSolution = lambda t: gravity
# solution = array([instantaneousSolution(t) for t in timeInstant])
# velocitySolution = array([instantaneousVelocitySolution(t) for t in timeInstant])
# accelerationSolution = array([instantaneousAccelerationSolution(t) for t in timeInstant])

# listDifference = lambda a, b: list(map(operator.sub, a, b))
# error = array( list(map(listDifference, propertyValue["Position"], solution)) )
# maxError = max([norm(x) for x in error])
# print("Maximum error: ", maxError)

# velocityError = array( list(map(listDifference, propertyValue["Velocity"], velocitySolution)) )
# # print("Velocity error: ", velocityError)
# # print("Instantaneous velocity solution: ", array(velocitySolution))
# # print("Instantaneous simulated velocity: ", array(propertyValue["Velocity"]))
# # print("Diff: ", array(velocitySolution) - array(propertyValue["Velocity"]))
# maxVelocityError = max([norm(x) for x in velocityError])
# print("Maximum velocity error: ", maxVelocityError)

# solution_x = list(map(list, zip(*solution)))[0]
# solution_y = list(map(list, zip(*solution)))[1]
# solution_z = list(map(list, zip(*solution)))[2]

# solution_vx = list(map(list, zip(*velocitySolution)))[0]
# solution_vy = list(map(list, zip(*velocitySolution)))[1]
# solution_vz = list(map(list, zip(*velocitySolution)))[2]

# solution_ax = list(map(list, zip(*accelerationSolution)))[0]
# solution_ay = list(map(list, zip(*accelerationSolution)))[1]
# solution_az = list(map(list, zip(*accelerationSolution)))[2]

# normalwidth = 7
# normalheight = 5
# smallwidth = 7 * 4/9
# smallheight = 5 * 4/9
# # smallsize = 4/9 * normalsize
# normalfontsize = 11
# smallfontsize = 9
# majorTickLabelSize = 10
# minorTickLabelSize = 10
# normalmarkersize = 3
# normallinewidth = 1
# family = 'serif'
# weight = 'light'

# ########################### Y POSITION

# fig = plt.figure(
# 	figsize=(normalwidth, normalheight),
# 	facecolor='w',
# 	edgecolor='k')

# ax = fig.add_subplot(111)

# ax.plot(
# 	timeInstant,
# 	solution_y,
# 	color = 'black',
# 	label = 'Solução Analítica',
# 	# marker = '.',
# 	linewidth = normallinewidth
# 	)

# ax.plot(
# 	timeInstant,
# 	propertyValue["Position - Y"],
# 	color = 'red',
# 	label = 'Simulação',
# 	marker = '.',
# 	linestyle="None",
# 	markersize = normalmarkersize
# 	)

# ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

# outputFolder = paths.getSimulationPlotsOutputFolder()
# filename = "y_position"
# extension = ".pdf"
# ax.set_xscale('linear')
# ax.set_yscale('linear')

# plt.xlim( min(timeInstant), max(timeInstant) )

# ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
# ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

# handles, labels = ax.get_legend_handles_labels()
# handle_list, label_list = [], []
# for handle, label in zip(handles, labels):
#     if label not in label_list:
#         handle_list.append(handle)
#         label_list.append(label)
# lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
# ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# ax.set_ylabel('Altura [m]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# plt.close(fig)

# ########################### X POSITION

# fig = plt.figure(
# 	figsize=(smallwidth, smallheight),
# 	facecolor='w',
# 	edgecolor='k')

# ax = fig.add_subplot(111)

# ax.plot(
# 	timeInstant,
# 	solution_x,
# 	color = 'black',
# 	label = 'Solução Analítica',
# 	# marker = '.',
# 	linewidth = normallinewidth
# 	)

# ax.plot(
# 	timeInstant,
# 	propertyValue["Position - X"],
# 	color = 'red',
# 	label = 'Simulação',
# 	marker = '.',
# 	linestyle="None",
# 	markersize = normalmarkersize
# 	)

# ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

# outputFolder = paths.getSimulationPlotsOutputFolder()
# filename = "x_position"
# extension = ".pdf"
# ax.set_xscale('linear')
# ax.set_yscale('linear')

# plt.xlim( min(timeInstant), max(timeInstant) )

# ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
# ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

# handles, labels = ax.get_legend_handles_labels()
# handle_list, label_list = [], []
# for handle, label in zip(handles, labels):
#     if label not in label_list:
#         handle_list.append(handle)
#         label_list.append(label)
# lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
# ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# ax.set_ylabel('Posição Horizontal [m]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# plt.close(fig)

# ########################### X VELOCITY

# fig = plt.figure(
# 	figsize=(smallwidth, smallheight),
# 	facecolor='w',
# 	edgecolor='k')

# ax = fig.add_subplot(111)

# ax.plot(
# 	timeInstant,
# 	solution_vx,
# 	color = 'black',
# 	label = 'Solução Analítica',
# 	# marker = '.',
# 	linewidth = normallinewidth
# 	)

# ax.plot(
# 	timeInstant,
# 	propertyValue["Velocity - X"],
# 	color = 'red',
# 	label = 'Simulação',
# 	marker = '.',
# 	linestyle="None",
# 	markersize = normalmarkersize
# 	)

# ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

# outputFolder = paths.getSimulationPlotsOutputFolder()
# filename = "x_velocity"
# extension = ".pdf"
# ax.set_xscale('linear')
# ax.set_yscale('linear')

# plt.xlim( min(timeInstant), max(timeInstant) )

# ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
# ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

# handles, labels = ax.get_legend_handles_labels()
# handle_list, label_list = [], []
# for handle, label in zip(handles, labels):
#     if label not in label_list:
#         handle_list.append(handle)
#         label_list.append(label)
# lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
# ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# ax.set_ylabel('Velocidade Horizontal [m/s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# plt.close(fig)

# ########################### Y VELOCITY

# fig = plt.figure(
# 	figsize=(smallwidth, smallheight),
# 	facecolor='w',
# 	edgecolor='k')

# ax = fig.add_subplot(111)

# ax.plot(
# 	timeInstant,
# 	solution_vy,
# 	color = 'black',
# 	label = 'Solução Analítica',
# 	# marker = '.',
# 	linewidth = normallinewidth
# 	)

# ax.plot(
# 	timeInstant,
# 	propertyValue["Velocity - Y"],
# 	color = 'red',
# 	label = 'Simulação',
# 	marker = '.',
# 	linestyle="None",
# 	markersize = normalmarkersize
# 	)

# ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

# outputFolder = paths.getSimulationPlotsOutputFolder()
# filename = "y_velocity"
# extension = ".pdf"
# ax.set_xscale('linear')
# ax.set_yscale('linear')

# plt.xlim( min(timeInstant), max(timeInstant) )

# ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
# ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

# handles, labels = ax.get_legend_handles_labels()
# handle_list, label_list = [], []
# for handle, label in zip(handles, labels):
#     if label not in label_list:
#         handle_list.append(handle)
#         label_list.append(label)
# lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
# ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# ax.set_ylabel('Velocidade Vertical [m/s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# plt.close(fig)

# ########################### Y ACCELERATION

# fig = plt.figure(
# 	figsize=(smallwidth, smallheight),
# 	facecolor='w',
# 	edgecolor='k')

# ax = fig.add_subplot(111)

# ax.plot(
# 	timeInstant,
# 	solution_ay,
# 	color = 'black',
# 	label = 'Solução Analítica',
# 	# marker = '.',
# 	linewidth = normallinewidth
# 	)

# ax.plot(
# 	timeInstant,
# 	propertyValue["Acceleration - Y"],
# 	color = 'red',
# 	label = 'Simulação',
# 	marker = '.',
# 	linestyle="None",
# 	markersize = normalmarkersize
# 	)

# ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

# outputFolder = paths.getSimulationPlotsOutputFolder()
# filename = "y_acceleration"
# extension = ".pdf"
# ax.set_xscale('linear')
# ax.set_yscale('linear')

# plt.xlim( min(timeInstant), max(timeInstant) )

# ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
# ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

# handles, labels = ax.get_legend_handles_labels()
# handle_list, label_list = [], []
# for handle, label in zip(handles, labels):
#     if label not in label_list:
#         handle_list.append(handle)
#         label_list.append(label)
# lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
# ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# ax.set_ylabel('Aceleração Vertical [m/s²]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# plt.close(fig)

# ########################### POSITION ERROR

# fig = plt.figure(
# 	figsize=(smallwidth, smallheight),
# 	facecolor='w',
# 	edgecolor='k')

# ax = fig.add_subplot(111)

# ax.plot(
# 	timeInstant,
# 	[norm(x) for x in error],
# 	color = 'red',
# 	label = 'Simulação',
# 	marker = '.',
# 	linestyle="None",
# 	markersize = normalmarkersize
# 	)

# ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

# outputFolder = paths.getSimulationPlotsOutputFolder()
# filename = "position_error"
# extension = ".pdf"
# ax.set_xscale('linear')
# ax.set_yscale('linear')

# plt.xlim( min(timeInstant), max(timeInstant) )

# ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
# ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

# # handles, labels = ax.get_legend_handles_labels()
# # handle_list, label_list = [], []
# # for handle, label in zip(handles, labels):
# #     if label not in label_list:
# #         handle_list.append(handle)
# #         label_list.append(label)
# # lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
# ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# ax.set_ylabel('Erro da Posição [m]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# ax.yaxis.set_major_formatter(mtick.ScalarFormatter(useMathText=True))
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# plt.close(fig)

# ########################### VELOCITY ERROR

# fig = plt.figure(
# 	figsize=(smallwidth, smallheight),
# 	facecolor='w',
# 	edgecolor='k')

# ax = fig.add_subplot(111)

# ax.plot(
# 	timeInstant,
# 	[norm(x) for x in velocityError],
# 	color = 'red',
# 	label = 'Simulação',
# 	marker = '.',
# 	linestyle="None",
# 	markersize = normalmarkersize
# 	)

# ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

# outputFolder = paths.getSimulationPlotsOutputFolder()
# filename = "velocity_error"
# extension = ".pdf"
# ax.set_xscale('linear')
# ax.set_yscale('linear')

# plt.xlim( min(timeInstant), max(timeInstant) )

# ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
# ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

# # handles, labels = ax.get_legend_handles_labels()
# # handle_list, label_list = [], []
# # for handle, label in zip(handles, labels):
# #     if label not in label_list:
# #         handle_list.append(handle)
# #         label_list.append(label)
# # lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
# ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# ax.set_ylabel('Erro da Velocidade [m/s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# ax.yaxis.set_major_formatter(mtick.ScalarFormatter(useMathText=True))
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# plt.close(fig)

# ########################### NORM OF HIGHER ORDER DERIVATIVES

# # plt.rc('text', usetex=True)
# # plt.rc('text.latex', preamble=r'\usepackage{amsmath}\usepackage{bm}\usepackage{xfrac}')

# # for i in range(2, propertyValue["TaylorOrder"][0]):
# # 	fig = plt.figure(
# # 		figsize=(smallwidth, smallheight),
# # 		facecolor='w',
# # 		edgecolor='k')

# # 	ax = fig.add_subplot(111)

# # 	derivative = i + 1
# # 	derivativeValue = [posDeriv[derivative] for posDeriv in propertyValue["PositionMatrix"]]
# # 	derivativeNorm = [norm(x) for x in derivativeValue]

# # 	unit = r"\left[\sfrac{\text{m}}{\text{s}^" + str(derivative) + r"}\right]"

# # 	if derivative == 3:
# # 		symbol = r"$\lVert\dddot{\bm{r}}\rVert" + unit + r"$"
# # 	else:
# # 		# symbol = r"$\lVert\bm{r}^{(" + str(derivative) + r")}\rVert$"
# # 		symbol = r"$\lVert\bm{r}^{(" + str(derivative) + r")}\rVert" + unit + r"$"

# # 	ax.plot(
# # 		timeInstant,
# # 		derivativeNorm,
# # 		color = 'red',
# # 		marker = '.',
# # 		linestyle="None",
# # 		markersize = normalmarkersize
# # 		)

# # 	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

# # 	outputFolder = paths.getSimulationPlotsOutputFolder()
# # 	filename = "position_derivative_" + str(derivative) + "_norm"
# # 	extension = ".pdf"
# # 	ax.set_xscale('linear')
# # 	ax.set_yscale('linear')

# # 	plt.xlim( min(timeInstant), max(timeInstant) )

# # 	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
# # 	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

# # 	# handles, labels = ax.get_legend_handles_labels()
# # 	# handle_list, label_list = [], []
# # 	# for handle, label in zip(handles, labels):
# # 	#     if label not in label_list:
# # 	#         handle_list.append(handle)
# # 	#         label_list.append(label)
# # 	# lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
# # 	ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# # 	ax.set_ylabel(symbol, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# # 	ax.yaxis.set_major_formatter(mtick.ScalarFormatter(useMathText=True))
# # 	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# # 	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
# # 	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# # 	plt.close(fig)


# ########################### MAXIMUM ERROR VERSUS TIMESTEP

# # with open(mainInputFilePath) as mainInputFile:
# # 	mainData = json.load(mainInputFile)

# # mainInputFilePath = "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/BouncingSphere/python/main.json"

# # null = None

# # maxError = []
# # Dt_vec = [2**(i/2)*1e-5 for i in range(20)]
# # outputs = 10
# # for i in range(len(Dt_vec)):
# # 	Dt = Dt_vec[i]
# # 	mainData["timeStep"] = Dt
# # 	# mainData["timeStepsForOutput"] = ceil((mainData["finalTime"] - mainData["initialTime"]) / (mainData["timeStep"] * outputs))
# # 	print("Dt = ", Dt)
# # 	print("timeStepsForOutput = ", mainData["timeStepsForOutput"])
# # 	with open(mainInputFilePath, 'w') as mainFile:
# # 		json.dump(mainData, mainFile)
# # 	userInput = PseudoUserInput(programPath, mainInputFilePath)
# # 	paths = PseudoPaths(userInput)
# # 	simulate = PseudoSimulate(userInput, paths)
# # 	simulate.execute()
# # 	simulationOutputData = PseudoSimulationOutputData(paths)
# # 	particleData = simulationOutputData.get()[1]
# # 	particle = particleData["SphericalParticle"]["Particle"]

# # 	propertyValue = {}
# # 	for propertyName, propertyHistory in particle.items():
# # 		propertyValue[propertyName] = list(propertyHistory.values())

# # 	time = simulationOutputData.get()[3]
# # 	timeIndex = list(time.keys())
# # 	timeInstant = list(time.values())

# # 	initialPosition = array(propertyValue["Position"][0])
# # 	initialVelocity = array(propertyValue["Velocity"][0])
# # 	gravity = array([0.0, -9.81, 0.0])

# # 	instantaneousSolution = lambda t: initialPosition + initialVelocity * t + gravity * t**2 / 2
# # 	solution = array([instantaneousSolution(t) for t in timeInstant])

# # 	listDifference = lambda a, b: list(map(operator.sub, a, b))
# # 	error = array( list(map(listDifference, propertyValue["Position"], solution)) )
# # 	maxError.append(max([norm(x) for x in error]))

# # fig = plt.figure(
# # 	figsize=(smallwidth, smallheight),
# # 	facecolor='w',
# # 	edgecolor='k')

# # ax = fig.add_subplot(111)

# # ax.plot(
# # 	Dt_vec,
# # 	maxError,
# # 	color = 'red',
# # 	label = 'Erro Máximo',
# # 	marker = '.',
# # 	linestyle="None",
# # 	markersize = normalmarkersize
# # 	)
	
# # outputFolder = paths.getSimulationPlotsOutputFolder()
# # filename = "maximum_error"
# # extension = ".pdf"

# # ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

# # ax.set_xscale('linear')
# # ax.set_yscale('linear')

# # ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
# # ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

# # handles, labels = ax.get_legend_handles_labels()
# # handle_list, label_list = [], []
# # for handle, label in zip(handles, labels):
# #     if label not in label_list:
# #         handle_list.append(handle)
# #         label_list.append(label)
# # lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': 'normal'})
# # ax.set_xlabel('Passo de Tempo [s]', fontdict={'size': normalfontsize, 'family': family})
# # ax.set_ylabel('Erro da Posição [m]', fontdict={'size': normalfontsize, 'family': family})
# # lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': 'normal'})

# # plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# # ax.set_xscale('log')
# # ax.set_yscale('linear')
# # filename = "maximum_error_logx"
# # plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# # ax.set_xscale('linear')
# # ax.set_yscale('log')
# # filename = "maximum_error_logy"
# # plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# # ax.set_xscale('log')
# # ax.set_yscale('log')
# # filename = "maximum_error_logx_logy"
# # plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# # plt.close(fig)