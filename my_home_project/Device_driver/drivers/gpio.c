/*
 * gpio.c
 *
 *  Created on: 02-Nov-2019
 *      Author: emes
 */


#include "gpio.h"
#include "stdint.h"
#include "stddef.h"

#define __vo volatile



//API SUPPORTED BY THIS DRIVER


void GPIO_Init(GPIO_Handle_t GPIO_handle)
{
	//CHECK FOR GPIO PIN MODE
	uint32_t temp1 = 0;
	if(GPIO_handle.GPIO_PinConfig.GPIO_Pin_mode <= GPIO_PIN_MODE_ANALOG)
	{
		temp1 = (GPIO_handle.GPIO_PinConfig.GPIO_Pin_mode << (2 * GPIO_handle.GPIO_PinConfig.GPIO_Pin_number));
		//RESET THE MODER REGISTER
		GPIO_handle.pGPIOx->MODER &= ~(0x3 << (2 * GPIO_handle.GPIO_PinConfig.GPIO_Pin_number));
		//PROGRAM THE MODER REGISTER
		GPIO_handle.pGPIOx->MODER |= temp1;

	}else
	{

	}

	//PROGRAM FOR PIN SPEED
	temp1 = 0;
	temp1 = (GPIO_handle.GPIO_PinConfig.GPIO_Pin_speed << (2 * GPIO_handle.GPIO_PinConfig.GPIO_Pin_number));
	//RESET OSPEED REGISTER
	GPIO_handle.pGPIOx->OSPEEDR &= ~(0x3 << (2 * GPIO_handle.GPIO_PinConfig.GPIO_Pin_number));
	//PROGRAM OSPEED REGISTER
	GPIO_handle.pGPIOx->OSPEEDR |= temp1;

	//PROGRAM FOR PIN OUTPUT TYPE
	temp1 = 0;
	temp1 = (GPIO_handle.GPIO_PinConfig.GPIO_Pin_Output_type << (GPIO_handle.GPIO_PinConfig.GPIO_Pin_number));
	//RESET OUTPUT TYPE REGISTER
	GPIO_handle.pGPIOx->OTYPER &= ~(0x3 << (GPIO_handle.GPIO_PinConfig.GPIO_Pin_number));
	//PROGRAM FOR OUTPUT TYPE REGISTER
	GPIO_handle.pGPIOx->OTYPER |= temp1;

	//PROGRAM FOR PIN PULL UP AND PUL DOWN
	temp1 = 0;
	temp1 = (GPIO_handle.GPIO_PinConfig.GPIO_Pin_Pu_Pd_control << (2 * GPIO_handle.GPIO_PinConfig.GPIO_Pin_number));
	//RESET PUPD REGISTER
	GPIO_handle.pGPIOx->PUPDR &= ~(0x3 << (2 * GPIO_handle.GPIO_PinConfig.GPIO_Pin_number));
	//PROGRAM PUPD REGISTER
	GPIO_handle.pGPIOx->PUPDR |= temp1;


	//PROGRAM FOR GPIO PIN ALTERNATE FUNCTION
	if(GPIO_handle.GPIO_PinConfig.GPIO_Pin_mode == GPIO_PIN_MODE_ALTERNATE_FUN)
	{
		uint8_t temp1 = 0 , temp2 = 0;
		temp1 = ((GPIO_handle.GPIO_PinConfig.GPIO_Pin_number) / 8);//FOR AFR REGISTER
		temp2 = ((GPIO_handle.GPIO_PinConfig.GPIO_Pin_number) % 8);//FOR AFR REGISTER BITS POSITION
		//RESET AFR REGISTER
		GPIO_handle.pGPIOx->AFR[temp1] &= ~(0xF << (4*temp2));
		//PROGRAM AFR REGISTER
		GPIO_handle.pGPIOx->AFR[temp1] |= (GPIO_handle.GPIO_PinConfig.GPIO_Pin_alternate_function << (4*temp2));

	}
}


void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();

	}else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();

	}else if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();

	}else if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();

	}else if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();

	}else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();

	}else if(pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();

	}else if(pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();

	}else if(pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();

	}else if(pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();

	}
}


void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
		{
			if(pGPIOx == GPIOA)
			{
				GPIOA_PCLK_EN();
			}else if(pGPIOx == GPIOB)
			{
				GPIOB_PCLK_EN();
			}else if(pGPIOx == GPIOC)
			{
				GPIOC_PCLK_EN();
			}else if(pGPIOx == GPIOD)
			{
				GPIOD_PCLK_EN();
			}else if(pGPIOx == GPIOE)
			{
				GPIOE_PCLK_EN();
			}else if(pGPIOx == GPIOB)
			{
				GPIOB_PCLK_EN();
			}else if(pGPIOx == GPIOF)
			{
				GPIOF_PCLK_EN();
			}else if(pGPIOx == GPIOG)
			{
				GPIOG_PCLK_EN();
			}else if(pGPIOx == GPIOH)
			{
				GPIOH_PCLK_EN();
			}else if(pGPIOx == GPIOI)
			{
				GPIOI_PCLK_EN();
			}
		}else
		{
			if(pGPIOx == GPIOA)
			{
					GPIOA_PCLK_DI();
			}else if(pGPIOx == GPIOB)
			{
				GPIOB_PCLK_DI();
			}else if(pGPIOx == GPIOC)
			{
				GPIOC_PCLK_DI();
			}else if(pGPIOx == GPIOD)
			{
				GPIOD_PCLK_DI();
			}else if(pGPIOx == GPIOE)
				{
				GPIOE_PCLK_DI();
			}else if(pGPIOx == GPIOB)
			{
				GPIOB_PCLK_DI();
			}else if(pGPIOx == GPIOF)
			{
				GPIOF_PCLK_DI();
			}else if(pGPIOx == GPIOG)
			{
				GPIOG_PCLK_DI();
			}else if(pGPIOx == GPIOH)
			{
				GPIOH_PCLK_DI();
			}else if(pGPIOx == GPIOI)
			{
				GPIOI_PCLK_DI();
			}
		}
}


//DATA READ
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx , uint8_t GPIO_pin)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> GPIO_pin) & 0x00000001);
	return value;
}


uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR ;
	return value;
}


//DATA WRITE
void GPIO_WriteToOutput_Pin(GPIO_RegDef_t *pGPIOx , uint8_t GPIO_pin , uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1 << GPIO_pin);
	}else
	{
		pGPIOx->ODR &=  ~(1 << GPIO_pin);
	}

}


void GPIO_WriteToOutput_Port(GPIO_RegDef_t *pGPIOx , uint16_t Value)
{
	pGPIOx->ODR = Value;
}


//TOGGLE PIN
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}


//GPIO INTRREPUT
void GPIO_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	 if (EnorDi==ENABLE)
	    {
	    	if(IRQNumber <= 31)
	    	{
	    		//PROGRAM ISER0 REGISTER
	    		*NVIC_ISER0 |= (1 << IRQNumber);
	    	}
	    	else if(IRQNumber > 31 && IRQNumber <64 )
	    	{
	    		//PROGRAM ISER1 REGISTER
	    		*NVIC_ISER1 |= (1 << IRQNumber % 32);
	    	}
	    	else if(IRQNumber >= 64 && IRQNumber <96 )
	    	{
	    		//PROGRAM ISER2 REGISTER
	    		*NVIC_ISER2 |= (1 << IRQNumber % 64);
	    	}

	    }else
	    {
	    	if(IRQNumber <= 31)
	    	{
	    		//PROGRAM ICER0 REGISTER
	    		*NVIC_ICER0 |= (1 << IRQNumber);
	    	}
	      	else if(IRQNumber > 31 && IRQNumber <64 )
	     	{
	      		//PROGRAM ICER1 REGISTER
	      		*NVIC_ICER1 |= (1 << IRQNumber % 32);
	     	}
	       	else if(IRQNumber >= 64 && IRQNumber <96 )
	     	{
	       		//PROGRAM ICER2 REGISTER
	       		*NVIC_ICER2 |= (1 << IRQNumber % 64);
	     	}
	    }
}


void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPL);
	*(NVIC_PR_BASEADDR + (iprx * 4)) |= (IRQPriority << shift_amount);
}


void GPIO_IRQHandling(uint8_t PinNumber)
{
//CLEAR THE PR REGISTERS CORRESPONDING TO THE PIN NUMBER
	if(EXTI->PR & (1 << PinNumber))
	{
		EXTI->PR |= (1 << PinNumber);
	}
}



