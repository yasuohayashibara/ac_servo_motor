#include "mbed.h"
#include "MakisumiACMotor.h"
#include "AS5600.h"

#ifndef M_PI
#define M_PI           3.14159265358979323846f
#endif

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

BusOut led(LED2, LED3, LED4);
BusIn sw(SW1, SW2);
MakisumiACMotor acmotor(LED1);
AS5600 as5600(I2C_SDA, I2C_SCL);
Serial serial(USBTX, USBRX);
Timer t;
float target_angle = 0;

void initialize()
{
	LPC_IOCON -> SWCLK_PIO0_10 |= 0x01; 
	LPC_IOCON -> SWDIO_PIO1_3 |= 0x01; 
}

void isrRx() {
	static char buf[10];
	static int n = 0;
	while(serial.readable()){
		buf[n ++] = serial.getc();
		if (n >= 10) n = 0;
		if (buf[n-1] == '\r'){
			int t_angle;
			n = 0;
			sscanf(buf, "%d", &t_angle);
			if ((t_angle > 50) || (t_angle < -50)) return;
			target_angle = t_angle * M_PI / 180.0f;
		}
	}
}

int main() {
	int previous_hole_state = 6;
	float gain = 10.0, max_value = 1.0;
	int counter = 25, led_counter  = 100, led_state = 0;
	initialize();
	led = 0;
	sw.mode(PullUp);
	serial.attach(isrRx, Serial::RxIrq);
	
	acmotor.servoOn();
	as5600 = as5600 - 2.3;
	while(1){
		float angle = as5600;
		float val = max(min(gain * (angle - target_angle), max_value), -max_value);
		acmotor = val;
		if (sw[0] == 0 && counter == 0){
			target_angle += 0.1;
			counter = 25;
		}
		if (sw[1] == 0 && counter == 0){
			target_angle -= 0.1;
			counter = 25;
		}
		if (counter > 0) counter --;
		if (led_counter == 0){
			led_state ^= 1;
			led[0] = led_state;
			led_counter = 100;
		}	
		led_counter --;
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
