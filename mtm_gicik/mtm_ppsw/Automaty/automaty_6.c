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

enum ButtonState{S0_PRESSED, S1_PRESSED, S2_PRESSED};

int main()
{
	
	enum ButtonState eButtonState = S1_PRESSED;
	LedInit();
	KeyboardInit();
	while(1)
	{
		//ZADANIE 6
		switch(eButtonState)
		{
			case S1_PRESSED:
				if(eKeyboardRead() == BUTTON_0)
				{
					eButtonState = S0_PRESSED;
				}
				else if(eKeyboardRead() == BUTTON_2)
				{
					eButtonState = S2_PRESSED;
				}
				break;
			case S0_PRESSED:
				if(eKeyboardRead() == BUTTON_1)
				{
					eButtonState = S1_PRESSED;
				}
				else
				{
					LedStepLeft();					
				}
				break;
			case S2_PRESSED:
				if(eKeyboardRead() == BUTTON_1)
				{
					eButtonState = S1_PRESSED;
				}
				else
				{
					LedStepRight();
				}
				break;
			default:
				break;
		}
		Delay(98);
	}
}

