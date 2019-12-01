#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

#define DETECTOR_bm (1<<10)

enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo
{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
};

struct Servo sServo;

enum DetectorState {ACTIVE, INACTIVE};

void DetectorInit(){
	IO0DIR = IO0DIR&(~DETECTOR_bm);
}

enum DetectorState eReadDetector(){
	if((IO0PIN&DETECTOR_bm)==0){
		return ACTIVE;
	}
	else{
		return INACTIVE;
	}
}

void Automat(){
	
	switch(sServo.eState){
		case CALLIB:
			if(eReadDetector() == INACTIVE)
			{
				LedStepLeft();
			}
			else
			{
				sServo.eState = IDLE;
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPosition = 0;
			}
			break;
		case IDLE:
			if(sServo.uiDesiredPosition != sServo.uiCurrentPosition)
			{
				sServo.eState = IN_PROGRESS;
			}
			else
			{
				sServo.eState = IDLE;
			}
			break;
		case IN_PROGRESS:
			if(sServo.uiCurrentPosition < sServo.uiDesiredPosition)
			{
				LedStepRight();
				sServo.uiCurrentPosition++;
			}
			else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition)
			{
				LedStepLeft();
				sServo.uiCurrentPosition--;
			}
			else
			{
				sServo.eState = IDLE;
			}
	}
}

void ServoCallib()
{
	sServo.eState = CALLIB;
	while(sServo.eState != IDLE){};
}

void ServoGoTo(unsigned int uiPosition)
{
	sServo.uiDesiredPosition = uiPosition;
	sServo.eState = IN_PROGRESS;
	while(sServo.eState != IDLE){};
}

void ServoInit(unsigned int uiServoFrequency)
{
	Timer0Interrupts_Init(1000000/uiServoFrequency,&Automat);
	LedInit();
	DetectorInit();
	ServoCallib();
	while(sServo.eState != IDLE) {}
}
