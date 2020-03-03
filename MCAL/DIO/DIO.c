/*
 *	File name: DIO.C
 *	Author : Sherif Adel
 *	version: 1.0
 *
 */
#include "std_types.h"
#include "registers.h"
#include "DIO.h"


/************************************************************************/
/*						Functions definition                             	*/
/************************************************************************/

/*
 *Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
 *Output: No output
 *In/Out:
 *Description: This function can set the direction of a full port, a nibble
 * 			  or even one pin.
 */
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info)
{
	ERROR_STATUS State=E_OK;

	switch(DIO_info->GPIO)
	{
	case GPIOA:
		if(DIO_info->dir==INPUT)
		{
			PORTA_DIR &= ~DIO_info->pins;
		}
		else if(DIO_info->dir==OUTPUT)
		{
			PORTA_DIR |= DIO_info->pins;
		}
		break;

	case GPIOB:
		if(DIO_info->dir==INPUT)
		{
			PORTB_DIR &= ~DIO_info->pins;
		}
		else if(DIO_info->dir==OUTPUT)
		{
			PORTB_DIR |= DIO_info->pins;
		}
		break;

	case GPIOC:
		if(DIO_info->dir==INPUT)
		{
			PORTC_DIR &= ~DIO_info->pins;
		}
		else if(DIO_info->dir==OUTPUT)
		{
			PORTC_DIR |= DIO_info->pins;
		}
		break;

	case GPIOD:
		if(DIO_info->dir==INPUT)
		{
			PORTD_DIR &= ~DIO_info->pins;
		}
		else if(DIO_info->dir==OUTPUT)
		{
			PORTD_DIR |= DIO_info->pins;
		}
		break;
	default:
		State=E_NOK;
		break;
	}
	return State;
}

/*
 *Input: GPIO -> to get PORT name
 *					- GPIOA
 *					- GPIOB
 *					- GPIOC
 *					- GPIOD
 *		pins -> pins to be written at.
 *					- PIN0
 *					- PIN1
 *					- PIN2
 *					- PIN3
 *					- PIN4
 *					- PIN5
 *					- PIN6
 *					- PIN7
 *					- UPPER_NIBBLE
 *					- LOWER_NIBBLE
 *					- FULL_PORT
 *		value 	-> The desired value
 *Output: No output
 *In/Out: No In/Out
 *Description: This function can set the value of a full port, a nibble
 * 			  or even one pin.
 */
ERROR_STATUS DIO_Write (uint8 GPIO, uint8 pins, uint8 value)
{
	ERROR_STATUS State=E_OK;
	switch(GPIO)
	{
	case GPIOA:
		if(value==HIGH)
		{
			PORTA_DATA |=pins;
		}
		else if(value==LOW)
		{
			PORTA_DATA &=~pins;
		}
		break;
	case GPIOB:
		if(value==HIGH)
		{
			PORTB_DATA |=pins;
		}
		else if(value==LOW)
		{
			PORTB_DATA &=~pins;
		}
		break;
	case GPIOC:
		if(value==HIGH)
		{
			PORTC_DATA |=pins;
		}
		else if(value==LOW)
		{
			PORTC_DATA &=~pins;
		}
		break;
	case GPIOD:
		if(value==HIGH)
		{
			PORTD_DATA |=pins;
		}
		else if(value==LOW)
		{
			PORTD_DATA &=~pins;
		}
		break;

	default:
		State=E_NOK;
		break;
	}
	return State;
}
/*
 *Input: GPIO -> to get PORT name
 *					- GPIOA
 *					- GPIOB
 *					- GPIOC
 *					- GPIOD
 *		pins -> pins to be written at.
 *					- PIN0
 *					- PIN1
 *					- PIN2
 *					- PIN3
 *					- PIN4
 *					- PIN5
 *					- PIN6
 *					- PIN7
 *					- UPPER_NIBBLE
 *					- LOWER_NIBBLE
 *					- FULL_PORT
 *Output: data -> the acquired data wether it was PORT data or pins data
 *In/Out:
 *Description: This function gets the value of a full port, a nibble
 * 			  or even one pin.
 */
ERROR_STATUS DIO_Read (uint8 GPIO,uint8 pins, uint8 *data)
{
	ERROR_STATUS State=E_OK;
	switch(GPIO)
	{
	case GPIOA:
		*data= PORTA_PIN& pins;
		break;
	case GPIOB:
		*data= PORTB_PIN& pins;
		break;
	case GPIOC:
		*data= PORTC_PIN& pins;
		break;
	case GPIOD:
		*data= PORTD_PIN& pins;
		break;
	default:
		State=E_NOK;
		break;
	}
	if(*data==pins)
	{
		*data=HIGH;
	}
	else
	{
		*data=LOW;
	}
	return State;
}
/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Toggle (uint8 GPIO, uint8 pins)
{
	ERROR_STATUS State=E_OK;
	switch(GPIO)
	{
	case GPIOA:
		PORTA_DATA ^=pins;
		break;
	case GPIOB:
		PORTB_DATA ^=pins;
		break;
	case GPIOC:
		PORTC_DATA ^=pins;
		break;
	case GPIOD:
		PORTD_DATA ^=pins;
		break;
	default:
		State=E_NOK;
		break;
	}
return 	State;
}


