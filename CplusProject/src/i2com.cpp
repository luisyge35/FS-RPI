#include "i2com.h"


#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

#include <iostream>
I2com::I2com(char * file_name, int address){
  //----- OPEN THE I2C BUS -----
  char *filename = (char*) file_name; //"/dev/i2c-1";
  if ((file_i2c = open(filename, O_RDWR)) < 0)
  {
    //ERROR HANDLING: you can check errno to see what went wrong
    throw("Failed to open the i2c bus");
  }

  int addr = address; //'0101000'; //Los 3 bits menos significativos se refieren a las salidas A2 A1 A0 del ADC. Conectar los 3 a tierra

  if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
  {
    throw("Failed to acquire bus access and/or talk to slave.");
  }
}

I2com::~I2com(){

}


unsigned char I2com::read_bus(int bytes_to_read){
  length = bytes_to_read;			//<<< Number of bytes to read. 2 by default
	if (read(file_i2c, buffer, length) != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		//ERROR HANDLING: i2c transaction failed
		throw("Failed to read from the i2c bus.");
	}
	else
	{
		return *buffer;
	}
}

void I2com::write_bus(int byte1, int byte2){
  buffer[0] = byte1;
  buffer[1] = byte2;
  length = 2;			//<<< Number of bytes to write
  if (write(file_i2c, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
  {

    throw("Failed to write to the i2c bus");
  }
}
