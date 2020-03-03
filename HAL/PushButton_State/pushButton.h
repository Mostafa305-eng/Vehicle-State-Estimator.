/*
 * pushButton.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#include "softwareDelay.h"





#define BTN_0 0
#define BTN_1 1
#define BTN_2 2
#define BTN_3 3


#define Released 0
#define Prepressed 1
#define Pressed		2
#define Prereleased 3

typedef struct PushButton_Cfg_st 
{
	uint8 btn_id;
}PushButton_Cfg_st;

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */
ERROR_STATUS pushButton_Init(PushButton_Cfg_st *Button_Cfg);
/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick hundler or in the super loop hundler
 */
ERROR_STATUS pushButton_Update(void);
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
ERROR_STATUS pushButton_GetStatus(uint8 BTN_ID,uint8 *Button_State);

#endif /* PUSHBUTTON_H_ */
