#include "mbed.h"
#include "MakisumiACMotor.h"
#include "AS5600.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

BusOut led(LED2, LED3, LED4);
BusIn sw(SW1, SW2);
MakisumiACMotor acmotor(LED1);
AS5600 as5600(I2C_SDA, I2C_SCL);

Timer t;

void initialize()
{
	LPC_IOCON -> SWCLK_PIO0_10 |= 0x01; 
	LPC_IOCON -> SWDIO_PIO1_3 |= 0x01; 
}

int main() {
	int previous_hole_state = acmotor.getHoleState();
	float gain = 10.0, max_value = 1.0;
	float target_angle = 0;
	int counter = 25;
	initialize();
	led = 0;
	sw.mode(PullUp);
	acmotor.servoOn();
	as5600 = as5600 - 2.3;
	while(1){
		float angle = as5600;
		float val = max(min(gain * (angle - target_angle), max_value), -max_value);
		acmotor = val;
//		printf("%f\r\n", target_angle);
		if (sw[0] == 0 && counter == 0){
			target_angle += 0.1;
			counter = 25;
		}
		if (sw[1] == 0 && counter == 0){
			target_angle -= 0.1;
			counter = 25;
		}
		if (counter > 0) counter --;
		t.reset();
		t.start();
		while(t.read() < 0.020f){
			if (acmotor.getHoleState() != previous_hole_state){
				acmotor.status_changed();
				previous_hole_state = acmotor.getHoleState();
			}
		}
	}
}
