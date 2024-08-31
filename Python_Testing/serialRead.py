import serial.tools.list_ports
import serial
import numpy as np

class SerialCom:
    def __init__(self):
        self.serial_com = None
        self.accel_gyro = np.array([0, 0, 0, 0, 0, 0]).astype(float) # np.zeros(shape=(1,6), dtype=float)
        self.accel_gyro_prev = np.array([0, 0, 0, 0, 0, 0]).astype(float) # np.zeros(shape=(1,6), dtype=float)
        self.port_number = "/dev/cu.usbserial-0001"
        self.dummy = False
        self.alpha = 0.1
        self.filtered = False

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

    def read_data(self,filtered=False):

        '''This function reads data from the serial port when it's available 
        and returns it.If the dummy flag is set, it returns dummy data.'''
        
        self.filtered = filtered

        if self.dummy:
            packet = (self.accel_gyro + np.random.uniform(-0.5, 0.5, 6))%10 # add random noise to the data
            if self.filtered:
                self.accel_gyro = self.alpha * packet.astype(float) + ( 1 - self.alpha) * self.accel_gyro # apply low pass filter
            else:  
                self.accel_gyro = packet.astype(float) # convert the data to float
            return self.accel_gyro.tolist() # return the data
        else:
            try:
                if self.serial_com.in_waiting: # if data is available
                    packet = np.array(self.serial_com.readline().decode('ascii').strip().split(",")) # read data from the serial port and convert string array
                    if self.filtered:
                        self.accel_gyro = self.alpha * packet.astype(float) + ( 1 - self.alpha) * self.accel_gyro # apply low pass filter
                    else:  
                        self.accel_gyro = packet.astype(float) # convert the data to float
                return self.accel_gyro.tolist() # return the data
            except Exception as e:
                print(e)
                return "1" # return error if no data is received

#################################

# For Testing

# ser = SerialCom() # create an object of the SerialCom class
# ser.serial_init() # initialize the serial port

# while True: # loop forever
#     data = ser.read_data() # read data from the serial port
#     print(data) # print the data