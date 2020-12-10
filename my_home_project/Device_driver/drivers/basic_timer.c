/*
 * basic_timer.c
 *
 *  Created on: 25-May-2020
 *      Author: emes
 */


#include "basic_timer.h"
#include "rcc.h"


//API SUPPORTED BY THIS DRIVER
void BASIC_TIMER_PeriClockControl(BasicTim_Handle_t *pBASIC_TIMERx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pBASIC_TIMERx->pTIMx == TIM6)
		{
			TIM6_PCLK_EN();
		}else
		{
			TIM7_PCLK_EN();
		}
	}else
	{
		if(pBASIC_TIMERx->pTIMx == TIM6)
		{
			TIM6_PCLK_DI();
		}else
		{
			TIM7_PCLK_DI();
		}
	}
}


void BASIC_TIMER_Init(BasicTim_Handle_t BASIC_TIMER_handle)
{
	uint16_t temp = 0;

	//CONFIGURATION OF CR1 REGISTER
	temp |= (BASIC_TIMER_handle.Basic_timer_config.Auto_Relod_Preload << BASIC_TIM_CR1_ARPE);
	temp |= (BASIC_TIMER_handle.Basic_timer_config.One_Pulse_Mode << BASIC_TIM_CR1_OPM);
	temp |= (BASIC_TIMER_handle.Basic_timer_config.Update_Disable << BASIC_TIM_CR1_UDIS);
	temp |= (BASIC_TIMER_handle.Basic_timer_config.Update_Request_Source << BASIC_TIM_CR1_URS);


	//PROGRAM TIMER CR1 REGISTER
	BASIC_TIMER_handle.pTIMx->CR1 = temp;

	temp = 0;
	//CONFIGURATION OF CR2 REGISTER
	temp |= (BASIC_TIMER_handle.Basic_timer_config.Master_Mode_Selection << BASIC_TIM_CR2_MMS);

	//PROGRAM CR2 REGISTER
	BASIC_TIMER_handle.pTIMx->CR2 = temp;

	temp = 0;
	//CONFIGURATION OF DATA INTERRUPT ENABLE REGISTER
	temp |= (BASIC_TIMER_handle.Basic_timer_config.Update_DMA_Request << BASIC_TIM_DIER_UDE);
	temp |= (BASIC_TIMER_handle.Basic_timer_config.Update_Interrupt << BASIC_TIM_DIER_UIE);

	//PROGRAM DATA INTERRUPT ENABLE REGISTER
	BASIC_TIMER_handle.pTIMx->DIER = temp;

	temp = 0;
	//PROGRAM PRESCALER VALUE IN PSC REGISTER
	BASIC_TIMER_handle.pTIMx->PSC = BASIC_TIMER_handle.Basic_timer_config.Basic_Timer_Prescler;

	//PROGRAM AUTO RELOAD REGISTER
	BASIC_TIMER_handle.pTIMx->ARR = BASIC_TIMER_handle.Basic_timer_config.Basic_Timer_Auto_Reload_value;

	//ENABLE COUNTER
	BASIC_TIMER_handle.pTIMx->CR1 |= (1 << BASIC_TIM_CR1_CEN);

}


void BASIC_TIMER_DeInit(BasicTim_Handle_t *pBASIC_TIMERx)
{

	if(pBASIC_TIMERx->pTIMx == TIM6)
	{
		TIM6_REG_RESET();
	}else
	{
		TIM7_REG_RESET();
	}
}


void BASIC_TIMER_GET_TIME(BasicTim_Handle_t BASIC_TIMER_handle)
{
	uint32_t APB1_clock_value;
	uint32_t Counter_freq;
	uint32_t time1;

	//GET THE VALUE OF ARR REGISTER
	//BASIC_TIMER_handle.Auto_Reload_value = BASIC_TIMER_handle.pTIMx->ARR;

	//GET THE VALUE OF PSC REGISTER
	BASIC_TIMER_handle.Prescaler_Value = BASIC_TIMER_handle.pTIMx->PSC;

	//GET THE APB1 CLOCK FERQUENCY
	APB1_clock_value = RCC_PCLK1_VALUE();

	Counter_freq = (APB1_clock_value/(BASIC_TIMER_handle.Prescaler_Value + 1));

	time1 = (BASIC_TIMER_handle.pTIMx->CNT/Counter_freq);

	BASIC_TIMER_handle.Time_Passed = time1;

}


//BASIC TIMER INTRREPUT
void BASIC_TIMER_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
 if (EnorDi==ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//PROGRAM ISER0 REGISTER
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber <64 )
		{
			//PROGRAM ISER1 REGISTER
			*NVIC_ISER1 |= (1 << IRQNumber % 32);
		}
		else if(IRQNumber >= 64 && IRQNumber <96 )
		{
			//PROGRAM ISER2 REGISTER
			*NVIC_ISER2 |= (1 << IRQNumber % 64);
		}

	}else
	{
		if(IRQNumber <= 31)
		{
			//PROGRAM ICER0 REGISTER
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber <64 )
		{
			//PROGRAM ICER1 REGISTER
			*NVIC_ICER1 |= (1 << IRQNumber % 32);
		}
		else if(IRQNumber >= 64 && IRQNumber <96 )
		{
			//PROGRAM ICER2 REGISTER
			*NVIC_ICER2 |= (1 << IRQNumber % 64);
		}
	}
}


void BASIC_TIMER_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{

}


void BASIC_TIMER_IRQHandling(uint8_t PinNumber)
{

}







