from matplotlib import pyplot as plt
from matplotlib import animation

def build_video(particleData , nParticles):

	# Config 
	fig_dpi = 100
	fig_x_size = 7
	fig_y_size = 6.5

	# create figure
	fig = plt.figure()
	fig.set_dpi(fig_dpi)
	fig.set_size_inches(fig_x_size, fig_y_size)
	ax = fig.add_subplot(111)
	ax.grid(visible=True)
	ax.autoscale(enable=True , axis='both')






	# # Set limits
	# # xMin = min(particleData[0]['position'][:,0])
	# # xMax = max(particleData[0]['position'][:,0])
	# # yMin = min(particleData[0]['position'][:,1])
	# # yMax = max(particleData[0]['position'][:,1])

	# # ax.set_xlim([xMin , xMax])
	# # ax.set_ylim([yMin , yMax])

	# # One circle to the first particle
	# p = 0
	# radius = float(particleData[p]['main']['Radius'])
	# timeStep = 0
	# X = 0
	# Y = 1
	# xCenter = particleData[p]['position'][timeStep,X]
	# yCenter = particleData[p]['position'][timeStep,Y]
	# circle = plt.Circle( (xCenter , yCenter), radius , fill=True , fc='b' )

	# # Initial function to animation
	# def init():
	# 	p = 0
	# 	ax.add_patch(circle)
	# 	return circle,

	# # Animate function
	# def animate(i):

	# 	p = 0
	# 	X = 0
	# 	Y = 1
	# 	xCenter = particleData[p]['position'][i,X]
	# 	yCenter = particleData[p]['position'][i,Y]
	# 	circle.center = (xCenter , yCenter)
	# 	print('i = ' , i)
	# 	return circle,

	# # Generating video
	# interval = 20
	# frames = 180
	# fps = 60

	# print('interval = ' , interval)
	# print('frames = ' , frames)
	# print('fps = ' , fps)

	# anim = animation.FuncAnimation(fig, animate, init_func=init, frames=180, interval=20 , blit=True)

	# anim.save('animation.mp4', fps=60 , extra_args=['-vcodec', 'h264', '-pix_fmt', 'yuv420p'])
	# #anim.save('animation.mp4', fps=fps, extra_args=['-vcodec', 'h264', '-pix_fmt', 'yuv420p'])









	# Set limits
	# xMin = min(particleData[0]['position'][:,0])
	# xMax = max(particleData[0]['position'][:,0])
	# yMin = min(particleData[0]['position'][:,1])
	# yMax = max(particleData[0]['position'][:,1])
	# for p in range(nParticles): # for each particle
	# 	# X
	# 	xLocalMin = min(particleData[p]['position'][:,0])
	# 	xLocalMax = max(particleData[p]['position'][:,0])
	# 	if(xLocalMin < xMin):
	# 		xMin = xLocalMin
	# 	if(xLocalMax > xMax):
	# 		xMax = xLocalMax
	# 	# Y
	# 	yLocalMin = min(particleData[p]['position'][:,0])
	# 	yLocalMax = max(particleData[p]['position'][:,0])
	# 	if(xLocalMin < xMin):
	# 		yMin = yLocalMin
	# 	if(xLocalMax > xMax):
	# 		yMax = yLocalMax

	# xWidth = xMax - xMin
	# yWidth = yMax - yMin
	# width = max(xWidth , yWidth)
	# ax.set_xlim([xMin , xMin + width])
	# ax.set_ylim([yMin , yMin + width])

	# Create several circles, one for each particle
	circles = []
	for p in range(nParticles):
		radius = float( particleData[p]['main']['Radius'] )
		timeStep = 0
		X = 0
		Y = 1
		xCenter = particleData[p]['position'][timeStep,X]
		yCenter = particleData[p]['position'][timeStep,Y]
		circles.append( plt.Circle( (xCenter , yCenter), radius , fill=True , facecolor='b' ) )

	# Initial function to animation
	def init():
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

	# Animate function
	def animate(t):
		for p in range(nParticles):
			xCenter, yCente = circles[p].center
			X = 0
			Y = 1
			xCenter = particleData[p]['position'][t,X]
			yCenter = particleData[p]['position'][t,Y]
			circles[p].center = (xCenter , yCenter)
		print('t = ' , t)
		ax.autoscale(enable=True , axis='both')
		return circles

	# Generating video
	interval = 10
	frames = 100
	fps = 30

	print('interval = ' , interval)
	print('frames = ' , frames)
	print('fps = ' , fps)

	anim = animation.FuncAnimation(fig, animate, init_func=init, frames=frames, interval=interval)

	anim.save('animation.mp4', fps=fps)
	anim.save('animation.mp4', fps=fps, extra_args=['-vcodec', 'h264', '-pix_fmt', 'yuv420p'])