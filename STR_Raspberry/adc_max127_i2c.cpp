#include "adc_max127_i2c.h"

ADC_MAX127_I2C::ADC_MAX127_I2C(int adress)
{
    filename = (char*)"/dev/i2c-1";
    if ((file_i2c = open(filename, O_RDWR)) < 0)
    {
        std::cout << "No ha sido posible abrir el bus" << std::endl;
    }

    // Miramos si podemos comunicarnos con el esclavo
    if (ioctl(file_i2c, I2C_SLAVE, adress) < 0)
    {
        std::cout << "No ha sido posible conectar con esclavo" << std::endl;
        // Podriamos meter un try catch aqui tambien
    }
}


void ADC_MAX127_I2C::Set_Channel(uint8_t channel){
    // Tenemos 8 canales analogicos disponibles, codificados en tres bits
    // Igual mola mas otra forma más elegante de hacerlo pero de momento
    // tiramos con un switch y a correr
    switch(channel){
    case 0:
        Control_Byte.SEL0 = 0;
        Control_Byte.SEL1 = 0;
        Control_Byte.SEL2 = 0;
        break;

    case 1:
        Control_Byte.SEL0 = 1;
        Control_Byte.SEL1 = 0;
        Control_Byte.SEL2 = 0;
        break;

    case 2:
        Control_Byte.SEL0 = 0;
        Control_Byte.SEL1 = 1;
        Control_Byte.SEL2 = 0;
        break;

        // Etc Etc, para el coche con 3 canales nos vale ya
    }
}

// Solo necesitamos mandar un byte, el de control pero
void ADC_MAX127_I2C::Write_Byte(uint8_t byte){
    uint8_t  length = 1;			//<<< Number of bytes to write
    //unsigned char BUFFER[1];
    //BUFFER[0] = byte;
    if (write(file_i2c, &byte ,length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to write to the i2c bus.\n");
    }
}

void ADC_MAX127_I2C::Start_Conversion(int channel){
    // Seleccion del canal
    Set_Channel(channel);

    // Bit start a 1
    Control_Byte.START = 1;

    // Contruimos el envio
    Byte_Sent = Control_Byte.START  << 7;
    Byte_Sent |= Control_Byte.SEL2  << 6;
    Byte_Sent |= Control_Byte.SEL1  << 5;
    Byte_Sent |= Control_Byte.SEL0  << 4;
    Byte_Sent |= Control_Byte.RNG   << 3;
    Byte_Sent |= Control_Byte.BIP   << 2;
    Byte_Sent |= Control_Byte.PD1   << 1;
    Byte_Sent |= Control_Byte.PD0;

    // Y enviamos orden al ADC para que empiece a enviar
    Write_Byte(Byte_Sent);

    std::cout << "Byte control: " << Byte_Sent<< std::endl;
}


float ADC_MAX127_I2C::Get_Voltage(int channel){
    uint8_t length = 2;			//<<< Number of bytes to read
    unsigned char BUFFER[2] = {0};
    // Empezamos la conversion
    Start_Conversion(channel);

    if (read(file_i2c, BUFFER, length) != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    {
        //ERROR HANDLING: i2c transaction failed
        printf("Failed to read from the i2c bus.\n");
        return -1;
    }
    else
    {
        int result;
        float voltage;
        result = BUFFER[0] * 256 + BUFFER[1];
        voltage = 5.0 * result / 65535;
        return voltage;
    }
}



