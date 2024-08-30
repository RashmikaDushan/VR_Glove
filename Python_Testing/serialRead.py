import serial.tools.list_ports
import numpy as np

ports = list(serial.tools.list_ports.comports())

portlist = []

accelGyro = np.array([0 , 0 , 0, 0, 0, 0])

for onePort in ports:
    portlist.append(str(onePort))
    print(str(onePort))

portNumber = "/dev/cu.usbserial-0001"
inputPortNumber = input(str("Please enter the port number: ").strip())

if not(inputPortNumber == ""):
    portNumber = inputPortNumber
    print("Using port number: " + portNumber)
else:
    print("Using default port number: " + portNumber)

SerialCom = serial.Serial("/dev/cu.usbserial-0001", 115200)

while True:
    try:
        if SerialCom.in_waiting:
            packet = np.array(SerialCom.readline().decode('ascii').strip().split(","))
            accelGyro = packet.astype(float)
            print(accelGyro)
    except:
        print("Error")
        pass
        