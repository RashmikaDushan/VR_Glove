import matplotlib.animation as mpl_animation
import numpy as np
import matplotlib.pyplot as plt

accelGyro = np.array([0.1, 0.5, 0.3, 0.4, 0.5, 0.6]) # dummy values

fig = plt.figure(figsize=(10, 7)) # create a figure with 10x7 size
ax = fig.add_subplot(111, projection='3d') # create axes for the plot

ax.set_xlim(0,10) # set x, y, z axes ranges
ax.set_ylim(0,10)
ax.set_zlim(0,10)

def animate(i): # function to animate the plot
    global accelGyro
    print(accelGyro)
    ReadData() # update data
    ax.clear()
    ax.set_xlim(0,10)
    ax.set_ylim(0,10)
    ax.set_zlim(0,10)
    ax.scatter(accelGyro[0], accelGyro[1], accelGyro[2], c='#1ec78d', marker='o') # plot data


def ReadData(): # dummy read data function
    global accelGyro
    offset = np.random.uniform(-0.5, 0.5, 6)
    accelGyro = (accelGyro + offset)%10
    print(accelGyro)

ani = mpl_animation.FuncAnimation(fig,animate, interval=1000/60) # animate the plot forever

plt.show() # show the plot