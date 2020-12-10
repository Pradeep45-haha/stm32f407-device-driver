/*
 * random_no_gen.c
 *
 *  Created on: 20-May-2020
 *      Author: emes
 */


#include "random_no_gen.h"
#include "rcc.h"

//API FOR RNG PERIPHERAL

//RNG PHERIPHERAL CLOCK EN OR DI API
void RNG_PCLK_ENorDI(uint8_t ENorDI)
{
	if(ENorDI == SET)
	{
		RCC_PLL_Config();
		RNG_PCLK_EN();
	}else
	{
		RNG_PCLK_DI();
	}

}

//RNG PERIPHERAL EN OR DISABLE
void RNG_ENorDI(RNG_Handle_t Random_no_gen, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		Random_no_gen.pRNG->CR |= (1 << RNG_CR_RNGEN);
	}else
	{
		Random_no_gen.pRNG->CR &= ~(1 << RNG_CR_RNGEN);
	}
}

//RNG PERIPHERAL INIT
void RNG_INIT(RNG_Handle_t RNG_Config)
{
	RNG_ENorDI(RNG_Config, ENABLE);
	if(RNG_Config.RNG_Config.RNG_Interrupt_EnorDi == RNG_INTERRUPT_EN)
	{
		//ENABLE THE IE BIT IN RNG CR REGISTER
		RNG_Config.pRNG->CR |= (1 << RNG_CR_IE);
	}else
	{
		//DISABLE THE INTERRUPT
		RNG_Config.pRNG->CR &= ~(1 << RNG_CR_IE);
	}
}


//RNG PERIPHERAL DEINIT
void RND_DEINIT()
{
	RNG_REG_RESET();
}

//GNG PERIPHERAL GET RANDOM NUMBER
uint32_t GET_RNG_NO(RNG_Handle_t Random_no_gen)
{
	uint32_t random_no;
	while(!(Random_no_gen.pRNG->SR & 1));

	random_no = Random_no_gen.pRNG->DR;
	return random_no;
}


uint32_t CHECK_RNG_NO(RNG_Handle_t Random_no_gen)
{
	uint32_t temp1, temp2;
	temp1 = GET_RNG_NO(Random_no_gen);
	temp2 = GET_RNG_NO(Random_no_gen);

	if(temp1 & temp2)
	{
		//SAME RANDOM NO IS GENERATED
		return 0;
	}else
	{
		return temp2;
	}

}


//RNG PERIPHERAL INTERRUPT
void RNG_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi)
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


void RNG_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{

}


void RNG_IRQHandling(RNG_Handle_t Random_no_gen)
{
	uint8_t temp1, temp2, temp3;

	//GET THE VALUE OF IE BIT FROM CR REGISTER INTO TEMP1
	temp1 = (Random_no_gen.pRNG->CR & (1 << RNG_CR_IE));
	//GET THE VALUE OF DRDY FLAG IN TEMP2
	temp2 = (Random_no_gen.pRNG->SR & (1 << RNG_SR_DRDY));

	if(temp1 && temp2)
	{
		//THIS INTERRUPT IS CAUSED BY DATA READY FLAG

		//GET THE DATA
		Random_no_gen.ran_num = Random_no_gen.pRNG->DR;

	}

	//GET THE VALUE OF CEIS FLAG IN TEMP2
	temp2 = (Random_no_gen.pRNG->SR & (1 << RNG_SR_CEIS));

	if(temp1 && temp2)
	{
		//THIS INTERRUPT IS CAUSED BY CLOCK ERROR FLAG

		//GET THE VAULE OF CECS FLAG INTO TEMP3
		temp3 = (Random_no_gen.pRNG->SR & (1 << RNG_SR_CECS));

		if(temp2 && temp3)
		{
			//CLOCK ERROR
		}else
		{
			//THE CLOCK ERROR IS DECETED BUT SITUATION IS RECOVERED
		}

	}

	//GET THE VALUE OF SEED ERROR FLAG IN TEMP2
	temp2 = (Random_no_gen.pRNG->SR & (1 << RNG_SR_SEIS));

	if(temp1 && temp2)
	{
		//THIS INTERUPT IS CAUSED BY SEED ERROR

		//GET THE VALUE OF SEDD ERROR CURRENT STATUS IN TEMP3
		temp3 = (Random_no_gen.pRNG->SR & (1 << RNG_SR_SECS));

		if(temp2 && temp3)
		{
			//SEED ERROR
		}else
		{
			//SEED ERROR HAS BEEN RECOVERED
		}
	}

}

//SOME OTHER API
uint8_t RNG_GetFlagStatus(RNG_Handle_t Random_no_gen, uint32_t status_name)
{
	if(Random_no_gen.pRNG->SR & (1 << status_name))
	{
		return SET;
	}else
	{
		return RESET;
	}

}


