# Animation with circle

import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

radius = 0.5
ho = 25
g = -0.98
Min = 0
Max = ho
tEnd = np.sqrt( -2*ho/g )
print(tEnd)

fig = plt.figure()
fig.set_dpi(100)
fig.set_size_inches(7, 6.5)

ax = plt.axes(xlim=(Min-Max/2 , Max-Max/2), ylim=(Min , Max))
circle = plt.Circle((0 , ho), radius, color='b' , fill=True)


def init():
    circle.center = (0 , ho)
    ax.add_patch(circle)
    return circle,

def animate(t):
    x, y = circle.center
    y = (g/2)*(t**2) + ho
    x = 0
    circle.center = (x, y)
    return circle,

interval = 1
frames = int(10*tEnd/interval)
fps = 30

print('tEnd = ' , tEnd)
print('interval = ' , interval)
print('frames = ' , frames)
print('fps = ' , fps)
#
#print('final time = ' , tEnd)
#print('interval between frames = ' , interval)
#print('number of frames = ' , frames)
#print('fps = ' , fps)
anim = animation.FuncAnimation(fig, animate, init_func=init, frames=frames, interval=interval, blit=True)

anim.save('animation.mp4', fps=fps, 
          extra_args=['-vcodec', 'h264', 
                      '-pix_fmt', 'yuv420p'])