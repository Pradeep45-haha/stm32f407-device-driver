/*
 * led_blink.c
 *
 *  Created on: 14-Mar-2020
 *      Author: emes
 */

#include "stdint.h"
#include "stddef.h"
#include "gpio.h"
#include <string.h>

			/***This program toggles led(GPIO-A_PIN10) forever after a button(GPIO-A_PIN9) is pressed***/

//Time delay function
void delay(void)
{
	uint32_t i = 0;
	for(i = 0; i < 50000; i++);
}

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

//GPIO pin initilize function
void GPIO_Btn_Inits(void)
{
	GPIO_Handle_t Gpio_pin;

	Gpio_pin.pGPIOx = GPIOA;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_INPUT;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_MEDIUM;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_PUSH_PULL;
	//Gpio_pin.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;//OR
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_DOWN;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_9;
	GPIO_PeriClockControl(Gpio_pin.pGPIOx,ENABLE);

	GPIO_Init(Gpio_pin);
}

int main (void)
{
	//GPIO pin initilizing
	GPIO_Inits();
	GPIO_Btn_Inits();

	while(1){
	//Read for button press
	while(GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_9))
	{
	while(1)
		for(int i = 0;i < 5; i++)
	{
	//LED on
	GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,SET);
	for(int i = 0;i < 25; i++)
		{
			delay();
		}
	//LED off
	GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,RESET);
	for(int i = 0;i < 25; i++)
	{
		delay();
	}
	}
	}
	}
}






