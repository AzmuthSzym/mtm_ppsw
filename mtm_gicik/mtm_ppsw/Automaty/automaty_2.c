#include "led.h"
#include "keyboard.h"

void Delay(int iHowLongDelay) 
{
	int iMiliSecond = 5997; 
	unsigned int uiCounter; 
	char cCharIncrementation;
	
	for(uiCounter=0; uiCounter < (iHowLongDelay*iMiliSecond); uiCounter++) {
		cCharIncrementation++; 
	}
}

int main(){

	enum LedState{STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};
	enum LedState eLedState = STATE0;
	LedInit();
	KeyboardInit();

	while(1)
	{
		switch(eLedState){
			case STATE0:
				LedStepRight();
				eLedState = STATE1;
				break;
			case STATE1:
				LedStepRight();
				eLedState = STATE2;
				break;
			case STATE2:
				LedStepRight();
				eLedState = STATE3;
				break;
			case STATE3:
				LedStepLeft();
				eLedState = STATE4;
				break;
			case STATE4:
				LedStepLeft();
				eLedState = STATE5;
				break;
			case STATE5:
				LedStepLeft();
				eLedState = STATE0;
				break;
		}
		Delay(100);
	}
}
