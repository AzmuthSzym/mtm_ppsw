#include <LPC21xx.H>
#include "led.h"

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

void LedInit()
{
	IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks)
{
	if(ucLedIndeks>4)
	{
		return;
	}
	IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	IO1SET = 1<<(16+ucLedIndeks);
}

void LedStep(enum LedDirection iDirection)
{
	static unsigned int suiPosition;
	switch(iDirection)
	{
		case LEFT:
			++suiPosition;
			LedOn(suiPosition%4);
		break;
		case RIGHT:
			suiPosition=(suiPosition-1);
			LedOn(suiPosition%4);
		break;
	}
}

void LedStepLeft(void)
{
	LedStep(LEFT);
}

void LedStepRight(void)
{
	LedStep(RIGHT);
}


