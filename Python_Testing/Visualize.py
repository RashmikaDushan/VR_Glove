import matplotlib.animation as mpl_animation
import numpy as np
import matplotlib.pyplot as plt

accelGyro = np.array([0.1, 0.5, 0.3, 0.4, 0.5, 0.6])

# plt.rcParams['figure.figsize'] = (6,4)

fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

ax.set_xlim(0, 10)
ax.set_ylim(0, 10)

def animate(i):
    global accelGyro
    print(accelGyro)
    ReadData()
    ax.clear()
    ax.scatter(accelGyro[0], accelGyro[1], accelGyro[2], c='#1ec78d', marker='o')


def ReadData():
    global accelGyro
    accelGyro = np.random.uniform(0, 10, 6)
    print(accelGyro)

ani = mpl_animation.FuncAnimation(fig,animate, frames=100, interval=1000) 

plt.show()