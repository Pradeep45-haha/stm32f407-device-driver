/*
 * i2c.c
 *
 *  Created on: 14-Apr-2020
 *      Author: emes
 */

#include "stdint.h"
#include "stddef.h"
#include "i2c.h"
#include "rcc.h"

//Helpers Functions
static void I2C_Execute_ADDR_Phase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr, uint8_t R_WR);
static void I2C_Clear_ADDR_Flag(I2C_Handle_t *pI2CHandle);


/*****APIs for I2C******/

//I2C PHERIPHERAL CLOCK CONTROLS APIS
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)

		{if(pI2Cx == I2C1)
	{
		I2C1_PCLK_EN();
	}else if(pI2Cx == I2C2)
	{
		I2C2_PCLK_EN();
	}else
	{
		I2C3_PCLK_EN();
	}
		}

	if(EnorDi == DISABLE)
	{
	if(pI2Cx == I2C1)
	{
		I2C1_PCLK_EN();
	}else if(pI2Cx == I2C2)
	{
		I2C2_PCLK_DI();
	}else
	{
		I2C3_PCLK_DI();
	}
	}

}



void I2C_Peripheral_EnorDi(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)

			{if(pI2Cx == I2C1)
		{
			I2C1->CR1 |= (1);
		}else if(pI2Cx == I2C2)
		{
			I2C2->CR1 |= (1);
		}else
		{
			I2C3->CR1 |= (1);
		}
			}

		if(EnorDi == DISABLE)
		{
		if(pI2Cx == I2C1)
		{
			I2C1->CR1 &= ~(1);
		}else if(pI2Cx == I2C2)
		{
			I2C2->CR1 &= ~(1);
		}else
		{
			I2C3->CR1 &= ~(1);
		}
		}
}


//I2C INIT AND DEINIT APIS
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint16_t temp1 = 0;
	pI2CHandle->pI2Cx->CR1 |= (1);
	//PROGRAM THE VALUE OF FREQ
	temp1 = 0;
	temp1 |= RCC_PCLK1_VALUE()/1000000;
	pI2CHandle->pI2Cx->CR2 |= (temp1 & 0x3F);

	//PROGRAM THE DEVICE OWN ADDRESS
	temp1 = 0;
	temp1 = pI2CHandle->I2C_Config_t.I2C_DeviceAddress << 1;
	pI2CHandle->pI2Cx->OAR1 |= temp1;
	pI2CHandle->pI2Cx->OAR1 |= (1 << 14);

	//PROGRAM THE VALUE OF ACK
	temp1 = 0;
	temp1 |= (pI2CHandle->I2C_Config_t.I2C_ACKControl << I2C_CR1_ACK);
	pI2CHandle->pI2Cx->CR1 |= temp1;


	//PROGRAM THE CCR
	uint16_t ccr_value = 0;
	temp1 = 0;

	if(pI2CHandle->I2C_Config_t.I2C_SCL_Speed <= I2C_SCL_SPEED_SM)
	{
		//MODE IS STANDERD MODE
		ccr_value = (RCC_PCLK1_VALUE()/ (2 * pI2CHandle->I2C_Config_t.I2C_SCL_Speed));
		temp1 |= ccr_value & 0xFFF;

	}else
	{
		//MODE IS FAST MODE
		pI2CHandle->pI2Cx->CCR |= (1 << 15);
		pI2CHandle->pI2Cx->CCR |= (pI2CHandle->I2C_Config_t.I2C_FM_DutyCycle << 14);
		if(pI2CHandle->I2C_Config_t.I2C_FM_DutyCycle == I2C_FM_DutyCycle_2)
		{
		ccr_value = (RCC_PCLK1_VALUE()/ (3 * pI2CHandle->I2C_Config_t.I2C_SCL_Speed));
		temp1 |= ccr_value & 0xFFF;

		}else
		{
		ccr_value = (RCC_PCLK1_VALUE()/ (25 * pI2CHandle->I2C_Config_t.I2C_SCL_Speed));
		temp1 |= ccr_value & 0xFFF;

		}

	}
	//PROGRAM THE CCR VLAUE
	pI2CHandle->pI2Cx->CCR |= temp1;

	if(pI2CHandle->I2C_Config_t.I2C_SCL_Speed <= I2C_SCL_SPEED_SM)
		{
		//STANDERD MODE
			temp1 = 0;
			temp1 = (RCC_PCLK1_VALUE()/1000000) + 1;

		}else
		{
		//FAST MODE
			temp1 = 0;
			temp1 = ((RCC_PCLK1_VALUE()*300)/1000000000) + 1;
		}
		pI2CHandle->pI2Cx->TRISE = temp1 & 0x3F; //Necessary to use assignment operation

}


void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{

	{if(pI2Cx == I2C1)
	{
		I2C1_REG_RESET();
	}else if(pI2Cx == I2C2)
	{
		I2C2_REG_RESET();
	}else
	{
		I2C3_REG_RESET();
	}
	}
}


//I2C DATA TRANSFER API
void I2C_Master_SendData(I2C_Handle_t *pI2C_handle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr)
{
	//GENERATE START CONDITION
	I2C_Generate_start(pI2C_handle->pI2Cx);


	//WAIT FOR STAR BIT TO SET
	while(! I2C_GetFlagStatus(pI2C_handle->pI2Cx,I2C_SR1_SB));


	//PUT THE SLAVE ADDRESS AND R/RW BIT IN DR REGISTER
	I2C_Execute_ADDR_Phase(pI2C_handle->pI2Cx, SlaveAddr, READ);

	//CHECK FOR ADDRESS PHASE
	while(! I2C_GetFlagStatus(pI2C_handle->pI2Cx,I2C_SR1_ADDR));

	//CLEAR THE ADDR FLAG
	I2C_Clear_ADDR_Flag(pI2C_handle);

	//SEND THE DATA
	while(Len > 0)
	{
		//WAIT TILL TXE IS SET
		while(! I2C_GetFlagStatus(pI2C_handle->pI2Cx, I2C_SR1_TxE));
		//PUT THE VALUE IN DATA REGISTER
		pI2C_handle->pI2Cx->DR = *pTxbuffer;
		pTxbuffer++;
		Len--;
	}
	//WAIT FOR TXE AND BTF TO BE SET
	while(! I2C_GetFlagStatus(pI2C_handle->pI2Cx, I2C_SR1_TxE));
	while(! I2C_GetFlagStatus(pI2C_handle->pI2Cx, I2C_SR1_BTF));
	//CLOSE THE COMMUNICATION
	I2C_Generate_stop(pI2C_handle->pI2Cx);
}


void I2C_Master_ReceiveData(I2C_Handle_t *pI2C_handle, uint8_t *pRxbuffer, uint32_t Len, uint8_t SlaveAddr)
{
	//ENABLE I2C PERIPHERAL
	//I2C_Peripheral_EnorDi(pI2C_handle->pI2Cx, ENABLE);

	//GENERATE START CONDITION
	I2C_Generate_start(pI2C_handle->pI2Cx);

	//CONFIRM THAT START GENERATOIN IS COMPLETED
	while(! I2C_GetFlagStatus(pI2C_handle->pI2Cx, I2C_SR1_SB));

	//SEND THE ADDRESS OF SLAVE WITH R/RW BIT
	I2C_Execute_ADDR_Phase(pI2C_handle->pI2Cx, SlaveAddr, WRITE);

	//CHECK FOR ADDRESS PHASE
	while(! I2C_GetFlagStatus(pI2C_handle->pI2Cx, I2C_SR1_ADDR));

	//CLEAR ADDR FLAG
	I2C_Clear_ADDR_Flag(pI2C_handle);

	//RECEIVE DATA

	//FOR 1 BYTE
	if(Len == 1)
	{
		//DISABLE ACK IN CR1
		pI2C_handle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);

		//CLEAR ADDR FLAG
		I2C_Clear_ADDR_Flag(pI2C_handle);

		//CHECK FOR RXNE
		while(! I2C_GetFlagStatus(pI2C_handle->pI2Cx, I2C_SR1_RxNE));

		//GENERATE STOP CONDITION
		I2C_Generate_stop(pI2C_handle->pI2Cx);

		//READ THE DATA INTO BUFFER
		*pRxbuffer = pI2C_handle->pI2Cx->DR;


	}

	if(Len > 1)
	{
		//CLEAR ADDR FLAG
		I2C_Clear_ADDR_Flag(pI2C_handle);

		for(uint32_t i = Len; i > 0; i--)
		{
			//WAIT UNTILL RXNE BECOMES 1
			while(! I2C_GetFlagStatus(pI2C_handle->pI2Cx, I2C_SR1_RxNE));

			if(Len == 2)
			{
				//DISABLE ACK BIT
				pI2C_handle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);

				//GENERATE STOP CONDITION
				I2C_Generate_stop(pI2C_handle->pI2Cx);
			}

			//READ THE DATA INTO BUFFER
			*pRxbuffer = pI2C_handle->pI2Cx->DR;

			//INCREMENT THE BUFFER ADDRESS
			pRxbuffer++;


		}
	}
	//RE-ENABLE THE ACK BIT
	if(pI2C_handle->I2C_Config_t.I2C_ACKControl == I2C_ACKControl_EN)
	{
	pI2C_handle->pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
	}

}

void I2C_Slave_SendData(I2C_Handle_t *pI2C_handle, uint8_t *pTxbuffer, uint32_t Len)
{
	//CHECK IF ADDR BIT IS SET
	while(!(pI2C_handle->pI2Cx->SR1 & (1 << I2C_SR1_ADDR)));

	//CLEAR ADDR FLAG
	I2C_Clear_ADDR_Flag(pI2C_handle);

	//SEND DATA
	for(uint16_t temp = 0; temp < Len; temp++)
	{
		//CHECK IF TXE IS EMPTY
		while(!(pI2C_handle->pI2Cx->SR1 & (1 << I2C_SR1_TxE)));

		pI2C_handle->pI2Cx->DR = *pTxbuffer;
		pTxbuffer++;
	}

}

void I2C_Slave_ReceiveData(I2C_Handle_t *pI2C_handle, uint8_t *pRxbuffer, uint32_t Len)
{
	//CHECK IF ADDR BIT IS SET
	while(!pI2C_handle->pI2Cx->SR1 & I2C_SR1_ADDR);

	//CLEAR ADDR FLAG
	I2C_Clear_ADDR_Flag(pI2C_handle);

	//RECEIVE DATA
	for(uint16_t temp = 0; temp < Len; temp++)
	{
		//CHECK IF RXE IS NOT EMPTY
		while(!(pI2C_handle->pI2Cx->SR1 & I2C_SR1_RxNE));

		*pRxbuffer = pI2C_handle->pI2Cx->DR;
		pRxbuffer++;
	}

}

//I2C DATA TRANSFER WITH INT
uint8_t I2C_Master_SendDataIT(I2C_Handle_t *pI2C_handle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr)
{
	uint8_t busystate = 0;
	busystate = pI2C_handle->TxRxState;
	if((busystate != I2C_BUSY_IN_TX)&&(busystate != I2C_BUSY_IN_RX))
	{
		pI2C_handle->pTxBuffer = pTxbuffer;
		pI2C_handle->TxRxState = I2C_BUSY_IN_TX;
		pI2C_handle->TxLen = Len;
		pI2C_handle->RS = 0;
		pI2C_handle->Deviceaddr = SlaveAddr;

		//IMPLEMENT THE CODE TO GENERATE START CONDITION
		I2C_Generate_start(pI2C_handle->pI2Cx);

		//IMPLEMENT THE CODE TO ENABLE ITBUFEN CONTROL BIT
		pI2C_handle->pI2Cx->CR2 |= (1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2C_handle->pI2Cx->CR2 |= (1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2C_handle->pI2Cx->CR2 |= (1 << I2C_CR2_ITERREN);
	}
	return busystate;
}


uint8_t I2C_Master_ReceiveDataIT(I2C_Handle_t *pI2C_handle, uint8_t *pRxbuffer, uint32_t Len, uint8_t SlaveAddr)
{
	uint8_t busystate = 0;
	busystate = pI2C_handle->TxRxState;
	if((busystate != I2C_BUSY_IN_TX)&&(busystate != I2C_BUSY_IN_RX))
	{
		pI2C_handle->pTxBuffer = pRxbuffer;
		pI2C_handle->TxRxState = I2C_BUSY_IN_RX;
		pI2C_handle->RxLen = Len;
		pI2C_handle->RS = 0;
		pI2C_handle->Deviceaddr = SlaveAddr;
		pI2C_handle->Rxsize = Len;

		//IMPLEMENT THE CODE TO GENERATE START CONDITION
		I2C_Generate_start(pI2C_handle->pI2Cx);

		//IMPLEMENT THE CODE TO ENABLE ITBUFEN CONTROL BIT
		pI2C_handle->pI2Cx->CR2 |= (1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2C_handle->pI2Cx->CR2 |= (1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2C_handle->pI2Cx->CR2 |= (1 << I2C_CR2_ITERREN);
	}
	return busystate;

}

//I2C IRQ CONFIGURATION AND ISR HANDLING APIS
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

}


void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{

}


void I2C_EVENT_IRQHandling(I2C_Handle_t *pI2CHandle)
{
	//CHECK IF SB CAUSED AN INTERRUPT
	uint32_t temp1, temp2, temp3;

	temp1 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITEVTEN);
	temp2 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITBUFEN);

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_SB);

	if(temp1 && temp3)
	{
		//SB FLAG CAUSED THE INTERRUPT

		if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
		{
			//EXECUTE ADDR PHASE
			I2C_Execute_ADDR_Phase(pI2CHandle->pI2Cx, pI2CHandle->Deviceaddr, READ);
		}else if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
		{
			//EXECUTE ADDR PHASE
			I2C_Execute_ADDR_Phase(pI2CHandle->pI2Cx, pI2CHandle->Deviceaddr, WRITE);
		}

	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_ADDR);

	if(temp1 && temp3)
	{
		//ADDR FLAG CAUSED THE INTERRUPT
		I2C_Clear_ADDR_Flag(pI2CHandle);
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_BTF);
	if(temp1 && temp3)
	{
		//BTF FLAG CAUSED THE INTERRUPT
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
		{
			if(pI2CHandle->TxLen == 0)
			{
			if(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_TxE))
			{
				if(pI2CHandle->RS == 0)
				{
				I2C_Generate_stop(pI2CHandle->pI2Cx);
				}

				I2C_Close_Trans(pI2CHandle);

				I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_TX_CMPLT);


			}
			}
		}else if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
		{
			if(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_RxNE))
			{
				/*if(pI2CHandle->RS == 0)
				{
				I2C_Generate_stop(pI2CHandle->pI2Cx);
				}*/


			}
		}
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_STOPF);
	if(temp1 && temp3)
	{
		//STOP FLAG CAUSED THE INTERRUPT
		pI2CHandle->pI2Cx->CR1 |= 0x0000;

		//NOTIFY THE APPLICATION THAT STOP IS GENERATED BY MASTER
		I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_STOP);
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_TxE);
	if(temp1 && temp3 && temp2)
	{
		//TXE FLAG CAUSED THE INTERRUPT
		if((pI2CHandle->pI2Cx->SR2 & (1 << I2C_SR2_MSL)))
		{
			if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
			{
				if(pI2CHandle->TxLen > 0)
				{
					pI2CHandle->pI2Cx->DR = (*pI2CHandle->pRxBuffer);
					pI2CHandle->TxLen--;
					pI2CHandle->pTxBuffer++;
				}
			}
		}
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_RxNE);
	if(temp1 && temp3 && temp2)
	{
		if(pI2CHandle->pI2Cx->SR2 & (1 << I2C_SR2_MSL))
		{
		//RXNE FLAG CAUSED THE INTERRUPT
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
			{
				if(pI2CHandle->Rxsize == 1)
				{
					*pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;
					pI2CHandle->RxLen--;
				}

				if(pI2CHandle->Rxsize > 1)
				{
					if(pI2CHandle->RxLen == 2)
					{
						//CLEAR THE ACK
						pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
					}

					*pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;
					pI2CHandle->RxLen--;
					pI2CHandle->pRxBuffer++;
				}
				if(pI2CHandle->RxLen == 0)
				{
					if(pI2CHandle->RS == 0)
					{
						I2C_Generate_stop(pI2CHandle->pI2Cx);

						I2C_Close_Rep(pI2CHandle);

						I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_RX_CMPLT);
					}
				}
			}
	}
	}


}


void I2C_ERROR_IRQHandling(I2C_Handle_t *pI2CHandle)
{
	uint32_t temp1,temp2;

	//Know the status of  ITERREN control bit in the CR2
	temp2 = (pI2CHandle->pI2Cx->CR2) & ( 1 << I2C_CR2_ITERREN);


/***********************Check for Bus error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1<< I2C_SR1_BERR);
	if(temp1  && temp2 )
	{
		//This is Bus error

		//Implement the code to clear the buss error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_BERR);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_BERR);
	}

/***********************Check for arbitration lost error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_ARLO );
	if(temp1  && temp2)
	{
		//This is arbitration lost error

		//Implement the code to clear the arbitration lost error flag
		pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_ARLO);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_ARLO);
	}

/***********************Check for ACK failure  error************************************/

	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_AF);
	if(temp1  && temp2)
	{
		//This is ACK failure error

		//Implement the code to clear the ACK failure error flag
		pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_AF);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_AF);
	}

/***********************Check for Overrun/underrun error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_OVR);
	if(temp1  && temp2)
	{
		//This is Overrun/underrun

		//Implement the code to clear the Overrun/underrun error flag
		pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_OVR);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_OVR);

	}

/***********************Check for Time out error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_TIMEOUT);
	if(temp1  && temp2)
	{
		//This is Time out error

		//Implement the code to clear the Time out error flag
		pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_TIMEOUT);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_TIMEOUT);
	}
}


//HELPER FUNCTION

void I2C_Generate_start(I2C_RegDef_t *pI2Cx)
{
	while(!(pI2Cx->SR2 & (1 << I2C_SR2_BUSY)));
	pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

void I2C_Generate_stop(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
	uint8_t flag_value = 0;
	flag_value = (pI2Cx->SR1 & (1 << FlagName));
	if (flag_value)
		{
			return 1;
		}
	else
		{
			return 0;
		}
}

void I2C_Execute_ADDR_Phase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr ,uint8_t R_WR)
{
	if(R_WR == WRITE)
	{
		SlaveAddr |= SlaveAddr << 1;
		SlaveAddr |= (1);
		pI2Cx->DR = SlaveAddr;

	}else
	{
		SlaveAddr = SlaveAddr << 1;
		SlaveAddr &= ~(1);
		pI2Cx->DR = SlaveAddr;
	}
}

void I2C_Clear_ADDR_Flag(I2C_Handle_t *pI2CHandle)
{
	uint16_t readdata = 0;
	if(pI2CHandle->pI2Cx->SR2 & (1 << I2C_SR2_MSL))
	{
		//DEVICE IS IN MASTER MODE
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
		{
			if(pI2CHandle->Rxsize == 1)
			{
				pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);

				readdata |= (pI2CHandle->pI2Cx->SR1);
				readdata |= (pI2CHandle->pI2Cx->SR2);
				(void)readdata;

			}
		}else
		{
			readdata |= (pI2CHandle->pI2Cx->SR1);
			readdata |= (pI2CHandle->pI2Cx->SR2);
			(void)readdata;
		}
	}else
	{
		//DEVICE IS IN SLAVE MODE
		readdata |= (pI2CHandle->pI2Cx->SR1);
		readdata |= (pI2CHandle->pI2Cx->SR2);
		(void)readdata;
	}
}

void I2C_Clear_OVR_Flag(I2C_RegDef_t *pI2Cx)
{

}


void I2C_Close_Trans(I2C_Handle_t *pI2CHandle)
{
	//IMPLEMENT THE CODE TO DISABLE INTERRUPTS
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);

	pI2CHandle->TxRxState = I2C_READY;
	pI2CHandle->TxLen = 0;
	pI2CHandle->pTxBuffer = NULL;

	//ENABLE ACKING
	if(pI2CHandle->I2C_Config_t.I2C_ACKControl == I2C_ACKControl_EN)
	pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
}


void I2C_Close_Rep(I2C_Handle_t *pI2CHandle)
{
	//IMPLEMENT THE CODE TO DISABLE INTERRUPTS
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);

	pI2CHandle->TxRxState = I2C_READY;
	pI2CHandle->RxLen = 0;
	pI2CHandle->Rxsize = 0;
	pI2CHandle->pRxBuffer = NULL;

	//ENABLE ACKING
	if(pI2CHandle->I2C_Config_t.I2C_ACKControl == I2C_ACKControl_EN)
	pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
}


void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle , uint8_t AppEV)
{

}



