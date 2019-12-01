#include "led.h"
#include "uart.h"
#include "servo.h"

#define M_MULTIPIER 1000000
#define NULL 0

int main(){
	extern char cOdebranyZnak;
	int iservoCounter=0;
	UART_InitWithInt(9600);
	ServoInit(150);

	while(1){
		switch(cOdebranyZnak){
			case '1':
				iservoCounter++;
				ServoGoTo(12*(iservoCounter%4));
				cOdebranyZnak = NULL;
				break;
			case '2':
				ServoGoTo(24);
				break;
			case '3':
				ServoGoTo(36);
				break;
			case 'c':
				ServoCallib();
				break;
			default:
				break;
		}
	}
}
