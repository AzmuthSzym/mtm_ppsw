#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE (1<<0)
#define COUNTER_RESET (1<<1)
#define PRESCALE_FREQ 15
#define INTERRUPT_ON_MR0 (1<<0)
#define INTERRUPT_FLAG (1<<0)
#define RESET_ON_MR0 (1<<1)

void InitTimer0(void)
{
	T0TCR = T0TCR|COUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime)
{
	T0TCR = (T0TCR | COUNTER_RESET);
	T0TCR = (T0TCR & (~COUNTER_RESET));
	while(T0TC < (uiTime*PRESCALE_FREQ)) {
	}
}

void InitTimer0Match0(unsigned int uiDelayTime)
{
	T0MR0 = (uiDelayTime * PRESCALE_FREQ);
	T0MCR = (T0MCR | INTERRUPT_ON_MR0 | RESET_ON_MR0);
	T0TCR = (T0TCR | COUNTER_RESET);
	T0TCR = (T0TCR & (~COUNTER_RESET));
	T0TCR = (T0TCR | COUNTER_ENABLE);
}

void WaitOnTimer0Match0(void)
{
	while((T0IR & INTERRUPT_FLAG) == 0){
	}
	T0IR = INTERRUPT_FLAG;
}
