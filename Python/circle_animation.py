# Import
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

# Generate figure
fig = plt.figure()
fig.set_dpi(100)
fig.set_size_inches(7, 6.5)
ax = plt.axes(xlim=(0, 10), ylim=(0, 10))
ax.grid(visible=True)

# Generate circles
nCircle = 3
theta = 360/nCircle
patch = []
for k in range(0,nCircle):
    patch.append( plt.Circle((5, -5), 0.75, fc='y') )

# Define initial condition
def init():
    for k in range(0,nCircle):
        io = theta * k
        x = 5 + 3 * np.sin(np.radians(io))
        y = 5 + 3 * np.cos(np.radians(io))
        patch[k].center = (x, y)
        ax.add_patch(patch[k])
    return patch

# Define position for each frame
def animate(i):
    for k in range(0,nCircle):
        x, y = patch[k].center
        io = theta * k
        x = 5 + 3 * np.sin(np.radians(i + io))
        y = 5 + 3 * np.cos(np.radians(i + io))
        patch[k].center = (x, y)
    print('i = ' , i)
    return patch

# Animate function
anim = animation.FuncAnimation(fig, animate,
                               init_func=init, 
                               frames=180, 
                               interval=20,
                               blit=True)

anim.save('animation.mp4',
          fps=60,
          extra_args=['-vcodec', 'h264', '-pix_fmt', 'yuv420p'])
