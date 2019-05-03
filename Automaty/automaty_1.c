#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

#define NULL 0

void Delay(int time_milisec)
{
	int delayInMiliSec = 2727 * time_milisec;
	int count;
	for(count=0; count < delayInMiliSec; count++) {}
}

enum LedState{LED_LEFT, LED_RIGHT};

int main()
{
	enum LedState eLedState = LED_LEFT;
	LedInit();
	KeyboardInit();
	while(1)
	{
		//ZADANIE 1
		switch(eLedState)
		{
			case LED_LEFT:
				eLedState = LED_RIGHT;
				LedStepRight();
				break;
			case LED_RIGHT:
				eLedState = LED_LEFT;
				LedStepLeft();
				break;
			default:
				break;
		}
		Delay(500);
	}
}

