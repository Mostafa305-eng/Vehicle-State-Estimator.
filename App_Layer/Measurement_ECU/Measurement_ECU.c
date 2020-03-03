/*
 * Measurement_ECU.c
 *
 *  Created on: 29/12/2019
 *      Author: Sherif Adel
 */
#include "DIO.h"
#include "softwareDelay.h"
#include "pushButton.h"
#include "PcData.h"
#include "Exchanger.h"
#include "Measurment_ECU.h"

extern volatile uint8 u8_Time;
extern volatile uint8 u8_Speed;
volatile uint8 gu8_InitalTime=0;
volatile uint8 gu8_StartTime=0;

volatile uint16 gu16_Distance=0;
volatile uint8 gu8_StartSpeed=0;

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize the PC module
 *
 */
ERROR_STATUS Measurement_ECU_init(void)
{
	PcData_init();
	Exhanger_Init();


	PushButton_Cfg_st mybtn1={BTN_0};
	pushButton_Init(&mybtn1);

	PushButton_Cfg_st mybtn0={BTN_1};
	pushButton_Init(&mybtn0);

	DIO_Cfg_s Fire_Fetch_Interrupt;
	Fire_Fetch_Interrupt.GPIO=GPIOA;
	Fire_Fetch_Interrupt.pins=BIT0;
	Fire_Fetch_Interrupt.dir=OUTPUT;
	DIO_init(&Fire_Fetch_Interrupt);

}



/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize the PC module
 *
 */
ERROR_STATUS Measurement_ECU_Update(void)
{
	DIO_Write(GPIOA,BIT0,LOW);
	uint8 u8_Button0_State=0;
	uint8 u8_Button1_State=0;
	pushButton_Update();

	pushButton_GetStatus(BTN_0,&u8_Button0_State);
	if(u8_Button0_State==Prepressed) // print button
	{
		DIO_Write(GPIOA,BIT0,HIGH); // send interrupt to estimate ecu
		SwDelay_ms(50);
		DIO_Write(GPIOA,BIT0,LOW);
		SwDelay_ms(100);
		gu16_Distance +=(u8_Time-gu8_StartTime)*u8_Speed;
		PcData_Update(gu8_InitalTime,u8_Speed,gu16_Distance);
		gu8_StartTime=0;
		u8_Time=0;
		gu8_InitalTime=0;
		gu16_Distance=0;
		u8_Speed=0;

	}

	pushButton_GetStatus(BTN_1,&u8_Button1_State);
	if(u8_Button1_State==Prepressed) //fetch button
	{
		DIO_Write(GPIOA,BIT0,HIGH); // send interrupt to estimate ecu
		SwDelay_ms(50);
		DIO_Write(GPIOA,BIT0,LOW);
		SwDelay_ms(100);
		gu8_StartTime=u8_Time;
		gu16_Distance=0;
		gu8_StartSpeed=u8_Speed;
		gu8_InitalTime=gu8_StartTime;
	}
	if(gu8_StartTime !=u8_Time)
	{
		gu16_Distance +=(u8_Time-gu8_StartTime)*gu8_StartSpeed;
		gu8_StartTime=u8_Time;
		gu8_StartSpeed=u8_Speed;
	}



}
