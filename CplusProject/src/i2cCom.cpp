#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

#include <iostream>
/*
	int file_i2c;
	int length;
	unsigned char buffer[60] = {0};
using namespace std;
void prueba(){
	//----- OPEN THE I2C BUS -----
	char *filename = (char*) "/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		cout << "Failed to open the i2c bus" << endl;
		return;
	}

	int addr = 40; //'0101000'; //Los 3 bits menos significativos se refieren a las salidas A2 A1 A0 del ADC. Conectar los 3 a tierra

	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		cout << "Failed to acquire bus access and/or talk to slave." << endl;
		//ERROR HANDLING; you can check errno to see what went wrong
		return;
	}


	//----- READ BYTES -----
	length = 2;			//<<< Number of bytes to read
	if (read(file_i2c, buffer, length) != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		//ERROR HANDLING: i2c transaction failed
		cout << "Failed to read from the i2c bus.\n" << endl;
	}
	else
	{
		cout << "Data read: %s\n"<< buffer << endl;
	}


	//----- WRITE BYTES -----
	buffer[0] = 0x01;
	buffer[1] = 0x02;
	length = 2;			//<<< Number of bytes to write
	if (write(file_i2c, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{

		cout << "Failed to write to the i2c bus.\n"<< endl;
	}
	return;
}
*/
