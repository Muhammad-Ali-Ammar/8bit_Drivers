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


Timer0_ConfigType Timer0 ={
		.select_mode= TIMER0_SELECT_MODE_NORMAL,
		.prescaler_value =TIMER0_PRESCALER_DIV_1024,
		.init_value = 0
};


///////////////////////////////////////////////////////////////////

extern Lcd_4bitType Lcd;
extern Keypad_ConfigType Keypad;
//////////////////////////////////////////////////

void Keypad_IsrRead(void);

void Calculator_GetEquation(void);
void Calculator_DisplayResult(void);
void Calculator_DoOperations(void);

void Calculator_DisplaySyntxError(void);
void Calculator_DisplayMathError(void);
void Calculator_Clear(void);

void Calculator_DoMulandDivide(void);
void Calculator_DoSumandSub(void);

void Calculator_InitValues(void);
/////////////////////////////////////////////////

typedef enum{
	CALCULATOR_FLAG_CLEAR,
	CALCULATOR_FLAG_OK

}Calculator_FlagType;

/////////////////////////////////////////////////
u8 Keypad_Result;
Keypad_ErrorStatusType Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
u8 Global_u8EquationArray[100];
u8 Global_u8Index =ZERO_VALUE;

u8 Global_u8Mul_Divide_Operations =0;
u8 Global_u8Mul_Divide_Inxdex =0;
u8 Global_u8Operations =0;

Calculator_FlagType Global_enuFlag = CALCULATOR_FLAG_OK;
//////////////////////////////////////////////////////////////////

int main(void){

	Port_voidInit();
	Lcd_4bit_enuInit(&Lcd);

	Timer0_enuInit(&Timer0);
	Timer0_SetCallbackFunction(&Timer0,Keypad_IsrRead);
	Timer0_enuEnableInterrupt(&Timer0);
	Gie_enuEnableGlobalInterrupt();



	while(1){
		Calculator_InitValues();
		Calculator_GetEquation();
		Calculator_DisplayResult();




	}
	return 0;
}
///////////////////////////////////////////////////////////////////

void Calculator_GetEquation(void){

	u8 Loc_u8Flag = ONE_VALUE;
	Global_enuFlag = CALCULATOR_FLAG_OK;


	while(Loc_u8Flag != ZERO_VALUE){
			if(Keypad_Status == KEYPAD_IS_PRESSED){
				switch(Keypad_Result){

				case 'c' :
					Global_enuFlag = CALCULATOR_FLAG_CLEAR;
					Loc_u8Flag = ZERO_VALUE;
					break;

				case '=' :
					Loc_u8Flag = ZERO_VALUE;
					Lcd_4bit_enuDisplayCharacter(&Lcd, Keypad_Result);
					break;


				case '+' :
				case '-' :

					Global_u8EquationArray[Global_u8Index++]=Keypad_Result;
					Global_u8Operations++;
					Lcd_4bit_enuDisplayCharacter(&Lcd, Keypad_Result);
					break;

				case '/' :
				case '*' :

					Global_u8Mul_Divide_Inxdex = Global_u8Index;
					Global_u8EquationArray[Global_u8Index++]=Keypad_Result;
					Global_u8Mul_Divide_Operations++;
					Global_u8Operations++;
					Lcd_4bit_enuDisplayCharacter(&Lcd, Keypad_Result);
					break;

				default:

					Global_u8EquationArray[Global_u8Index++]=Keypad_Result;

					Lcd_4bit_enuDisplayCharacter(&Lcd, Keypad_Result);
					break;

				}





				Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
			}
	}

	Global_u8EquationArray[Global_u8Index]='\0';

}


void Calculator_DisplayResult(void){

	u8 Loc_u8Flag = ONE_VALUE;


	switch(Global_enuFlag){

	case CALCULATOR_FLAG_CLEAR:
		Calculator_Clear();
		break;

	case CALCULATOR_FLAG_OK :

			if(Global_u8Mul_Divide_Operations >1 || (Global_u8EquationArray[0]=='*' ||Global_u8EquationArray[0]=='/') ){
				// more than one * /
				Calculator_DisplaySyntxError();
			}
			else if(Global_u8EquationArray[Global_u8Index-1]=='*' ||Global_u8EquationArray[Global_u8Index-1]=='/' ||
					Global_u8EquationArray[Global_u8Index-1]=='-' || Global_u8EquationArray[Global_u8Index-1]=='+'  ) {
				// ends with += -=
				Calculator_DisplaySyntxError();
			}

			else if(Global_u8Operations == 0){

				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, Global_u8EquationArray,LCD_ROW3,LCD_COL5);

			}
			else if(Global_u8Mul_Divide_Inxdex != 0 && (Global_u8EquationArray[Global_u8Mul_Divide_Inxdex-1]=='*' ||Global_u8EquationArray[Global_u8Mul_Divide_Inxdex-1]=='/'||
					Global_u8EquationArray[Global_u8Mul_Divide_Inxdex-1]=='-' || Global_u8EquationArray[Global_u8Mul_Divide_Inxdex-1]=='+'  )  ){
						Calculator_DisplaySyntxError();
			}
			else{

				Calculator_DoOperations();

				// poing til press Clear
						while(Loc_u8Flag != ZERO_VALUE){
							if(Keypad_Status == KEYPAD_IS_PRESSED && Keypad_Result =='c'){
								Calculator_Clear();

								Loc_u8Flag = ZERO_VALUE;

							}
						}
			}

		break;

	default :
			break;

	}
}

///////////////////////////////////////////////////////////////////



void Calculator_DisplaySyntxError(void){

	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
	_delay_ms(LCD_CLEAR_DELAY);
	Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Syntax Error", LCD_ROW2, LCD_COL2);
}


void Calculator_DisplayMathError(void){
	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
	_delay_ms(LCD_CLEAR_DELAY);
	Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Math Error", LCD_ROW2, LCD_COL2);
}

void Calculator_Clear(void){
	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
	_delay_ms(LCD_CLEAR_DELAY);
}

///////////////////////////////////////////////////////////////////

void Calculator_DoOperations(void){


			if(Global_u8Mul_Divide_Operations != 0){  // it's mul or division
				Calculator_DoMulandDivide();
			}

		// it's + - operations
			else{
				Calculator_DoSumandSub();
			}
}


///////////////////////////////////////////////////////////////////


void Calculator_DoMulandDivide(void){
	u8 Loc_u8Counter = ZERO_VALUE;

	s8 Loc_s8FirstOperandSign = 1;
	u8 Loc_u8FirstOperandArr[100] ;
	u8 Loc_u8FirstOperandIndex = 0;
	u32 Loc_u32FirstOperand;

	u8 Loc_u8Operation ;


	s8 Loc_s8SecondOperandSign = 1;
	u8 Loc_u8SecondOperandArr[100] ;
	u8 Loc_u8SecondOperandIndex = 0;
	u32 Loc_u32SecondOperand;


	s8 Loc_s8ResultSign = 1;
	u32 Loc_u32ResultOperand;
	f32 Loc_f32ResultOperandInFloat;
	u8 Loc_u8ArrResultOperandInFloat[100];
	while( (Global_u8EquationArray[Loc_u8Counter] != '/') && (Global_u8EquationArray[Loc_u8Counter] != '*') ){

		if (Global_u8EquationArray[Loc_u8Counter] == '-'){
			Loc_s8FirstOperandSign*=-1;
		}
		else if(Global_u8EquationArray[Loc_u8Counter] >= '0' && Global_u8EquationArray[Loc_u8Counter] <= '9' ){
			Loc_u8FirstOperandArr[Loc_u8FirstOperandIndex++]= Global_u8EquationArray[Loc_u8Counter];


		}

		Loc_u8Counter++;
	}



	Loc_u8FirstOperandArr[Loc_u8FirstOperandIndex]= '\0';
	Convert_StringTou32(&Loc_u32FirstOperand, Loc_u8FirstOperandArr);



	Loc_u8Operation = Global_u8EquationArray[Loc_u8Counter];



	for(Loc_u8Counter= Loc_u8Counter+1;Loc_u8Counter<Global_u8Index;Loc_u8Counter++){
		if (Global_u8EquationArray[Loc_u8Counter] == '-'){
			Loc_s8SecondOperandSign*=-1;
		}
		else if(Global_u8EquationArray[Loc_u8Counter] >= '0' && Global_u8EquationArray[Loc_u8Counter] <= '9' ){
			Loc_u8SecondOperandArr[Loc_u8SecondOperandIndex++]= Global_u8EquationArray[Loc_u8Counter];
		}
	}

	Loc_u8SecondOperandArr[Loc_u8SecondOperandIndex]= '\0';
	Convert_StringTou32(&Loc_u32SecondOperand, Loc_u8SecondOperandArr);




	if(Loc_u8FirstOperandIndex == ZERO_VALUE){
		// -+-*5
		Calculator_DisplaySyntxError();

	}

	else{


		Loc_s8ResultSign = Loc_s8FirstOperandSign * Loc_s8SecondOperandSign;

		if(Loc_u8Operation =='*'){
			Loc_u32ResultOperand = Loc_u32SecondOperand *Loc_u32FirstOperand;

			if(Loc_u32FirstOperand == 0){

				Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, 0,LCD_ROW3, LCD_COL6);
			}
			else{
				if(Loc_s8ResultSign==-1)
					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);


				Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u32ResultOperand,LCD_ROW3, LCD_COL6);
			}
		}

		else if(Loc_u8Operation =='/'){

			if(Loc_u32SecondOperand == 0){
				Calculator_DisplayMathError();
			}

			else{
				Loc_f32ResultOperandInFloat = (float)Loc_u32FirstOperand/Loc_u32SecondOperand;
				if(Loc_u32FirstOperand == 0){

					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, 0,LCD_ROW3, LCD_COL6);
				}
				else {


				if(Loc_s8ResultSign==-1)
					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);
				Convert_FloatToString(Loc_f32ResultOperandInFloat, Loc_u8ArrResultOperandInFloat);
				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, Loc_u8ArrResultOperandInFloat,LCD_ROW3, LCD_COL6);


				}
			}
		}
	}






}

void Calculator_DoSumandSub(void){
	u8 Loc_u8Counter = ZERO_VALUE;

	s8 Loc_s8FirstOperandSign = 1;
	u8 Loc_u8FirstOperandArr[100] ;
	u8 Loc_u8FirstOperandIndex = 0;
	u32 Loc_u32FirstOperand;
	u8 Loc_u8FirstOperandFlag= ZERO_VALUE;

	u8 Loc_u8Operation ;


	s8 Loc_s8SecondOperandSign = 1;
	u8 Loc_u8SecondOperandArr[100]={'0'} ;
	u8 Loc_u8SecondOperandIndex = 0;
	u32 Loc_u32SecondOperand;


	s8 Loc_s8ResultSign = 1;
	u32 Loc_u32ResultOperand;
	f32 Loc_f32ResultOperandInFloat;
	u8 Loc_u8ArrResultOperandInFloat[100];

	// first find position of starting of first operand

	for(Loc_u8Counter = ZERO_VALUE;   (Global_u8EquationArray[Loc_u8Counter] >= '0' && Global_u8EquationArray[Loc_u8Counter] <= '9') ==ZERO_VALUE;  Loc_u8Counter++ ){

		if (Global_u8EquationArray[Loc_u8Counter] == '-'){
			Loc_s8FirstOperandSign*=-1;
		}

	}



	// loop til find first operation
	for( ;  Global_u8EquationArray[Loc_u8Counter]!= '\0' && (Global_u8EquationArray[Loc_u8Counter] >= '0' && Global_u8EquationArray[Loc_u8Counter] <= '9');  Loc_u8Counter++ ){

		Loc_u8FirstOperandArr[Loc_u8FirstOperandIndex++]= Global_u8EquationArray[Loc_u8Counter];

		}



	Loc_u8FirstOperandArr[Loc_u8FirstOperandIndex]= '\0';
	Convert_StringTou32(&Loc_u32FirstOperand, Loc_u8FirstOperandArr);

	if( Global_u8EquationArray[Loc_u8Counter]== '\0'){

		if(Loc_u32FirstOperand == 0){
			Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, 0,LCD_ROW3, LCD_COL6);
		}
		else{
			if(Loc_s8FirstOperandSign==-1)
						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);

					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, Loc_u8FirstOperandArr,LCD_ROW3, LCD_COL6);
		}

	}


	else{
		// loop til find second operation
			for(; (Global_u8EquationArray[Loc_u8Counter] >= '0' && Global_u8EquationArray[Loc_u8Counter] <= '9') ==ZERO_VALUE;  Loc_u8Counter++ ){

				if (Global_u8EquationArray[Loc_u8Counter] == '-'){
					Loc_s8SecondOperandSign*=-1;
				}

			}


			// loop til find second operation
			while (Global_u8EquationArray[Loc_u8Counter]!= '\0' ){

				Loc_u8SecondOperandArr[Loc_u8SecondOperandIndex++]= Global_u8EquationArray[Loc_u8Counter++];

				}
			Loc_u8SecondOperandArr[Loc_u8SecondOperandIndex]= '\0';
				Convert_StringTou32(&Loc_u32SecondOperand, Loc_u8SecondOperandArr);

				if(Loc_s8SecondOperandSign == Loc_s8FirstOperandSign){

					Loc_u32ResultOperand = Loc_u32SecondOperand + Loc_u32FirstOperand;
					if(Loc_s8FirstOperandSign==-1)
						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);

					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u32ResultOperand,LCD_ROW3, LCD_COL6);
				}


				else{
					if(Loc_u32SecondOperand== Loc_u32FirstOperand){
						Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, 0,LCD_ROW3, LCD_COL6);
					}
					else if (Loc_u32SecondOperand < Loc_u32FirstOperand){
						Loc_u32ResultOperand = Loc_u32FirstOperand-Loc_u32SecondOperand;
						if(Loc_s8FirstOperandSign==-1)
							Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);

						Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u32ResultOperand,LCD_ROW3, LCD_COL6);
					}

					else{
						Loc_u32ResultOperand = Loc_u32SecondOperand-Loc_u32FirstOperand;
						if(Loc_u32SecondOperand==-1)
							Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);

						Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u32ResultOperand,LCD_ROW3, LCD_COL6);
					}

				}



	}






}



void Keypad_IsrRead(void){

	static u8 counter = 0;
	counter ++;

	if(counter == 8){

		counter = 0;
		Keypad_Status = Keypad_enuRead(&Keypad, &Keypad_Result);
	}


}

void Calculator_InitValues(void){
	Keypad_Result='g';
	Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
	Global_u8EquationArray[0]='\0';
	Global_u8Index =ZERO_VALUE;

	Global_u8Mul_Divide_Operations =0;
	Global_u8Operations =0;
	Global_enuFlag = CALCULATOR_FLAG_OK;
	Global_u8Mul_Divide_Inxdex=0;


}


