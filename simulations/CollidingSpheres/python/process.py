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

lpurple = [0.65, 0.12, 0.82]

programPath = "/home/ruancomelli/GitProjects/ParticleSimulator/build_sublime/bin/Release/psinApp"
mainInputFilePath = "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/CollidingSpheres/input/main.json"

userInput = PseudoUserInput(programPath, mainInputFilePath)
paths = PseudoPaths(userInput)
simulationOutputData = PseudoSimulationOutputData(paths)
simulate = PseudoSimulate(userInput, paths)

# simulate.execute()
plotCoefError = False

particleData = simulationOutputData.get()[1]
redParticle = particleData["SphericalParticle"]["Partícula Vermelha"]
blueParticle = particleData["SphericalParticle"]["Partícula Azul"]

redProperty = {}
for propertyName, propertyHistory in redParticle.items():
	redProperty[propertyName] = list(propertyHistory.values())

blueProperty = {}
for propertyName, propertyHistory in blueParticle.items():
	blueProperty[propertyName] = list(propertyHistory.values())

time = simulationOutputData.get()[3]
timeIndex = list(time.keys())
timeInstant = list(time.values())
timestep = (timeInstant[1] - timeInstant[0]) / (timeIndex[1] - timeIndex[0])

outputPath = paths.getSimulationMainOutputFolder()

with open(os.path.join(outputPath, "coefficient_of_restitution.txt")) as coefficientOfRestitutionFile:
	coefficientOfRestitutionHistory = json.load(coefficientOfRestitutionFile)

coeffOfRestitutionTimeForPlot = []
coeffOfRestitutionHistoryForPlot = []
for j in coefficientOfRestitutionHistory:
	initialVelocity = j["velocities"][0]
	finalVelocity = j["velocities"][1]
	timeIndicesVector = list(range(j["timeIndices"][0], j["timeIndices"][1] + 1))
	coeffOfRestitutionTimeForPlot.append([1000 * x*timestep for x in timeIndicesVector])
	coeffOfRestitutionHistoryForPlot.append([- finalVelocity / initialVelocity] * len(timeIndicesVector))

effectiveMass = resistanceRule(redProperty["Mass"][0], blueProperty["Mass"][0])
effectiveElasticModulus = resistanceRule(redProperty["ElasticModulus"][0], blueProperty["ElasticModulus"][0])
effectiveNormalDissipativeConstant = resistanceRule(redProperty["NormalDissipativeConstant"][0], blueProperty["NormalDissipativeConstant"][0])
omegaStar = sqrt(effectiveElasticModulus / effectiveMass)

beta = 0.5 * effectiveNormalDissipativeConstant / effectiveMass
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

propName = {}
propName["Position-X"] = "Posição Horizontal [m]"
propName["Position-Y"] = "Posição Vertical [m]"
propName["Acceleration-X"] = "Aceleração Horizontal [m/s²]"
propName["Acceleration-Y"] = "Aceleração Vertical [m/s²]"
propName["AngularAcceleration-Z"] = "Aceleração Angular [rad/s²]"
propName["AngularVelocity-Z"] = "Velocidade Angular [rad/s]"
propName["Velocity-X"] = "Velocidade Horizontal [m/s]"
propName["Velocity-Y"] = "Velocidade Vertical [m/s]"
propName["angularMomentum-Z"] = "Quantidade de Movimento\nAngular [kg m²/s]"
propName["contactForce-X"] = "Força de Contato Horizontal [N]"
propName["contactForce-Y"] = "Força de Contato Vertical [N]"
propName["kineticEnergy"] = "Enegia Cinética [J]"
propName["linearMomentum-X"] = "Quantidade de Movimento\nLinear Horizontal [kg m/s]"
propName["linearMomentum-Y"] = "Quantidade de Movimento\nLinear Vertical [kg m/s]"
propName["resultingForce-X"] = "Força Resultante Horizontal [N]"
propName["resultingForce-Y"] = "Força Resultante Vertical [N]"
propName["resultingTorque-Z"] = "Torque Resultante [N m]"
propName["rotationalEnergy"] = "Enegia Rotacional [J]"
propName["translationalEnergy"] = "Enegia Translacional [J]"

redParticleNormalLabel = "Partícula Vermelha"
blueParticleNormalLabel = "Partícula Azul"
redParticleSmallLabel = "Partícula\nVermelha"
blueParticleSmallLabel = "Partícula\nAzul"
timeInstantForPlot = [1000*t for t in timeInstant]
xLabel = "Tempo [ms]"

# ########################### ALMOST EVERYTHING
for prop in propName:
	print(prop)
	print("\t\t Normal size without total")
	# Normal size
	fig = plt.figure(
		figsize=(normalwidth, normalheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	if(len(timeInstant) > 100):
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleNormalLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleNormalLabel,
			linewidth = normallinewidth
			)
	else:
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleNormalLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleNormalLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = prop + "_normal"
	extension = ".pdf"
	ax.set_xscale('linear')
	ax.set_yscale('linear')

	plt.xlim( min(timeInstantForPlot), max(timeInstantForPlot) )

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
	ax.set_xlabel(xLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel(propName[prop], fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	# Small size
	print("\t\t Small size without total")
	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	if(len(timeInstantForPlot) > 100):
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleSmallLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleSmallLabel,
			linewidth = normallinewidth
			)
	else:
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleSmallLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleSmallLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = prop + "_small"
	extension = ".pdf"
	ax.set_xscale('linear')
	ax.set_yscale('linear')

	plt.xlim( min(timeInstantForPlot), max(timeInstantForPlot) )

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
	ax.set_xlabel(xLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel(propName[prop], fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	##################### With total
	print("\t\t Normal size with total")
	total = [x+y for x,y in zip(redProperty[prop], blueProperty[prop])]

	# Normal size
	fig = plt.figure(
		figsize=(normalwidth, normalheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	if(len(timeInstantForPlot) > 100):
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleNormalLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleNormalLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			total,
			color = 'black',
			label = 'Total',
			linewidth = normallinewidth
			)
	else:
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleNormalLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleNormalLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			total,
			color = 'black',
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = prop + "_normal_total"
	extension = ".pdf"
	ax.set_xscale('linear')
	ax.set_yscale('linear')

	plt.xlim( min(timeInstantForPlot), max(timeInstantForPlot) )

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
	ax.set_xlabel(xLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel(propName[prop], fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	# Small size
	print("\t\t Small size with total")
	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	if(len(timeInstantForPlot) > 100):
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleSmallLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleSmallLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			total,
			color = 'black',
			label = 'Total',
			linewidth = normallinewidth
			)
	else:
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleSmallLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleSmallLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			total,
			color = 'black',
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = prop + "_small_total"
	extension = ".pdf"
	ax.set_xscale('linear')
	ax.set_yscale('linear')

	plt.xlim( min(timeInstantForPlot), max(timeInstantForPlot) )

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
	ax.set_xlabel(xLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel(propName[prop], fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

# ########################### COEFFICIENT OF RESTITUTION
# Normal size
fig = plt.figure(
	figsize=(normalwidth, normalheight),
	facecolor='w',
	edgecolor='k')

ax = fig.add_subplot(111)

ax.plot(
	timeInstantForPlot,
	analyticalCoefficientOfRestitutionVector,
	color = 'black',
	label = 'Solução Analítica',
	# marker = '.',
	linewidth = normallinewidth
	)

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
filename = "coefficient_of_restitution_normal"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstantForPlot), max(timeInstantForPlot) )
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
ax.set_xlabel(xLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
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
	timeInstantForPlot,
	analyticalCoefficientOfRestitutionVector,
	color = 'black',
	label = 'Solução Analítica',
	# marker = '.',
	linewidth = normallinewidth
	)

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
filename = "coefficient_of_restitution_small"
extension = ".pdf"
ax.set_xscale('linear')
ax.set_yscale('linear')

plt.xlim( min(timeInstantForPlot), max(timeInstantForPlot) )
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
ax.set_xlabel(xLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
ax.set_ylabel('Coeficiente de Restituição', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

plt.close(fig)

#################################### Alternative energy and linear momentum plot

for prop in ["linearMomentum-X", "kineticEnergy", "translationalEnergy", "rotationalEnergy", "contactForce-Y", "AngularVelocity-Z", "angularMomentum-Z"]:
	print(prop)
	print("\t\t Normal size without total")
	# Normal size
	fig = plt.figure(
		figsize=(normalwidth, normalheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	if(len(timeInstant) > 100):
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleNormalLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleNormalLabel,
			linewidth = normallinewidth
			)
	else:
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleNormalLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleNormalLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = prop + "_normal_alternative"
	extension = ".pdf"
	ax.set_xscale('linear')
	ax.set_yscale('linear')

	plt.xlim( min(timeInstantForPlot), max(timeInstantForPlot) )

	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
	ax.ticklabel_format(useOffset=False)

	handles, labels = ax.get_legend_handles_labels()
	handle_list, label_list = [], []
	for handle, label in zip(handles, labels):
	    if label not in label_list:
	        handle_list.append(handle)
	        label_list.append(label)
	lgd = ax.legend(handle_list, label_list, loc='right', prop={'size': smallfontsize, 'family': family, 'weight': weight})
	lgd.get_frame().set_facecolor(llgray)
	lgd.get_frame().set_edgecolor(dgray)
	ax.set_xlabel(xLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel(propName[prop], fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	# Small size
	print("\t\t Small size without total")
	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	if(len(timeInstantForPlot) > 100):
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleSmallLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleSmallLabel,
			linewidth = normallinewidth
			)
	else:
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleSmallLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleSmallLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = prop + "_small_alternative"
	extension = ".pdf"
	ax.set_xscale('linear')
	ax.set_yscale('linear')

	plt.xlim( min(timeInstantForPlot), max(timeInstantForPlot) )

	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
	ax.ticklabel_format(useOffset=False)

	handles, labels = ax.get_legend_handles_labels()
	handle_list, label_list = [], []
	for handle, label in zip(handles, labels):
	    if label not in label_list:
	        handle_list.append(handle)
	        label_list.append(label)
	lgd = ax.legend(handle_list, label_list, loc='right', prop={'size': smallfontsize, 'family': family, 'weight': weight})
	lgd.get_frame().set_facecolor(llgray)
	lgd.get_frame().set_edgecolor(dgray)
	ax.set_xlabel(xLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel(propName[prop], fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	##################### With total
	print("\t\t Normal size with total")
	total = [x+y for x,y in zip(redProperty[prop], blueProperty[prop])]

	# Normal size
	fig = plt.figure(
		figsize=(normalwidth, normalheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	if(len(timeInstantForPlot) > 100):
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleNormalLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleNormalLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			total,
			color = 'black',
			label = 'Total',
			linewidth = normallinewidth
			)
	else:
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleNormalLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleNormalLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			total,
			color = 'black',
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = prop + "_normal_total_alternative"
	extension = ".pdf"
	ax.set_xscale('linear')
	ax.set_yscale('linear')

	plt.xlim( min(timeInstantForPlot), max(timeInstantForPlot) )

	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
	ax.ticklabel_format(useOffset=False)

	handles, labels = ax.get_legend_handles_labels()
	handle_list, label_list = [], []
	for handle, label in zip(handles, labels):
	    if label not in label_list:
	        handle_list.append(handle)
	        label_list.append(label)
	lgd = ax.legend(handle_list, label_list, loc='right', prop={'size': smallfontsize, 'family': family, 'weight': weight})
	lgd.get_frame().set_facecolor(llgray)
	lgd.get_frame().set_edgecolor(dgray)
	ax.set_xlabel(xLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel(propName[prop], fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	# Small size
	print("\t\t Small size with total")
	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	if(len(timeInstantForPlot) > 100):
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleSmallLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleSmallLabel,
			linewidth = normallinewidth
			)
		ax.plot(
			timeInstantForPlot,
			total,
			color = 'black',
			label = 'Total',
			linewidth = normallinewidth
			)
	else:
		ax.plot(
			timeInstantForPlot,
			redProperty[prop],
			color = 'red',
			label = redParticleSmallLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			blueProperty[prop],
			color = 'blue',
			label = blueParticleSmallLabel,
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)
		ax.plot(
			timeInstantForPlot,
			total,
			color = 'black',
			marker = '.',
			linestyle="None",
			markersize = normalmarkersize
			)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = prop + "_small_total_alternative"
	extension = ".pdf"
	ax.set_xscale('linear')
	ax.set_yscale('linear')

	plt.xlim( min(timeInstantForPlot), max(timeInstantForPlot) )

	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
	ax.ticklabel_format(useOffset=False)

	handles, labels = ax.get_legend_handles_labels()
	handle_list, label_list = [], []
	for handle, label in zip(handles, labels):
	    if label not in label_list:
	        handle_list.append(handle)
	        label_list.append(label)
	lgd = ax.legend(handle_list, label_list, loc='right', prop={'size': smallfontsize, 'family': family, 'weight': weight})
	lgd.get_frame().set_facecolor(llgray)
	lgd.get_frame().set_edgecolor(dgray)
	ax.set_xlabel(xLabel, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel(propName[prop], fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

# #################################### COEFFICIENT OF RESTITUTION ERROR
print("plotCoefError is ", plotCoefError)
if plotCoefError:
	with open(mainInputFilePath) as mainInputFile:
		mainData = json.load(mainInputFile)
	coefError = []
	Dt_vec = [2**(i/2)*1e-8 for i in range(21)]
	mainInputFilePathForRestitutionError = "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/CollidingSpheres/python/main.json"
	stepsForStoring = 100000000000
	for i in range(len(Dt_vec)):
		Dt = Dt_vec[i]
		mainData["TimeStep"] = Dt
		mainData["StepsForStoring"] = stepsForStoring
		print("Dt = ", Dt)
		print("stepsForStoring = ", mainData["StepsForStoring"])
		with open(mainInputFilePathForRestitutionError, 'w') as mainFile:
			json.dump(mainData, mainFile)
		userInput = PseudoUserInput(programPath, mainInputFilePathForRestitutionError)
		paths = PseudoPaths(userInput)
		simulate = PseudoSimulate(userInput, paths)
		simulate.execute()

		with open(os.path.join(outputPath, "coefficient_of_restitution.txt")) as coefficientOfRestitutionFile:
			coefficientOfRestitutionHistoryForError = json.load(coefficientOfRestitutionFile)

		coeffOfRestitutionList = []
		for j in coefficientOfRestitutionHistoryForError:
			initialVelocity = j["velocities"][0]
			finalVelocity = j["velocities"][1]
			coeffOfRestitutionList.append(- finalVelocity / initialVelocity)

		error = max([abs(coef - analyticalCoefficientOfRestitution) for coef in coeffOfRestitutionList])
		coefError.append(error)


	# Normal size
	fig = plt.figure(
		figsize=(normalwidth, normalheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	ax.plot(
		Dt_vec,
		coefError,
		color = lpurple,
		marker = '.',
		linestyle="None",
		markersize = normalmarkersize
		)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	extension = ".pdf"

	plt.xlim( min(Dt_vec), max(Dt_vec) )

	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
	ax.ticklabel_format(useOffset=False)
	ax.set_xlabel('Passo de Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel('Erro Máximo do Coeficiente de Restituição', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})

	ax.set_xscale('linear')
	ax.set_yscale('linear')
	filename = "coefficient_of_restitution_error_linear_normal"

	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	ax.set_xscale('log')
	ax.set_yscale('linear')
	filename = "coefficient_of_restitution_error_logx_normal"
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	ax.set_xscale('linear')
	ax.set_yscale('log')
	filename = "coefficient_of_restitution_error_logy_normal"
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	ax.set_xscale('log')
	ax.set_yscale('log')
	filename = "coefficient_of_restitution_error_loglog_normal"
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	# Small size
	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	ax.plot(
		Dt_vec,
		coefError,
		color = lpurple,
		marker = '.',
		linestyle="None",
		markersize = normalmarkersize
		)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	extension = ".pdf"

	plt.xlim( min(Dt_vec), max(Dt_vec) )

	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
	ax.ticklabel_format(useOffset=False)
	ax.set_xlabel('Passo de Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel('Erro Máximo do\nCoeficiente de Restituição', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})

	ax.set_xscale('linear')
	ax.set_yscale('linear')
	filename = "coefficient_of_restitution_error_linear_small"

	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	ax.set_xscale('log')
	ax.set_yscale('linear')
	filename = "coefficient_of_restitution_error_logx_small"
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	ax.set_xscale('linear')
	ax.set_yscale('log')
	filename = "coefficient_of_restitution_error_logy_small"
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	ax.set_xscale('log')
	ax.set_yscale('log')
	filename = "coefficient_of_restitution_error_loglog_small"
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")


# ####################################
redKineticEnergy = redProperty["kineticEnergy"]
blueKineticEnergy = blueProperty["kineticEnergy"]
totalKineticEnergy = redKineticEnergy + blueKineticEnergy
print("Initial total kinetic energy: ", totalKineticEnergy[0], "J")
print("Final total kinetic energy: ", totalKineticEnergy[-1], "J")
print("Diff: ", totalKineticEnergy[0] - totalKineticEnergy[-1], "J")
print("Coefficient of restitution: ", coeffOfRestitutionHistoryForPlot[0][0])
print("Analytical coefficient of restitution: ", analyticalCoefficientOfRestitution)
print("Diff: ", analyticalCoefficientOfRestitution - coeffOfRestitutionHistoryForPlot[0][0])