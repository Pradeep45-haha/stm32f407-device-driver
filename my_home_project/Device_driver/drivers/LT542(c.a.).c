/*
 * LT542(c.a.).c
 *
 *  Created on: 01-Apr-2020
 *      Author: emes
 */


/*****This is a driver for LT542(common anode) to display digits on it*****/


#include "gpio.h"



//GPIO PA5
//GPIO PA6
//GPIO PA7
//GPIO PA8
//GPIO PA9
//GPIO PA10
//GPIO PB5
//GPIO PA6



void Led_GPIOA_Inits(void)
{
	GPIO_Handle_t Gpio_pin;

	Gpio_pin.pGPIOx = GPIOA;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_OUTPUT;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_MEDIUM;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_PUSH_PULL;
	//Gpio_pin.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;//OR
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_DOWN;
	GPIO_PeriClockControl(Gpio_pin.pGPIOx,ENABLE);

	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_5;
	GPIO_Init(Gpio_pin);
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_6;
	GPIO_Init(Gpio_pin);
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_7;
	GPIO_Init(Gpio_pin);
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_8;
	GPIO_Init(Gpio_pin);
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_9;
	GPIO_Init(Gpio_pin);
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_10;
	GPIO_Init(Gpio_pin);


}


void Led_GPIOB_Inits(void)
{
	GPIO_Handle_t Gpio_pin;

	Gpio_pin.pGPIOx = GPIOB;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_OUTPUT;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_MEDIUM;
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_PUSH_PULL;
	//Gpio_pin.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;//OR
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_DOWN;
	GPIO_PeriClockControl(Gpio_pin.pGPIOx,ENABLE);

	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_5;
	GPIO_Init(Gpio_pin);
	Gpio_pin.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_6;
	GPIO_Init(Gpio_pin);


}


void Led_display(uint8_t value)
{
	Led_GPIOA_Inits();
	Led_GPIOB_Inits();

	if(value == 0)
	{
		GPIO_WriteToOutput_Port(GPIOA,0xFFFF);
		GPIO_WriteToOutput_Port(GPIOB,0xFFFF);

		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_6,RESET);//f
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_7,RESET);//e
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_8,RESET);//d
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_9,RESET);//c
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOB,GPIO_PIN_5,RESET);//b

	}else if(value == 1)
	{
		GPIO_WriteToOutput_Port(GPIOA,0xFFFF);
		GPIO_WriteToOutput_Port(GPIOB,0xFFFF);
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_7,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOB,GPIO_PIN_5,RESET);//c
	}else if(value == 2)
	{
		GPIO_WriteToOutput_Port(GPIOA,0xFFFF);
		GPIO_WriteToOutput_Port(GPIOB,0xFFFF);
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_5,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_7,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_8,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_9,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,RESET);//b


	}else if(value == 3)
	{
		GPIO_WriteToOutput_Port(GPIOA,0xFFFF);
		GPIO_WriteToOutput_Port(GPIOB,0xFFFF);
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_5,RESET);
		GPIO_WriteToOutput_Pin(GPIOB,GPIO_PIN_5,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_7,RESET);//g
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_8,RESET);//e
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,RESET);//d

	}else if(value == 4)
	{
		GPIO_WriteToOutput_Port(GPIOA,0xFFFF);
		GPIO_WriteToOutput_Port(GPIOB,0xFFFF);
		GPIO_WriteToOutput_Pin(GPIOB,GPIO_PIN_5,RESET);//a
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_5,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_6,RESET);//g
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_8,RESET);//c

	}else if(value == 5)
	{
		GPIO_WriteToOutput_Port(GPIOA,0xFFFF);
		GPIO_WriteToOutput_Port(GPIOB,0xFFFF);
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_5,RESET);//a
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_6,RESET);//f
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_7,RESET);//g
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,RESET);//c
		GPIO_WriteToOutput_Pin(GPIOB,GPIO_PIN_5,RESET);//d

	}else if(value == 6)
	{
		GPIO_WriteToOutput_Port(GPIOA,0xFFFF);
		GPIO_WriteToOutput_Port(GPIOB,0xFFFF);
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_5,RESET);//a
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_6,RESET);//f
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_7,RESET);//g
		GPIO_WriteToOutput_Pin(GPIOB,GPIO_PIN_5,RESET);//e
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_9,RESET);//d
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,RESET);//b

	}else if(value == 7)
	{
		GPIO_WriteToOutput_Port(GPIOA,0xFFFF);
		GPIO_WriteToOutput_Port(GPIOB,0xFFFF);
		GPIO_WriteToOutput_Pin(GPIOB,GPIO_PIN_5,RESET);//a
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_8,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_7,RESET);//c

	}else if(value == 8)
	{
		GPIO_WriteToOutput_Port(GPIOA,0xFFFF);
		GPIO_WriteToOutput_Port(GPIOB,0xFFFF);
		GPIO_WriteToOutput_Pin(GPIOB,GPIO_PIN_5,RESET);//a
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_6,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_7,RESET);//c
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_8,RESET);//d
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_9,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOB,GPIO_PIN_5,RESET);//b


	}else if(value == 9)
	{
		GPIO_WriteToOutput_Port(GPIOA,0xFFFF);
		GPIO_WriteToOutput_Port(GPIOB,0xFFFF);
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_5,RESET);//a
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_6,RESET);//b
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_7,RESET);//c
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_8,RESET);//d
		GPIO_WriteToOutput_Pin(GPIOB,GPIO_PIN_5,RESET);//f
		GPIO_WriteToOutput_Pin(GPIOA,GPIO_PIN_10,RESET);//g

	}


}
