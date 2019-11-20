from adc import *
from multiprocessing import Process
from multiprocessing import Pipe
from multiprocessing import Array
from multiprocessing import Event
from canScript import *
from time import sleep
from os import system

from random import randint
import serial
 
        
def main():
    trama_de_error = 0 #TODO
    try:
        arduino = serial.Serial('/dev/ttyACM0',9600,timeout = 3.0)       #DELETE THIS
        print("\n------------INICIANDO PROGRAMA DE PRUEBA---------\n")

        print("\n\r Estableciendo conexion con bus can")

        system("sudo /sbin/ip link set can0 up type can bitrate 500000")
    except:
        sleep(1)

    print("Conexión realizada. Se empieza a transmitir en segundo plano")
    trama_de_datos = Trama()
    trama_de_datos.id = 0
    trama_de_datos.data[0] = 0
    trama_de_datos.data[1] = 0
    #Se inicializa el proceso
    receiver, Sender = Pipe()
    CAN_tx_Procress = Process(target=CAN_tx_task, args=(receiver,))
    CAN_tx_Procress.start()
    print("\nArranca el proceso de transmision")

    arduino.flushInput()
    
    while(1):
        #Recoger valor de sensores
        ValorDigital1=int.from_bytes(arduino.read(),"big")
        ValorDigital2 =32767-ValorDigital1
        trama_de_datos.Prepara(ValorDigital1,ValorDigital2)
 
        Sender.send(trama_de_datos)

if(__name__ == "__main__"):
    main()

