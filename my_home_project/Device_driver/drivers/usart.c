/*
 * usart.c
 *
 *  Created on: 08-May-2020
 *      Author: emes
 */

#include <usart.h>
#include "rcc.h"

//USART API

//USART PHERIPHERAL CLOCK CONTROLS APIS
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	if(pUSARTx == USART1)
	{
		if(EnorDi == ENABLE)
		{
			USART1_PCLK_EN();
		}else
		{
			USART1_PCLK_DI();
		}
	}else if(pUSARTx == USART2)
	{
		if(EnorDi == ENABLE)
		{
			USART2_PCLK_EN();
		}else
		{
			USART2_PCLK_DI();
		}
	}else if(pUSARTx == USART3)
	{
		if(EnorDi == ENABLE)
		{
			USART3_PCLK_EN();
		}else
		{
			USART3_PCLK_DI();
		}
	}else if(pUSARTx == UART4)
	{
		if(EnorDi == ENABLE)
		{
			UART4_PCLK_EN();
		}else
		{
			UART4_PCLK_DI();
		}
	}else if(pUSARTx == UART5)
	{
		if(EnorDi == ENABLE)
		{
			UART5_PCLK_EN();
		}else
		{
			UART5_PCLK_DI();
		}
	}else
	{
		if(EnorDi == ENABLE)
		{
			USART6_PCLK_EN();
		}else
		{
			USART6_PCLK_DI();
		}
	}
}



void USART_Peripheral_EnorDi(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	if(pUSARTx == USART1)
	{
		if(EnorDi == ENABLE)
		{
			USART1->CR1 |= (1 << USART_CR1_UE);
		}else
		{
			USART1->CR1 &= ~(1 << USART_CR1_UE);
		}
	}else if(pUSARTx == USART2)
	{
		if(EnorDi == ENABLE)
		{
			USART2->CR1 |= (1 << USART_CR1_UE);
		}else
		{
			USART2->CR1 &= ~(1 << USART_CR1_UE);
		}
	}else if(pUSARTx == USART3)
	{
		if(EnorDi == ENABLE)
		{
			USART3->CR1 |= (1 << USART_CR1_UE);
		}else
		{
			USART2->CR1 &= ~(1 << USART_CR1_UE);
		}
	}else if(pUSARTx == UART4)
	{
		if(EnorDi == ENABLE)
		{
			UART4->CR1 |= (1 << USART_CR1_UE);
		}else
		{
			UART4->CR1 &= ~(1 << USART_CR1_UE);
		}
	}else if(pUSARTx == UART5)
	{
		if(EnorDi == ENABLE)
		{
			UART5->CR1 |= (1 << USART_CR1_UE);
		}else
		{
			UART5->CR1 &= ~(1 << USART_CR1_UE);
		}
	}else
	{
		if(EnorDi == ENABLE)
		{
			USART6->CR1 |= (1 << USART_CR1_UE);
		}else
		{
			USART6->CR1 &= ~(1 << USART_CR1_UE);
		}
	}
}


//USART BAUDRATE
void USART_Set_Baud_Rate(USART_Handle_t *pUSARTHandle, uint32_t Baud_rate)
{
	//VARIABLE TO HOLD THE APB2 CLOCK
	uint32_t Pclkx;

	uint32_t usartdiv;

	//VARIABLES TO HOLD MANTISSA AND FRACTION VALUES
	uint32_t M_part, F_part;

	uint32_t tempreg = 0;

	//GET THE VALUE OF APB CLOCK
	if((pUSARTHandle->pUSARTx == USART1) || (pUSARTHandle->pUSARTx == USART6))
	{
		//USART1 AND USART6 ARE ON ABP2 BUS
		Pclkx = RCC_PCLK2_VALUE();
	}else
	{
		Pclkx = RCC_PCLK1_VALUE();
	}

	//CHECK FOR OVER8 CONFIGUARTION
	if(pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_OVER8))
	{
		usartdiv = ((25*Pclkx)/(2*Baud_rate));
	}else
	{
		usartdiv = ((25*Pclkx)/(4*Baud_rate));
	}

	//CALCULATE THE MANTISSA PART
	M_part = usartdiv/100;

	//PROGRAM THE MANTISSA PART
	tempreg |= (M_part << 4);

	//EXTRACT THE FRACTIONAL PART
	F_part = (usartdiv - (M_part*100));

	//CALCUTE THE ROUND OFF VALUE OF DECIMAL
	if(pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_OVER8))
	{
		//OVER =1 , OVER SAMPLING BY 8
		F_part = (((F_part*100) + 50)/ 100 & (uint8_t)0x07);
	}else
	{
		F_part = (((F_part*100) + 50)/ 100 & (uint8_t)0xF);
	}

	//PLACE THE FRACTIONAL PART IN BRR REGISTER
	tempreg |= F_part;

	pUSARTHandle->pUSARTx->BRR = tempreg;
}

//USART INIT AND DEINIT APIS
void USART_Init(USART_Handle_t *pUSARTHandle)
{
	uint32_t tempreg = 0;

	//CONFIGURATION OF CR1 REGISTER

	//ENABLE THE CLOCK FOR USART PERIPHERAL
	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

	//ENABLE USART TX AND RX ENGINE
	if(pUSARTHandle->USART_config_t.USART_Mode == USART_MODE_ONLY_RX)
	{
		tempreg |= (1 << USART_CR1_RE);
	}else if(pUSARTHandle->USART_config_t.USART_Mode == USART_MODE_ONLY_TX)
	{
		tempreg |= (1 << USART_CR1_TE);
	}else if(pUSARTHandle->USART_config_t.USART_Mode == USART_MODE_TXRX)
	{
		tempreg |= (1 << USART_CR1_TE)|(1 << USART_CR1_RE);
	}

	//CONFIGURE THE WORD LENGTH
	tempreg |= pUSARTHandle->USART_config_t.USART_Word_Len << USART_CR1_M;

	//CONFIGURE THE PARITY CONTROL BIT
	if(pUSARTHandle->USART_config_t.USART_Parity_Control == USART_PARITY_EN_EVEN)
	{
		//ENABLE PARITY CONTROL
		tempreg |= (1 << USART_CR1_PCE);

		//ENABLE EVEN PARITY
		tempreg &= ~(1 << USART_CR1_PS);
	}else if(pUSARTHandle->USART_config_t.USART_Parity_Control == USART_PARITY_EN_ODD)
	{
		//ENABLE PARITY CONTROL
		tempreg |= (1 << USART_CR1_PCE);

		//ENABLE OOD PARITY
		tempreg |= (1 << USART_CR1_PS);
	}

	//PROGRAM CR1 REGISTER
	pUSARTHandle->pUSARTx->CR1 = tempreg;

	//CONFIGURE CR2 REGISTER
	tempreg = 0;

	//CONFIGURE THE NUMBER OF STOP BITS
	tempreg |= pUSARTHandle->USART_config_t.NoOf_Stop_Bits;

	//PROGRAM THE CR2 REGISTER
	pUSARTHandle->pUSARTx->CR2 = tempreg;

	//CONFIGURE THE CR3 REGISTER
	tempreg = 0;

	if(pUSARTHandle->USART_config_t.USART_HWF_FLOW_Control == USART_HW_FLOW_CTRL_CTS)
	{
		//ENABLE THE CTS FLOW CONTROL
		tempreg |= (1 << USART_CR3_CTSE);
	}else if(pUSARTHandle->USART_config_t.USART_HWF_FLOW_Control == USART_HW_FLOW_CTRL_RTS)
	{
		//ENABLE THE RTS FLOW CONTROL
		tempreg |= (1 << USART_CR3_RTSE);
	}else if(pUSARTHandle->USART_config_t.USART_HWF_FLOW_Control == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		//ENABLE THE CTS FLOW CONTROL
		tempreg |= (1 << USART_CR3_CTSE);

		//ENABLE THE RTS FLOW CONTROL
		tempreg |= (1 << USART_CR3_RTSE);
	}

	//PROGRAM CR3 REGISTER
	pUSARTHandle->pUSARTx->CR3 = tempreg;

	//CONFIGURATION OF BRR REGISTER
	USART_Set_Baud_Rate(pUSARTHandle,  pUSARTHandle->USART_config_t.USART_Baud);
}


void USART_DeInit(USART_RegDef_t *pUSARTx)
{
	if(pUSARTx == USART1)
	{
		USART1_REG_RESET();
	}else if(pUSARTx == USART2)
	{
		USART2_REG_RESET();
	}else if(pUSARTx == USART3)
	{
		USART3_REG_RESET();
	}else if(pUSARTx == UART4)
	{
		UART4_REG_RESET();
	}else if(pUSARTx == UART5)
	{
		UART5_REG_RESET();
	}else
	{
		USART6_REG_RESET();
	}
}


//USART DATA SEND AND RECEIVE APIS
void USART_Send_Data(USART_Handle_t *pUSART_Handle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint16_t *pdata;
	//LOOP OVER UNTILL LEN NO OF BYTES AR TRANSFERRED
	for(uint32_t i = 0;i < Len; i++)
	{
		//WAIT UNTIL TXE FLAG IS SET IS SR
		while(! USART_GetFlagStatus(pUSART_Handle->pUSARTx, USART_SR_TXE));

		//CHECK USART WORD LENGHT
		if(pUSART_Handle->USART_config_t.USART_Word_Len == USART_WORDLEN_9BITS)
		{
			//if 9 BIT LOAD DR WITH 2 BYTES MASKING THE BITS OTHER THAN FIRST 9 BITS
			pdata = (uint16_t*)pTxBuffer;
			pUSART_Handle->pUSARTx->DR = (*pdata&(uint16_t)0x01FF);

			//CHECK FOR USART PARITY CONTROL
			if(pUSART_Handle->USART_config_t.USART_Parity_Control == USART_PARITY_DISABLE)
			{
				//NO PARITY IS TRANSFERRED SO 9 BIT OF DATA IS SENT
				pTxBuffer++;
				pTxBuffer++;
			}else
			{
				//PARITY BIT IS SENT SO 8 BIT OF DATA IS SENT
				pTxBuffer++;
			}

		}else
		{
			//THIS IS 8 BIT DATA TRANSMISSION
			pUSART_Handle->pUSARTx->DR = (*pTxBuffer &(uint8_t)0xFF);

			//INCRESE THE BUFFER ADDRESS
			pTxBuffer++;

		}
	}

}


void USART_Receive_Data(USART_Handle_t *pUSART_Handle, uint8_t *pRxBuffer, uint32_t Len)
{
	//LOOP UNTIL THE LEN NUMBER OF DATA IS NOT RECEIVED
	for(uint32_t i = 0; i < Len; i++)
	{
		//WAIT UNTIL RXNE FLAG IS SET
		while(! USART_GetFlagStatus(pUSART_Handle->pUSARTx, USART_SR_RXNE));

		//CHECK FOR USART DATA WORD LENGHT
		if(pUSART_Handle->USART_config_t.USART_Word_Len == USART_WORDLEN_9BITS)
		{
			//CHECK FOR USART PARITY
			if(pUSART_Handle->USART_config_t.USART_Parity_Control == USART_PARITY_DISABLE)
			{
				//NO PARITY BIT IS USED SO 9 BIT DATA IS RECEIVED
				*pRxBuffer = (pUSART_Handle->pUSARTx->DR &(uint16_t)0x01FF);
				pRxBuffer++;
			}else
			{
				//PARITY IS USED SO 8 BIT IS RECEIVED
				*pRxBuffer = (pUSART_Handle->pUSARTx->DR & (uint8_t)0xFF);
				pRxBuffer++;
			}
		}else
		{
			//THIS IS 8 BIT DATA
			if(pUSART_Handle->USART_config_t.USART_Parity_Control == USART_PARITY_DISABLE)
			{
				//NO PARITY BIT IS USED
				*pRxBuffer = (pUSART_Handle->pUSARTx->DR /*&(uint8_t)0xFF*/);
				pRxBuffer++;
			}else
			{
				//PARITY BIT IS USED
				//READ ONLY SEVEN BITS
				*pRxBuffer = (pUSART_Handle->pUSARTx->DR & (uint8_t)0xFF);
				pRxBuffer++;
			}
		}
	}
}


//USART DATA SEND AND RECIVE APIS WITH IT
uint8_t USART_Send_DataIT(USART_Handle_t *pUSART_Handle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t txstate = pUSART_Handle->TxBusyState;

	if(txstate != USART_BUSY_IN_TX)
	{
		pUSART_Handle->Len = Len;
		pUSART_Handle->pTxBuffer = pTxBuffer;
		pUSART_Handle->TxBusyState = USART_BUSY_IN_TX;


	//IMPELEMENT THE CODE TO ENABLE THE INTERRUPT FOR TXE
	pUSART_Handle->pUSARTx->CR1 |= (1 << USART_CR1_TXEIE);

	//IMPELEMENT THE CODE TO ENABLE THE INTERRUPT FOR TXE
	pUSART_Handle->pUSARTx->CR1 |= (1 << USART_CR1_TCIE);
	}

	return txstate;
}


uint8_t USART_Receive_DataIT(USART_Handle_t *pUSART_Handle, uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t rxstate = pUSART_Handle->RxBusyState;

	if(rxstate != USART_BUSY_IN_RX)
	{
		pUSART_Handle->Len = Len;
		pUSART_Handle->pTxBuffer = pRxBuffer;
		pUSART_Handle->TxBusyState = USART_BUSY_IN_RX;


	//IMPELEMENT THE CODE TO ENABLE THE INTERRUPT FOR RXNE
	pUSART_Handle->pUSARTx->CR1 |= (1 << USART_CR1_RXNEIE);

	}

	return rxstate;

}



//USART IRQ CONFIGURATION AND ISR HANDLING APIS
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

}


void USART_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{

}


void USART_IRQHandling(USART_Handle_t *pUSARTHandle)
{
	uint32_t temp1, temp2, temp3;

	//CHECK FOR TC FLAG
	//CHECK THE STATE OF TC BIT IN THE SR
	temp1 = pUSARTHandle->pUSARTx->SR &(1 << USART_SR_TC);

	//CHECK THE STATE OF TCEIE BIT
	temp2 = pUSARTHandle->pUSARTx->CR1 &(1 << USART_CR1_TXEIE);

	if(temp1 && temp2)
	{
		//TC TRIGGERED THIS INTERRUPT
		//CLOSE THE TRANSMISSION AND CALL APP CALLBACK IF TXLEN IS ZERO
		if(pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
		{
			//CHECK THE TXLEN IF TXLEN IS ZERO CLOSE THE TRANSMISSION
			if(! pUSARTHandle->Len)
			{
				//CLEAR THE TC FLAG
				pUSARTHandle->pUSARTx->SR &= ~(1 << USART_SR_TC);

				//CLEAR THE TCIE CONTROL BIT
				pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_TCIE);

				//RESET BUF ADD TO NULL AND LEN TO ZERO
				pUSARTHandle->Len = 0;
				pUSARTHandle->pTxBuffer = NULL;

				//RESET APPLICATION STATE
				pUSARTHandle->TxBusyState = USART_REDY;

				//CALL THE APP;ICATION CALL BACK EVENT
				USART_AppilicationEventCallBack(pUSARTHandle->pUSARTx,USART_EVENT_TX_CMPLT);
			}
		}

	}

	//CHECK FOR TXE FLAG
	//CHECK THE STATE OF TXE BIT IN SR
	temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_TXE);

	//CHECK THE STATE OF TXEIE BIT
	temp2 = pUSARTHandle->pUSARTx->CR1 &(1 << USART_CR1_TXEIE);

	if(temp1 && temp2)
	{
		//TXE FLAG CAUSED THIS INTERRUPT

		if(pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
		{
			//KEEP SENDING DATA UNTILL TXLEN REACHES TO ZERO
			if(pUSARTHandle->Len > 0)
			{
				//CHECK THE USART_WORD LEN
				if(pUSARTHandle->USART_config_t.USART_Word_Len == USART_WORDLEN_9BITS)
				{
					//IF 9 BIT LOAD THE DR WITH 2 BYTES MASKING THE BITS OTHER THAN FIRST 9 BITS
					pUSARTHandle->pUSARTx->DR = ((*(uint16_t*)pUSARTHandle->pTxBuffer) &(uint16_t)0x01FF);

					//CHECK FOR  USART_PARITY
					if(pUSARTHandle->USART_config_t.USART_Parity_Control == USART_PARITY_DISABLE)
					{
						//NO PARITY IS USED 9 BITS OF DATA IS TRANSMITTED
						pUSARTHandle->pTxBuffer++;
						pUSARTHandle->pTxBuffer++;

						pUSARTHandle->Len--;
					}else
					{
						//PARITY IS USED 8 BIT OF DATA IS TRANSFERREF
						pUSARTHandle->pTxBuffer++;

						pUSARTHandle->Len--;
					}
				}else
				{
					//THIS IS 8 BIT DATA TRANSMISSION
					pUSARTHandle->pUSARTx->DR = (*pUSARTHandle->pTxBuffer& (uint8_t)0xFF);

					//IMPLEMENT THE CODE TO INCREMENT THE BUFFER ADDRESS
					pUSARTHandle->pTxBuffer++;

					pUSARTHandle->Len--;
				}
			}if(pUSARTHandle->Len == 0)
			{
				//CLEAR THE TXEIE BIT
				pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_TXEIE);
			}
		}
	}

	//CHECK FOR RXNE FLAG
	//CHECK THE RXNE BIT IN SR REGISTER
	temp1 = pUSARTHandle->pUSARTx->SR &(1 << USART_SR_RXNE);

	//CHECK THE RXNEIE BIT IN CR1 RREGISTER
	temp2 = pUSARTHandle->pUSARTx->CR1 &(1 << USART_CR1_RXNEIE);

	if(temp1 && temp2)
	{
		//RXNE FLAG CAUSED THIS INTERRUPT

		if(pUSARTHandle->RxBusyState == USART_BUSY_IN_RX)
		{
			if(pUSARTHandle->RxLen > 0)
			{
				//CHECK THE USART WORD_LEN
				if(pUSARTHandle->USART_config_t.USART_Word_Len == USART_WORDLEN_9BITS)
				{
					//9 BITS OF DATA IS RECEIVED IN A FRAME

					//CHECK FOR PARITY
					if(pUSARTHandle->USART_config_t.USART_Parity_Control == USART_PARITY_DISABLE)
					{
						//NO PARITY BIT IS USED , 9 BIT OF DATA WILL BE RECEIVED
						*((uint16_t*)pUSARTHandle->pRxBuffer) = (pUSARTHandle->pUSARTx->DR & (uint16_t)0x01FF);

						//INCREMENT THE pRxBuffer
						pUSARTHandle->pRxBuffer++;
						pUSARTHandle->pRxBuffer++;

						//DECREMENT THE LENGHT
						pUSARTHandle->RxLen--;
					}
				}else
				{
					//ELSE PARITY IS USED
					//8 BITS OF DATA WILL BE RECEIVED
					if(pUSARTHandle->USART_config_t.USART_Parity_Control == USART_PARITY_DISABLE)
					{
						*pUSARTHandle->pRxBuffer = (pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);

						//INCREMENT THE BUFFER
						pUSARTHandle->pRxBuffer++;

						//DECREMENT THE LEN
						pUSARTHandle->RxLen--;
					}else
					{
						//PARITY IS USED WE WILL RECEIVE 7 BITS OF DATA
						*pUSARTHandle->pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0x7F);

						//INCREMENT THE pRXBuffer
						pUSARTHandle->pRxBuffer++;

						//DECREMENT THE LEN
						pUSARTHandle->RxLen--;
					}
				}
			}if(pUSARTHandle->RxLen == 0)
			{
				//DISABLE THE RXNE
				pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_RXNEIE);
				pUSARTHandle->RxBusyState = USART_REDY;
				USART_AppilicationEventCallBack(pUSARTHandle->pUSARTx, USART_EVENT_RX_CMPLT);
			}
		}

	}

	//CHECK FOR CTS FLAG
	//CTS FEATURE IS NOT APPLICABLE FOR UART4 AND UART5
	//CHECK THE STATUS OF CTS BIT IN SR
	temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_CTS);

	//CHECK FOR CTSE BIT IN CR3
	temp2 = pUSARTHandle->pUSARTx->CR3 & (1 << USART_CR3_CTSE);

	//CHECK FOR CTSIE BIT IN IN CR3
	temp3 = pUSARTHandle->pUSARTx->CR3 & (1 << USART_CR3_CTSIE);

	if(temp1 && temp2 && temp3)
	{
		//THIS INTERRUPT IS CAUSED BY CTS FLAG
		//CLEAR THE CTS FLAG
		pUSARTHandle->pUSARTx->SR &= ~(1 << USART_SR_CTS);

		USART_AppilicationEventCallBack(pUSARTHandle->pUSARTx, USART_EVENT_CTS);
	}

	//CHECK FOR IDLE FLAG
	//CHECK THIE IDLE BIT IN SR
	temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_IDLE);

	//CHECK THE STATE IF IDLEIE BIT IN CR1
	temp2 = pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_IDLEIE);

	if(temp1 && temp2 )
	{
		//THIS INTERRUPT IS CAUSED BY IDLE FLAG
		//CLEAR THE IDLE FLAG IN SR
		pUSARTHandle->pUSARTx->SR &= ~(1 << USART_SR_IDLE);

		USART_AppilicationEventCallBack(pUSARTHandle->pUSARTx, USART_EVENT_IDLE);
	}

	//CHECK FOR OVERRUN FLAG DETECTION
	//CHECH THE ORE FLAG IN THE SR
	temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_ORE);

	//CHECK FOR RXNEIE BIT IN CR1
	temp2 = pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_RXNEIE);

	if(temp1 && temp2)
	{
		//THIS INTERRUPT IS CAUSED BY OVERRUN FLAG
		//CLEAR THE ORE FLAG IN SR
		pUSARTHandle->pUSARTx->SR &= ~(1 << USART_SR_ORE);

		USART_AppilicationEventCallBack(pUSARTHandle->pUSARTx, USART_EVENT_ORE);
	}

	//CHECK FOR ERROR FLAG

}



//SOME OTHER API
uint8_t USART_GetFlagStatus(USART_RegDef_t *USARTx, uint32_t FlagName)
{
	if(USART2->SR & (1 << FlagName))
	{
		return SET;
	}else
	{
		return RESET;
	}

}

void USART_AppilicationEventCallBack(USART_RegDef_t *USARTx, uint8_t AppEV)
{

}



