import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

# Config 
fig_dpi = 100

# create figure
fig = plt.figure()
fig.set_dpi(fig_dpi)
fig.set_size_inches(7, 6.5)
ax = fig.add_subplot(111)

# Set limits
xMin = min(particleData[0]['position'][:,0])
xMax = max(particleData[0]['position'][:,0])
for p in range(nParticles): # for each particle
	# X
	xLocalMin = min(particleData[p]['position'][:,0])
	xLocalMax = max(particleData[p]['position'][:,0])
	if(xLocalMin < xMin):
		xMin = xLocalMin
	if(xLocalMax > xMax):
		xMax = xLocalMax
	# Y
	yLocalMin = min(particleData[p]['position'][:,0])
	yLocalMax = max(particleData[p]['position'][:,0])
	if(localMin < xMin):
		yMin = yLocalMin
	if(localMax > xMax):
		yMax = yLocalMax

ax.set_xlim([xMin , xMax])
ax.set_ylim([yMin , yMax])

# Create several circles
circles = []
for p in range(nParticles):
	#radius = float(particleData['main']['Radius'])
	radius = particleData['main']['Radius']




def init():
	