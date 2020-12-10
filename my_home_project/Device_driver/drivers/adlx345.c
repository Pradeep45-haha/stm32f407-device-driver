/*
 * adlx345.c
 *
 *  Created on: 02-Dec-2020
 *      Author: emes
 */
#include "adlx345.h"

//I2C1_SCL--> GPIO B6
//I2C1_SDA--> GPIO B7

#define My_address 		0x61

GPIO_Handle_t gpio_I2C1_Handle;
I2C_Handle_t I2C1_Handle;

void Gpio_I2C_Init(void)
{
	gpio_I2C1_Handle.pGPIOx = GPIOB;
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_ALTERNATE_FUN;
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_alternate_function = 4;
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_OPEN_DRAIN;
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;
	gpio_I2C1_Handle.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_HIGH;

	//I2C1_SCL--> GPIO B6
	//I2C1_SDA--> GPIO B7
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


void ADLX345_Config(uint8_t mode)
{
	uint8_t sendData[2] = {ADLX_345_POWER_CTL, 8};

	//SET MEASURE BIT IN POWER_CTL REG
	I2C_Master_SendData(&I2C1_Handle, (uint8_t*)&sendData, 2, ADLX_ADDRESS);

	sendData[0] = ADLX_345_DATA_FORMAT;
	sendData[1] = 15;
	//CONFIGURE SPI, RANGE & FULL RESOLUTION BIT IN DATA_FORMAT REG
	I2C_Master_SendData(&I2C1_Handle, (uint8_t*)&sendData, 2, ADLX_ADDRESS);

	sendData[0] = ADLX_345_FIFO_CTL;
	sendData[1] = 128;
	//CONFIGURE FIFO MODE BIT IN FIFO_CTL REG
	I2C_Master_SendData(&I2C1_Handle, (uint8_t*)&sendData, 2, ADLX_ADDRESS);


}


void ADLX345_GetData(uint16_t axis_x, uint16_t axis_y, uint16_t axis_z)
{
	//RECEIVE DATA FROM DATAX0,1; DATAY0,1; DATAZ0,1; REGISTER
	uint8_t dataX0 = 0;
	uint8_t dataX1 = 0;
	uint8_t dataY0 = 0;
	uint8_t dataY1 = 0;
	uint8_t dataZ0 = 0;
	uint8_t dataZ1 = 0;

	/*******FOR X AXIS DATA**********/
	uint8_t sendData = ADLX_345_DATAX0;

	//SEND REG ADDRESS TO PERFORM READ OPERATION
	I2C_Master_SendData(&I2C1_Handle, &sendData, 1, ADLX_ADDRESS);

	//READ DATA
	I2C_Master_ReceiveData(&I2C1_Handle, &dataX0, 1, ADLX_ADDRESS);

	sendData = ADLX_345_DATAX1;
	//SEND REG ADDRESS TO PERFORM READ OPERATION
	I2C_Master_SendData(&I2C1_Handle, &sendData, 1, ADLX_ADDRESS);

	//READ DATA
	I2C_Master_ReceiveData(&I2C1_Handle, &dataX1, 1, ADLX_ADDRESS);



	/*******FOR Y AXIS DATA**********/
	sendData = ADLX_345_DATAY0;

	//SEND REG ADDRESS TO PERFORM READ OPERATION
	I2C_Master_SendData(&I2C1_Handle, &sendData, 1, ADLX_ADDRESS);

	//READ DATA
	I2C_Master_ReceiveData(&I2C1_Handle, &dataY0, 1, ADLX_ADDRESS);

	sendData = ADLX_345_DATAY1;
	//SEND REG ADDRESS TO PERFORM READ OPERATION
	I2C_Master_SendData(&I2C1_Handle, &sendData, 1, ADLX_ADDRESS);

	//READ DATA
	I2C_Master_ReceiveData(&I2C1_Handle, &dataY1, 1, ADLX_ADDRESS);



	/*******FOR Z AXIS DATA**********/
	sendData = ADLX_345_DATAZ0;

	//SEND REG ADDRESS TO PERFORM READ OPERATION
	I2C_Master_SendData(&I2C1_Handle, &sendData, 1, ADLX_ADDRESS);

	//READ DATA
	I2C_Master_ReceiveData(&I2C1_Handle, &dataZ0, 1, ADLX_ADDRESS);

	sendData = ADLX_345_DATAZ1;
	//SEND REG ADDRESS TO PERFORM READ OPERATION
	I2C_Master_SendData(&I2C1_Handle, &sendData, 1, ADLX_ADDRESS);

	//READ DATA
	I2C_Master_ReceiveData(&I2C1_Handle, &dataZ1, 1, ADLX_ADDRESS);

}



