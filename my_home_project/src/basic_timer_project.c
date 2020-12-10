/*
 * basic_timer.c
 *
 *  Created on: 27-May-2020
 *      Author: emes
 */

#include "stm32f4.h"
#include "basic_timer.h"
#include "gpio.h"

BasicTim_Handle_t Basic_tim6;
uint16_t passed_time;

//GPIO pin initilize function
void GPIO_Inits(void)
{
	GPIO_Handle_t Gpio_pin;

	Gpio_pin.pGPIOx = GPIOA;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_OUTPUT;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_MEDIUM;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_PUSH_PULL;
	//Gpio_pin.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;//OR
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_DOWN;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_10;
	GPIO_PeriClockControl(Gpio_pin.pGPIOx,ENABLE);//This reset GPIO port A

	GPIO_DeInit(Gpio_pin.pGPIOx);
	GPIO_Init(Gpio_pin);
}

int main (void)
{
	Basic_tim6.pTIMx  = TIM6;
	Basic_tim6.Basic_timer_config.Auto_Relod_Preload = AUTO_RELOAD_PRELOAD_ENABLE;
	Basic_tim6.Basic_timer_config.Master_Mode_Selection = MASTER_MODE_RESET;
	Basic_tim6.Basic_timer_config.One_Pulse_Mode = ONE_PULSE_MODE_DISABLE;
	Basic_tim6.Basic_timer_config.Update_Disable = UPDATE_ENABLE;
	Basic_tim6.Basic_timer_config.Update_Request_Source = UPDATE_REQUEST_SOURCE_COUNTER;
	//Basic_tim6.Basic_timer_config.Update_Interrupt = UPDATE_INTERRUPT_ENABLE;
	Basic_tim6.Basic_timer_config.Basic_Timer_Prescler = 63999;
	Basic_tim6.Basic_timer_config.Basic_Timer_Auto_Reload_value = 500;
	BASIC_TIMER_PeriClockControl(&Basic_tim6, ENABLE);
	//BASIC_TIMER_IRQITConfig(TIM6_DAC, ENABLE);
	BASIC_TIMER_Init(Basic_tim6);
	GPIO_Inits();

	while(1)
	{
		while(!Basic_tim6.pTIMx->SR & (1 << BASIC_TIM_SR_UIF));
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,SET);
		Basic_tim6.pTIMx->SR &= ~(1 << BASIC_TIM_SR_UIF);
		while(!Basic_tim6.pTIMx->SR & (1 << BASIC_TIM_SR_UIF));
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,RESET);
		Basic_tim6.pTIMx->SR &= ~(1 << BASIC_TIM_SR_UIF);
	}
	return 0;
}

/*void TIM6_DAC_IRQHandler(void)
{
	Basic_tim6.pTIMx->SR &= ~(1 << BASIC_TIM_SR_UIF);
	GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,SET);
	while(!Basic_tim6.pTIMx->SR & (1 << BASIC_TIM_SR_UIF));
	GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,RESET);

}*/



