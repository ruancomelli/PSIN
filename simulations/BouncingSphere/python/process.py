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

def resistanceRule(a, b):
	if b==0:
		return a
	elif a==0:
		return b
	else:
		return a*b/(a+b)

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
dred = [0.5, 0.1, 0.1]

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
timestep = (timeInstant[1] - timeInstant[0]) / (timeIndex[1] - timeIndex[0])

particle = particleData["SphericalParticle"]["Particle"]
wall = boundaryData["FixedInfinitePlane"]["Wall"]
gravity = array(boundaryData["GravityField"]["Gravity"]["Gravity"][0])

particlePropertyValue = {}
for propertyName, propertyHistory in particle.items():
	particlePropertyValue[propertyName] = list(propertyHistory.values())

wallPropertyValue = {}
for propertyName, propertyHistory in particle.items():
	wallPropertyValue[propertyName] = list(propertyHistory.values())

particlePosition = [array(x) for x in particlePropertyValue["Position"]]
particleMass = particlePropertyValue["Mass"][0]
particleHeight = [position[1] for position in particlePropertyValue["Position"]]
particleContactForceY = particlePropertyValue["contactForce - Y"]

effectiveMass = particleMass
effectiveElasticModulus = resistanceRule(particlePropertyValue["ElasticModulus"][0], wallPropertyValue["ElasticModulus"][0])
effectiveNormalDissipativeConstant = resistanceRule(particlePropertyValue["NormalDissipativeConstant"][0], wallPropertyValue["NormalDissipativeConstant"][0])
omegaStar = sqrt(effectiveElasticModulus / effectiveMass)
beta = 0.5 * effectiveNormalDissipativeConstant / effectiveMass

if beta < omegaStar / sqrt(2):
	omega = sqrt(omegaStar**2 - beta**2)
	limitedAnalyticalCoefficientOfRestitution = exp(-beta/omega * (pi - atan2(2*beta*omega, omega**2 - beta**2)))
elif omegaStar / sqrt(2) <= beta and beta <= omegaStar:
	omega = sqrt(omegaStar**2 - beta**2)
	limitedAnalyticalCoefficientOfRestitution = exp(-beta/omega * atan2(2*beta*omega, omega**2 - beta**2))
else:
	Omega = sqrt(beta**2 - omegaStar**2)
	limitedAnalyticalCoefficientOfRestitution = exp(-beta/Omega * log((beta+Omega)/(beta-Omega)))

limitedAnalyticalCoefficientOfRestitutionVector = [limitedAnalyticalCoefficientOfRestitution] * len(timeIndex)

# nonlimitedAnalyticalCoefficientOfRestitution = exp(-pi*effectiveNormalDissipativeConstant/(2*effectiveMass) / sqrt(effectiveElasticModulus/effectiveMass - (effectiveNormalDissipativeConstant/effectiveMass)**2))
# nonlimitedAnalyticalCoefficientOfRestitutionVector = [nonlimitedAnalyticalCoefficientOfRestitution] * len(timeIndex)

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

potentialEnergy = [particleMass * norm(gravity) * h for h in particleHeight]
kineticEnergy = particlePropertyValue["kineticEnergy"]
mechanicalEnergy = [p + k for p, k in zip(potentialEnergy, kineticEnergy)]
# elasticEnergy = [0] + [f*dr[1] for f,dx in zip(particleContactForceY[1:], consecute_diff(particlePosition))]
# mechanicalEnergy = [p + k + e for p, k, e in zip(potentialEnergy, kineticEnergy, elasticEnergy)]

# ########################### COEFFICIENT OF RESTITUTION
# Normal size
fig = plt.figure(
	figsize=(normalwidth, normalheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

ax.plot(
	timeInstant,
	limitedAnalyticalCoefficientOfRestitutionVector,
	color = 'black',
	label = 'Solução Analítica',
	# marker = '.',
	linewidth = normallinewidth
	)

# ax.plot(
# 	timeInstant,
# 	nonlimitedAnalyticalCoefficientOfRestitutionVector,
# 	color = dgray,
# 	label = 'Solução Analítica sem Limitação',
# 	# marker = '.',
# 	linewidth = normallinewidth
# 	)

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
plt.ylim( ymin=0, ymax=1.2 )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
ax.ticklabel_format(useOffset=False)

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
ax.set_ylabel('Coeficiente de Restituição', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

# Small size
fig = plt.figure(
	figsize=(smallwidth, smallheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

ax.plot(
	timeInstant,
	limitedAnalyticalCoefficientOfRestitutionVector,
	color = 'black',
	label = 'Solução Analítica',
	# marker = '.',
	linewidth = normallinewidth
	)

# ax.plot(
# 	timeInstant,
# 	nonlimitedAnalyticalCoefficientOfRestitutionVector,
# 	color = dgray,
# 	label = 'Solução Analítica sem Limitação',
# 	# marker = '.',
# 	linewidth = normallinewidth
# 	)

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
filename = "small_coefficient_of_restitution"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )
plt.ylim( ymin=0, ymax=1.2 )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
ax.ticklabel_format(useOffset=False)

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
ax.set_ylabel('Coeficiente de Restituição', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

# # ########################### COEFFICIENT OF RESTITUTION ERROR
# # Normal size
# fig = plt.figure(
# 	figsize=(normalwidth, normalheight),
# 	facecolor='w',
# 	edgecolor='k')

# ax = fig.add_subplot(111)

# ax.plot(
# 	timeInstant,
# 	limitedAnalyticalCoefficientOfRestitutionVector,
# 	color = dred,
# 	label = 'Solução Analítica com Limitação',
# 	# marker = '.',
# 	linewidth = normallinewidth
# 	)

# # ax.plot(
# # 	timeInstant,
# # 	nonlimitedAnalyticalCoefficientOfRestitutionVector,
# # 	color = dgray,
# # 	label = 'Solução Analítica sem Limitação',
# # 	# marker = '.',
# # 	linewidth = normallinewidth
# # 	)

# for i in range(len(coeffOfRestitutionTimeForPlot)):
# 	ax.plot(
# 		coeffOfRestitutionTimeForPlot[i],
# 		coeffOfRestitutionHistoryForPlot[i],
# 		color = 'red',
# 		label = 'Simulação',
# 		marker = '.',
# 		linestyle="None",
# 		# linewidth = normallinewidth,
# 		markersize = normalmarkersize
# 		)

# ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

# outputFolder = paths.getSimulationPlotsOutputFolder()
# filename = "coefficient_of_restitution"
# extension = ".pdf"
# ax.set_xscale('linear')
# ax.set_yscale('linear')

# plt.xlim( min(timeInstant), max(timeInstant) )

# ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
# ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
# ax.ticklabel_format(useOffset=False)

# handles, labels = ax.get_legend_handles_labels()
# handle_list, label_list = [], []
# for handle, label in zip(handles, labels):
#     if label not in label_list:
#         handle_list.append(handle)
#         label_list.append(label)
# lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
# lgd.get_frame().set_facecolor(llgray)
# lgd.get_frame().set_edgecolor(dgray)
# ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# ax.set_ylabel('Coeficiente de Restituição', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# plt.close(fig)

# # Small size
# fig = plt.figure(
# 	figsize=(smallwidth, smallheight),
# 	facecolor='w',
# 	edgecolor='k')

# ax = fig.add_subplot(111)

# ax.plot(
# 	timeInstant,
# 	limitedAnalyticalCoefficientOfRestitutionVector,
# 	color = dred,
# 	label = 'Solução Analítica com Limitação',
# 	# marker = '.',
# 	linewidth = normallinewidth
# 	)

# ax.plot(
# 	timeInstant,
# 	nonlimitedAnalyticalCoefficientOfRestitutionVector,
# 	color = dgray,
# 	label = 'Solução Analítica sem Limitação',
# 	# marker = '.',
# 	linewidth = normallinewidth
# 	)

# for i in range(len(coeffOfRestitutionTimeForPlot)):
# 	ax.plot(
# 		coeffOfRestitutionTimeForPlot[i],
# 		coeffOfRestitutionHistoryForPlot[i],
# 		color = 'red',
# 		label = 'Simulação',
# 		marker = '.',
# 		linestyle="None",
# 		# linewidth = normallinewidth,
# 		markersize = normalmarkersize
# 		)

# ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

# outputFolder = paths.getSimulationPlotsOutputFolder()
# filename = "small_coefficient_of_restitution"
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
# lgd.get_frame().set_facecolor(llgray)
# lgd.get_frame().set_edgecolor(dgray)
# ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# ax.set_ylabel('Coeficiente de Restituição', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
# plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

# plt.close(fig)

# ########################### KINETIC ENERGY

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
filename = "kinetic_energy"
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
filename = "mechanical_energy"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
lgd.get_frame().set_facecolor(llgray)
lgd.get_frame().set_edgecolor(dgray)
ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel('Energia mecânica da partícula [J]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

# ########################### Y POSITION
# Normal size
fig = plt.figure(
	figsize=(normalwidth, normalheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

if len(timeInstant) > 100:
	ax.plot(
		timeInstant,
		particleHeight,
		color = 'red',
		label = 'Simulação',
		linewidth = normallinewidth
		)
else:
	ax.plot(
		timeInstant,
		particleHeight,
		color = 'red',
		label = 'Simulação',
		marker = '.',
		linestyle="None",
		markersize = normalmarkersize
		)

ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "y_position"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel('Altura [m]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

# Small size
fig = plt.figure(
	figsize=(smallwidth, smallheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

if len(timeInstant) > 100:
	ax.plot(
		timeInstant,
		particleHeight,
		color = 'red',
		label = 'Simulação',
		linewidth = normallinewidth
		)
else:
	ax.plot(
		timeInstant,
		particleHeight,
		color = 'red',
		label = 'Simulação',
		marker = '.',
		linestyle="None",
		markersize = normalmarkersize
		)

ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

outputFolder = paths.getSimulationPlotsOutputFolder()
filename = "small_y_position"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstant), max(timeInstant) )

ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel('Altura [m]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

print("Initial mechanical energy: ", mechanicalEnergy[0])
print("Final mechanical energy: ", mechanicalEnergy[-1])
print("Diff mechanical energy: ", abs(mechanicalEnergy[-1] - mechanicalEnergy[0]))
coeffDiff = [x - limitedAnalyticalCoefficientOfRestitution for y in coeffOfRestitutionHistoryForPlot for x in y]
print("Erro máximo do coeficiente de restituição: ", max([abs(cDiff) for cDiff in coeffDiff]))