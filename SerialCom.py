""" 
The Raspberry pi 3 has changed things a bit and you might need to add the option enable_uart=1 at the end of /boot/config.txt
Usare la librería i2c de python para comunicarme con el ADC
Asegurarse de que está instalada la librería
sudo apt-get install -y i2c-tools
"""
import time
import smbus

SLAVE_ADDRESS = b'0101000' #Los 3 bits menos significativos se refieren a las salidas A2 A1 A0 del ADC. Conectar los 3 a tierra
CONTROL_BYE = b'10000000' #Los dos bits más bajos son para cambiar el modo de funcionamiento. 0 0 significa siempre encendido

bus = smbus.SMBus(1)

number = bus.read_byte_data(SLAVE_ADDRESS,0, 1) #Esto debería leer 2 bytes. el 0 y el 1