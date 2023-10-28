/*
 * main.c
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */


#include "../SERIVICES/include/STD_TYPES.h"
#include "../SERIVICES/include/BIT_UTILS.h"
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




/////////////////////////////////////////////////////////////////////

/*******************************Ping Bong ******************************************/

#define LEFT_CUSTOM_INDEX	    1
#define RIGHT_CUSTOM_INDEX    	2
#define THEBALL_CUSTOM_INDEX	3
#define HITRIGHT_CUSTOM_INDEX	4
#define HITLEF_CUSTOM_INDEX		5


///////////////////////////////////////////

u8 Global_u8CurrentRightRowWall =LCD_ROW2 ;
u8 Global_u8CurrentLeftRowWall = LCD_ROW2 ;

u8 Loc_u8CurrentBallRow = LCD_ROW2;
u8 Loc_u8CurrentBallCol = LCD_COL10;
//////////////////////////////////
extern Lcd_4bitType Lcd;

Adc_PinConfigType Adc1 ={
		.channel_number = ADC_SELECT_CHANNEL1,
		.conversion_frequancy = ADC_FOSC_DIV_128,
		.result_format = ADC_RIGHT_JUSTIFIED,
		.vref_source = ADC_REF_VOLTAGE_AVCC_WITH_EXTERNAL_CAPACITOR

};

Adc_PinConfigType Adc4 ={
		.channel_number = ADC_SELECT_CHANNEL4,
		.conversion_frequancy = ADC_FOSC_DIV_128,
		.result_format = ADC_RIGHT_JUSTIFIED,
		.vref_source = ADC_REF_VOLTAGE_AVCC_WITH_EXTERNAL_CAPACITOR

};





u8 Lcd_LeftCustomChar[]={0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10};
u8 Lcd_RightCustomChar[]={0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01};
u8 Lcd_TheBallCustomChar[]={0x00,0x04,0x0E,0x1F,0x1F,0x0E,0x04,0x00};

u8 Lcd_HitRightCustomChar[]={0x01,0x05,0x0F,0x1F,0x1F,0x0F,0x05,0x01};
u8 Lcd_HitLeftCustomChar[]={0x10,0x14,0x1E,0x1F,0x1F,0x1E,0x14,0x10};


void Application_Adc1Left(u16 Copy_u16result);

void Application_Adc4Right(u16 Copy_u16result);

int main(void){



	u8 Loc_u8PrevBallRow = LCD_ROW2;
	u8 Loc_u8PrevBallCol = LCD_COL10;

	u8 Loc_u8ColCounter;
	u8 Loc_u8RowCounter;
	s8 Loc_s8RowFlag = -1;

	u8 Loc_OnceFlag = 0;

	Port_voidInit();
	Lcd_4bit_enuInit(&Lcd);
	Adc_enuInit(&Adc1);
	Adc_enuInit(&Adc4);

	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_LeftCustomChar, LEFT_CUSTOM_INDEX);
	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_RightCustomChar, RIGHT_CUSTOM_INDEX);
	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_TheBallCustomChar, THEBALL_CUSTOM_INDEX);
	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_HitRightCustomChar, HITRIGHT_CUSTOM_INDEX);
	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_HitLeftCustomChar, HITLEF_CUSTOM_INDEX);

	Adc_SetCallbackFunction(&Adc1, Application_Adc1Left);
	Adc_SetCallbackFunction(&Adc4, Application_Adc4Right);
	Adc_enuEnableInterrupt();
	Gie_enuEnableGlobalInterrupt();


	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2, LCD_COL1);
	Lcd_4bit_enuDisplayCharacter(&Lcd,LEFT_CUSTOM_INDEX);



	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2, LCD_COL20);
	Lcd_4bit_enuDisplayCharacter(&Lcd,RIGHT_CUSTOM_INDEX);

	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2, LCD_COL10);
	Lcd_4bit_enuDisplayCharacter(&Lcd,THEBALL_CUSTOM_INDEX);



	_delay_ms(500);
	while(1){

		Adc_StartConversionAsync(&Adc1);
		Adc_StartConversionAsync(&Adc4);


		if(Loc_u8CurrentBallRow == LCD_ROW4)
			Loc_s8RowFlag = -1;
		else if(Loc_u8CurrentBallRow == LCD_ROW1)
			Loc_s8RowFlag = 1;


		// Moving Right First

		for(Loc_u8CurrentBallCol = Loc_u8PrevBallCol+1,Loc_u8CurrentBallRow+=Loc_s8RowFlag;
				Loc_u8CurrentBallCol<=LCD_COL20;
				                    Loc_u8CurrentBallCol++,Loc_u8CurrentBallRow+=Loc_s8RowFlag){


			_delay_ms(500);
			 Loc_u8PrevBallRow = Loc_u8CurrentBallRow - Loc_s8RowFlag;
			 Loc_u8PrevBallCol = Loc_u8CurrentBallCol - 1;

			 if(Loc_OnceFlag == 0){
				 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,' ', Loc_u8PrevBallRow, Loc_u8PrevBallCol);
			 }
			 else{
				 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,LEFT_CUSTOM_INDEX,Loc_u8PrevBallRow , LCD_COL1);
				 Loc_OnceFlag =0;
				 Adc_enuEnableInterrupt();
			 }

			 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, THEBALL_CUSTOM_INDEX, Loc_u8CurrentBallRow, Loc_u8CurrentBallCol);



			if(Loc_u8CurrentBallRow == LCD_ROW4)
				Loc_s8RowFlag = -1;
			else if(Loc_u8CurrentBallRow == LCD_ROW1)
				Loc_s8RowFlag = 1;

			Adc_StartConversionAsync(&Adc1);
			Adc_StartConversionAsync(&Adc4);

		}


		Adc_enuDisableInterrupt();
		Loc_u8CurrentBallRow =Loc_u8CurrentBallRow - Loc_s8RowFlag;
		Loc_u8CurrentBallCol =LCD_COL20;

		if(Loc_u8CurrentBallRow == LCD_ROW4)
			Loc_s8RowFlag = -1;
		else if(Loc_u8CurrentBallRow == LCD_ROW1)
			Loc_s8RowFlag = 1;


		if(Loc_u8CurrentBallRow == Global_u8CurrentRightRowWall){

			 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, HITRIGHT_CUSTOM_INDEX, Loc_u8CurrentBallRow, Loc_u8CurrentBallCol);
			 Loc_OnceFlag = 1;


		}

		else{
			Gie_enuDisableGlobalInterrupt();
			_delay_ms(500);
				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
				_delay_ms(3);
				Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL5);

				Lcd_4bit_enuDisplayString(&Lcd, " GAME OVER");
				while(1);

		}


		Loc_u8PrevBallRow = Loc_u8CurrentBallRow;
		Loc_u8PrevBallCol = LCD_COL20;

		// Moving Left


		for(Loc_u8CurrentBallCol = Loc_u8PrevBallCol-1,Loc_u8CurrentBallRow+=Loc_s8RowFlag;
				Loc_u8CurrentBallCol>=LCD_COL1;
				                    Loc_u8CurrentBallCol--,Loc_u8CurrentBallRow+=Loc_s8RowFlag){

			_delay_ms(500);
			 Loc_u8PrevBallRow = Loc_u8CurrentBallRow - Loc_s8RowFlag;
			 Loc_u8PrevBallCol = Loc_u8CurrentBallCol + 1;


			 if(Loc_OnceFlag == 0){
				 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,' ', Loc_u8PrevBallRow, Loc_u8PrevBallCol);
			 }

			 else{
				 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,RIGHT_CUSTOM_INDEX,Loc_u8PrevBallRow , LCD_COL20);
				 				 Loc_OnceFlag =0;
				 				 Adc_enuEnableInterrupt();

			 }

			 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, THEBALL_CUSTOM_INDEX, Loc_u8CurrentBallRow, Loc_u8CurrentBallCol);



			if(Loc_u8CurrentBallRow == LCD_ROW4)
				Loc_s8RowFlag = -1;
			else if(Loc_u8CurrentBallRow == LCD_ROW1)
				Loc_s8RowFlag = 1;

			Adc_StartConversionAsync(&Adc1);
			Adc_StartConversionAsync(&Adc4);
		}

		Adc_enuDisableInterrupt();

		Loc_u8CurrentBallRow =Loc_u8CurrentBallRow - Loc_s8RowFlag;
		Loc_u8CurrentBallCol =LCD_COL1;

		if(Loc_u8CurrentBallRow == LCD_ROW4)
			Loc_s8RowFlag = -1;
		else if(Loc_u8CurrentBallRow == LCD_ROW1)
			Loc_s8RowFlag = 1;


		Loc_u8PrevBallRow = Loc_u8CurrentBallRow;
		Loc_u8PrevBallCol = Loc_u8CurrentBallCol;
		if(Loc_u8CurrentBallRow == Global_u8CurrentLeftRowWall){

			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, HITRIGHT_CUSTOM_INDEX, Loc_u8CurrentBallRow, Loc_u8CurrentBallCol);
			Loc_OnceFlag = 1;
		}
		else{

			Gie_enuDisableGlobalInterrupt();
			_delay_ms(500);
			Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
			_delay_ms(3);
			Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL5);

			Lcd_4bit_enuDisplayString(&Lcd, " GAME OVER");
			while(1);
		}


	}
	return 0;
}



void Application_Adc1Left(u16 Copy_u16Result){

	if(Copy_u16Result<=255){

		// ROW 4
			Global_u8CurrentLeftRowWall =LCD_ROW4;
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL1);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL1);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LEFT_CUSTOM_INDEX, LCD_ROW4, LCD_COL1);

		}

		else if(Copy_u16Result<=511){
			// ROW3
			Global_u8CurrentLeftRowWall =LCD_ROW3;
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL1);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL1);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LEFT_CUSTOM_INDEX, LCD_ROW3, LCD_COL1);



			}
		else if(Copy_u16Result<=767){
			// ROW 2
			Global_u8CurrentLeftRowWall =LCD_ROW2;
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL1);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL1);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LEFT_CUSTOM_INDEX, LCD_ROW2, LCD_COL1);

		}
		else{


			// ROW 1
			Global_u8CurrentLeftRowWall =LCD_ROW1;
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL1);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL1);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LEFT_CUSTOM_INDEX, LCD_ROW1, LCD_COL1);


		}

	if(Global_u8CurrentLeftRowWall == Loc_u8CurrentBallRow && Loc_u8CurrentBallCol == LCD_COL1)
		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, HITLEF_CUSTOM_INDEX, Loc_u8CurrentBallRow, LCD_COL1);
	else{
		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LEFT_CUSTOM_INDEX, Global_u8CurrentLeftRowWall, LCD_COL1);

	}


}



void Application_Adc4Right(u16 Copy_u16Result){
	if(Copy_u16Result<=255){

		// ROW 4
			Global_u8CurrentRightRowWall =LCD_ROW4;
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL20);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL20);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX ,LCD_ROW4, LCD_COL20);


		}

		else if(Copy_u16Result<=511){
			// ROW3
			Global_u8CurrentRightRowWall =LCD_ROW3;
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL20);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL20);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX, LCD_ROW3, LCD_COL20);

			}
		else if(Copy_u16Result<=767){
			// ROW 2
			Global_u8CurrentRightRowWall =LCD_ROW2;
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL20);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL20);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX, LCD_ROW2, LCD_COL20);

		}
		else{

			// ROW 1
			Global_u8CurrentRightRowWall =LCD_ROW1;
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL20);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL20);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX, LCD_ROW1, LCD_COL20);

		}

	if(Global_u8CurrentRightRowWall == Loc_u8CurrentBallRow && Loc_u8CurrentBallCol == 20)
		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, HITRIGHT_CUSTOM_INDEX, Loc_u8CurrentBallRow, LCD_COL20);
	else{
		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX, Global_u8CurrentRightRowWall, LCD_COL20);
	}

//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX, Global_u8CurrentRightRowWall, LCD_COL20);

}






