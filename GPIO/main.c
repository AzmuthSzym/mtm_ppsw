#include <LPC21xx.H>

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)
#define S0_bm (1<<3)
#define S1_bm (1<<5)
#define S2_bm (1<<4)
#define S3_bm (1<<6)

//TEST DO GITA

enum ButtonState {RELEASED1, PRESSED};
enum KeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum LedDirection {LEFT,RIGHT};
int count;

void Delay(int time_milisec)
{
	int delayInMiliSec = 2727 * time_milisec;
	for(count=0; count < delayInMiliSec; count++) {}
}

void LedInit_zad13()
{
	IO1DIR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
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

void LedInit()
{
	IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	IO1SET = LED0_bm;
}

enum ButtonState ReadButton1()
{
	if((IO1PIN & S0_bm)==1)
	{
		return PRESSED;
	}
	else
	{
		return RELEASED1;
	}
}

void KeyboardInit()
{
	//IO1DIR = IO1DIR & ~LED0_bm;
	IO0DIR = IO0DIR & ~(S0_bm|S1_bm|S2_bm|S3_bm);
}

enum KeyboardState eKeyboardRead()
{
	if((IO0PIN & S0_bm)==0)
	{
		return BUTTON_0;
	}
	else if((IO0PIN & S1_bm)==0)
	{
		return BUTTON_1;
	}
	else if((IO0PIN & S2_bm)==0)
	{
		return BUTTON_2;
	}
	else if((IO0PIN & S3_bm)==0)
	{
		return BUTTON_3;
	}
	return RELEASED;
}

void LedStep(int iDirection)
{
	static unsigned int suiPosition;
	switch(iDirection)
	{
		case 0:
			++suiPosition;
			LedOn(suiPosition%4);
		break;
		case 1:
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

int main()
{
	//IO1DIR = LED0_bm;
	LedInit();
	while(1)
	{
		KeyboardInit();
		//ZADANIE 24
//		switch(eKeyboardRead())
//		{
//			case BUTTON_1:
//				LedStep(RIGHT);
//			break;
//			case BUTTON_2:
//				LedStep(LEFT);
//			break;
//			default:
//				break;
//		}
	}
}

