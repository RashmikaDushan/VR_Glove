import numpy as np

def cal_velocity(accel_gyro,dt):
    '''This function calculates the velocity of the sensor using the accelerometer data'''
    accel = accel_gyro[:3] # extract the accelerometer data
    velocity = np.zeros(3) # initialize the velocity array
    velocity = accel * dt # calculate the velocity
    return velocity # return the velocity

def cal_position(accel_gyro,dt):
    '''This function calculates the position of the sensor using the accelerometer data'''
    accel = accel_gyro[:3] # extract the accelerometer data
    position = np.zeros(3) # initialize the position array
    position = 0.5 * accel * dt**2 # calculate the position
    return position # return the position