import struct
DIGITAL_MAX = 32767
DIGITAL_MIN = 0

ERROR_PERMITIDO  = 100 #Error admisible entre las medidas de la pedalera

class Trama:
    def __init__(self):
        self.id = 0
        self.data= []
        self.data.append(0)
        self.data.append(0)
        self.maximun_value = DIGITAL_MAX
        self.minimun_value = DIGITAL_MIN
        self.error = ERROR_PERMITIDO
        
    def Prepara(self,Val1,Val2):
        val_bytes = Val1.to_bytes(2,"little")
        #val_converted = [hex(val_bytes[0]),hex(val_bytes[1])]
        self.id = 3
        self.data[0] = val_bytes[0]
        self.data[1] = val_bytes[1]


    def Check(self,Vol1,Vol2): #Return true if ok
        if ( abs((self.maximum_value+self.minimum_value)- (Vol1+Vol2)) > self.error):
                return False
        else:
            return True



