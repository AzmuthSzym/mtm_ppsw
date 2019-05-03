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
	int imovesCounter = 0;
	enum LedState eLedState = LED_LEFT;
	LedInit();
	KeyboardInit();
	while(1)
	{
		//ZADANIE 3
		switch(eLedState)
		{
			case LED_LEFT:
				for(imovesCounter = 0; imovesCounter < 3; imovesCounter++)
				{
					LedStepRight();
				}
				eLedState = LED_RIGHT;
				break;
			case LED_RIGHT:
				for(imovesCounter = 0; imovesCounter < 3; imovesCounter++)
				{
					LedStepLeft();
				}
				eLedState = LED_LEFT;
				break;
			default:
				break;
		}
		Delay(500);
	}
}

