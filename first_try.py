import os
import time
import can
print("\nEstableciendo conexion con el bus can...")
os.system("sudo /sbin/ip link set can0 up type can bitrate 500000")
time.sleep(0.1)

bus = can.interface.Bus(channel = 'can0', bustype = 'socketcan')
msg = can.Message(arbitration_id = 0x181, data = [0, 1, 2, 3, 4, 5, 6, 7], is_extended_id = True)
#Hay que invertir las tramas

try:
    bus.send(msg)
    print("Message sent on {}".format(bus.channel_info))
except can.CanError:
    print("Message NOT sent")
