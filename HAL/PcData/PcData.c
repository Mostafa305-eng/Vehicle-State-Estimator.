/*
 * PcData.c
 *
 *  Created on: 29/12/2019
 *      Author: Sherif Adel
 */
#include "std_types.h"
#include "DIO.h"
#include "UART.h"
#include"PcData.h"
/************************************************************************/
/*		               FUNCTIONS' Definition		                    */
/************************************************************************/

/******************* convert only one character to int  ********************/
static uint32 ConvCharToInt(uint8 CHAR){
	return (CHAR - '0');
}
/*************************convert string to int ************************************/

static uint32 ConvStringToInt(uint8 * ptr,uint32 exponent){
	uint32 i,total_number=0,number,digit=1;
	    for(i=0;i<(exponent-1);i++)
	    digit *=10;
	for(i=0;i<exponent;i++){
		number = ConvCharToInt(*(ptr+i));
		total_number += number * digit ;
		digit *=.100000;
	}
	return total_number;
}
/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize the PC module
 *
 */
ERROR_STATUS PcData_init(void)
{
	UART_cfg_s myUart={UART_POLLING,TRANSCEIVER,UART_NO_DOUBLE_SPEED,UART_ONE_STOP_BIT\
			,UART_NO_PARITY,UART_8_BIT,9600,NULL,NULL,NULL};

	UART_Init(&myUart);
}

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Takes Inital values of both speed and time
 *
 *
 */
ERROR_STATUS PcData_Update(uint8 u8_InitTime,uint8 u8_InitSpeed,uint16 u16_Distance)
{
	uint8 u8_UserTimeMessage[]="fetch time : ";
	uint8 u8_UserSpeedMessage[]="speed : ";
	uint8 u8_UserDistanceMessage[]="distance : ";



	uint8 u8_loopCounter=0;
	char buffer[16];




	for (u8_loopCounter=0;u8_loopCounter<13;u8_loopCounter++)
	{
		UART_SendByte(u8_UserTimeMessage[u8_loopCounter]);
	}

	itoa(u8_InitTime,buffer,10);

	for(u8_loopCounter=0;u8_loopCounter<3;u8_loopCounter++)
	{
		UART_SendByte(buffer[u8_loopCounter]);

	}
	UART_SendByte('\r');

	for (u8_loopCounter=0;u8_loopCounter<8;u8_loopCounter++)
	{
		UART_SendByte(u8_UserSpeedMessage[u8_loopCounter]);
	}


	itoa(u8_InitSpeed,buffer,10);

	for(u8_loopCounter=0;u8_loopCounter<3;u8_loopCounter++)
	{
		UART_SendByte(buffer[u8_loopCounter]);

	}

	UART_SendByte('\r');


	for (u8_loopCounter=0;u8_loopCounter<12;u8_loopCounter++)
	{
		UART_SendByte(u8_UserDistanceMessage[u8_loopCounter]);
	}


	itoa(u16_Distance,buffer,10);

	for(u8_loopCounter=0;u8_loopCounter<3;u8_loopCounter++)
	{
		UART_SendByte(buffer[u8_loopCounter]);

	}

	UART_SendByte('\r');


}


