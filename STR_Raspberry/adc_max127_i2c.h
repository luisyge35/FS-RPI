#ifndef ADC_MAX127_I2C_H
#define ADC_MAX127_I2C_H

#include <iostream>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port


struct CONTROLBYTE {
    bool PD0   : 1;
    bool PD1   : 1;
    bool BIP   : 1;
    bool RNG   : 1;
    bool SEL0  : 1;
    bool SEL1  : 1;
    bool SEL2  : 1;
    bool START : 1;
};


class ADC_MAX127_I2C
{
public:
    ADC_MAX127_I2C(int adress);
    void Set_Channel(uint8_t);
    void Write_Byte(uint8_t);
    float Get_Voltage(int channel);
    int Byte_Sent = 0;

private:
    void Start_Conversion(int);

protected:
    uint8_t Device_Adress = 0x28;
    CONTROLBYTE Control_Byte;
    int file_i2c;
    char *filename;

}
;

#endif // ADC_MAX127_I2C_H
