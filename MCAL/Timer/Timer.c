/*
 * Timer.c
 *
 *  Created on: 22/12/2019
 *      Author: Sherif Adel
 */

/************************************************************************/
/*				               Includes                                 */
/************************************************************************/
#include "std_types.h"
#include "registers.h"
#include "interrupt.h"
#include "Timer.h"

/************************************************************************/
/*				               Defines                                  */
/************************************************************************/
/**********Timer 0& 1  PreScalars****/
#define T_Prescalar_No    1
#define T_Prescalar_8     2
#define T_Prescalar_64    3
#define T_Prescalar_256   4
#define T_Prescalar_1024  5

/******Timer 2 PreScalars****/
#define T2_Prescalar_No     1
#define T2_Prescalar_8      2
#define T2_Prescalar_32     3
#define T2_Prescalar_64     4
#define T2_Prescalar_128    5
#define T2_Prescalar_256    6
#define T2_Prescalar_1024   7


/*************Global Pointer to Function*************/
 static void (*Timer_Gptr_CBK[3])(void)={NULL,NULL,NULL};

/************************************************************************/
/*		                Global and static Variables                     */
/************************************************************************/
uint8 gu8_Timer0_PreScallar;
uint8 gu8_Timer1_PreScallar;
uint8 gu8_Timer2_PreScallar;

static uint8 gu8_Timer0_started;
static uint8 gu8_Timer1_started;
static uint8 gu8_Timer2_started;

/************************************************************************/
/*		         TIMER FUNCTIONS' Definition		                    */
/************************************************************************/
/**
 * Input: Pointer to a structure contains the information needed to initialize the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Initiates the module.
 *
 */
ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg)
{
	/********************Inital State*****************************/
	ERROR_STATUS State=E_OK;

	switch(Timer_cfg->Timer_CH_NO)
	{
	/********************Timer 0*****************************/
	case TIMER_CH0:

		Timer_Gptr_CBK[0]=Timer_cfg->Timer_Cbk_ptr;  /****CALL BACK FUNC.***/

		switch(Timer_cfg->Timer_Prescaler)
		{
		case TIMER_PRESCALER_NO	:
			gu8_Timer0_PreScallar=T_Prescalar_No;
			break;

		case TIMER_PRESCALER_8:
			gu8_Timer0_PreScallar=T_Prescalar_8;
			break;

		case TIMER_PRESCALER_64:
			gu8_Timer0_PreScallar=T_Prescalar_64;
			break;

		case TIMER_PRESCALER_256:
			gu8_Timer0_PreScallar=T_Prescalar_256;
			break;

		case TIMER_PRESCALER_1024:
			gu8_Timer0_PreScallar=T_Prescalar_1024;
			break;

		default:
			State=E_NOK;
			break;
		}
		/********************Timer 0 Mode*****************************/
		switch(Timer_cfg->Timer_Mode)
		{
		case TIMER_MODE:
			TCCR0=0x00;
			break;

		case COUNTER_UP_MODE:
			TCCR0=0x00;
			gu8_Timer0_PreScallar=0x07;
			break;

		case COUNTER_DOWN_MODE:
			TCCR0=0x00;
			gu8_Timer0_PreScallar=0x06;
			break;

		default:
			State=E_NOK;
			break;
		}
		/********************Timer 0 Interrupt*****************************/
		switch(Timer_cfg->Timer_Polling_Or_Interrupt)
		{
		case TIMER_POLLING_MODE:
			TIMSK |=0x00;
			break;

		case TIMER_INTERRUPT_MODE:
			TIMSK |=(1<<0);
			break;

		default:
			State=E_NOK;
			break;
		}
		break;
		/********************Timer 1*****************************/
		case TIMER_CH1:

			Timer_Gptr_CBK[1]=Timer_cfg->Timer_Cbk_ptr;  /****CALL BACK FUNC.***/

			switch(Timer_cfg->Timer_Prescaler)
			{
			case TIMER_PRESCALER_NO	:
				gu8_Timer1_PreScallar=T_Prescalar_No;
				break;

			case TIMER_PRESCALER_8:
				gu8_Timer1_PreScallar=T_Prescalar_8;
				break;

			case TIMER_PRESCALER_64:
				gu8_Timer1_PreScallar=T_Prescalar_64;
				break;

			case TIMER_PRESCALER_256:
				gu8_Timer1_PreScallar=T_Prescalar_256;
				break;

			case TIMER_PRESCALER_1024:
				gu8_Timer1_PreScallar=T_Prescalar_1024;
				break;

			default:
				State=E_NOK;
			}
			/********************Timer 1 Mode*****************************/
			switch(Timer_cfg->Timer_Mode)
			{
			case TIMER_MODE:
				TCCR1=0x0000;
				break;

			case COUNTER_UP_MODE:
				TCCR1=0x0000;
				gu8_Timer1_PreScallar=0x07;
				break;

			case COUNTER_DOWN_MODE:
				TCCR0=0x00;
				gu8_Timer1_PreScallar=0x06;
				break;

			default:
				State=E_NOK;
				break;
			}
			/********************Timer 1 Interrupt*****************************/
			switch(Timer_cfg->Timer_Polling_Or_Interrupt)
			{
			case TIMER_POLLING_MODE:
				TIMSK |=0x00;
				break;

			case TIMER_INTERRUPT_MODE:
				TIMSK |=(1<<2);
				break;

			default:
				State=E_NOK;
				break;

			}
			break;
			/********************Timer 2*****************************/
			case TIMER_CH2:

				Timer_Gptr_CBK[2]=Timer_cfg->Timer_Cbk_ptr;  /****CALL BACK FUNC.***/

				switch(Timer_cfg->Timer_Prescaler)
				{
				case TIMER_PRESCALER_NO	:
					gu8_Timer2_PreScallar=T2_Prescalar_No;
					break;

				case TIMER_PRESCALER_8:
					gu8_Timer2_PreScallar=T2_Prescalar_8;
					break;

				case TIMER_PRESCALER_32:
					gu8_Timer2_PreScallar=T2_Prescalar_32;
					break;

				case TIMER_PRESCALER_64:
					gu8_Timer2_PreScallar=T2_Prescalar_64;
					break;

				case TIMER_PRESCALER_128:
					gu8_Timer2_PreScallar=T2_Prescalar_128;
					break;

				case TIMER_PRESCALER_256:
					gu8_Timer2_PreScallar=T2_Prescalar_256;
					break;

				case TIMER_PRESCALER_1024:
					gu8_Timer2_PreScallar=T2_Prescalar_1024;
					break;

				default:
					State=E_NOK;
					break;
				}
				/********************Timer_2 Mode*****************************/
				switch(Timer_cfg->Timer_Mode)
				{
				case TIMER_MODE:
					TCCR2=0x00;
					break;
				case COUNTER_UP_MODE:
					ASSR=0x00;
					break;

				case COUNTER_DOWN_MODE:
					ASSR=0x00;
					break;

				default:
					State=E_NOK;
					break;
				}
				/********************Timer_2 Interrupt*****************************/
				switch(Timer_cfg->Timer_Polling_Or_Interrupt)
				{
				case TIMER_POLLING_MODE:
					TIMSK |=0x00;
					break;

				case TIMER_INTERRUPT_MODE:
					TIMSK |=(1<<6);
					break;

				default:
					State=E_NOK;
					break;

				}

	}
return State;
}

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_Count: The start value of the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function strats the needed timer.
 *
 */
ERROR_STATUS Timer_Start(uint8 Timer_CH_NO, uint16 Timer_Count)
{

	ERROR_STATUS State=E_OK;
	switch(Timer_CH_NO)
	{
	case TIMER_CH0:
		TCCR0 |=gu8_Timer0_PreScallar;
		TCNT0 =(uint8)Timer_Count;
		gu8_Timer0_started=1;
		break;

	case TIMER_CH1:
		TCCR1 |=gu8_Timer1_PreScallar;
		TCNT1 =Timer_Count;
		gu8_Timer1_started=1;
		break;

	case TIMER_CH2:
		TCCR2 |=gu8_Timer2_PreScallar;
		TCNT0 =(uint8)Timer_Count;
		gu8_Timer2_started=1;
		break;

	default:
		State=E_NOK;
		break;

	}

return State;

}


/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function stops the needed timer.
 *
 */
ERROR_STATUS Timer_Stop(uint8 Timer_CH_NO)
{
	ERROR_STATUS State=E_OK;

	switch(Timer_CH_NO)
	{
	case TIMER_CH0:
		TCNT0=0;
		if(gu8_Timer0_started==1)
		{
		TCCR0 &=~gu8_Timer0_PreScallar;
		}
		else
		{
			State=E_NOK;
		}
		break;

	case TIMER_CH1:
		TCNT1=0;
		if(gu8_Timer1_started==1)
		{
		TCCR1 &=~gu8_Timer1_PreScallar;
		}
		else
		{
			State=E_NOK;
		}
		break;

	case TIMER_CH2:
		TCNT2=0;

		if(gu8_Timer2_started==1)
		{
		TCCR2 &=~gu8_Timer2_PreScallar;
		}
		else
		{
			State=E_NOK;
		}
		break;

	default:
		State=E_NOK;
		break;
	}
return 	State;
}

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return if the flag of the timer is raised or not.
 *
 */
ERROR_STATUS Timer_GetStatus(uint8 Timer_CH_NO, bool* Data)
{
	ERROR_STATUS State=E_OK;
	switch(Timer_CH_NO)
	{
	case TIMER_CH0:
		* Data=TIFR &(1<<0);
		break;

	case TIMER_CH1:
		* Data=(TIFR &(1<<2))>>2;
		break;

	case TIMER_CH2:
		* Data=(TIFR &(1<<6))>>6;
		break;

	default:
		State=E_NOK;
		break;
	}
return State;

}

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return the value of the timer.
 *
 */
ERROR_STATUS Timer_GetValue(uint8 Timer_CH_NO, uint16* Data)
{
	ERROR_STATUS State=E_OK;
	switch(Timer_CH_NO)
	{
	case TIMER_CH0:
		* Data=TCNT0;
		break;

	case TIMER_CH1:
		* Data=TCNT1;
		break;

	case TIMER_CH2:
		* Data=TCNT2;
		break;

	default:
		State=E_NOK;
		break;
	}
return State;


}


void Delay(void)
{
	uint32 counter=0;
	uint8 data;
	for(counter=0;counter<=5000;counter++)
	{
	Timer_GetStatus(TIMER_CH2,&data);
		while(!data)
		{
			Timer_GetStatus(TIMER_CH2,&data);
		}
	TIFR |=(1<<0);
	}

}
/***********Timer0 ISR*********/
ISR(TIMER0_OVF_vect)
{
	if(NULL !=Timer_Gptr_CBK[0])
	{
		Timer_Gptr_CBK[0]();
	}
}
/***********Timer1 ISR*********/
ISR(TIMER1_OVF_vect)
{
	if(NULL !=Timer_Gptr_CBK[1])
	{
		Timer_Gptr_CBK[1]();
	}
}
/***********Timer2 ISR*********/
ISR(TIMER2_OVF_vect)
{
	if(NULL !=Timer_Gptr_CBK[2])
	{
		Timer_Gptr_CBK[2]();
	}
}
