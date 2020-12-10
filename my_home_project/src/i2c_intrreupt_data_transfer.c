/*
 * i2c_intrreupt_data_transfer.c
 *
 *  Created on: 06-May-2020
 *      Author: emes
 */

//I2C1_SCL--> GPIO B6
//I2C1_SDA--> GPIO B7


#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "i2c.h"
#include "gpio.h"

#define My_address 		0x61
#define Slave_address 	0x68


void delay(void)
{
	uint32_t i = 0;
	for(i = 0; i < 500000; i++);
}



void Gpio_I2C_Init(void)
{
	GPIO_Handle_t gpio_I2C1_Handle;

	gpio_I2C1_Handle.pGPIOx = GPIOB;
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_ALTERNATE_FUN;
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_alternate_function = 4;
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_OPEN_DRAIN;
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_HIGH;

	GPIO_PeriClockControl(gpio_I2C1_Handle.pGPIOx, ENABLE);
	//I2C1_SCL
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_6;
	GPIO_Init(gpio_I2C1_Handle);
	//I2C1_SDA
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_7;
	GPIO_Init(gpio_I2C1_Handle);
}

void GPIO_Btn_Init(void){
	GPIO_Handle_t gpio_handle;

	gpio_handle.pGPIOx = GPIOC;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_INPUT;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_DOWN;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_MEDIUM;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_4;
	GPIO_PeriClockControl(GPIOC,ENABLE);

	GPIO_Init(gpio_handle);

}


I2C_Handle_t I2C1_Handle;
void I2C1_Inits(void)
{
	I2C1_Handle.pI2Cx = I2C1;
	I2C1_Handle.I2C_Config_t.I2C_DeviceAddress = My_address;
	I2C1_Handle.I2C_Config_t.I2C_ACKControl = I2C_ACKControl_EN;
	I2C1_Handle.I2C_Config_t.I2C_SCL_Speed = I2C_SCL_SPEED_SM;

	I2C_PeriClockControl(I2C1_Handle.pI2Cx, ENABLE);
	I2C_DeInit(I2C1);

	I2C_Init(&I2C1_Handle);
}


uint8_t data[32];



int main(void)
{
	uint8_t commandcode, len = 0;

	Gpio_I2C_Init();
	GPIO_Btn_Init();
	I2C1_Inits();

	I2C_IRQInterruptConfig(I2C1_IRQ_EV, ENABLE);
	I2C_IRQInterruptConfig(I2C1_IRQ_ER, ENABLE);



	while(1){

	while(!GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_4));
	delay();

	commandcode = 0x51;
	//SEND THE COMMAND TO I2C SLAVE
	while(I2C_Master_SendDataIT(&I2C1_Handle, &commandcode, 1, Slave_address) != I2C_READY);

	//RECEIVE THE DATA SEND BY SLAVE
	while(I2C_Master_ReceiveDataIT(&I2C1_Handle, &len, 1, Slave_address) != I2C_READY);

	//SEND COMMAND TO I2C SLAVE
	commandcode = 0x52;
	while(I2C_Master_SendDataIT(&I2C1_Handle, &commandcode, 1, Slave_address) != I2C_READY);

	//RECEIVE FULL DATA FROM SLAVE
	while(I2C_Master_ReceiveDataIT(&I2C1_Handle, data, len, Slave_address) != I2C_READY);

	}
	return 0;
}



void I2C1_EV_IRQHandler(void)
{
	I2C_EVENT_IRQHandling(&I2C1_Handle);
}


void I2C1_ER_IRQHandler(void)
{
	I2C_ERROR_IRQHandling(&I2C1_Handle);
}


void I2C_ApplicationEventCallBack(I2C_Handle_t *pI2CHandle , uint8_t AppEV)
{
	if(AppEV == I2C_EV_TX_CMPLT)
	{

	}else if(AppEV == I2C_EV_RX_CMPLT)
	{

	}else if(AppEV == I2C_ERROR_AF)
	{
		I2C_Close_Rep(pI2CHandle);

		//GENERTAE THE STOP CONDITION
		I2C_Generate_stop(pI2CHandle->pI2Cx);

		while(1);
	}

}


