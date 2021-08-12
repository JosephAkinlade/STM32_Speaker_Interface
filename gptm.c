#include "stm32f10x.h"                  // Device header
#include <stdbool.h>
#include "gptm.h"


void GPTM_PWM_Init(TIM_TypeDef* timerPort, 
													uint16_t prescale,
													uint16_t reload,
													uint16_t dutyCycle)
{
	timerPort->PSC = prescale;
	timerPort->ARR = reload;
	timerPort->CCR1 = dutyCycle;
	timerPort->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2); // Enable PWM1
	timerPort->CCMR1 |= TIM_CCMR1_OC1PE; //output compare preload enable
	timerPort->CR1 |= TIM_CR1_ARPE; //Buffer the autoreload register
	timerPort->CCER |= TIM_CCER_CC1E; // Enable output capture
	//timerPort->CR1 |= TIM_CR1_CEN; //Enable timer's counter
}

void GPTM_Control(TIM_TypeDef* timerPort, bool timerEn)
{
	if(timerEn)
	{
		timerPort->CR1 |= TIM_CR1_CEN;
	}
	else
	{
		timerPort->CCMR1 &= ~( TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 );
		timerPort->CCMR1 &= ~TIM_CCMR1_OC1PE;
		timerPort->CR1 &= ~TIM_CR1_ARPE; 
		timerPort->CCER &= ~TIM_CCER_CC1E; 
		timerPort->CR1 &= ~TIM_CR1_CEN;
	}
}
