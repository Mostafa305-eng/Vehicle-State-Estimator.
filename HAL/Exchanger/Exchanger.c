/*
 * Exchanger.c
 *
 *  Created on: 29/12/2019
 *      Author: Sherif Adel
 */

#include "std_types.h"
#include "Exchanger.h"
#include "spi.h"
#include "DIO.h"
#include "softwareDelay.h"
#include <stdlib.h>




volatile uint8 u8_Time;
volatile uint8 u8_Speed;
volatile uint8 u8_TempRead;
volatile uint8 gu8_time_Flag;
volatile uint8 gu8_speed_Flag;
char LCD_buffer[16];
/************************************************************************/
/*		               FUNCTIONS' Definition		                    */
/************************************************************************/
/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize The AVR1 as Master
 *
 */

ERROR_STATUS Exhanger_Init(void)
{
	ERROR_STATUS State=E_OK;


	SPI_Cfg_s SPI_cfg=
	{
			SLAVE ,
			MODE_0,
			MSB,
			INTERRUPT,
			SPI_PRESCALER_32,
			Exhanger_RecieveData
	};
	if(SPI_Init(&SPI_cfg)==E_NOK)
	{
		State=E_NOK;
	}
	return State;
}

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Send Time and Speed To measurment ECU
 *
 */
void Exhanger_RecieveData(void)
{
	SPI_ReceiveByte(&u8_TempRead);
	if(gu8_time_Flag==1  )
	{
		SPI_ReceiveByte(&u8_Time);
		gu8_time_Flag=0;
	}
	else if(gu8_speed_Flag==1 )
	{
		SPI_ReceiveByte(&u8_Speed);
		gu8_speed_Flag=0;

	}
	else if(u8_TempRead == 't' )
	{
		gu8_time_Flag=1;


	}
	else if(u8_TempRead == 's' )
    {
		gu8_speed_Flag=1;

	}


	//

}
/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize The AVR2 as Slave
 *
 */

