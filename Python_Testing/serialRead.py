import serial.tools.list_ports
import numpy as np

class SerialCom:
    def __init__(self):
        self.serial_com = None
        self.accel_gyro = np.array([0 , 0 , 0, 0, 0, 0])
        self.port_number = "/dev/cu.usbserial-0001"

    def serial_init(self,default_port_number=True, baud_rate=115200):

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

    def read_data(self):
        try:
            if self.serial_com.in_waiting: # if data is available
                packet = np.array(self.serial_com.readline().decode('ascii').strip().split(",")) # read data from the serial port and convert string array
                self.accel_gyro = packet.astype(float) # convert the string array to float array
            return self.accel_gyro # return the data
        except:
            return "Error" # return error if no data is received