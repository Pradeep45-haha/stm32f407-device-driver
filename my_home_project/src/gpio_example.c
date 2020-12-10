/*
 * GPIO.C
 *
 *  Created on: 01-Nov-2019
 *      Author: emes
 */


#include "stdint.h"
#include "stddef.h"
#include "gpio.h"
#include <string.h>


void delay(void)
{
	uint32_t i = 0;
	for(i = 0; i < 50000; i++);
}

int main (void)
{
	GPIO_Handle_t Gpio_pin;

	Gpio_pin.pGPIOx = GPIOA;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_INPUT;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_MEDIUM;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_PUSH_PULL;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_10;
	GPIO_PeriClockControl(Gpio_pin.pGPIOx,ENABLE);
	GPIO_DeInit(Gpio_pin.pGPIOx);
	GPIO_Init(Gpio_pin);

	while(1)
	{
	GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_10,SET);
	delay();
	}
}
