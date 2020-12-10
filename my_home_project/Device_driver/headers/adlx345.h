/*
 * adlx345.h
 *
 *  Created on: 02-Dec-2020
 *      Author: emes
 */

#ifndef HEADERS_ADLX345_H_
#define HEADERS_ADLX345_H_

#include "stm32f4.h"
#include "i2c.h"
#include "spi.h"
#include "gpio.h"


#define ADLX_ADDRESS       0x1D
#define ADLX345_BASEADDR   0x0


#define ADLX_345_DEVID				0x00
#define ADLX_345_THRESH_TAP			0x1D
#define ADLX_345_OFSX				0x1E
#define ADLX_345_OFSY				0x1F
#define ADLX_345_OFSZ				0x20
#define ADLX_345_DUR				0x21
#define ADLX_345_Latent				0x22
#define ADLX_345_Window				0x23
#define ADLX_345_					0x24
#define ADLX_345_THRESH_INACT		0x25
#define ADLX_345_TIME_INACT			0x26
#define ADLX_345_ACT_INACT_CTL		0x27
#define ADLX_345_THRESH_FF			0x28
#define ADLX_345_TIME_FF			0x29
#define ADLX_345_TAP_AXES			0x2A
#define ADLX_345_ACT_TAP_STATUS		0x2B
#define ADLX_345_BW_RATE			0x2C
#define ADLX_345_POWER_CTL			0x2D
#define ADLX_345_INT_ENABLE			0x2E
#define ADLX_345_INT_MAP			0x2F
#define ADLX_345_INT_SOURCE			0x30
#define ADLX_345_DATA_FORMAT		0x31
#define ADLX_345_DATAX0				0x32
#define ADLX_345_DATAX1				0x33
#define ADLX_345_DATAY0				0x34
#define ADLX_345_DATAY1				0x35
#define ADLX_345_DATAZ0				0x36
#define ADLX_345_DATAZ1				0x37
#define ADLX_345_FIFO_CTL			0x38
#define ADLX_345_FIFO_STATUS		0x39



/*****************API FOR ADLX345 OPERATION*************/

void ADLX345_Config(uint8_t mode);
void ADLX345_GetData(uint16_t axis_x, uint16_t axis_y, uint16_t axis_z);



#endif /* HEADERS_ADLX345_H_ */
