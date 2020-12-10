/*
 * gpio.h
 *
 *  Created on: 06-Nov-2019
 *      Author: emes
 */

#ifndef HEADERS_GPIO_H_
#define HEADERS_GPIO_H_

#include "stdint.h"
#include "stddef.h"

#define __vo volatile
#include "stm32f4.h"


//GPIO PIN CONFIGURATION
typedef struct
{
	uint8_t GPIO_Pin_number;
	uint8_t GPIO_Pin_mode;
	uint8_t GPIO_Pin_speed;
	uint8_t GPIO_Pin_Pu_Pd_control;
	uint8_t GPIO_Pin_Output_type;
	uint8_t GPIO_Pin_alternate_function;

}GPIO_PinConfig_t;


//GPIO PORT CONFIGURATION
typedef struct
{
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handle_t;


//GPIO PIN NUMBER POSSIBLE VALUE
#define GPIO_PIN_0          0
#define GPIO_PIN_1			1
#define GPIO_PIN_2			2
#define GPIO_PIN_3			3
#define GPIO_PIN_4			4
#define GPIO_PIN_5			5
#define GPIO_PIN_6			6
#define GPIO_PIN_7			7
#define GPIO_PIN_8			8
#define GPIO_PIN_9			9
#define GPIO_PIN_10			10
#define GPIO_PIN_11			11
#define GPIO_PIN_12			12
#define GPIO_PIN_13			13
#define GPIO_PIN_14			14
#define GPIO_PIN_15			15


//GPIO PIN MODE POSSIBLE VALUE
#define GPIO_PIN_MODE_INPUT				0
#define GPIO_PIN_MODE_OUTPUT			1
#define GPIO_PIN_MODE_ALTERNATE_FUN		2
#define GPIO_PIN_MODE_ANALOG			3
#define GPIO_PIN_MODE_IT_FT       		4
#define GPIO_PIN_MODE_IT_RT       		5
#define GPIO_PIN_MODE_IT_RFT      		6


//GPIO PIN SPEED POSSIBLE VALUE
#define GPIO_PIN_SPEED_LOW				0
#define GPIO_PIN_SPEED_MEDIUM			1
#define GPIO_PIN_SPEED_HIGH				2
#define GPIO_PIN_SPEED_ULTRA_HIGH		3


//GPIO PIN PULL UP PULL DOWN POSSIBLE VALUE
#define GPIO_PIN_NO_PULL_UP_DOWN		0
#define GPIO_PIN_PULL_UP				1
#define GPIO_PIN_PULL_DOWN				2


//GPIO PIN OUTPUT TYPE POSSIBLE VALUE
#define GPIO_PIN_PUSH_PULL				0
#define GPIO_PIN_OPEN_DRAIN				1




//API SUPPORTED BY THIS DRIVER
void GPIO_Init(GPIO_Handle_t GPIO_handle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

//DATA READ
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx , uint8_t GPIO_pin);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

//DATA WRITE
void GPIO_WriteToOutput_Pin(GPIO_RegDef_t *pGPIOx , uint8_t GPIO_pin , uint8_t Value);
void GPIO_WriteToOutput_Port(GPIO_RegDef_t *pGPIOx , uint16_t Value);

//TOGGLE PIN
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

//GPIO INTRREPUT
void GPIO_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);



#endif /* HEADERS_GPIO_H_ */
