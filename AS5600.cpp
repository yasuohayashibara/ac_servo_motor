#include "mbed.h"
#include "AS5600.h"

#define SLAVE_ADRESS	0x36

AS5600::AS5600(PinName i2c_sda, PinName i2c_scl):
	i2c(i2c_sda, i2c_scl), angle0(0)
{
}

void AS5600::updateAngle()
{
  char cmd[1];
  char out[2];
  cmd[0] = 0x0E;
  i2c.write(SLAVE_ADRESS << 1, cmd, 1);
  i2c.read(SLAVE_ADRESS << 1, out, 2);
 
  angle = ((out[0] << 8) + out[1]) * 0.087912087 - angle0;
}

float AS5600::getAngle()
{
	return angle;
}

void AS5600::write(double value)
{
	updateAngle();
	angle0 = (angle + angle0) - value;
}

double AS5600::read()
{	
	return angle;
}
