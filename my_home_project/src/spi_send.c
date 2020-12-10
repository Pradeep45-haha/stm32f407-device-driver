/*
 * spi_exmple.c
 *
 *  Created on: 06-Dec-2019
 *      Author: emes
 */

#include "spi.h"
#include "gpio.h"
#include "string.h"

				/****SPI SEND DATA EXAMPLE****/

//Button GPIO C 4

//SPI1 GPIO PIN

//SPI1-NSS  --> PA4
//SPI1-SCLK --> PA5
//SPI1-MISO --> PA6
//SPI1-MOSI --> PA7




void delay(void)
{
	uint32_t i = 0;
	for(i = 0; i < 50000; i++);


}

void SPI1_GPIO_Init(void){
	GPIO_Handle_t gpio_handle;

	gpio_handle.pGPIOx = GPIOA;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_alternate_function = 5;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_mode = GPIO_PIN_MODE_ALTERNATE_FUN;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_Output_type = GPIO_PIN_PUSH_PULL;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control = GPIO_PIN_PULL_UP;
	gpio_handle.GPIO_PinConfig.GPIO_Pin_speed = GPIO_PIN_SPEED_MEDIUM;

	GPIO_PeriClockControl(GPIOA,ENABLE);

	//For NSS
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_4;
	GPIO_Init(gpio_handle);

	//For SCLK
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_5;
	GPIO_Init(gpio_handle);

	//For MISO
	//gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_6;
	//GPIO_Init(gpio_handle);

	//For MOSI
	gpio_handle.GPIO_PinConfig.GPIO_Pin_number = GPIO_PIN_7;
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
void SPI1_Init(void)
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

	//ENABLE THE SPI PERIPHERAL
	//spi_handle.pSPIx->CR1 |= (1 << 6);
}

int main (void)
{
	SPI1_GPIO_Init();
	GPIO_Btn_Init();
	SPI1_Init();

	char data[] = "Hello I am stm discovery board";

	SPI_SSOEConfig(SPI1,ENABLE);

	while(1){
	while(!GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_4));


	//ENABLE THE SPI PERIPHERAL
	SPI_Peripheral_EnorDi(SPI1,ENABLE);
	delay();
	uint8_t data_len = strlen(data);
	SPI_Send_Data(SPI1,&data_len,1);
	SPI_Send_Data(SPI1,(uint8_t*)data,strlen(data));
	while(SPI_GetFlagStatus(SPI1,SPI_SR_BSY));
	SPI1->CR1 &= ~(1 << 6);

	}

	 return 0;
}



