/*
 * spi_receive.c
 *
 *  Created on: 08-Apr-2020
 *      Author: emes
 */

#include "spi.h"
#include "gpio.h"
#include "string.h"


		/****SPI RECEIVE DATA EXAMPLE****/

//Button GPIO_C4

//SPI1 GPIO PIN

//SPI1-NSS  --> PA4
//SPI1-SCLK --> PA5
//SPI1-MISO --> PA6
//SPI1-MOSI --> PA7

//SPI2 GPIO PIN

//SPI2_NSS--> 	PB12
//SPI2_SCLK-->	PB13
//SPI2_MISO-->	PB14
//SPI2_MOSI-->	PB15

#define COMMAND_LED_CTRL		0x50
#define COMMAND_SENSOR_READ		0x51
#define COMMAND_LED_READ		0x52
#define COMMAND_PRINT			0x53
#define COMMAND_ID_READ			0x54

#define LED_ON		1
#define LED_OFF		0

//ARDUINO UNO ANALOG PIN
#define ANALOG_PIN_0	0
#define ANALOG_PIN_1	1
#define ANALOG_PIN_2	2
#define ANALOG_PIN_3	3
#define ANALOG_PIN_4	4

//LED CONNECTED ON ARDUINO UNO
#define LED_PIN		9



void delay(void)
{
	uint32_t i = 0;
	for(i = 0; i < 500000/2; i++);
}



/*void SPI1_GPIO_Init(void){
	GPIO_Handle_t gpio_handle;

	gpio_handle.pGPIOx = GPIOA;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_alternate_function = 5;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_ALTERNATE_FUN;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_PUSH_PULL;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_MEDIUM;

	GPIO_PeriClockControl(GPIOA,ENABLE);


	//For SCLK
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_5;
	GPIO_Init(gpio_handle);

	//For MISO
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_6;
	GPIO_Init(gpio_handle);

	//For MOSI
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_7;
	GPIO_Init(gpio_handle);

	//For NSS
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_4;
	GPIO_Init(gpio_handle);

	}*/


void SPI2_GPIO_Init(void){
	GPIO_Handle_t gpio_handle;

	gpio_handle.pGPIOx = GPIOB;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_alternate_function = 5;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_ALTERNATE_FUN;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_PUSH_PULL;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_HIGH;

	GPIO_PeriClockControl(GPIOB,ENABLE);

	//For NSS
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_12;
	GPIO_Init(gpio_handle);

	//For SCLK
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_13;
	GPIO_Init(gpio_handle);

	//For MISO
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_14;
	GPIO_Init(gpio_handle);

	//For MOSI
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_15;
	GPIO_Init(gpio_handle);


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

/*void SPI1_Init(void)
{
	SPI_Handle_t spi_handle;

	spi_handle.pSPIx = SPI1;
	spi_handle.SPI_PinConfig.SPI_Bus_config = SPI_BUS_2_UNI_DIR;
	spi_handle.SPI_PinConfig.SPI_Device_mode = SPI_DEVICE_MASTER_MODE;
	spi_handle.SPI_PinConfig.SPI_Clock_speed = SPI_CLOCK_Speed_DIV8;//This produce 2Mhz clock speed
	spi_handle.SPI_PinConfig.SPI_Data_frame_size = SPI_DATA_8_BITS;
	spi_handle.SPI_PinConfig.SPI_Software_slave_mngmt = SPI_SOFTWARE_DISABLE;
	//spi_handle.SPI_PinConfig.SPI_Software_slave_mngmt = SPI_SOFTWARE_ENABLE;
	spi_handle.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
	spi_handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;


	SPI_PeriClockControl(SPI1,ENABLE);
	SPI_Init(&spi_handle);
}*/


void SPI2_Init(void)
{
	SPI_Handle_t spi_handle;

	spi_handle.pSPIx = SPI2;
	spi_handle.SPI_PinConfig.SPI_Bus_config = SPI_BUS_2_UNI_DIR;
	spi_handle.SPI_PinConfig.SPI_Device_mode = SPI_DEVICE_MASTER_MODE;
	spi_handle.SPI_PinConfig.SPI_Clock_speed = SPI_CLOCK_Speed_DIV8;//This produce 2Mhz clock speed
	spi_handle.SPI_PinConfig.SPI_Data_frame_size = SPI_DATA_8_BITS;
	spi_handle.SPI_PinConfig.SPI_Software_slave_mngmt = SPI_SOFTWARE_DISABLE;
	//spi_handle.SPI_PinConfig.SPI_Software_slave_mngmt = SPI_SOFTWARE_ENABLE;
	spi_handle.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
	spi_handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;


	SPI_PeriClockControl(SPI2,ENABLE);
	SPI_Init(&spi_handle);
}

int SPI_Verify_response(uint8_t ack)
{
	if(ack == 0xF5)
	{
		return 1;
	}else{
		return 0;
	}
}

int main (void)
{

	SPI2_GPIO_Init();
	GPIO_Btn_Init();
	SPI2_Init();
	uint8_t dummy_read = 0;
	uint8_t dummy_write = 0xFF;
	uint8_t ackbyte = 0;


	SPI_SSOEConfig(SPI2,ENABLE);

	while(1){

	while(! (GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_4)));
	delay(); //TO AVOID BUTTON DEBOUNCING ISSUE


	//COMMAND LED CONTROL SEND TO SLAVE
	uint8_t data = COMMAND_LED_CTRL;

	//ENABLE THE SPI PERIPHERAL
	SPI_Peripheral_EnorDi(SPI2,ENABLE);

	SPI_Send_Data(SPI2,&data,1);
	//DUMMY READ
	SPI_Recive_Data(SPI2,&dummy_read,1);


	//SEND SOME DUMMY DATA TO FETCH THE RESPONSE FROM SLAVE
	SPI_Send_Data(SPI2,&dummy_write,1);
	//READ THE ACK BYTE RECEIVED
	SPI_Recive_Data(SPI2,&ackbyte,1);

	uint8_t Command_args[2];

	if(SPI_Verify_response(ackbyte) )
	{
		//SEND ARGUMENTS
		Command_args[0] = LED_PIN;
		Command_args[1] = LED_ON;
		SPI_Send_Data(SPI1,Command_args,2);
	}

	while(SPI_GetFlagStatus(SPI2,SPI_SR_BSY));
	SPI_Peripheral_EnorDi(SPI2,DISABLE);

		}

	return 0;
}
