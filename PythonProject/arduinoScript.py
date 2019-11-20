import serial
import time

arduino = serial.Serial('/dev/ttyACM0',9600,timeout = 3.0)

while True:
    while (arduino.inWaiting() > 0):
        print(arduino.read(1))
        arduino.flush()
        time.sleep(1)
arduino.close()
    