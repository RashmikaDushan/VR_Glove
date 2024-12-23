import matplotlib.animation as mpl_animation
import numpy as np
import matplotlib.pyplot as plt
from serialRead import SerialCom

np.set_printoptions(precision=2) # set the precision of the numpy array to 2 decimal places

accel_gyro = np.array([0, 0, 0, 0, 0, 0]) # dummy values

serial_in = SerialCom() # create an object of the SerialCom class
serial_in.serial_init() # initialize the serial port

fig = plt.figure(figsize=(10, 7)) # create a figure with 10x7 size
ax = fig.add_subplot(111, projection='3d') # create axes for the plot

ax.set_xlim(-10,10) # set x, y, z axes ranges
ax.set_ylim(-10,10)
ax.set_zlim(-10,10)

def animate(i): # function to animate the plot
    global accel_gyro
    accel_gyro = serial_in.read_data() # update data
    print(accel_gyro)
    if not(accel_gyro.tolist() == "1") and len(accel_gyro)==6: # if no data is received
        ax.clear()
        ax.set_xlim(-10,10)
        ax.set_ylim(-10,10)
        ax.set_zlim(-10,10)
        ax.scatter(accel_gyro[0], accel_gyro[1], accel_gyro[2], c='#1ec78d', marker='o') # plot data

ani = mpl_animation.FuncAnimation(fig,animate, interval=1) # animate the plot forever

plt.show() # show the plot