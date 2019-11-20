import time
import can
from adc import *

    
def CAN_tx_task(pipe):
    while(1):
        trama = pipe.recv()
        bus = can.interface.Bus(channel = 'can0', bustype = 'socketcan_native')
        msg = can.Message(arbitration_id=trama.id,
                          data=[trama.data[0],trama.data[1]])

        try:
            bus.send(msg)
        except can.CanError:
            print("Message NOT sent")


