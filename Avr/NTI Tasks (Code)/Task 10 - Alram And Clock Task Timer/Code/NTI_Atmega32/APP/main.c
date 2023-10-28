/*
 * main.c
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */


#include "../SERIVICES/include/STD_TYPES.h"
#include "../SERIVICES/include/BIT_UTILS.h"
#include "../SERIVICES/include/calculation_functions.h"
#include "../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../MCAL/PORT/include/PORT.h"
#include "../MCAL/DIO/include/DIO.h"

#include <util/delay.h>
#include  "../HAL/include/LCD/LCD.h"
#include  "../HAL/include/LCD/LCD_config.h"

#include  "../HAL/include/KEYPAD/KEYPAD_config.h"
#include  "../HAL/include/KEYPAD/KEYPAD.h"
#include "../MCAL/GIE/include/GIE.h"
#include "../MCAL/EXTI/include/EXTI.h"
#include  "../HAL/include/BUTTON/BUTTON.h"
#include  "../HAL/include/SEVEN_SEGMENT/SEVEN_SEGMENT.h"
#include "../MCAL/ADC/include/ADC.h"
#include "../MCAL/TIMER0/include/TIMER0.h"






///////////////////////////////////////////////////////////////////

extern Lcd_4bitType Lcd;
extern Keypad_ConfigType Keypad;

Timer0_ConfigType Timer0 ={
		.select_mode= TIMER0_SELECT_MODE_NORMAL,
		.prescaler_value =TIMER0_PRESCALER_DIV_1024,
		.init_value = 0
};


u32 Global_u32GlobalAramCounter =10;


u32 Global_u32GlobalHour;
u32 Global_u32GlobalMin ;
u32 Global_u32GlobalSec;

void Application_GetKeypadAlarm(void);
void Application_GetKeypadHour(void);
void Application_GetKeypadMin(void);
void Application_GetKeypadSecond(void);

void Application_AlaramMode(void);
void Application_ClockMode(void);

void Alram_Isr(void);
void Clock_Isr(void);




int main(void){

		u8 Loc_u8KeypadResult=5;
		Keypad_ErrorStatusType Loc_KeypadStatus = KEYPAD_STATUS_NOT_PRESSED;
		Port_voidInit();
		Lcd_4bit_enuInit(&Lcd);




				/////////////

		Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL3);
		Lcd_4bit_enuDisplayString(&Lcd, "Choose Which Mode :");

		Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW3, LCD_COL1);
		Lcd_4bit_enuDisplayString(&Lcd, "1- Alram");

		Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW4, LCD_COL1);
		Lcd_4bit_enuDisplayString(&Lcd, "2- Clock");

			////////////


		while(1){

			Keypad_enuRead(&Keypad, &Loc_u8KeypadResult);

			if(Loc_u8KeypadResult == '1'){

				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
				_delay_ms(KEYPAD_DELAY);



				Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL1);
				Lcd_4bit_enuDisplayString(&Lcd, "Alarm: ");

				_delay_ms(LCD_DISPLAY_DELAY);

				Application_GetKeypadAlarm();

				Timer0_enuInit(&Timer0);
				Timer0_SetCallbackFunction(&Timer0,Alram_Isr);
				Timer0_enuEnableInterrupt(&Timer0);
				Gie_enuEnableGlobalInterrupt();
				Application_AlaramMode();

			}

			else if(Loc_u8KeypadResult == '2'){

								Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
								_delay_ms(KEYPAD_DELAY);

								Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Clock  ", LCD_ROW2, LCD_COL1);
								Application_GetKeypadHour();
								Lcd_4bit_enuDisplayStringWithPosition(&Lcd, ":", LCD_ROW2, LCD_COL10);
								Application_GetKeypadMin();
								Lcd_4bit_enuDisplayStringWithPosition(&Lcd, ":", LCD_ROW2, LCD_COL13);
								Application_GetKeypadSecond();

								Timer0_enuInit(&Timer0);
								Timer0_SetCallbackFunction(&Timer0,Clock_Isr);
								Timer0_enuEnableInterrupt(&Timer0);
								Gie_enuEnableGlobalInterrupt();

								Application_ClockMode();
									while(1){

									}
			}

		}
}






void Alram_Isr(void){

	static volatile u8 Loc_u8Counter = ZERO_VALUE;



	if(Loc_u8Counter ==  61){
		Global_u32GlobalAramCounter --;

		Loc_u8Counter = ZERO_VALUE;
	}

	else{
		Loc_u8Counter++;
	}
}


void Clock_Isr(void){
	static volatile u8 Loc_u8Counter = ZERO_VALUE;


	if(Loc_u8Counter ==  61){
		Global_u32GlobalSec ++;
		if(Global_u32GlobalSec == 60){
			Global_u32GlobalSec =0;
			Global_u32GlobalMin++;
		}
		if(Global_u32GlobalMin == 60){
			Global_u32GlobalSec = 0;
			Global_u32GlobalMin = 0;
			Global_u32GlobalHour++;
		}
	if(Global_u32GlobalHour == 24){
		Global_u32GlobalSec = ZERO_VALUE;
		Global_u32GlobalMin = ZERO_VALUE;
		Global_u32GlobalHour= ZERO_VALUE;
	}

	Loc_u8Counter = ZERO_VALUE;
	}

	else{
		Loc_u8Counter++;
	}
}

void Application_AlaramMode(void){

	while(1){
		Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL8);
		Lcd_4bit_enuDisplayString(&Lcd,"    ");

		if(Global_u32GlobalAramCounter != 0){
			Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL8);
			Lcd_4bit_enuDisplayNumber(&Lcd, Global_u32GlobalAramCounter);

		_delay_ms(100);
		}
		else {
			Dio_enuWriteChannel(DIO_PINC6_CHANNEL22,DIO_HIGH);
			Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Buzzer is On", LCD_ROW2, LCD_COL8);

			Timer0_enuDisableInterrupt(&Timer0);
			while(1);
		}

	}

}


//								Hour 8,9
//								min 11,12
//								sec 14,15



void Application_ClockMode(void){
	while(1){


		if(Global_u32GlobalHour<=9){
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,'0', LCD_ROW2, LCD_COL8);
			Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalHour,LCD_ROW2,LCD_COL9);
		}
		else{
			Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalHour,LCD_ROW2,LCD_COL8);
		}

		if(Global_u32GlobalMin<=9){
					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,'0', LCD_ROW2, LCD_COL11);
					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalMin,LCD_ROW2,LCD_COL12);
				}
				else{
					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalMin,LCD_ROW2,LCD_COL11);
				}

		if(Global_u32GlobalSec<=9){
					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,'0', LCD_ROW2, LCD_COL14);
					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalSec,LCD_ROW2,LCD_COL15);
				}
				else{
					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalSec,LCD_ROW2,LCD_COL14);
				}

			_delay_ms(LCD_DISPLAY_DELAY);



		}
}




void Application_GetKeypadAlarm(void){

	u8 temp='a';
	Keypad_ErrorStatusType Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
	u8 tempArr[100];
	u8 Loc_u8Index = 0;
	u8 Loc_u8Check = ONE_VALUE;

	while(Loc_u8Check == ONE_VALUE){

		Keypad_Status = Keypad_enuRead(&Keypad, &temp);
		if(Keypad_Status == KEYPAD_IS_PRESSED){

			if(temp>='0' && temp<='9'){
				Lcd_4bit_enuDisplayCharacter(&Lcd, temp);
				tempArr[Loc_u8Index++]=temp;
				_delay_ms(KEYPAD_DELAY);
			}
			else if(temp == '='){
				Loc_u8Check = ZERO_VALUE;
			}
		}
	}

	tempArr[Loc_u8Index]='\0';
	Convert_StringTou32(&Global_u32GlobalAramCounter, tempArr);

}

void Application_GetKeypadHour(void){
	u8 temp='a';
	Keypad_ErrorStatusType Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
	u8 tempArr[100];
	u8 Loc_u8Index = 0;
	u8 Loc_u8Check = 2;

	while(Loc_u8Check != ZERO_VALUE){

		Keypad_Status = Keypad_enuRead(&Keypad, &temp);
		if(Keypad_Status == KEYPAD_IS_PRESSED){

			if(temp>='0' && temp<='9'){
				Lcd_4bit_enuDisplayCharacter(&Lcd, temp);
				tempArr[Loc_u8Index++]=temp;

				Loc_u8Check--;
				_delay_ms(KEYPAD_DELAY);
			}

		}
	}

	tempArr[Loc_u8Index]='\0';
	Convert_StringTou32(&Global_u32GlobalHour, tempArr);
}


void Application_GetKeypadSecond(void){
	u8 temp='a';
	Keypad_ErrorStatusType Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
	u8 tempArr[100];
	u8 Loc_u8Index = 0;
	u8 Loc_u8Check = 2;

	while(Loc_u8Check != ZERO_VALUE){

		Keypad_Status = Keypad_enuRead(&Keypad, &temp);
		if(Keypad_Status == KEYPAD_IS_PRESSED){

			if(temp>='0' && temp<='9'){
				Lcd_4bit_enuDisplayCharacter(&Lcd, temp);
				tempArr[Loc_u8Index++]=temp;

				Loc_u8Check--;
				_delay_ms(KEYPAD_DELAY);
			}

		}
	}

	tempArr[Loc_u8Index]='\0';
	Convert_StringTou32(&Global_u32GlobalSec, tempArr);
}

void Application_GetKeypadMin(void){
	u8 temp='a';
	Keypad_ErrorStatusType Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
	u8 tempArr[100];
	u8 Loc_u8Index = 0;
	u8 Loc_u8Check = 2;

	while(Loc_u8Check != ZERO_VALUE){

		Keypad_Status = Keypad_enuRead(&Keypad, &temp);
		if(Keypad_Status == KEYPAD_IS_PRESSED){

			if(temp>='0' && temp<='9'){
				Lcd_4bit_enuDisplayCharacter(&Lcd, temp);
				tempArr[Loc_u8Index++]=temp;

				Loc_u8Check--;
				_delay_ms(KEYPAD_DELAY);
			}

		}
	}

	tempArr[Loc_u8Index]='\0';
	Convert_StringTou32(&Global_u32GlobalMin, tempArr);
}

