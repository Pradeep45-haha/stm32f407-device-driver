/*
 * random_no.c
 *
 *  Created on: 20-May-2020
 *      Author: emes
 */


#include "random_no_gen.h"

RNG_Handle_t Random_no_gen;

void HASH_RNG_IRQHandler(void)
	{
		RNG_IRQHandling(Random_no_gen);
	}

int main(void)
{

	Random_no_gen.pRNG = RNG;
	Random_no_gen.RNG_Config.RNG_Interrupt_EnorDi = RNG_INTERRUPT_EN;

	uint32_t random_n[100];
	(void)random_n;

	RNG_PCLK_ENorDI(ENABLE);
	RNG_ENorDI(Random_no_gen, ENABLE);
	RNG_INIT(Random_no_gen);
	RNG_IRQITConfig(RNG_IRQ, ENABLE);

	while(1)
	{
		HASH_RNG_IRQHandler();
	}

	return 0;
}


