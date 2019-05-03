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

enum ButtonState{PRESSED, NOT_PRESSED};

int main()
{
	int imovesCounter = 0;
	enum ButtonState eButtonState = NOT_PRESSED;
	LedInit();
	KeyboardInit();
	while(1)
	{
		//ZADANIE 4
		switch(eButtonState)
		{
			case PRESSED:
				for(imovesCounter = 0; imovesCounter < 3; imovesCounter++)
					{
						LedStepRight();
					}
					eButtonState = NOT_PRESSED;
				break;
			case NOT_PRESSED:
				if(eKeyboardRead() == BUTTON_0)
				{
					eButtonState = PRESSED;
					break;
				}
			default:
				break;
		}
		//Delay(500);
	}
}

