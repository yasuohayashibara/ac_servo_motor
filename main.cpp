#include "mbed.h"

BusOut led(LED1, LED2, LED3, LED4);
BusIn sw(SW1, SW2);
BusIn hole(MOTOR_HOLE1, MOTOR_HOLE2, MOTOR_HOLE3);
PwmOut pwm_u(MOTOR_U1);
PwmOut pwm_v(MOTOR_V1);
PwmOut pwm_w(MOTOR_W1);
BusOut motor(MOTOR_U2, MOTOR_V2, MOTOR_W2);

void initialize()
{
	LPC_IOCON -> SWCLK_PIO0_10 |= 0x01; 
	LPC_IOCON -> SWDIO_PIO1_3 |= 0x01; 
}

int main() {
	initialize();
	motor = 0x01;
	pwm_u.period(0.00005);
	pwm_v.period(0.00005);
	pwm_w.period(0.00005);
	pwm_u = 0;
	pwm_v = 0.01;
	pwm_w = 0;
  sw.mode(PullUp);
	led = 0;
  hole.mode(PullUp);
  while(1) {
		int res = hole;
		printf("%d\r\n", res);
    wait(0.1);
  }
}
