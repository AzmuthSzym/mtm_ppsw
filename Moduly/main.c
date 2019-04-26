#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

#define NULL 0


int main()
{
	
	LedInit();
	KeyboardInit();
	while(1)
	{
		//ZADANIE 24
		switch(eKeyboardRead())
		{
			case BUTTON_1:
				LedStepRight();
			break;
			case BUTTON_2:
				LedStepLeft();
			break;
			default:
				break;
		}
	}
}

