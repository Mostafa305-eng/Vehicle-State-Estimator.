/*
 * Exchanger.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: mohamed
 */

#ifndef HAL_EXCHANGER_EXCHANGER_H_
#define HAL_EXCHANGER_EXCHANGER_H_
#include "std_types.h"








/************************************************************************/
/*		                   FUNCTIONS' PROTOTYPES          		        */
/************************************************************************/

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize The AVR1 as Master
 *
 */
ERROR_STATUS Exhanger_Init(void);

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Recieve Time and Speed from Estimator ECU ECU
 *
 */
void Exhanger_RecieveData(void);
/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize The AVR2 as Slave
 *
 */
ERROR_STATUS SPI_Slave_init(void);


#endif /* HAL_EXCHANGER_EXCHANGER_H_ */
