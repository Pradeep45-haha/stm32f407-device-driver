/*
 * LT542_driver.c
 *
 *  Created on: 31-Mar-2020
 *      Author
*/
#include "stdint.h"
#include "stddef.h"
#include "LT542(c.a.).h"

//#include "LT542(c.a.).c"

void delay(void)
{
	uint32_t i = 0;
	for(i = 0; i < 200000; i++);
}

int main (void)
{


	while(1)
	{
	Led_display(0);
	for(int i = 0; i < 25; i++)
	{
		delay();
	}

	Led_display(1);
	for(int i = 0; i < 25; i++)
		{
			delay();
		}
	;

	Led_display(2);
	for(int i = 0; i < 25; i++)
		{
			delay();
		}


	Led_display(3);
	for(int i = 0; i < 25; i++)
		{
			delay();
		}


	Led_display(4);
	for(int i = 0; i < 25; i++)
		{
			delay();
		}


	Led_display(5);
	for(int i = 0; i < 25; i++)
		{
			delay();
		}


	Led_display(6);
	for(int i = 0; i < 25; i++)
		{
			delay();
		}


	Led_display(7);
	for(int i = 0; i < 25; i++)
		{
			delay();
		}

	Led_display(8);
	for(int i = 0; i < 25; i++)
		{
			delay();
		}


	Led_display(9);
	for(int i = 0; i < 25; i++)
		{
			delay();
		}



	}

	return 0;
}
