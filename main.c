/*
 * main.c
 *
 *  Created on: 29/12/2019
 *      Author: Sherif Adel
 */
#include <stdlib.h>
#include "interrupt.h"
#include "Exchanger.h"
#include "char_lcd .h"
#include "softwareDelay.h"

int main(void)
{
	extern volatile uint8 u8_Time;
	extern volatile uint8 u8_Speed;
	extern uint8 gu8_InitalTime;

	extern uint8 gu8_StartTime;

	extern uint16 gu16_Distance;

	sei();
	LCD_init();

	char LCD_buffer[16];


	Measurement_ECU_init();
	while(1)
	{
		Measurement_ECU_Update();

		LCD_goto_xy(0,0);
		LCD_send_string("time:");
		LCD_goto_xy(6,0);
		itoa(gu8_InitalTime,LCD_buffer,10);
		LCD_send_string(LCD_buffer);

		LCD_goto_xy(0,1);
		LCD_send_string("speed:");
		LCD_goto_xy(6,1);
		itoa(u8_Speed,LCD_buffer,10);
		LCD_send_string(LCD_buffer);

		LCD_goto_xy(9,0);
		LCD_send_string("Dis:");
		LCD_goto_xy(13,0);
		itoa(gu16_Distance,LCD_buffer,10);
		LCD_send_string(LCD_buffer);

		LCD_goto_xy(9,1);
		LCD_send_string("st:");
		LCD_goto_xy(13,1);
		itoa(gu8_StartTime,LCD_buffer,10);
		LCD_send_string(LCD_buffer);
	}



	return 0;
}
