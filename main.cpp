#include "mbed.h"
#include "MakisumiACMotor.h"

BusOut led(LED2, LED3, LED4);
BusIn sw(SW1, SW2);
MakisumiACMotor acmotor(LED1);

void initialize()
{
	LPC_IOCON -> SWCLK_PIO0_10 |= 0x01; 
	LPC_IOCON -> SWDIO_PIO1_3 |= 0x01; 
}

int main() {
	initialize();
	led = 0;
	sw.mode(PullUp);
	led =  2;
	acmotor.servoOn();
	acmotor = -1.0;
	led = 4;
	while(1){
//		wait(0.5);
		led = led ^ 1;
		acmotor.status_changed();
//		printf("%d\r\n", acmotor.getState());
	}
}
