#ifndef _I2COM_H_
#define _I2COM_H_

#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

class I2com{
protected:
  int file_i2c;
  int length;
  unsigned char buffer[4] = {0};
  bool isVirtual;

public:
  I2com(bool,char*, int);
  ~I2com();
  unsigned char* read_bus(int);
  void write_bus(int,int);
  void Connect(char*, int);
  void VirtualConnect(char*, int);
};

#endif
