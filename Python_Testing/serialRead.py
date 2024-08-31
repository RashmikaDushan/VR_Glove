import serial.tools.list_ports
import serial
import numpy as np
import time

np.set_printoptions(precision=2) # set the precision of the numpy array to 2 decimal places

class SerialCom:
    def __init__(self):
        self.serial_com = None # initialize the serial port
        self.accel_gyro = np.array([0, 0, 0, 0, 0, 0]).astype(float) # initialize the data array
        self.port_number = "/dev/cu.usbserial-0001" # default port number
        self.dummy = False # flag to enable dummy data
        self.alpha = 0.1 # filter coefficient aplha high --> slow rate of change | low --> fast rate of change
        self.filtered = False # flag to enable filtering
        self.cal_buffer = [] # buffer to store calibration data
        self.error = np.array([0, 0, 0, 0, 0, 0]).astype(float) # initialize the error array

    def serial_init(self,default_port_number=True, baud_rate=115200, dummy=False):

        '''This function initializes the serial port. If the dummy flag is set, 
        it doesn't initialize the serial port. If the default_port_number flag 
        is set, it uses the default port number.'''

        if dummy:
            self.dummy = True
            print("Using dummy data")
        else:
            if not(default_port_number):
                ports = list(serial.tools.list_ports.comports()) # get all available ports

                port_list = []

                for one_port in ports:
                    port_list.append(str(one_port))
                    print(str(one_port)) # print all available ports
                
                print("Please enter the port number: ")

                while True: # loop until a valid port number is entered
                    input_port_number = input(str().strip()) # get the port number from the user
                    if input_port_number in ports:
                        self.port_number = input_port_number
                        print("Using port number: " + input_port_number)
                        break
                    elif input_port_number == "":
                        print("Using default port number: " + self.port_number)
                        break
                    else:
                        print("Please enter a valid port number: ") # if the port number is wrong
                        continue

            self.serial_com = serial.Serial(self.port_number, baud_rate) # open the serial port

    def read_data(self,filtered=False,alpha=0.1,print_data=False):

        '''This function reads data from the serial port when it's available 
        and returns it.If the dummy flag is set, it returns dummy data.'''
        
        self.filtered = filtered
        self.alpha = alpha

        if self.dummy:
            packet = (self.accel_gyro + np.random.uniform(-0.5, 0.5, 6))%10 # add random noise to the data
            if self.filtered:
                self.accel_gyro = self.alpha * packet.astype(float) + ( 1 - self.alpha) * self.accel_gyro # apply low pass filter
            else:  
                self.accel_gyro = packet.astype(float) # convert the data to float
            return self.accel_gyro # return the data
        else:
            try:
                if self.serial_com.in_waiting: # if data is available
                    packet = np.array(self.serial_com.readline().decode('ascii').strip().split(",")).astype(float) - self.error # read data from the serial port and convert string array
                    if self.filtered:
                        self.accel_gyro = (self.alpha * packet.astype(float) + ( 1 - self.alpha) * self.accel_gyro) # apply low pass filter
                    else:  
                        self.accel_gyro = packet.astype(float) # convert the data to float
                    if print_data:
                        print("corrected values:",self.accel_gyro)
                return self.accel_gyro # return the data
            except Exception as e:
                print(e)
                return "1" # return error if no data is received
    
    def calibrate(self):
        '''This function calculates the error in the sensor data'''

        print("Please keep the sensor steady for calibration")
        input("Press Enter to continue...")
        print("Calibrating...")
        i = 0
        timeout = 0

        while i < 100:
            data = list(self.read_data())
            if not(data == "1") and len(data)==6 and data != [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]:
                print(i+1,".",data)
                self.cal_buffer.append(data)
                i += 1
            timeout += 1
            if timeout > 1000:
                print("Timeout")
                break
            time.sleep(0.01)

        self.cal_buffer = np.array(self.cal_buffer).astype(float)
        self.error = np.mean(self.cal_buffer, axis=0)
        self.accel_gyro = np.array([0, 0, 0, 0, 0, 0]).astype(float)
        print("error:",self.error)
        print("Calibration complete!")
        input("Press Enter to continue...")

#################################

# For Testing

# ser = SerialCom() # create an object of the SerialCom class
# ser.serial_init() # initialize the serial port
# ser.calibrate() # calibrate the sensor

# while True: # loop forever
#     data = ser.read_data(filtered=True,alpha=0.5,print_data=True) # read data from the serial port