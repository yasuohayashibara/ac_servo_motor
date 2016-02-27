#include "mbed.h"
#include "ACMotor.h"

BusOut led(LED1, LED2, LED3, LED4);
BusIn sw(SW1, SW2);
/*
BusIn hole(MOTOR_HOLE1, MOTOR_HOLE2, MOTOR_HOLE3);
DigitalOut uh(MOTOR_UH);
DigitalOut vh(MOTOR_VH);
DigitalOut wh(MOTOR_WH);
DigitalOut ul(MOTOR_UL);
DigitalOut vl(MOTOR_VL);
DigitalOut wl(MOTOR_WL);
*/
InterruptIn pwm_int(SERVO1);
//DigitalOut led1(SERVO1);
PwmOut pwm(SERVO1);
DigitalOut led2(LED2);

//ACMotor acmotor(MOTOR_UH, MOTOR_UL, MOTOR_VH, MOTOR_VL, MOTOR_WH, MOTOR_WL,
//	MOTOR_HOLE1, MOTOR_HOLE2, MOTOR_HOLE3);

void initialize()
{
	LPC_IOCON -> SWCLK_PIO0_10 |= 0x01; 
	LPC_IOCON -> SWDIO_PIO1_3 |= 0x01; 
}

void pwmSignalRise(void)
{
	led2 = 1;
}

void pwmSignalFall(void)
{
	led2 = 0;
}

int main() {
	float duty = 0.5;
	initialize();

//	ul = 1;
//	vl = 0;
//	wl = 0;
	
	pwm_int.rise(&pwmSignalRise);
	pwm_int.fall(&pwmSignalFall);
//	pwm_gpio.rise(pwmSignalChnaged);
	pwm.period(0.001);
	pwm = duty;
		
  sw.mode(PullUp);
	led = 0;
//  hole.mode(PullUp);
  while(1) {
		duty += 0.1;
		if (duty >= 1.1) duty = 0.0;
		pwm = duty;
//		led2 = led1;
//		int res = hole;
		printf("%f\r\n", duty);
    wait(1.0);
  }
}

