/*
 * PcData.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: mohamed
 */

#ifndef HAL_PCDATA_PCDATA_H_
#define HAL_PCDATA_PCDATA_H_

#include "std_types.h"
/************************************************************************/
/*		                   FUNCTIONS' PROTOTYPES          		        */
/************************************************************************/

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize the PC module
 *
 */
ERROR_STATUS PcData_init(void);

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Takes Inital values of both speed and time
 *
 */
ERROR_STATUS PcData_Update(uint8 u8_InitTime,uint8 u8_InitSpeed,uint16 u16_Distance);

#endif /* HAL_PCDATA_PCDATA_H_ */
