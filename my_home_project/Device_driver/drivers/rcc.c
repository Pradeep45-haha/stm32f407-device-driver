/*
 * rcc.c
 *
 *  Created on: 12-May-2020
 *      Author: emes
 */


#include "rcc.h"
#include "stdint.h"
#include "stddef.h"


//API TO GET THE VAUE OF CLOCK
uint32_t RCC_PLL(void)
{

	return 0;
}


uint32_t ahb_prescalers[8] = {2,4,8,16,64,128,256,512};
uint32_t apb1_prescalers[4] = {2,4,8,16};
uint32_t apb2_prescalers[4] = {2,4,8,16};

uint32_t RCC_PCLK1_VALUE(void)
{
	uint32_t pclk1,temp = 0,temp1 = 0;
	uint8_t ahb_prescaler,apb1_prescaler;
	uint8_t sysclk = 0;
	sysclk |= ((RCC->CFGR >> 2) & 0X3);

	//FOR SYSTEM CLOCK
	if(sysclk == 0)
	{
		pclk1 = 16000000;
	}else if(sysclk == 1)
	{
		pclk1 = 8000000;
	}else if(sysclk == 3)
	{
		pclk1 = RCC_PLL();
	}

	//FOR AHB PRESCALER
	temp |= ((RCC->CFGR >> 4) & 0xF);

	if(temp < 8)
	{
		ahb_prescaler = 1;
	}
	else
	{
		ahb_prescaler = ahb_prescalers[temp - 8];
	}

	//FOR APB1 PRESCALER
	temp1 |= ((RCC->CFGR >> 10) & 0x7);

	if(temp1 < 4)
		{
			apb1_prescaler = 1;
		}
		else
		{
			apb1_prescaler = apb1_prescalers[temp1 - 4];
		}

	pclk1 = ((pclk1/ahb_prescaler)/apb1_prescaler);
	return pclk1;
}


uint32_t RCC_PCLK2_VALUE(void)
{
	uint32_t pclk2,temp = 0,temp1 = 0;
	uint8_t ahb_prescaler,apb2_prescaler;
	uint8_t sysclk = 0;
	sysclk |= ((RCC->CFGR >> 2) & 0X3);

	//FOR SYSTEM CLOCK
	if(sysclk == 0)
	{
		pclk2 = 16000000;
	}else if(sysclk == 1)
	{
		pclk2 = 8000000;
	}else if(sysclk == 2)
	{
		pclk2 = RCC_PLL();
	}

	//FOR AHB PRESCALER
	temp |= ((RCC->CFGR >> 4) & 0xF);

	if(temp < 8)
	{
		ahb_prescaler = 1;
	}
	else
	{
		ahb_prescaler = ahb_prescalers[temp - 8];
	}

	//FOR APB2 PRESCALER
	temp1 |= ((RCC->CFGR >> 13) & 0x7);

	if(temp1 < 4)
		{
			apb2_prescaler = 1;
		}
		else
		{
			apb2_prescaler = apb2_prescalers[temp1 - 4];
		}

	pclk2 = ((pclk2/ahb_prescaler)/apb2_prescaler);
	return pclk2;

}


//APIS TO CONFIGURE DIFFERENT CLOCK
void RCC_PLL_Config(void)
{

	//FIRST DISABLE MAIN PLL
	RCC->CR &= ~(1 << RCC_CR_PLLON);

	//SELECT PLL CLK SOURCE
	RCC->PLLCFGR &= ~(1 << RCC_PLL_CFGR_PLLSRC);//HSI 16Mhz

	//CONFIGURE MAIN PLL DIVISION FACTOR FOR MAIN SYSTEM CLOCK
	RCC->PLLCFGR &= ~(1 << RCC_PLL_CFGR_PLLP0);    //DIVISION FACTOR OF 2
	RCC->PLLCFGR &= ~(1 << RCC_PLL_CFGR_PLLP1);

	//CONFIGUR MAIN PLL MULTIPLICATOIN FACTOR FOR VC0
	RCC->PLLI2SCFGR |= (50 << RCC_PLL_CFGR_PLLN); //MULTIPLICATION FACTOR OF 50

	//CONFIGURE DIVISION FACTOR FOR MAIN PLL AND AUDIO PLL INPUT CLOCK
	RCC->PLLI2SCFGR |= (10 << RCC_PLL_CFGR_PLLM0); //DIVISION FACTOR OF 10

	//PLL MAIN DIVISION FACTOR FOR RNG CLOCK
	RCC->PLLCFGR |= (2 << RCC_PLL_CFGR_PLLQ0);	   //DIVISION FACTOR OF 2

	//ENABLE PLL
	RCC->CR |= (1 << RCC_CR_PLLON);

	//WAIT UNTILL PLL IS READY
	while(!(RCC->CR & (1 << RCC_CR_PLLRDY)));


}
















