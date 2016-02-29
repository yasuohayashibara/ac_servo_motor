// Chiba Institute of Technology

#ifndef ASS5600_H
#define ASS5600_H

#include "mbed.h"

class AS5600
{
public:
  AS5600(PinName i2c_sda, PinName i2c_scl);

  void updateAngle();

  float getAngleRad();

  float getAngleDeg();

  void write(float value);

  float read();

  AS5600& operator= (double value) {
    write(value);
    return *this;
  }

	operator float(){
		return read();
	}

private:
  I2C i2c;
  float angle;
  float angle0;
};

#endif
