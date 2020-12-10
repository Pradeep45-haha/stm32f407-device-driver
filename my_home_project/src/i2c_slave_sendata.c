//I2C1_SCL--> GPIO B10
//I2C1_SDA--> GPIO B11


#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "i2c.h"
#include "gpio.h"


#define My_address 		0x45



void delay(void)
{
	uint32_t i = 0;
	for(i = 0; i < 500000; i++);
}


void Gpio_I2C_Init(void)
{
	GPIO_Handle_t gpio_I2C2_Handle;

	gpio_I2C2_Handle.pGPIOx = GPIOB;
	gpio_I2C2_Handle.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_ALTERNATE_FUN;
	gpio_I2C2_Handle.GPIO_PinConfig.GPIO_Pin_alternate_function = 4;
	gpio_I2C2_Handle.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_OPEN_DRAIN;
	gpio_I2C2_Handle.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;
	//gpio_I2C2_Handle.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_NO_PULL_UP_DOWN;
	gpio_I2C2_Handle.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_HIGH;

	GPIO_PeriClockControl(gpio_I2C2_Handle.pGPIOx, ENABLE);
	//I2C1_SCL
	gpio_I2C2_Handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_10;
	GPIO_Init(gpio_I2C2_Handle);
	//I2C1_SDA
	gpio_I2C2_Handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_11;
	GPIO_Init(gpio_I2C2_Handle);

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
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_5;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_OUTPUT;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_PUSH_PULL;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;

	GPIO_Init(gpio_handle);

}

I2C_Handle_t I2C2_Handle;
void I2C2_Inits(void)
{
	I2C2_Handle.pI2Cx = I2C2;
	I2C2_Handle.I2C_Config_t.I2C_DeviceAddress = My_address;
	I2C2_Handle.I2C_Config_t.I2C_ACKControl = I2C_ACKControl_EN;
	I2C2_Handle.I2C_Config_t.I2C_SCL_Speed = I2C_SCL_SPEED_SM;

	I2C_PeriClockControl(I2C2_Handle.pI2Cx, ENABLE);
	I2C_DeInit(I2C2);
	//I2C_Peripheral_EnorDi(I2C2, ENABLE);
	I2C_Init(&I2C2_Handle);
}


	uint8_t data[] = "Hello MSP432P40\n";

int main(void)
{
	Gpio_I2C_Init();
	GPIO_Btn_Init();
	I2C2_Inits();

	while(1)
	{

	//I2C_Peripheral_EnorDi(I2C2, ENABLE);
	while(!GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_4));
	GPIO_WriteToOutput_Pin(GPIOC, GPIO_PIN_5, SET);
	delay();
	/*I2C2->CR1 |= (1 << 15);
	delay();
	delay();
	I2C2->CR1 &= ~(1 << 15);
	delay();
	delay();
	I2C1_Inits();
	I2C_Peripheral_EnorDi(I2C2, ENABLE);*/
	I2C_Slave_SendData(&I2C2_Handle, data, strlen((char*)data));
	GPIO_WriteToOutput_Pin(GPIOC, GPIO_PIN_5, RESET);
	}
	return 0;
}
