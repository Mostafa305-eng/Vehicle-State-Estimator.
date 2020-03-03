/*
 * CFile1.c
 *
 * Created: 12/5/2019 1:00:28 PM
 *  Author: Mostafa Metwaly
 */ 
#include "pushButton.h"

#include "std_types.h"
#include "DIO.h"
#include "softwareDelay.h"

#define BTN_MAX_NUM		(2)


#define BTN_0_GPIO	GPIOC
#define BTN_0_BIT	BIT4

#define BTN_1_GPIO	GPIOB
#define BTN_1_BIT	BIT2

#define BTN_2_GPIO	GPIOA
#define BTN_2_BIT	BIT2

#define BTN_3_GPIO 	GPIOA
#define BTN_3_BIT	BIT3



typedef enum EN_buttonInit_t{
	Init,
	NotInit
	}EN_buttonInit_t;

typedef struct ST_buttons_t{
	uint8 buttonGpio;
	uint8 buttonBit;
	uint8 buttonStatus;
	EN_buttonInit_t buttonInit;
	}ST_buttons_t;


static ST_buttons_t STA_buttons[]={ {BTN_0_GPIO,BTN_0_BIT,Released,NotInit},
									{BTN_1_GPIO,BTN_1_BIT,Released,NotInit},
									{BTN_2_GPIO,BTN_2_BIT,Released,NotInit},
									{BTN_3_GPIO,BTN_3_BIT,Released,NotInit},	
									} ;
	


ERROR_STATUS pushButton_Init(PushButton_Cfg_st *Button_Cfg){
	DIO_Cfg_s PushButton0;
	DIO_Cfg_s PushButton1;
	DIO_Cfg_s PushButton2;
	DIO_Cfg_s PushButton3;
	switch(Button_Cfg->btn_id){
		case (BTN_0) :
			PushButton0.GPIO=BTN_0_GPIO;
			PushButton0.pins=BTN_0_BIT;
			PushButton0.dir=INPUT;
			DIO_init(&PushButton0);
			(STA_buttons)->buttonInit=Init;
			break;
		case (BTN_1) :
			PushButton1.GPIO=BTN_1_GPIO;
			PushButton1.pins=BTN_1_BIT;
			PushButton1.dir=INPUT;
			DIO_init(&PushButton1);
			(STA_buttons+1)->buttonInit=Init;
			break;
		case (BTN_2) :
			PushButton2.GPIO=BTN_2_GPIO;
			PushButton2.pins=BTN_2_BIT;
			PushButton2.dir=INPUT;
			DIO_init(&PushButton2);	
			(STA_buttons+2)->buttonInit=Init;
			break;
		case (BTN_3) :
			PushButton3.GPIO=BTN_3_GPIO;
			PushButton3.pins=BTN_3_BIT;
			PushButton3.dir=INPUT;
			DIO_init(&PushButton3);
			(STA_buttons+3)->buttonInit=Init;
			break;
	}
}

ERROR_STATUS pushButton_Update(void){
	uint8 counter;
	uint8 TempFirstRead;
	uint8 TempSecondRead;
	

	
	for (counter=0;counter<4;counter++)
	{
		

		if((STA_buttons+counter)->buttonInit==Init)
		{


			DIO_Read((STA_buttons+counter)->buttonGpio,(STA_buttons+counter)->buttonBit,\
			&TempFirstRead);
	
			SwDelay_ms(20);

			DIO_Read((STA_buttons+counter)->buttonGpio,(STA_buttons+counter)->buttonBit,\
			&TempSecondRead);

			if(TempFirstRead == TempSecondRead)
			{
				switch ((STA_buttons+counter)->buttonStatus)
				{

					case Released :

						if(TempSecondRead)
						{
								(STA_buttons+counter)->buttonStatus=Prepressed;

						}
						break;
			
					case Prereleased :
						if(TempSecondRead)
								(STA_buttons+counter)->buttonStatus=Prepressed;	
						else
								(STA_buttons+counter)->buttonStatus=Released;
						break;

					case Prepressed :
						if(TempSecondRead)
								(STA_buttons+counter)->buttonStatus=Pressed;	
						else
								(STA_buttons+counter)->buttonStatus=Prereleased;
						break;

					case Pressed :
						if(TempSecondRead)
								(STA_buttons+counter)->buttonStatus=Pressed;
						else
								(STA_buttons+counter)->buttonStatus=Prereleased;
						break;

				}	
			}
		}
	}
}


ERROR_STATUS pushButton_GetStatus(uint8 BTN_ID,uint8 *Button_State){
	switch (BTN_ID)
	{
		case BTN_0:
			*Button_State = STA_buttons[0].buttonStatus;
			break;
		case BTN_1:
			*Button_State = STA_buttons[1].buttonStatus;
			break;
		case BTN_2:
			*Button_State = STA_buttons[2].buttonStatus;
			break;
		case BTN_3:
			*Button_State = STA_buttons[3].buttonStatus;
			break;
	}
}
