/*
 * SPI.c
 *
 *  Created on: 28/12/2019
 *      Author: Sherif Adel
 */

/************************************************************************/
/*				               Includes                                 */
/************************************************************************/
#include "registers.h"
#include "interrupt.h"
#include "DIO.h"
#include "SPI.h"

/************************************************************************/
/*				               Defines                                  */
/************************************************************************/
/**********SPCR registers*****/
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0

/**********SPSR registers*****/
#define SPIF    7
#define WCOL    6
#define SPI2X   0



/************************************************************************/
/*		                Global and static Variables                     */
/************************************************************************/
static uint8 gu8_Status=0;     /*****Interrupt Mode or Polling*****/
volatile uint8 u8_Recieve_flag=0;
volatile uint8 ReadFlag=0;
volatile uint8 u8_ActualTime;
volatile uint8 u8_ActualSpeed;
static uint8 gu8_RecieveData=0;
volatile uint8 u8_StateFlag=0;
volatile uint8 gu8_time_Flag=0;
volatile uint8 gu8_speed_Flag=0;

/************Static Global Pointer To Function******/
static void (*SPI_GptrFunc)(void)=NULL;




/* Description : SPI Initialization                                              */
/* Input       : SPI_Cfg_s* "Pointer to Struct of SPI Configration" */
/* Output      : Error Checking                                                  */
ERROR_STATUS SPI_Init(SPI_Cfg_s* pstr_SPI_Confg)
{
	ERROR_STATUS State=E_OK;


	/******Enable SPI*****/



	if(NULL!= pstr_SPI_Confg)
	{
		SPI_GptrFunc=pstr_SPI_Confg->CBK_Func;
		SPCR=(1<<SPE);
		switch(pstr_SPI_Confg->u8_SPIMode)
		{
		case MASTER:

			/***********SET SS, MOSI and Clock as OUTPUT***/

			SPCR |=(1<<MSTR);
			DIO_Cfg_s Master_Cfg;
			Master_Cfg.GPIO=GPIOB;
			Master_Cfg.pins=BIT4 |BIT5 |BIT7;
			Master_Cfg.dir=OUTPUT;
			DIO_init(&Master_Cfg);


			/****** Configure MISO Pins as INPUT***/
			DIO_Cfg_s MISO_Cfg;
			MISO_Cfg.GPIO=GPIOB;
			MISO_Cfg.pins=BIT6;
			MISO_Cfg.dir=INPUT;
			DIO_init(&MISO_Cfg);

			switch(pstr_SPI_Confg->u8_InterruptMode)
			{
			case INTERRUPT:
				SPCR |=(1<<SPIE);
				gu8_Status=INTERRUPT;
				break;
			case POLLING:
				SPCR &=~(1<<SPIE);
				gu8_Status=POLLING;
				break;
			default:
				State=E_NOK;
				break;
			}

			switch(pstr_SPI_Confg->u8_DataOrder)
			{
			case MSB:
				SPCR &= ~(1<<DORD);
				break;
			case LSB:
				SPCR |= (1<<DORD);
				break;
			default:
				State=E_NOK;
				break;
			}

			switch(pstr_SPI_Confg->u8_DataMode)
			{
			case MODE_0:
				SPCR &= ~ (1<<CPOL);
				SPCR &= ~ (1<<CPHA);
				break;

			case MODE_1:
				SPCR |=  (1<<CPHA);
				SPCR &= ~(1<<CPOL);
				break;

			case MODE_2:
				SPCR |=  (1<<CPOL);
				SPCR &= ~(1<<CPHA);
				break;

			case MODE_3:
				SPCR |=  (1<<CPOL);
				SPCR |=  (1<<CPHA);
				break;

			default:
				State=E_NOK;
				break;
			}

			switch(pstr_SPI_Confg->u8_Prescaler)
			{
			case SPI_PRESCALER_2:
				SPCR &= ~((1<<SPR1)|(1<<SPR0));
				SPSR |=  (1<<SPI2X);
				break;

			case SPI_PRESCALER_4:
				SPCR &= ~((1<<SPR1)|(1<<SPR0));
				SPSR &= ~(1<<SPI2X);
				break;

			case SPI_PRESCALER_8:
				SPCR |=  (1<<SPR0);
				SPCR &= ~(1<<SPR1);
				SPSR |=  (1<<SPI2X);
				break;

			case SPI_PRESCALER_16:
				SPCR |=  (1<<SPR0);
				SPCR &= ~(1<<SPR1);
				SPSR &= ~(1<<SPI2X);
				break;

			case SPI_PRESCALER_32:
				SPCR |=  (1<<SPR1);
				SPCR &= ~(1<<SPR0);
				SPSR |=  (1<<SPI2X);
				break;

			case SPI_PRESCALER_64:
				SPCR |= (1<<SPR0);
				SPCR |= (1<<SPR1);
				SPSR |= (1<<SPI2X);
				break;

			case SPI_PRESCALER_128:
				SPCR |=  (1<<SPR0);
				SPCR |=  (1<<SPR1);
				SPSR &= ~(1<<SPI2X);
				break;

			default:
				State=E_NOK;
				break;
			}
			break;

			case SLAVE:
				SPCR &=~(1<<MSTR);
				/***********SET SS, MOSI and Clock as INPUT***/
				DIO_Cfg_s Slave_Cfg;
				Master_Cfg.GPIO=GPIOB;
				Master_Cfg.pins=BIT4 |BIT5 |BIT7;
				Master_Cfg.dir=INPUT;
				DIO_init(&Slave_Cfg);

				/****** Configure MIS0 Pins as OUTPUT***/
				DIO_Cfg_s MOSI_Cfg;
				MOSI_Cfg.GPIO=GPIOB;
				MOSI_Cfg.pins=BIT6;
				MOSI_Cfg.dir=OUTPUT;
				DIO_init(&MOSI_Cfg);

				switch(pstr_SPI_Confg->u8_InterruptMode)
				{
				case INTERRUPT:
					SPCR |=(1<<SPIE);
					gu8_Status=INTERRUPT;
					break;
				case POLLING:
					SPCR &=~(1<<SPIE);
					gu8_Status=POLLING;
					break;
				default:
					State=E_NOK;
					break;
				}
				break;
				default:
					State=E_NOK;
					break;

		}

	}

	DIO_Write(GPIOB,BIT4,HIGH);
	return State;
}


/* Description : SPI Send Byte                                                    */
/* Input       :                                                                  */
/* Output      : Error Checking                                                   */
/* INOUT       : u8_Data 					                                      */

ERROR_STATUS SPI_SendByte(uint8 u8_Data)
{
	ERROR_STATUS State=E_OK;
	DIO_Write(GPIOB,BIT4,LOW);
	static uint8 u8_Interrupt_flag=0;

	switch(gu8_Status)
	{
	case INTERRUPT:
		SPDR=u8_Data;

		break;
	case POLLING:
		SPDR=u8_Data;
		if(SPI_GetStatus(&u8_Interrupt_flag)==E_NOK)
		{
			State=E_NOK;
		}
		while(!u8_Interrupt_flag)
		{
			if(SPI_GetStatus(&u8_Interrupt_flag)==E_NOK)
			{
				State=E_NOK;
			}

		}

		/********Clear Interrupt Flag***/
		SPSR |=(1<<SPIF);
		break;
	}


	return State;
	DIO_Write(GPIOB,BIT4,HIGH);
}

/**
 * @brief: Receive one byte over SPI
 * @param:
 * Input : None
 * Output: *ptru8_Data "points to where received byte is going to be stored in"
 * @return: Error codes if present
 */
ERROR_STATUS SPI_ReceiveByte(uint8 *ptru8_Data)
{
	ERROR_STATUS State=E_OK;
	static uint8 u8_Interrupt_flag=0;

	switch(gu8_Status)
	{
	case INTERRUPT:

			*ptru8_Data=SPDR;


		break;
	case POLLING:
		*ptru8_Data=SPDR;
		if(SPI_GetStatus(&u8_Interrupt_flag)==E_NOK)
		{
			State=E_NOK;
		}
		while(!u8_Interrupt_flag)
		{
			if(SPI_GetStatus(&u8_Interrupt_flag)==E_NOK)
			{
				State=E_NOK;
			}
		}
		//gu8_Recieve_Flag=1;
		/********Clear Interrupt Flag***/
		SPSR |=(1<<SPIF);
		break;
	}
	return State;

}



ERROR_STATUS SPI_GetStatus(uint8 *u8_Data)
{
	ERROR_STATUS State=E_OK;
	*u8_Data= (SPSR &(1<<SPIF))>>SPIF ;
	return State;
}

ISR(SPI_STC_vect)
{


	if(NULL !=SPI_GptrFunc)
	{
		SPI_GptrFunc();
	}
}


