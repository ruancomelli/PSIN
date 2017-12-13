import sys

sys.path.insert(0, '/home/ruancomelli/GitProjects/ParticleSimulator/Python/Pseudo')

from PseudoInterface import *

import operator
import numpy as np
from numpy import array
from numpy.linalg import norm
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
from math import ceil
from matplotlib import animation
from math import floor
from numpy import log10
from matplotlib.lines import Line2D

generateVideo = True
executeSimulation = False
plotData = False
animationTime = 1.2

def consecute_diff(x):
	return [j-i for i, j in zip(x[:-1], x[1:])]

programPath = "/home/ruancomelli/GitProjects/ParticleSimulator/build_sublime/bin/Release/psinApp"
mainInputFilePath = "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/FallingSphere/input/main.json"

userInput = PseudoUserInput(programPath, mainInputFilePath)
paths = PseudoPaths(userInput)
simulationOutputData = PseudoSimulationOutputData(paths)
simulate = PseudoSimulate(userInput, paths)

if executeSimulation:
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
instantaneousVelocitySolution = lambda t: initialVelocity + t*gravity
instantaneousAccelerationSolution = lambda t: gravity
solution = array([instantaneousSolution(t) for t in timeInstant])
velocitySolution = array([instantaneousVelocitySolution(t) for t in timeInstant])
accelerationSolution = array([instantaneousAccelerationSolution(t) for t in timeInstant])

listDifference = lambda a, b: list(map(operator.sub, a, b))
error = array( list(map(listDifference, propertyValue["Position"], solution)) )
maxError = max([norm(x) for x in error])
print("Maximum error: ", maxError)

velocityError = array( list(map(listDifference, propertyValue["Velocity"], velocitySolution)) )
# print("Velocity error: ", velocityError)
# print("Instantaneous velocity solution: ", array(velocitySolution))
# print("Instantaneous simulated velocity: ", array(propertyValue["Velocity"]))
# print("Diff: ", array(velocitySolution) - array(propertyValue["Velocity"]))
maxVelocityError = max([norm(x) for x in velocityError])
print("Maximum velocity error: ", maxVelocityError)

solution_x = list(map(list, zip(*solution)))[0]
solution_y = list(map(list, zip(*solution)))[1]
solution_z = list(map(list, zip(*solution)))[2]

solution_vx = list(map(list, zip(*velocitySolution)))[0]
solution_vy = list(map(list, zip(*velocitySolution)))[1]
solution_vz = list(map(list, zip(*velocitySolution)))[2]

solution_ax = list(map(list, zip(*accelerationSolution)))[0]
solution_ay = list(map(list, zip(*accelerationSolution)))[1]
solution_az = list(map(list, zip(*accelerationSolution)))[2]

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

potentialEnergy = [propertyValue["Mass"][0] * norm(gravity) * h for h in propertyValue["Position-Y"]]
kineticEnergy = propertyValue["kineticEnergy"]
mechanicalEnergy = [p + k for p, k in zip(potentialEnergy, kineticEnergy)]

if plotData:
	########################### Y POSITION

	fig = plt.figure(
		figsize=(normalwidth, normalheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	ax.plot(
		timeInstant,
		solution_y,
		color = 'black',
		label = 'Solução Analítica',
		# marker = '.',
		linewidth = normallinewidth
		)

	ax.plot(
		timeInstant,
		propertyValue["Position-Y"],
		color = 'red',
		label = 'Simulação',
		marker = '.',
		linestyle="None",
		markersize = normalmarkersize
		)

	ax.grid(visible=True , which='major' , color=lgray)

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = "y_position"
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
	ax.set_ylabel('Altura [m]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	########################### X POSITION

	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	ax.plot(
		timeInstant,
		solution_x,
		color = 'black',
		label = 'Solução Analítica',
		# marker = '.',
		linewidth = normallinewidth
		)

	ax.plot(
		timeInstant,
		propertyValue["Position - X"],
		color = 'red',
		label = 'Simulação',
		marker = '.',
		linestyle="None",
		markersize = normalmarkersize
		)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = "x_position"
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
	ax.set_ylabel('Posição Horizontal [m]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	########################### X VELOCITY

	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	ax.plot(
		timeInstant,
		solution_vx,
		color = 'black',
		label = 'Solução Analítica',
		# marker = '.',
		linewidth = normallinewidth
		)

	ax.plot(
		timeInstant,
		propertyValue["Velocity - X"],
		color = 'red',
		label = 'Simulação',
		marker = '.',
		linestyle="None",
		markersize = normalmarkersize
		)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = "x_velocity"
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
	ax.set_ylabel('Velocidade Horizontal [m/s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	########################### Y VELOCITY

	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	ax.plot(
		timeInstant,
		solution_vy,
		color = 'black',
		label = 'Solução Analítica',
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
	filename = "y_velocity"
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
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	########################### Y ACCELERATION

	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	ax.plot(
		timeInstant,
		solution_ay,
		color = 'black',
		label = 'Solução Analítica',
		# marker = '.',
		linewidth = normallinewidth
		)

	ax.plot(
		timeInstant,
		propertyValue["Acceleration - Y"],
		color = 'red',
		label = 'Simulação',
		marker = '.',
		linestyle="None",
		markersize = normalmarkersize
		)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = "y_acceleration"
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
	ax.set_ylabel('Aceleração Vertical [m/s²]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	########################### POSITION ERROR

	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	ax.plot(
		timeInstant,
		[norm(x) for x in error],
		color = 'red',
		label = 'Simulação',
		marker = '.',
		linestyle="None",
		markersize = normalmarkersize
		)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = "position_error"
	extension = ".pdf"
	ax.set_xscale('linear')
	ax.set_yscale('linear')

	plt.xlim( min(timeInstant), max(timeInstant) )

	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

	# handles, labels = ax.get_legend_handles_labels()
	# handle_list, label_list = [], []
	# for handle, label in zip(handles, labels):
	#     if label not in label_list:
	#         handle_list.append(handle)
	#         label_list.append(label)
	# lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
	ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel('Erro da Posição [m]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.yaxis.set_major_formatter(mtick.ScalarFormatter(useMathText=True))
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	########################### VELOCITY ERROR

	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	ax.plot(
		timeInstant,
		[norm(x) for x in velocityError],
		color = 'red',
		label = 'Simulação',
		marker = '.',
		linestyle="None",
		markersize = normalmarkersize
		)

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = "velocity_error"
	extension = ".pdf"
	ax.set_xscale('linear')
	ax.set_yscale('linear')

	plt.xlim( min(timeInstant), max(timeInstant) )

	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

	# handles, labels = ax.get_legend_handles_labels()
	# handle_list, label_list = [], []
	# for handle, label in zip(handles, labels):
	#     if label not in label_list:
	#         handle_list.append(handle)
	#         label_list.append(label)
	# lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
	ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel('Erro da Velocidade [m/s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.yaxis.set_major_formatter(mtick.ScalarFormatter(useMathText=True))
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	########################### NORM OF HIGHER ORDER DERIVATIVES

	# plt.rc('text', usetex=True)
	# plt.rc('text.latex', preamble=r'\usepackage{amsmath}\usepackage{bm}\usepackage{xfrac}')

	# for i in range(2, propertyValue["TaylorOrder"][0]):
	# 	fig = plt.figure(
	# 		figsize=(smallwidth, smallheight),
	# 		facecolor='w',
	# 		edgecolor='k')

	# 	ax = fig.add_subplot(111)

	# 	derivative = i + 1
	# 	derivativeValue = [posDeriv[derivative] for posDeriv in propertyValue["PositionMatrix"]]
	# 	derivativeNorm = [norm(x) for x in derivativeValue]

	# 	unit = r"\left[\sfrac{\text{m}}{\text{s}^" + str(derivative) + r"}\right]"

	# 	if derivative == 3:
	# 		symbol = r"$\lVert\dddot{\bm{r}}\rVert" + unit + r"$"
	# 	else:
	# 		# symbol = r"$\lVert\bm{r}^{(" + str(derivative) + r")}\rVert$"
	# 		symbol = r"$\lVert\bm{r}^{(" + str(derivative) + r")}\rVert" + unit + r"$"

	# 	ax.plot(
	# 		timeInstant,
	# 		derivativeNorm,
	# 		color = 'red',
	# 		marker = '.',
	# 		linestyle="None",
	# 		markersize = normalmarkersize
	# 		)

	# 	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	# 	outputFolder = paths.getSimulationPlotsOutputFolder()
	# 	filename = "position_derivative_" + str(derivative) + "_norm"
	# 	extension = ".pdf"
	# 	ax.set_xscale('linear')
	# 	ax.set_yscale('linear')

	# 	plt.xlim( min(timeInstant), max(timeInstant) )

	# 	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
	# 	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

	# 	# handles, labels = ax.get_legend_handles_labels()
	# 	# handle_list, label_list = [], []
	# 	# for handle, label in zip(handles, labels):
	# 	#     if label not in label_list:
	# 	#         handle_list.append(handle)
	# 	#         label_list.append(label)
	# 	# lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': weight})
	# 	ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	# 	ax.set_ylabel(symbol, fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	# 	ax.yaxis.set_major_formatter(mtick.ScalarFormatter(useMathText=True))
	# 	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	# 	# lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': weight})
	# 	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	# 	plt.close(fig)


	########################### MAXIMUM ERROR VERSUS TIMESTEP

	with open(mainInputFilePath) as mainInputFile:
		mainData = json.load(mainInputFile)

	mainInputFilePath = "/home/ruancomelli/GitProjects/ParticleSimulator/simulations/FallingSphere/python/main.json"

	maxError = []
	Dt_vec = [2**(i/2)*1e-5 for i in range(20)]
	timeVector = []
	positionMtx = []
	marginalErrorVec = []
	initialError = []
	outputs = 10
	for i in range(len(Dt_vec)):
		Dt = Dt_vec[i]
		mainData["TimeStep"] = Dt
		mainData["StepsForStoring"] = ceil((mainData["FinalInstant"] - mainData["InitialInstant"]) / (mainData["TimeStep"] * outputs))
		print("Dt = ", Dt)
		print("stepsForStoring = ", mainData["StepsForStoring"])
		with open(mainInputFilePath, 'w') as mainFile:
			json.dump(mainData, mainFile)
		userInput = PseudoUserInput(programPath, mainInputFilePath)
		paths = PseudoPaths(userInput)
		simulate = PseudoSimulate(userInput, paths)
		simulate.execute()
		simulationOutputData = PseudoSimulationOutputData(paths)
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
		maxError.append(max([norm(x) for x in error]))

		positionMtx.append(propertyValue["Position"])
		# marginalErrorVec.append([norm(x) for x in consecute_diff(array(propertyValue["Position"]))])
		initialError.append(norm(error[0]))
		timeVector.append(timeInstant)


	fig = plt.figure(
		figsize=(smallwidth, smallheight),
		facecolor='w',
		edgecolor='k')

	ax = fig.add_subplot(111)

	ax.plot(
		Dt_vec,
		maxError,
		color = 'red',
		label = 'Erro Máximo',
		marker = '.',
		linestyle="None",
		markersize = normalmarkersize
		)
		
	outputFolder = paths.getSimulationPlotsOutputFolder()
	filename = "maximum_error"
	extension = ".pdf"

	ax.grid(visible=True , which='major' , color=[0.8 , 0.8 , 0.8])

	ax.set_xscale('linear')
	ax.set_yscale('linear')

	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)

	handles, labels = ax.get_legend_handles_labels()
	handle_list, label_list = [], []
	for handle, label in zip(handles, labels):
	    if label not in label_list:
	        handle_list.append(handle)
	        label_list.append(label)
	lgd = ax.legend(handle_list, label_list, loc='best', prop={'size': smallfontsize, 'family': family, 'weight': 'normal'})
	ax.set_xlabel('Passo de Tempo [s]', fontdict={'size': normalfontsize, 'family': family})
	ax.set_ylabel('Erro Máximo da Posição [m]', fontdict={'size': normalfontsize, 'family': family})
	lgd.set_title("Legenda", prop={'size': normalfontsize, 'family': family, 'weight': 'normal'})

	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	ax.set_xscale('log')
	ax.set_yscale('linear')
	filename = "maximum_error_logx"
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	ax.set_xscale('linear')
	ax.set_yscale('log')
	filename = "maximum_error_logy"
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	ax.set_xscale('log')
	ax.set_yscale('log')
	filename = "maximum_error_logx_logy"
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

	########################### LINEAR REGRESSION
	print('Coefficients: ', np.polyfit(np.log(Dt_vec), np.log(maxError), 1))

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

	ax.tick_params(axis='both', which='major', labelsize=majorTickLabelSize)
	ax.tick_params(axis='both', which='minor', labelsize=minorTickLabelSize)
	lgd.get_frame().set_facecolor(llgray)
	lgd.get_frame().set_edgecolor(dgray)
	ax.set_xlabel('Tempo [s]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	ax.set_ylabel('Energia mecânica da partícula [J]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
	plt.savefig(os.path.join(outputFolder, filename + extension), bbox_inches = "tight")

	plt.close(fig)

if generateVideo:
	def intersect_with_xy(normalVector, origin):
		xy_normal_versor = [0, 0, 1]

		a = normalVector[0]
		b = normalVector[1]
		c = normalVector[2]
		d = np.dot(normalVector, origin)

		director = list(np.cross(normalVector, xy_normal_versor))
		director = director[0:2]

		if a != 0:
			point = [d/a, 0]
		else:
			point = [0, d/b]

		line = (director, point)

		return line

	def isInside(point, limits):
		(xmin, xmax, ymin, ymax) = limits
		(x, y) = point

		return xmin <= x and x <= xmax and ymin <= y and y <= ymax

	def getExtremes(line, limits):
		(xmin, xmax, ymin, ymax) = limits

		begin = (0, 0)
		end = (0, 0)

		(director, point) = line

		u = director[0]
		v = director[1]

		x = point[0]
		y = point[1]

		if u == 0:
			begin = (x, ymin)
			end = (x, ymax)

			return (isInside(begin, limits) and isInside(end, limits), begin, end)
		elif v == 0:
			begin = (xmin, y)
			end = (xmax, y)

			return (isInside(begin, limits) and isInside(end, limits), begin, end)

		a = v/u
		b = y - v*x/u
		# y = a*x + b

		xmin_intersect = (xmin, a*xmin + b)
		xmax_intersect = (xmax, a*xmax + b)
		ymin_intersect = ((ymin-b)/a, ymin)
		ymax_intersect = ((ymax-b)/a, ymax)

		if isInside(xmin_intersect, limits):
			begin = xmin_intersect

			if isInside(xmax_intersect, limits):
				end = xmax_intersect
				return (True, begin, end)

			if isInside(ymin_intersect, limits):
				end = ymin_intersect
				return (True, begin, end)

			if isInside(ymax_intersect, limits):
				end = ymax_intersect
				return (True, begin, end)

		elif isInside(xmax_intersect, limits):
			begin = xmax_intersect

			if isInside(ymin_intersect, limits):
				end = ymin_intersect
				return (True, begin, end)

			if isInside(ymax_intersect, limits):
				end = ymax_intersect
				return (True, begin, end)

		elif isInside(ymin_intersect, limits):
			begin = ymin_intersect

			if isInside(ymax_intersect, limits):
				end = ymax_intersect
				return (True, begin, end)

		else:
			return (False, begin, end)

	def getIntersectPoints(normalVector, origin, limits):
		line = intersect_with_xy(normalVector, origin)
		return getExtremes(line, limits)
	def setSquare(xmin , xmax , ymin , ymax):
		xWidth = xmax - xmin
		middleX = (xmax + xmin) / 2

		yWidth = ymax - ymin
		middleY = (ymax + ymin) / 2

		width = max( xWidth , yWidth )
		
		xmin = middleX - width/2
		xmax = middleX + width/2
		
		ymin = middleY - width/2
		ymax = middleY + width/2
		
		return [ xmin , xmax , ymin , ymax ]

	def getColor(color):
		if color[1] == "":
			return (color[0][0], color[0][1], color[0][2])
		else:
			return color[1]

	def getLimits_global( particleData ):
		#Set limits

		X = 0
		Y = 1
		Z = 2

		xmin = min([
				min([
					position[X] - radius
					for position in particle["Position"].values()
					for radius in particle["Radius"].values()
					])
				for particle in particleData["SphericalParticle"].values()
			])

		xmax = max([
				max([
					position[X] + radius
					for position in particle["Position"].values()
					for radius in particle["Radius"].values()
					])
				for particle in particleData["SphericalParticle"].values()
			])

		ymin = min([
				min([
					position[Y] - radius
					for position in particle["Position"].values()
					for radius in particle["Radius"].values()
					])
				for particle in particleData["SphericalParticle"].values()
			])

		ymax = max([
				max([
					position[Y] + radius
					for position in particle["Position"].values()
					for radius in particle["Radius"].values()
					])
				for particle in particleData["SphericalParticle"].values()
			])
		
		[ xmin , xmax , ymin , ymax ] = setSquare(xmin , xmax , ymin , ymax)

		return [ xmin , xmax , ymin , ymax ]

	def build( simulationOutputData , paths , animationTime ):

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
		ax.grid(visible=False)

		# Set axes limits
		ax.autoscale(enable=True , axis='both')
		ax.set_xlabel('Posição Horizontal [m]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})
		ax.set_ylabel('Altura [m]', fontdict={'size': normalfontsize, 'family': family, 'weight': weight})

		# Time indices
		timeIndices = list(time.keys())[::2]
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
				circles[particleName] = plt.Circle( (xCenter , yCenter), radius , fill=True, facecolor='white', edgecolor=color, linewidth=3 )

		limits = getLimits_global( particleData )
		lines = {}
		if "FixedInfinitePlane" in boundaryData:
			for boundaryName, boundary in boundaryData["FixedInfinitePlane"].items():
				t = beginning
				X = 0
				Y = 1
				normalVersor = list(boundary["NormalVersor"][t])
				origin = list(boundary["Origin"][t])
				color = getColor(boundary["Color"][t])
				(boolReturn, begin, end) = getIntersectPoints(normalVersor, origin, limits)
				if boolReturn:
					(xbeg, ybeg) = begin
					(xend, yend) = end
					lines[boundaryName] = Line2D([xbeg, xend], [ybeg, yend], color=color)

		round_to_n = lambda x, n: round(x, -int(floor(log10(x))) + (n - 1)) if x != 0 else 0

		### Initial function to animation ###
		def init():
			ax.set_title(str(time[0]) + " s")
			# circles = {}
			if "SphericalParticle" in particleData:
				for name, particle in particleData["SphericalParticle"].items():
					t = beginning
					X = 0
					Y = 1
					xCenter = float(particle["Position"][t][X])
					yCenter = float(particle["Position"][t][Y])
					radius = float(particle["Radius"][t])
					color = getColor(particle["Color"][t])

					circles[particleName] = plt.Circle( (xCenter , yCenter), radius , fill=True, facecolor='white', edgecolor=color, linewidth=3 )
					ax.add_patch(circles[name])

			lines = {}
			if "FixedInfinitePlane" in boundaryData:
				for boundaryName, boundary in boundaryData["FixedInfinitePlane"].items():
					t = beginning
					X = 0
					Y = 1
					normalVersor = list(boundary["NormalVersor"][t])
					origin = list(boundary["Origin"][t])
					color = getColor(boundary["Color"][t])
					(boolReturn, begin, end) = getIntersectPoints(normalVersor, origin, limits)
					if boolReturn:
						(xbeg, ybeg) = begin
						(xend, yend) = end
						lines[boundaryName] = Line2D([xbeg, xend], [ybeg, yend], color=color)
						ax.add_line(lines[boundaryName])

			# return list(circles.values())
			return list(circles.values()) + list(lines.values())

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

		def updateLines(t):
			if "FixedInfinitePlane" in boundaryData:
				for boundaryName, boundary in boundaryData["FixedInfinitePlane"].items():
					t = beginning
					X = 0
					Y = 1
					normalVersor = list(boundary["NormalVersor"][t])
					origin = list(boundary["Origin"][t])
					color = getColor(boundary["Color"][t])
					(boolReturn, begin, end) = getIntersectPoints(normalVersor, origin, limits)
					if boolReturn:
						(xbeg, ybeg) = begin
						(xend, yend) = end
						lines[boundaryName] = Line2D([xbeg, xend], [ybeg, yend], color=color)

			return lines

		### Animate function ###
		def animate_global(t):
			t = timeIndices[t]
			# set graph limits
			limits = getLimits_global( particleData )
			setAxisLimits(limits)
			ax.set_title(str(round_to_n(time[t], 2)) + " s")
			circles = updateCircles(t)
			lines = updateLines(t)

			return list(circles.values()) + list(lines.values())

		### video settings ###
		frames = len(timeIndices)
		fps = frames/animationTime

		### build and save video ###
		anim = animation.FuncAnimation(fig, animate_global, init_func=init, frames=frames , blit=True)
		extension = "_global" + ".mp4"
		filename = "Animation" + extension
		filepath = os.path.join(simulationAnimationsOutputFolder, filename)
		anim.save(filepath, fps=fps)

	build( simulationOutputData , paths , animationTime )