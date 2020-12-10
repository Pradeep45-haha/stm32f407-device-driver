/*
 * usart_rx.c
 *
 *  Created on: 07-Jun-2020
 *      Author: emes
 */

#include "stm32f4.h"
#include "usart.h"
#include "gpio.h"


GPIO_Handle_t USART_gpio;
USART_Handle_t USART_init;

void delay(void)
{
	uint32_t i = 0;
	for(i = 0; i < 50000; i++);
}

/*void GPIO_Inits(void)
{
	GPIO_Handle_t Gpio_pin;

	Gpio_pin.pGPIOx = GPIOA;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_OUTPUT;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_MEDIUM;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_PUSH_PULL;
	//Gpio_pin.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;//OR
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_DOWN;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_10;
	GPIO_PeriClockControl(Gpio_pin.pGPIOx,ENABLE);

	GPIO_DeInit(Gpio_pin.pGPIOx);
	GPIO_Init(Gpio_pin);
}*/

void USART_Gpio_init(GPIO_Handle_t USART_gpio)
{
	USART_gpio.pGPIOx = GPIOA;
	USART_gpio.GPIO_PinConfig.GPIO_Pin_alternate_function = 7;
	USART_gpio.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_ALTERNATE_FUN;
	USART_gpio.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;
	USART_gpio.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_MEDIUM;
	USART_gpio.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_PUSH_PULL;

	USART_gpio.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_3;
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(USART_gpio);
}


void USART2_init(USART_Handle_t USART_init)
{
	USART_init.pUSARTx = USART2;
	USART_init.USART_config_t.NoOf_Stop_Bits = USART_STOPBITS_1;
	USART_init.USART_config_t.USART_Baud = USART_STD_BAUD_9600;
	USART_init.USART_config_t.USART_Parity_Control = USART_PARITY_DISABLE;
	USART_init.USART_config_t.USART_HWF_FLOW_Control = USART_HW_FLOW_CTRL_NONE;
	USART_init.USART_config_t.USART_Mode = USART_MODE_ONLY_RX;
	USART_init.USART_config_t.USART_Word_Len = USART_WORDLEN_8BITS;

	USART_Init(&USART_init);
}

int main(void)
{

	USART_Gpio_init(USART_gpio);
	USART2_init(USART_init);
	USART_Peripheral_EnorDi(USART2, ENABLE);

	char data[5];
	while(1)
	{
		USART_Receive_Data(&USART_init, (uint8_t *)&data, 4);
		data[4] = '\n';

	}
}


