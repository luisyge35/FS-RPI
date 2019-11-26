#ifndef _I2COM_H_
#define _I2COM_H_


class I2com{
protected:
  int file_i2c;
  int length;
  unsigned char buffer[60] = {0};

public:
  I2com(char*, int);
  ~I2com();
  unsigned char read_bus(int);
  void write_bus(int,int);
};

#endif
