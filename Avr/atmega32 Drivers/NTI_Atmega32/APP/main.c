/**************************************************************************/
/* Filename						: main.c                                  */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 23 Oct 2023  	           	 	      	  */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At		  			: NTI 								  	  */
/* Instructor		  			: Mahmoud Embabi 					  	  */
/**************************************************************************/



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
#include "../MCAL/TIMER1/include/TIMER1.h"
#include "../MCAL/TIMER2/include/TIMER2.h"
#include "../MCAL/WTD/include/WDT.h"
#include  "../HAL/include/ICUSW/ICUSW.h"
#include  "../MCAL/USART/include/USART.h"
#include  "../MCAL/SPI/include/SPI_config.h"
#include  "../MCAL/SPI/include/SPI.h"
#include  "../MCAL/I2C/include/I2C.h"
#include "../HAL/include/EXTERNAL_EEPROM/EXTERNAL_EEPROM.h"
#include "../HAL/include/TC74/TC74_config.h"
#include "../HAL/include/TC74/TC74.h"
#include "../HAL/include/RTC/RTC.h"
#include "../HAL/include/DC_MOTOR/DC_MOTOR.h"
#include "../HAL/include/SERVO/SERVO.h"

/////////////////////////////The Running Boy ////////////////////////////////////////////////

//
//extern Lcd_4bitType Lcd;
//
//u8 Lcd_BoyCustomCharacter[]={0x1F, 0x15, 0x1F, 0x04,  0x1F,  0x04, 0x0E,  0x1F};
//u8 Lcd_FloorCustomCharacter[]={0x00, 0x00, 0x00, 0x00,  0x00,  0x00, 0x1F,  0x00};
//u8 Lcd_UpCustomCharacter[]={0x00, 0x00, 0x01, 0x02,  0x04,  0x08, 0x10,  0x00};
//u8 Lcd_DeathCustomCharacter[]={0x04, 0x04, 0x04, 0x04,  0x04,  0x04, 0x04,  0x04};
//
//#define LCD_BOY_INDEX		0
//#define LCD_FLOOR_INDEX		1
//
//#define LCD_UP_INDEX		2
//#define LCD_DEATH_INDEX		3
//
//
//
//void Lcd_FillTheFloor(void);
//void Lcd_MovingTheBoyTheWholeScreen(void);
//void Lcd_CreatingTheHoleAndLadderUp(void);
//void Lcd_KillingTheBoy(void);
//void Lcd_GameOver(void);
//
//int main(){
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	/* This is Init Part */
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	/* Generte Custom Characters
//	 *
//	 * 1- The boy
//	 * 2- The ground ( The floor ) _
//	 * 3- Up Ladder \
//	 * 4- Death Ladder |
//	 *  */
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_BoyCustomCharacter, LCD_BOY_INDEX);
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_FloorCustomCharacter, LCD_FLOOR_INDEX);
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_UpCustomCharacter, LCD_UP_INDEX);
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_DeathCustomCharacter, LCD_DEATH_INDEX);
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	// Display the floor to the all Screen cells
//	Lcd_FillTheFloor();
//
//	// Display the boy on the first cell
//	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX,LCD_ROW1,LCD_COL1);
//
//
//	// first step : move the boy to the whole of cells
//		Lcd_MovingTheBoyTheWholeScreen();
//
//
//	// Second Step : Create The Hole
//	Lcd_CreatingTheHoleAndLadderUp();
//
//
//	// Third Step : Killing and Game Over
//	Lcd_KillingTheBoy();
//
//	//Game Over
//	Lcd_GameOver();
//
//	while(1){
//
//
//	}
//
//
//
//}
//
//
//void Lcd_FillTheFloor(void){
//
//	u8 Loc_RowCounter = LCD_ROW1;
//	u8 Loc_ColCounter = LCD_COL1;
//
//	for(Loc_RowCounter = LCD_ROW1; Loc_RowCounter<=LCD_ROW_NUMBERS;Loc_RowCounter++){
//		for(Loc_ColCounter = LCD_COL1; Loc_ColCounter<=LCD_COL_NUMBERS;Loc_ColCounter++){
//
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_RowCounter,Loc_ColCounter);
//
//		}
//	}
//
//
//}
//
//void Lcd_MovingTheBoyTheWholeScreen(void){
//
//	u8 Loc_RowCounter = LCD_ROW1;
//	u8 Loc_ColCounter = LCD_COL2;
//
//	u8 Loc_PreviousRow = LCD_ROW1;
//	u8 Loc_PreviousCol = LCD_COL1;
//	for(Loc_RowCounter = LCD_ROW1; Loc_RowCounter<=LCD_ROW_NUMBERS;Loc_RowCounter++){
//		for(Loc_ColCounter = LCD_COL1; Loc_ColCounter<=LCD_COL_NUMBERS;Loc_ColCounter++){
//
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_RowCounter,Loc_ColCounter);
//
//			Loc_PreviousRow = Loc_RowCounter;
//			Loc_PreviousCol = Loc_ColCounter;
//			_delay_ms(100);
//		}
//	}
//
//	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, LCD_ROW1,LCD_COL1);
//	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);
//
//}
//
//
//void Lcd_CreatingTheHoleAndLadderUp(void){
//	u8 Loc_RowCounter = LCD_ROW1;
//	u8 Loc_ColCounter = LCD_COL2;
//
//	u8 Loc_PreviousRow = LCD_ROW1;
//	u8 Loc_PreviousCol = LCD_COL1;
//
//	u8 Loc_HoleRow = LCD_ROW1;
//	u8 Loc_HoleCol = LCD_COL15;
//
//	u8 Loc_LadderRow = LCD_ROW2;
//	u8 Loc_LadderCol = LCD_COL15;
//
//	// create hole
//
//	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1,LCD_COL15);
//
//	// loop til reach to the hole
//	for(Loc_ColCounter = LCD_COL2;Loc_ColCounter<= Loc_HoleCol; Loc_ColCounter++){
//
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_RowCounter,Loc_ColCounter);
//		Loc_PreviousRow = Loc_RowCounter;
//		Loc_PreviousCol = Loc_ColCounter;
//		_delay_ms(100);
//	}
//
//
//	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', Loc_PreviousRow,Loc_PreviousCol);
//
//	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_LadderRow,Loc_LadderCol);
//	_delay_ms(100);
//
//	Loc_PreviousRow = Loc_LadderRow;
//	Loc_PreviousCol = Loc_LadderCol;
//
//
//	// continue after the whole
//	for(Loc_ColCounter = Loc_HoleCol+ONE_VALUE; Loc_ColCounter<=LCD_COL_NUMBERS;Loc_ColCounter++){
//
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);
//
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_LadderRow,Loc_ColCounter);
//
//		Loc_PreviousCol = Loc_ColCounter;
//
//		_delay_ms(100);
//	}
//
//
//
//	// Create the Ladder
//	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,LCD_UP_INDEX, Loc_LadderRow,Loc_LadderCol);
//	// loop til you reach the ladder
//	for(Loc_ColCounter = LCD_COL1; Loc_ColCounter<=Loc_LadderCol;Loc_ColCounter++){
//
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);
//
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_LadderRow,Loc_ColCounter);
//
//		Loc_PreviousCol = Loc_ColCounter;
//
//		_delay_ms(100);
//	}
//
//
//	// continute he lifting up
//	Loc_PreviousRow = Loc_LadderRow;
//	Loc_PreviousCol = Loc_HoleCol;
//
//	for(Loc_ColCounter = Loc_HoleCol; Loc_ColCounter<=LCD_COL_NUMBERS;Loc_ColCounter++){
//
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);
//
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_HoleRow,Loc_ColCounter);
//
//		Loc_PreviousCol = Loc_ColCounter;
//		Loc_PreviousRow = Loc_HoleRow;
//
//		_delay_ms(100);
//	}
//
//
//
//
//	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, LCD_ROW1,LCD_COL1);
//	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);
//
//
//}
//
//void Lcd_KillingTheBoy(void){
//		u8 Loc_RowCounter = LCD_ROW1;
//		u8 Loc_ColCounter = LCD_COL2;
//
//		u8 Loc_PreviousRow = LCD_ROW1;
//		u8 Loc_PreviousCol = LCD_COL1;
//
//		u8 Loc_ObstalceRow = LCD_ROW2;
//		u8 Loc_ObstalceCol = LCD_COL10;
//
//
//		// create the Obstalce
//
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,LCD_DEATH_INDEX, Loc_ObstalceRow,Loc_ObstalceCol);
//
//		// loop til reach to the Obstcale
//		for(Loc_RowCounter = LCD_ROW1;((Loc_RowCounter != Loc_ObstalceRow) || Loc_ColCounter !=  Loc_ObstalceCol);Loc_RowCounter++){
//				for(Loc_ColCounter = LCD_COL1;Loc_ColCounter <= LCD_COL_NUMBERS  ;Loc_ColCounter++){
//
//					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);
//					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_RowCounter,Loc_ColCounter);
//
//					Loc_PreviousRow = Loc_RowCounter;
//					Loc_PreviousCol = Loc_ColCounter;
//					_delay_ms(100);
//
//					if ( (Loc_RowCounter == Loc_ObstalceRow) && Loc_ColCounter ==  Loc_ObstalceCol){
//						--Loc_RowCounter;
//						break;
//					}
//
//				}
//			}
//
//		Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
//
//}
//
//
//void Lcd_GameOver(){
//
//	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
//	_delay_ms(3);
//	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL5);
//
//	Lcd_4bit_enuDisplayString(&Lcd, " GAME OVER");
//
//
//
//}

///////////////////////////////////////////////////////////////////////////////////////////

//
//extern Lcd_4bitType Lcd;
//extern Keypad_ConfigType Keypad;
//
//
//
//void Task_GetFirstNumberAndAsign(s64* number1, u8* assign);
//void Task_GetSecondNumber(s64* number2, u8* assign);
//
//
//
//int main(void){
//
//		Port_voidInit();
//		Lcd_4bit_enuInit(&Lcd);
//		s64 Loc_s64FirstNumber = 0;
//		s64 Loc_s64SecondNumber = 0;
//		f64 Loc_f64Result = 0;
//		s64 Loc_s64Result = 0;
//		u8 Loc_u8Assin =0;
//		while(1){
//			Task_GetFirstNumberAndAsign(&Loc_s64FirstNumber, &Loc_u8Assin);
//
//			Task_GetSecondNumber(&Loc_s64SecondNumber,& Loc_u8Assin);
//
//			switch(Loc_u8Assin){
//
//			case '+':
//				Loc_s64Result = Loc_s64FirstNumber + Loc_s64SecondNumber;
//				Lcd_4bit_enuDisplayNumber(&Lcd, Loc_s64Result);
//				break;
//
//			case '-':
//				Loc_s64Result = Loc_s64FirstNumber - Loc_s64SecondNumber;
//				Lcd_4bit_enuDisplayNumber(&Lcd, Loc_s64Result);
//				break;
//
//			case '/':
//				Loc_f64Result = Loc_s64FirstNumber / Loc_s64SecondNumber;
//				Lcd_4bit_enuDisplayFloatNumber(&Lcd, Loc_s64Result);
//				break;
//
//			case '*':
//				Loc_s64Result = Loc_s64FirstNumber * Loc_s64SecondNumber;
//				Lcd_4bit_enuDisplayNumber(&Lcd, Loc_s64Result);
//				break;
//
//			case 'c':
//
//				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
//				break;
//			default:
//				break;
//
//
//			}
//			break;
//		}
//}
//
//
//void Task_GetFirstNumberAndAsign(s64* number1, u8* assign){
//
//	Keypad_ErrorStatusType Loc_KeypadStatus = KEYPAD_STATUS_NOT_PRESSED;
//	u8 tempArrNumber[100];
//	u8 Loc_u8Index =0;
//	u8 Loc_u8Value;
//	s8 Loc_s8ReturnResult = 0;
//	s8 Loc_s8Negative = 1;
//	while(1){
//
//		Loc_KeypadStatus = KEYPAD_STATUS_NOT_PRESSED;
//		Loc_KeypadStatus = Keypad_enuRead(&Keypad, &Loc_u8Value);
//
//		if(Loc_KeypadStatus == KEYPAD_IS_PRESSED){
//
//
//			Lcd_4bit_enuDisplayCharacter(&Lcd, Loc_u8Value);
//
//			if(Loc_u8Value == '-'  && Loc_u8Index ==0)
//				Loc_s8Negative -=Loc_s8Negative;
//
//			else if(Loc_u8Value>='0' &&Loc_u8Value<='9'){
//				tempArrNumber[Loc_u8Index++]= Loc_u8Value;
//				tempArrNumber[Loc_u8Index]= '\0';
//
//			}
//
//
//			else if(Loc_u8Value == 'c'){
//				Loc_u8Index =0;
//				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
//				Loc_s8Negative = 1;
//				return;
//			}
//			else {
//				*assign= Loc_u8Value;
//				Convert_StringToInt(number1, tempArrNumber);
//				(*number1) *=Loc_s8Negative;
//
//				return;
//			}
//
//			_delay_ms(500);
//		}
//
//
//
//
//	}
//}
//
//void Task_GetSecondNumber(s64* number2, u8* Address_Asign){
//	Keypad_ErrorStatusType Loc_KeypadStatus = KEYPAD_STATUS_NOT_PRESSED;
//	u8 tempArrNumber[100];
//	u8 Loc_u8Index =0;
//	u8 Loc_u8Value;
//	s8 Loc_s8ReturnResult = 0;
//	s8 Loc_s8Negative = 1;
//	while(1){
//
//		Loc_KeypadStatus = KEYPAD_STATUS_NOT_PRESSED;
//		Loc_KeypadStatus = Keypad_enuRead(&Keypad, &Loc_u8Value);
//
//		if(Loc_KeypadStatus == KEYPAD_IS_PRESSED){
//
//
//			Lcd_4bit_enuDisplayCharacter(&Lcd, Loc_u8Value);
//			if(Loc_u8Value == '='){
//				Convert_StringToInt(number2, tempArrNumber);
//				break;
//			}
//
//
//			else if(Loc_u8Value>='0' &&Loc_u8Value<='9')
//				{
//				tempArrNumber[Loc_u8Index++]= Loc_u8Value;
//				tempArrNumber[Loc_u8Index]='\0';
//				}
//
//			else if(Loc_u8Value == 'c'){
//				*Address_Asign = 'c';
//				return;
//			}
//
//
//
//			_delay_ms(500);
//		}
//
//
//
//
//	}
//
//
//
//}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/* EXTI with LEDS */

//void Exti_ApplicationIsr0(){
//
//	Dio_enuFlipChannel(DIO_PINA4_CHANNEL4);
//
//}
//
//void Exti_ApplicationIsr1(){
//
//
//	Dio_enuFlipChannel(DIO_PINA6_CHANNEL6);
//}
//
//
//void Exti_ApplicationIsr2(){
//
//
//	Dio_enuFlipChannel(DIO_PINA5_CHANNEL5);
//
//}
//
//int main(void){
//
//	Port_voidInit();
//
//	Exti_enuEnable(EXTI_INT0_INDEX, EXTI_INT0_SELECT_FAILING_EDGE);
//	Exti_enuSetCallbackFunction(EXTI_INT0_INDEX, Exti_ApplicationIsr0);
//
//	Exti_enuEnable(EXTI_INT1_INDEX, EXTI_INT1_SELECT_FAILING_EDGE);
//	Exti_enuSetCallbackFunction(EXTI_INT1_INDEX, Exti_ApplicationIsr1);
//
//	Exti_enuEnable(EXTI_INT2_INDEX, EXTI_INT2_SELECT_FAILING_EDGE);
//	Exti_enuSetCallbackFunction(EXTI_INT2_INDEX, Exti_ApplicationIsr2);
//
//
//	Gie_enuEnableGlobalInterrupt();
//
//	while(1){
//
//
//
//	}
//	return 0;
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////// Button ///////////////////////////////////////



//extern Button_ConfigType Button1;
//
//Button_StatusErrorType Button1_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State ){
//
//	Button_StatusErrorType Loc_enuStatus = BUTTON_STATUS_OK;
//
//	/* Button Part */
//	static u16 Loc_u16ButtonCounter = 0;
//
//	Button_PressStatusType Loc_enuButton1Temp = BUTTON_NOT_PRESSED;
//	Button_PressStatusType Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//	static Button_PressStatusType Loc_enuButton1AcutalLastState = BUTTON_NOT_PRESSED;
//
//	////////////////////////////////////////////////////////////////////////////
//	Button_PressStatusType Loc_enuButton1Result = BUTTON_NOT_PRESSED;
//
//	/////////////////////////////////////////////////////////////////
//		if( NULL == Address_Button || NULL == Address_State ){
//			Loc_enuStatus = BUTTON_STATUS_NULL_POINTER_ADDRESS;
//
//		}
//		else{
//			/* Bouncing Part */
//						    Button_enuRead(&Button1,&Loc_enuButton1Temp);
//						    if(BUTTON_PRESSED == Loc_enuButton1Temp){
//						    	Loc_u16ButtonCounter++;
//						        if(Loc_u16ButtonCounter>500){
//						        	Loc_enuButton1TrueState = BUTTON_PRESSED;
//						        }
//						        else {/* nothing */}
//						    }
//
//						    else{
//						    	Loc_u16ButtonCounter = 0;
//						    	Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//						    }
//
//						    if(Loc_enuButton1TrueState != Loc_enuButton1AcutalLastState){
//						        /* there is change on the button */
//
//						    	Loc_enuButton1AcutalLastState = Loc_enuButton1TrueState;
//
//						        if(BUTTON_PRESSED == Loc_enuButton1AcutalLastState){
//						            /* TAKE THE ACTION*/
//						        	Loc_enuButton1Result = BUTTON_PRESSED;
//						        }
//
//						    }
//
//		    }
//		*Address_State = Loc_enuButton1Result;
//
//
//
//
//		return Loc_enuStatus;
//
//}
//
//
//
//int main(void){
//
//	Port_voidInit();
//
//
//	    Button_PressStatusType Button_Result = BUTTON_NOT_PRESSED;
//
//
//	while(1){
//		Button1_enuReadWithDebouncing(&Button1, &Button_Result);
//		if(Button_Result == BUTTON_PRESSED)
//			Dio_enuFlipChannel(DIO_PINA5_CHANNEL5);
//
//	}
//	return 0;
//}




///////////////////////////////////STOP WATCH /////////////////////////////////////////////////////////////////////////////
//
//extern Seven_Segment_BCDType Seven_Segment;
//extern u8 	Seven_SegmentCom4 ;
//extern u8 	Seven_SegmentCom3 ;
//extern u8 	Seven_SegmentCom2 ;
//extern u8 	Seven_SegmentCom1 ;
//
//extern Button_ConfigType StartButton;
//extern Button_ConfigType StopButton;
//extern Button_ConfigType ResetButton;
//
/////////////////////////////////////////////////////////////////////////
//
//
//#define START_FLAG 				    	ZERO_VALUE
//#define STOP_FLAG 			    		ONE_VALUE
//#define RESET_FLAG			            TWO_VALUE
//
//
//
/////////////////////////////////////////////////////////////////////
//u8 Global_u8ForthDigit = ZERO_VALUE;
//u8 Global_u8ThirdDigit = ZERO_VALUE;
//u8 Global_u8SecondDigit = ZERO_VALUE;
//u8 Global_u8FirstDigit = ZERO_VALUE;
//u8 Global_u8Flag = RESET_FLAG;
//
//Button_PressStatusType Start_ButtonState = BUTTON_NOT_PRESSED;
//Button_PressStatusType Stop_ButtonState = BUTTON_NOT_PRESSED;
//Button_PressStatusType Reset_ButtonState = BUTTON_NOT_PRESSED;
/////////////////////////////////////////////////////////////////////////
//
//void DisableSegment(u8 Copy_u8SegmentCom);
//void EnableSegment(u8 Copy_u8SegmentCom);
//void StartSegments(void);
//void StopSegments(void);
//void ResetSegments(void);
//
/////////////////////////////////////////////////////////////////////////
//
//int main(void){
//
//
//	Port_voidInit();
//
//	ResetSegments();
//
//	while(1){
//
//		switch(Global_u8Flag){
//			case START_FLAG:
//				StartSegments();
//				break;
//			case STOP_FLAG:
//				StopSegments();
//				break;
//			case RESET_FLAG:
//				ResetSegments();
//				break;
//			default:
//				break;
//
//
//		}
//
//
//
//
//	}
//	return 0;
//}
//
//void DisableSegment(u8 Copy_u8SegmentCom){
//
//	Dio_enuWriteChannel(Copy_u8SegmentCom, 1);
//}
//
//void EnableSegment(u8 Copy_u8SegmentCom){
//
//	Dio_enuWriteChannel(Copy_u8SegmentCom, 0);
//}
//void StartSegments(void){
//
//
//
//	u32 Loc_u32Ticks = ZERO_VALUE;
//
//
//	do{
//		do{
//			do{
//				do{
//
//
//					for( Loc_u32Ticks = 0;Loc_u32Ticks<40;++Loc_u32Ticks){
//
//									Button_enuRead(&StopButton, &Stop_ButtonState);
//									if(Stop_ButtonState == BUTTON_PRESSED){
//										Global_u8Flag = STOP_FLAG;
//										return ;
//									}
//									Button_enuRead(&ResetButton, &Reset_ButtonState);
//									if(Reset_ButtonState == BUTTON_PRESSED){
//										Global_u8Flag = RESET_FLAG;
//										return ;
//									}
//
//						Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ForthDigit);
//						DisableSegment(Seven_SegmentCom1);
//						EnableSegment(Seven_SegmentCom4);
//						_delay_ms(5);
//
//													Button_enuRead(&StopButton, &Stop_ButtonState);
//													if(Stop_ButtonState == BUTTON_PRESSED){
//														Global_u8Flag = STOP_FLAG;
//														return ;
//													}
//													Button_enuRead(&ResetButton, &Reset_ButtonState);
//													if(Reset_ButtonState == BUTTON_PRESSED){
//														Global_u8Flag = RESET_FLAG;
//														return ;
//													}
//						Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ThirdDigit);
//						DisableSegment(Seven_SegmentCom4);
//						EnableSegment(Seven_SegmentCom3);
//						_delay_ms(5);
//
//
//						Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8SecondDigit);
//						DisableSegment(Seven_SegmentCom3);
//						EnableSegment(Seven_SegmentCom2);
//						_delay_ms(5);
//
//										Button_enuRead(&StopButton, &Stop_ButtonState);
//										if(Stop_ButtonState == BUTTON_PRESSED){
//											Global_u8Flag = STOP_FLAG;
//											return ;
//										}
//										Button_enuRead(&ResetButton, &Reset_ButtonState);
//										if(Reset_ButtonState == BUTTON_PRESSED){
//											Global_u8Flag = RESET_FLAG;
//											return ;
//										}
//
//
//						Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8FirstDigit);
//						DisableSegment(Seven_SegmentCom2);
//						EnableSegment(Seven_SegmentCom1);
//						_delay_ms(15);
//					}// for
//
//					Global_u8FirstDigit++;
//				}while(Global_u8FirstDigit<=9);
//
//				Global_u8FirstDigit = 0;
//				Global_u8SecondDigit++;
//			}while(Global_u8SecondDigit<=9);
//
//			Global_u8SecondDigit=0;
//			Global_u8ThirdDigit++;
//		}while(Global_u8ThirdDigit<=9);
//
//		Global_u8ThirdDigit=0;
//		Global_u8ForthDigit++;
//	}while(Global_u8ForthDigit<=9);
//
//}
//
//void StopSegments(void){
//
//	u32 Loc_u32Ticks = ZERO_VALUE;
//	for( Loc_u32Ticks = 0;Loc_u32Ticks<40;++Loc_u32Ticks){
//
//				Button_enuRead(&StartButton, &Start_ButtonState);
//				if(Start_ButtonState == BUTTON_PRESSED){
//					Global_u8Flag = START_FLAG;
//					return ;
//				}
//				Button_enuRead(&ResetButton, &Reset_ButtonState);
//				if(Reset_ButtonState == BUTTON_PRESSED){
//					Global_u8Flag = RESET_FLAG;
//					return ;
//				}
//
//		Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ForthDigit);
//		DisableSegment(Seven_SegmentCom1);
//		EnableSegment(Seven_SegmentCom4);
//		_delay_ms(5);
//
//
//		Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ThirdDigit);
//		DisableSegment(Seven_SegmentCom4);
//		EnableSegment(Seven_SegmentCom3);
//		_delay_ms(5);
//
//					Button_enuRead(&StartButton, &Start_ButtonState);
//					if(Start_ButtonState == BUTTON_PRESSED){
//						Global_u8Flag = START_FLAG;
//						return ;
//					}
//					Button_enuRead(&ResetButton, &Reset_ButtonState);
//					if(Reset_ButtonState == BUTTON_PRESSED){
//						Global_u8Flag = RESET_FLAG;
//						return ;
//					}
//
//
//
//
//		Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8SecondDigit);
//		DisableSegment(Seven_SegmentCom3);
//		EnableSegment(Seven_SegmentCom2);
//		_delay_ms(5);
//
//					Button_enuRead(&StartButton, &Start_ButtonState);
//					if(Start_ButtonState == BUTTON_PRESSED){
//						Global_u8Flag = START_FLAG;
//						return ;
//					}
//					Button_enuRead(&ResetButton, &Reset_ButtonState);
//					if(Reset_ButtonState == BUTTON_PRESSED){
//						Global_u8Flag = RESET_FLAG;
//						return ;
//					}
//
//		Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8FirstDigit);
//		DisableSegment(Seven_SegmentCom2);
//		EnableSegment(Seven_SegmentCom1);
//		_delay_ms(15);
//	}// for
//
//
//}
//
//
//void ResetSegments(void){
//
//	u32 Loc_u32Ticks = ZERO_VALUE;
//
//	Global_u8FirstDigit = 0;
//	Global_u8SecondDigit = 0;
//	Global_u8ThirdDigit = 0;
//	Global_u8ForthDigit = 0;
//
//						for( Loc_u32Ticks = 0;Loc_u32Ticks<40;++Loc_u32Ticks){
//
//								Button_enuRead(&StartButton, &Start_ButtonState);
//								if(Start_ButtonState == BUTTON_PRESSED){
//									Global_u8Flag = START_FLAG;
//									return ;
//								}
//
//							Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ForthDigit);
//							DisableSegment(Seven_SegmentCom1);
//							EnableSegment(Seven_SegmentCom4);
//							_delay_ms(5);
//
//
//							Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ThirdDigit);
//							DisableSegment(Seven_SegmentCom4);
//							EnableSegment(Seven_SegmentCom3);
//							_delay_ms(5);
//
//									Button_enuRead(&StartButton, &Start_ButtonState);
//									if(Start_ButtonState == BUTTON_PRESSED){
//										Global_u8Flag = START_FLAG;
//										return ;
//									}
//
//
//
//
//							Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8SecondDigit);
//							DisableSegment(Seven_SegmentCom3);
//							EnableSegment(Seven_SegmentCom2);
//							_delay_ms(5);
//
//
//									Button_enuRead(&StartButton, &Start_ButtonState);
//									if(Start_ButtonState == BUTTON_PRESSED){
//										Global_u8Flag = START_FLAG;
//										return ;
//									}
//
//							Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8FirstDigit);
//							DisableSegment(Seven_SegmentCom2);
//							EnableSegment(Seven_SegmentCom1);
//							_delay_ms(15);
//						}// for
//
//
//
//
//}



/*		Segment As Counters */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//extern Seven_Segment_BCDType Seven_Segment;
//extern u8 	Seven_SegmentCom4 ;
//extern u8 	Seven_SegmentCom3 ;
//extern u8 	Seven_SegmentCom2 ;
//extern u8 	Seven_SegmentCom1 ;
//
//extern Button_ConfigType Inc_Button;
//extern Button_ConfigType Dec_Button;
//extern Button_ConfigType Reset_Button;
//
/////////////////////////////////////////////////////////////////////////
//
//
//#define START_FLAG 				    	ZERO_VALUE
//#define STOP_FLAG 			    		ONE_VALUE
//#define RESET_FLAG			            TWO_VALUE
//
//
//
/////////////////////////////////////////////////////////////////////
//
//
//Button_StatusErrorType IncButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State );
//Button_StatusErrorType DecButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State );
//Button_StatusErrorType ResetButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State );
//void DisableSegment(u8 Copy_u8SegmentCom);
//void EnableSegment(u8 Copy_u8SegmentCom);
//
/////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//int main(void){
//
//
//	u8 Loc_u8ForthDigit = ZERO_VALUE;
//	u8 Loc_u8ThirdDigit = ZERO_VALUE;
//	u8 Loc_u8SecondDigit = ZERO_VALUE;
//	u8 Loc_u8FirstDigit = ZERO_VALUE;
//
//	u32 Loc_u32Number = ZERO_VALUE;
//
//	Button_PressStatusType Inc_ButtonState = BUTTON_NOT_PRESSED;
//	Button_PressStatusType Dec_ButtonState = BUTTON_NOT_PRESSED;
//	Button_PressStatusType Reset_ButtonState = BUTTON_NOT_PRESSED;
//	Port_voidInit();
//
//
//	while(1){
//
//		u32 Loc_u32Ticks = ZERO_VALUE;
//			for( Loc_u32Ticks = 0;Loc_u32Ticks<40;++Loc_u32Ticks){
//
//				IncButton_enuReadWithDebouncing(&Inc_Button, &Inc_ButtonState);
//				if(Inc_ButtonState == BUTTON_PRESSED && Loc_u32Number<9999){
//					Loc_u32Number++;
//
//
//				}
//
//				DecButton_enuReadWithDebouncing(&Dec_Button, &Dec_ButtonState);
//				if(Dec_ButtonState == BUTTON_PRESSED && Loc_u32Number!=0){
//					Loc_u32Number--;
//
//				}
//				ResetButton_enuReadWithDebouncing(&Reset_Button, &Reset_ButtonState);
//				if(Reset_ButtonState == BUTTON_PRESSED){
//					Loc_u32Number=0;
//
//				}
//
//				Loc_u8FirstDigit = Loc_u32Number %10;
//				Loc_u8SecondDigit = (Loc_u32Number/10) %10;
//				Loc_u8ThirdDigit = (Loc_u32Number/100) %10;
//				Loc_u8ForthDigit = (Loc_u32Number/1000) %10; //9999 --> 9.9999
//
//				Seven_Segment_WriteBCDConnection(&Seven_Segment, Loc_u8ForthDigit);
//				DisableSegment(Seven_SegmentCom1);
//				EnableSegment(Seven_SegmentCom4);
//				_delay_ms(5);
//
//
//				Seven_Segment_WriteBCDConnection(&Seven_Segment, Loc_u8ThirdDigit);
//				DisableSegment(Seven_SegmentCom4);
//				EnableSegment(Seven_SegmentCom3);
//				_delay_ms(5);
//
//
//				Seven_Segment_WriteBCDConnection(&Seven_Segment, Loc_u8SecondDigit);
//				DisableSegment(Seven_SegmentCom3);
//				EnableSegment(Seven_SegmentCom2);
//				_delay_ms(5);
//
//
//				Seven_Segment_WriteBCDConnection(&Seven_Segment, Loc_u8FirstDigit);
//				DisableSegment(Seven_SegmentCom2);
//				EnableSegment(Seven_SegmentCom1);
//				_delay_ms(15);
//			}// for
//
//
//		}
//
//
//
//	return 0;
//}
//
//Button_StatusErrorType IncButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State ){
//
//	Button_StatusErrorType Loc_enuStatus = BUTTON_STATUS_OK;
//
//	/* Button Part */
//	static u16 Loc_u16ButtonCounter = 0;
//
//	Button_PressStatusType Loc_enuButton1Temp = BUTTON_NOT_PRESSED;
//	Button_PressStatusType Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//	static Button_PressStatusType Loc_enuButton1AcutalLastState = BUTTON_NOT_PRESSED;
//
//	////////////////////////////////////////////////////////////////////////////
//	Button_PressStatusType Loc_enuButton1Result = BUTTON_NOT_PRESSED;
//
//	/////////////////////////////////////////////////////////////////
//		if( NULL == Address_Button || NULL == Address_State ){
//			Loc_enuStatus = BUTTON_STATUS_NULL_POINTER_ADDRESS;
//
//		}
//		else{
//			/* Bouncing Part */
//						    Button_enuRead(Address_Button,&Loc_enuButton1Temp);
//						    if(BUTTON_PRESSED == Loc_enuButton1Temp){
//						    	Loc_u16ButtonCounter++;
//						        if(Loc_u16ButtonCounter>2){
//						        	Loc_enuButton1TrueState = BUTTON_PRESSED;
//						        }
//						        else {/* nothing */}
//						    }
//
//						    else{
//						    	Loc_u16ButtonCounter = 0;
//						    	Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//						    }
//
//						    if(Loc_enuButton1TrueState != Loc_enuButton1AcutalLastState){
//						        /* there is change on the button */
//
//						    	Loc_enuButton1AcutalLastState = Loc_enuButton1TrueState;
//
//						        if(BUTTON_PRESSED == Loc_enuButton1AcutalLastState){
//						            /* TAKE THE ACTION*/
//						        	Loc_enuButton1Result = BUTTON_PRESSED;
//						        }
//
//						    }
//
//		    }
//		*Address_State = Loc_enuButton1Result;
//
//
//
//
//		return Loc_enuStatus;
//
//}
//
//Button_StatusErrorType ResetButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State ){
//
//	Button_StatusErrorType Loc_enuStatus = BUTTON_STATUS_OK;
//
//	/* Button Part */
//	static u16 Loc_u16ButtonCounter = 0;
//
//	Button_PressStatusType Loc_enuButton1Temp = BUTTON_NOT_PRESSED;
//	Button_PressStatusType Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//	static Button_PressStatusType Loc_enuButton1AcutalLastState = BUTTON_NOT_PRESSED;
//
//	////////////////////////////////////////////////////////////////////////////
//	Button_PressStatusType Loc_enuButton1Result = BUTTON_NOT_PRESSED;
//
//	/////////////////////////////////////////////////////////////////
//		if( NULL == Address_Button || NULL == Address_State ){
//			Loc_enuStatus = BUTTON_STATUS_NULL_POINTER_ADDRESS;
//
//		}
//		else{
//			/* Bouncing Part */
//						    Button_enuRead(Address_Button,&Loc_enuButton1Temp);
//						    if(BUTTON_PRESSED == Loc_enuButton1Temp){
//						    	Loc_u16ButtonCounter++;
//						        if(Loc_u16ButtonCounter>2){
//						        	Loc_enuButton1TrueState = BUTTON_PRESSED;
//						        }
//						        else {/* nothing */}
//						    }
//
//						    else{
//						    	Loc_u16ButtonCounter = 0;
//						    	Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//						    }
//
//						    if(Loc_enuButton1TrueState != Loc_enuButton1AcutalLastState){
//						        /* there is change on the button */
//
//						    	Loc_enuButton1AcutalLastState = Loc_enuButton1TrueState;
//
//						        if(BUTTON_PRESSED == Loc_enuButton1AcutalLastState){
//						            /* TAKE THE ACTION*/
//						        	Loc_enuButton1Result = BUTTON_PRESSED;
//						        }
//
//						    }
//
//		    }
//		*Address_State = Loc_enuButton1Result;
//
//
//
//
//		return Loc_enuStatus;
//
//}
//
//
//Button_StatusErrorType DecButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State ){
//
//	Button_StatusErrorType Loc_enuStatus = BUTTON_STATUS_OK;
//
//	/* Button Part */
//	static u16 Loc_u16ButtonCounter = 0;
//
//	Button_PressStatusType Loc_enuButton1Temp = BUTTON_NOT_PRESSED;
//	Button_PressStatusType Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//	static Button_PressStatusType Loc_enuButton1AcutalLastState = BUTTON_NOT_PRESSED;
//
//	////////////////////////////////////////////////////////////////////////////
//	Button_PressStatusType Loc_enuButton1Result = BUTTON_NOT_PRESSED;
//
//	/////////////////////////////////////////////////////////////////
//		if( NULL == Address_Button || NULL == Address_State ){
//			Loc_enuStatus = BUTTON_STATUS_NULL_POINTER_ADDRESS;
//
//		}
//		else{
//			/* Bouncing Part */
//						    Button_enuRead(Address_Button,&Loc_enuButton1Temp);
//						    if(BUTTON_PRESSED == Loc_enuButton1Temp){
//						    	Loc_u16ButtonCounter++;
//						        if(Loc_u16ButtonCounter>2){
//						        	Loc_enuButton1TrueState = BUTTON_PRESSED;
//						        }
//						        else {/* nothing */}
//						    }
//
//						    else{
//						    	Loc_u16ButtonCounter = 0;
//						    	Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//						    }
//
//						    if(Loc_enuButton1TrueState != Loc_enuButton1AcutalLastState){
//						        /* there is change on the button */
//
//						    	Loc_enuButton1AcutalLastState = Loc_enuButton1TrueState;
//
//						        if(BUTTON_PRESSED == Loc_enuButton1AcutalLastState){
//						            /* TAKE THE ACTION*/
//						        	Loc_enuButton1Result = BUTTON_PRESSED;
//						        }
//
//						    }
//
//		    }
//		*Address_State = Loc_enuButton1Result;
//
//
//
//
//		return Loc_enuStatus;
//
//}
//
//
//
//void DisableSegment(u8 Copy_u8SegmentCom){
//
//	Dio_enuWriteChannel(Copy_u8SegmentCom, 1);
//}
//
//void EnableSegment(u8 Copy_u8SegmentCom){
//
//	Dio_enuWriteChannel(Copy_u8SegmentCom, 0);
//}



 /******************************** ADC VOLT TASK WITH LCD *************************/
///////////////////////////////////////////////////////////////////////
//

//#define VOLT_FLAG			0
//#define MILLI_VOLT_FLAG		1
//
////////////////////////////////////////////////////////////////////
//extern Lcd_4bitType Lcd;
//
//u8 Global_Flag = VOLT_FLAG;
//
//Adc_PinConfigType Adc1 ={
//		.channel_number = ADC_SELECT_CHANNEL1,
//		.conversion_frequancy = ADC_FOSC_DIV_128,
//		.result_format = ADC_RIGHT_JUSTIFIED,
//		.vref_source = ADC_REF_VOLTAGE_AVCC_WITH_EXTERNAL_CAPACITOR
//
//};
//
//
//void	Exti_ApplicationIsr0_VOLT(){
//	Global_Flag = VOLT_FLAG;
//}
//
//
//void	Exti_ApplicationIsr1_MILIVOLT(){
//	Global_Flag = MILLI_VOLT_FLAG;
//}
//
//
//
//
//int main(void){
//
//	u16 Loc_u16Result= ZERO_VALUE;
//	f32 Loc_f32Result;
//
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//	Adc_enuInit(&Adc1);
//
//		Exti_enuEnable(EXTI_INT0_INDEX, EXTI_INT0_SELECT_FAILING_EDGE);
//		Exti_enuSetCallbackFunction(EXTI_INT0_INDEX, Exti_ApplicationIsr0_VOLT);
//
//		Exti_enuEnable(EXTI_INT1_INDEX, EXTI_INT1_SELECT_FAILING_EDGE);
//		Exti_enuSetCallbackFunction(EXTI_INT1_INDEX, Exti_ApplicationIsr1_MILIVOLT);
//		Gie_enuEnableGlobalInterrupt();
//		Lcd_4bit_enuDisplayString(&Lcd, "Volt= ");
//
//	while(1){
//		Adc_enuStartConversionSync(&Adc1,&Loc_u16Result);
//		Adc_ConvertResultToVoltage(Loc_u16Result, &Loc_f32Result);
//
//		// Volt Mode
//		if(Global_Flag == VOLT_FLAG){
//
//						Loc_u16Result= Loc_f32Result;
//						Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL7);
//						Lcd_4bit_enuDisplayString(&Lcd,"       ");
//						Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL7);
//						Lcd_4bit_enuDisplayNumber(&Lcd,Loc_u16Result);
//						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ',LCD_ROW4, LCD_COL18);
//						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 'V',LCD_ROW4, LCD_COL19);
//
//					}
//					else {
//						Loc_u16Result= Loc_f32Result* 1000;
//						Lcd_4bit_enuDisplayString(&Lcd,"       ");
//						Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL7);
//						Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL7);
//						Lcd_4bit_enuDisplayNumber(&Lcd,Loc_u16Result);
//						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 'm',LCD_ROW4, LCD_COL18);
//						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 'V',LCD_ROW4, LCD_COL19);
//					}
//
//			_delay_ms(25);
//
//	}
//	return 0;
//}




/////////////////////////////////////////////////////////////////////


// ADC  TASK2 Volume Sound Using Interrupts
/////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//extern Lcd_4bitType Lcd;
//
//Adc_PinConfigType Adc0 ={
//		.channel_number = ADC_SELECT_CHANNEL1,
//		.conversion_frequancy = ADC_FOSC_DIV_128,
//		.result_format = ADC_RIGHT_JUSTIFIED,
//		.vref_source = ADC_REF_VOLTAGE_AVCC_WITH_EXTERNAL_CAPACITOR
//
//};
//
//
//
//
//
//u8 Lcd_Custom1[]={0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F};
//u8 Lcd_Custom2[]={0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F};
//u8 Lcd_Custom3[]={0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
//
//void adc_isr(u16 result){
//	if(result<=341){
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 1, LCD_ROW2, LCD_COL12);
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL13);
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL14);
//
//	}
//
//	else if(result<=682){
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 1, LCD_ROW2, LCD_COL12);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 2, LCD_ROW2, LCD_COL13);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL14);
//
//		}
//	else {
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 1, LCD_ROW2, LCD_COL12);
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 2, LCD_ROW2, LCD_COL13);
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 3, LCD_ROW2, LCD_COL14);
//	}
//
//}
//int main(void){
//
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//	Adc_enuInit(&Adc0);
//
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_Custom1, 1);
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_Custom2, 2);
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_Custom3, 3);
//
//	u16 Loc_u32Result= ZERO_VALUE;
//
//
//	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2, LCD_COL5);
//	Lcd_4bit_enuDisplayString(&Lcd, "VOLUME ");
//
//	Adc_SetCallbackFunction(&Adc0, adc_isr);
//	Adc_enuEnableInterrupt();
//
//	Gie_enuEnableGlobalInterrupt();
//
//	while(1){
//		Adc_StartConversionAsync(&Adc0);
//
//
//
//
//		_delay_ms(14);
//	}
//	return 0;
//}
//
//


/////////////////////////////////////////////////////////////////////

//	extern Lcd_4bitType Lcd;
//
//
//int main(void){
//
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//
//	Lcd_4bit_enuDisplayFloatNumber(&Lcd,(f32)(5.4));
//
//	while(1){
//
//
//	}
//	return 0;
//}


//////////////////////////////////LCD As Counters ////////////////////////////////////////


//extern Button_ConfigType Inc_Button;
//extern Button_ConfigType Dec_Button;
//extern Button_ConfigType Reset_Button;
//extern Lcd_4bitType Lcd;
//
/////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////
//
//
//Button_StatusErrorType IncButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State );
//Button_StatusErrorType DecButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State );
//Button_StatusErrorType ResetButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State );
//
//void Application_LcdDisplay(Loc_u32Number);
/////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//int main(void){
//
//
//	u32 Loc_u32Number = ZERO_VALUE;
//
//	Button_PressStatusType Inc_ButtonState = BUTTON_NOT_PRESSED;
//	Button_PressStatusType Dec_ButtonState = BUTTON_NOT_PRESSED;
//	Button_PressStatusType Reset_ButtonState = BUTTON_NOT_PRESSED;
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//
//	Lcd_4bit_enuDisplayString(&Lcd, "The Counter :"); // use 13 cols
//
//	while(1){
//
//
//				IncButton_enuReadWithDebouncing(&Inc_Button, &Inc_ButtonState);
//				if(Inc_ButtonState == BUTTON_PRESSED && Loc_u32Number<9999){
//					Loc_u32Number++;
//
//					Application_LcdDisplay(Loc_u32Number);
//
//				}
//
//				DecButton_enuReadWithDebouncing(&Dec_Button, &Dec_ButtonState);
//				if(Dec_ButtonState == BUTTON_PRESSED && Loc_u32Number!=0){
//					Loc_u32Number--;
//					Application_LcdDisplay(Loc_u32Number);
//
//				}
//				ResetButton_enuReadWithDebouncing(&Reset_Button, &Reset_ButtonState);
//				if(Reset_ButtonState == BUTTON_PRESSED){
//					Loc_u32Number=0;
//					Application_LcdDisplay(Loc_u32Number);
//
//				}
//
//
//
//
//
//	}
//
//
//	return 0;
//}
//
//Button_StatusErrorType IncButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State ){
//
//	Button_StatusErrorType Loc_enuStatus = BUTTON_STATUS_OK;
//
//	/* Button Part */
//	static u16 Loc_u16ButtonCounter = 0;
//
//	Button_PressStatusType Loc_enuButton1Temp = BUTTON_NOT_PRESSED;
//	Button_PressStatusType Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//	static Button_PressStatusType Loc_enuButton1AcutalLastState = BUTTON_NOT_PRESSED;
//
//	////////////////////////////////////////////////////////////////////////////
//	Button_PressStatusType Loc_enuButton1Result = BUTTON_NOT_PRESSED;
//
//	/////////////////////////////////////////////////////////////////
//		if( NULL == Address_Button || NULL == Address_State ){
//			Loc_enuStatus = BUTTON_STATUS_NULL_POINTER_ADDRESS;
//
//		}
//		else{
//			/* Bouncing Part */
//						    Button_enuRead(Address_Button,&Loc_enuButton1Temp);
//						    if(BUTTON_PRESSED == Loc_enuButton1Temp){
//						    	Loc_u16ButtonCounter++;
//						        if(Loc_u16ButtonCounter>100){
//						        	Loc_enuButton1TrueState = BUTTON_PRESSED;
//						        }
//						        else {/* nothing */}
//						    }
//
//						    else{
//						    	Loc_u16ButtonCounter = 0;
//						    	Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//						    }
//
//						    if(Loc_enuButton1TrueState != Loc_enuButton1AcutalLastState){
//						        /* there is change on the button */
//
//						    	Loc_enuButton1AcutalLastState = Loc_enuButton1TrueState;
//
//						        if(BUTTON_PRESSED == Loc_enuButton1AcutalLastState){
//						            /* TAKE THE ACTION*/
//						        	Loc_enuButton1Result = BUTTON_PRESSED;
//						        }
//
//						    }
//
//		    }
//		*Address_State = Loc_enuButton1Result;
//
//
//
//
//		return Loc_enuStatus;
//
//}
//
//Button_StatusErrorType ResetButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State ){
//
//	Button_StatusErrorType Loc_enuStatus = BUTTON_STATUS_OK;
//
//	/* Button Part */
//	static u16 Loc_u16ButtonCounter = 0;
//
//	Button_PressStatusType Loc_enuButton1Temp = BUTTON_NOT_PRESSED;
//	Button_PressStatusType Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//	static Button_PressStatusType Loc_enuButton1AcutalLastState = BUTTON_NOT_PRESSED;
//
//	////////////////////////////////////////////////////////////////////////////
//	Button_PressStatusType Loc_enuButton1Result = BUTTON_NOT_PRESSED;
//
//	/////////////////////////////////////////////////////////////////
//		if( NULL == Address_Button || NULL == Address_State ){
//			Loc_enuStatus = BUTTON_STATUS_NULL_POINTER_ADDRESS;
//
//		}
//		else{
//			/* Bouncing Part */
//						    Button_enuRead(Address_Button,&Loc_enuButton1Temp);
//						    if(BUTTON_PRESSED == Loc_enuButton1Temp){
//						    	Loc_u16ButtonCounter++;
//						        if(Loc_u16ButtonCounter>100){
//						        	Loc_enuButton1TrueState = BUTTON_PRESSED;
//						        }
//						        else {/* nothing */}
//						    }
//
//						    else{
//						    	Loc_u16ButtonCounter = 0;
//						    	Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//						    }
//
//						    if(Loc_enuButton1TrueState != Loc_enuButton1AcutalLastState){
//						        /* there is change on the button */
//
//						    	Loc_enuButton1AcutalLastState = Loc_enuButton1TrueState;
//
//						        if(BUTTON_PRESSED == Loc_enuButton1AcutalLastState){
//						            /* TAKE THE ACTION*/
//						        	Loc_enuButton1Result = BUTTON_PRESSED;
//						        }
//
//						    }
//
//		    }
//		*Address_State = Loc_enuButton1Result;
//
//
//
//
//		return Loc_enuStatus;
//
//}
//
//
//Button_StatusErrorType DecButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State ){
//
//	Button_StatusErrorType Loc_enuStatus = BUTTON_STATUS_OK;
//
//	/* Button Part */
//	static u16 Loc_u16ButtonCounter = 0;
//
//	Button_PressStatusType Loc_enuButton1Temp = BUTTON_NOT_PRESSED;
//	Button_PressStatusType Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//	static Button_PressStatusType Loc_enuButton1AcutalLastState = BUTTON_NOT_PRESSED;
//
//	////////////////////////////////////////////////////////////////////////////
//	Button_PressStatusType Loc_enuButton1Result = BUTTON_NOT_PRESSED;
//
//	/////////////////////////////////////////////////////////////////
//		if( NULL == Address_Button || NULL == Address_State ){
//			Loc_enuStatus = BUTTON_STATUS_NULL_POINTER_ADDRESS;
//
//		}
//		else{
//			/* Bouncing Part */
//						    Button_enuRead(Address_Button,&Loc_enuButton1Temp);
//						    if(BUTTON_PRESSED == Loc_enuButton1Temp){
//						    	Loc_u16ButtonCounter++;
//						        if(Loc_u16ButtonCounter>100){
//						        	Loc_enuButton1TrueState = BUTTON_PRESSED;
//						        }
//						        else {/* nothing */}
//						    }
//
//						    else{
//						    	Loc_u16ButtonCounter = 0;
//						    	Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
//						    }
//
//						    if(Loc_enuButton1TrueState != Loc_enuButton1AcutalLastState){
//						        /* there is change on the button */
//
//						    	Loc_enuButton1AcutalLastState = Loc_enuButton1TrueState;
//
//						        if(BUTTON_PRESSED == Loc_enuButton1AcutalLastState){
//						            /* TAKE THE ACTION*/
//						        	Loc_enuButton1Result = BUTTON_PRESSED;
//						        }
//
//						    }
//
//		    }
//		*Address_State = Loc_enuButton1Result;
//
//
//
//
//		return Loc_enuStatus;
//
//}
//
//
//void Application_LcdDisplay(u32 Number){
//	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL14);
//	Lcd_4bit_enuDisplayString(&Lcd, "    ");
//	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL14);
//	Lcd_4bit_enuDisplayNumber(&Lcd, Number);
//}


/////////////////////////////////////////////////////////////////////

/*******************************Ping Bong ******************************************/

//#define LEFT_CUSTOM_INDEX	    1
//#define RIGHT_CUSTOM_INDEX    	2
//#define THEBALL_CUSTOM_INDEX	3
//#define HITRIGHT_CUSTOM_INDEX	4
//#define HITLEF_CUSTOM_INDEX		5
//
//
/////////////////////////////////////////////
//
//u8 Global_u8CurrentRightRowWall =LCD_ROW2 ;
//u8 Global_u8CurrentLeftRowWall = LCD_ROW2 ;
//
//u8 Loc_u8CurrentBallRow = LCD_ROW2;
//u8 Loc_u8CurrentBallCol = LCD_COL10;
////////////////////////////////////
//extern Lcd_4bitType Lcd;
//
//Adc_PinConfigType Adc1 ={
//		.channel_number = ADC_SELECT_CHANNEL1,
//		.conversion_frequancy = ADC_FOSC_DIV_128,
//		.result_format = ADC_RIGHT_JUSTIFIED,
//		.vref_source = ADC_REF_VOLTAGE_AVCC_WITH_EXTERNAL_CAPACITOR
//
//};
//
//Adc_PinConfigType Adc4 ={
//		.channel_number = ADC_SELECT_CHANNEL4,
//		.conversion_frequancy = ADC_FOSC_DIV_128,
//		.result_format = ADC_RIGHT_JUSTIFIED,
//		.vref_source = ADC_REF_VOLTAGE_AVCC_WITH_EXTERNAL_CAPACITOR
//
//};
//
//
//
//
//
//u8 Lcd_LeftCustomChar[]={0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10};
//u8 Lcd_RightCustomChar[]={0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01};
//u8 Lcd_TheBallCustomChar[]={0x00,0x04,0x0E,0x1F,0x1F,0x0E,0x04,0x00};
//
//u8 Lcd_HitRightCustomChar[]={0x01,0x05,0x0F,0x1F,0x1F,0x0F,0x05,0x01};
//u8 Lcd_HitLeftCustomChar[]={0x10,0x14,0x1E,0x1F,0x1F,0x1E,0x14,0x10};
//
//
//void Application_Adc1Left(u16 Copy_u16result);
//
//void Application_Adc4Right(u16 Copy_u16result);
//
//int main(void){
//
//
//
//	u8 Loc_u8PrevBallRow = LCD_ROW2;
//	u8 Loc_u8PrevBallCol = LCD_COL10;
//
//	u8 Loc_u8ColCounter;
//	u8 Loc_u8RowCounter;
//	s8 Loc_s8RowFlag = -1;
//
//	u8 Loc_OnceFlag = 0;
//
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//	Adc_enuInit(&Adc1);
//	Adc_enuInit(&Adc4);
//
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_LeftCustomChar, LEFT_CUSTOM_INDEX);
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_RightCustomChar, RIGHT_CUSTOM_INDEX);
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_TheBallCustomChar, THEBALL_CUSTOM_INDEX);
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_HitRightCustomChar, HITRIGHT_CUSTOM_INDEX);
//	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_HitLeftCustomChar, HITLEF_CUSTOM_INDEX);
//
//	Adc_SetCallbackFunction(&Adc1, Application_Adc1Left);
//	Adc_SetCallbackFunction(&Adc4, Application_Adc4Right);
//	Adc_enuEnableInterrupt();
//	Gie_enuEnableGlobalInterrupt();
//
//
//	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2, LCD_COL1);
//	Lcd_4bit_enuDisplayCharacter(&Lcd,LEFT_CUSTOM_INDEX);
//
//
//
//	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2, LCD_COL20);
//	Lcd_4bit_enuDisplayCharacter(&Lcd,RIGHT_CUSTOM_INDEX);
//
//	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2, LCD_COL10);
//	Lcd_4bit_enuDisplayCharacter(&Lcd,THEBALL_CUSTOM_INDEX);
//
//
//
//	_delay_ms(500);
//	while(1){
//
//		Adc_StartConversionAsync(&Adc1);
//		Adc_StartConversionAsync(&Adc4);
//
//
//		if(Loc_u8CurrentBallRow == LCD_ROW4)
//			Loc_s8RowFlag = -1;
//		else if(Loc_u8CurrentBallRow == LCD_ROW1)
//			Loc_s8RowFlag = 1;
//
//
//		// Moving Right First
//
//		for(Loc_u8CurrentBallCol = Loc_u8PrevBallCol+1,Loc_u8CurrentBallRow+=Loc_s8RowFlag;
//				Loc_u8CurrentBallCol<=LCD_COL20;
//				                    Loc_u8CurrentBallCol++,Loc_u8CurrentBallRow+=Loc_s8RowFlag){
//
//
//			_delay_ms(500);
//			 Loc_u8PrevBallRow = Loc_u8CurrentBallRow - Loc_s8RowFlag;
//			 Loc_u8PrevBallCol = Loc_u8CurrentBallCol - 1;
//
//			 if(Loc_OnceFlag == 0){
//				 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,' ', Loc_u8PrevBallRow, Loc_u8PrevBallCol);
//			 }
//			 else{
//				 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,LEFT_CUSTOM_INDEX,Loc_u8PrevBallRow , LCD_COL1);
//				 Loc_OnceFlag =0;
//				 Adc_enuEnableInterrupt();
//			 }
//
//			 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, THEBALL_CUSTOM_INDEX, Loc_u8CurrentBallRow, Loc_u8CurrentBallCol);
//
//
//
//			if(Loc_u8CurrentBallRow == LCD_ROW4)
//				Loc_s8RowFlag = -1;
//			else if(Loc_u8CurrentBallRow == LCD_ROW1)
//				Loc_s8RowFlag = 1;
//
//			Adc_StartConversionAsync(&Adc1);
//			Adc_StartConversionAsync(&Adc4);
//
//		}
//
//
//		Adc_enuDisableInterrupt();
//		Loc_u8CurrentBallRow =Loc_u8CurrentBallRow - Loc_s8RowFlag;
//		Loc_u8CurrentBallCol =LCD_COL20;
//
//		if(Loc_u8CurrentBallRow == LCD_ROW4)
//			Loc_s8RowFlag = -1;
//		else if(Loc_u8CurrentBallRow == LCD_ROW1)
//			Loc_s8RowFlag = 1;
//
//
//		if(Loc_u8CurrentBallRow == Global_u8CurrentRightRowWall){
//
//			 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, HITRIGHT_CUSTOM_INDEX, Loc_u8CurrentBallRow, Loc_u8CurrentBallCol);
//			 Loc_OnceFlag = 1;
//
//
//		}
//
//		else{
//			Gie_enuDisableGlobalInterrupt();
//			_delay_ms(500);
//				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
//				_delay_ms(3);
//				Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL5);
//
//				Lcd_4bit_enuDisplayString(&Lcd, " GAME OVER");
//				while(1);
//
//		}
//
//
//		Loc_u8PrevBallRow = Loc_u8CurrentBallRow;
//		Loc_u8PrevBallCol = LCD_COL20;
//
//		// Moving Left
//
//
//		for(Loc_u8CurrentBallCol = Loc_u8PrevBallCol-1,Loc_u8CurrentBallRow+=Loc_s8RowFlag;
//				Loc_u8CurrentBallCol>=LCD_COL1;
//				                    Loc_u8CurrentBallCol--,Loc_u8CurrentBallRow+=Loc_s8RowFlag){
//
//			_delay_ms(500);
//			 Loc_u8PrevBallRow = Loc_u8CurrentBallRow - Loc_s8RowFlag;
//			 Loc_u8PrevBallCol = Loc_u8CurrentBallCol + 1;
//
//
//			 if(Loc_OnceFlag == 0){
//				 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,' ', Loc_u8PrevBallRow, Loc_u8PrevBallCol);
//			 }
//
//			 else{
//				 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,RIGHT_CUSTOM_INDEX,Loc_u8PrevBallRow , LCD_COL20);
//				 				 Loc_OnceFlag =0;
//				 				 Adc_enuEnableInterrupt();
//
//			 }
//
//			 Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, THEBALL_CUSTOM_INDEX, Loc_u8CurrentBallRow, Loc_u8CurrentBallCol);
//
//
//
//			if(Loc_u8CurrentBallRow == LCD_ROW4)
//				Loc_s8RowFlag = -1;
//			else if(Loc_u8CurrentBallRow == LCD_ROW1)
//				Loc_s8RowFlag = 1;
//
//			Adc_StartConversionAsync(&Adc1);
//			Adc_StartConversionAsync(&Adc4);
//		}
//
//		Adc_enuDisableInterrupt();
//
//		Loc_u8CurrentBallRow =Loc_u8CurrentBallRow - Loc_s8RowFlag;
//		Loc_u8CurrentBallCol =LCD_COL1;
//
//		if(Loc_u8CurrentBallRow == LCD_ROW4)
//			Loc_s8RowFlag = -1;
//		else if(Loc_u8CurrentBallRow == LCD_ROW1)
//			Loc_s8RowFlag = 1;
//
//
//		Loc_u8PrevBallRow = Loc_u8CurrentBallRow;
//		Loc_u8PrevBallCol = Loc_u8CurrentBallCol;
//		if(Loc_u8CurrentBallRow == Global_u8CurrentLeftRowWall){
//
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, HITRIGHT_CUSTOM_INDEX, Loc_u8CurrentBallRow, Loc_u8CurrentBallCol);
//			Loc_OnceFlag = 1;
//		}
//		else{
//
//			Gie_enuDisableGlobalInterrupt();
//			_delay_ms(500);
//			Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
//			_delay_ms(3);
//			Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL5);
//
//			Lcd_4bit_enuDisplayString(&Lcd, " GAME OVER");
//			while(1);
//		}
//
//
//	}
//	return 0;
//}
//
//
//
//void Application_Adc1Left(u16 Copy_u16Result){
//
//	if(Copy_u16Result<=255){
//
//		// ROW 4
//			Global_u8CurrentLeftRowWall =LCD_ROW4;
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL1);
////			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LEFT_CUSTOM_INDEX, LCD_ROW4, LCD_COL1);
//
//		}
//
//		else if(Copy_u16Result<=511){
//			// ROW3
//			Global_u8CurrentLeftRowWall =LCD_ROW3;
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL1);
////			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LEFT_CUSTOM_INDEX, LCD_ROW3, LCD_COL1);
//
//
//
//			}
//		else if(Copy_u16Result<=767){
//			// ROW 2
//			Global_u8CurrentLeftRowWall =LCD_ROW2;
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL1);
////			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LEFT_CUSTOM_INDEX, LCD_ROW2, LCD_COL1);
//
//		}
//		else{
//
//
//			// ROW 1
//			Global_u8CurrentLeftRowWall =LCD_ROW1;
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL1);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL1);
////			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LEFT_CUSTOM_INDEX, LCD_ROW1, LCD_COL1);
//
//
//		}
//
//	if(Global_u8CurrentLeftRowWall == Loc_u8CurrentBallRow && Loc_u8CurrentBallCol == LCD_COL1)
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, HITLEF_CUSTOM_INDEX, Loc_u8CurrentBallRow, LCD_COL1);
//	else{
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LEFT_CUSTOM_INDEX, Global_u8CurrentLeftRowWall, LCD_COL1);
//
//	}
//
//
//}
//
//
//
//void Application_Adc4Right(u16 Copy_u16Result){
//	if(Copy_u16Result<=255){
//
//		// ROW 4
//			Global_u8CurrentRightRowWall =LCD_ROW4;
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL20);
////			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX ,LCD_ROW4, LCD_COL20);
//
//
//		}
//
//		else if(Copy_u16Result<=511){
//			// ROW3
//			Global_u8CurrentRightRowWall =LCD_ROW3;
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL20);
////			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX, LCD_ROW3, LCD_COL20);
//
//			}
//		else if(Copy_u16Result<=767){
//			// ROW 2
//			Global_u8CurrentRightRowWall =LCD_ROW2;
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL20);
////			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX, LCD_ROW2, LCD_COL20);
//
//		}
//		else{
//
//			// ROW 1
//			Global_u8CurrentRightRowWall =LCD_ROW1;
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW3, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL20);
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW4, LCD_COL20);
////			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX, LCD_ROW1, LCD_COL20);
//
//		}
//
//	if(Global_u8CurrentRightRowWall == Loc_u8CurrentBallRow && Loc_u8CurrentBallCol == 20)
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, HITRIGHT_CUSTOM_INDEX, Loc_u8CurrentBallRow, LCD_COL20);
//	else{
//		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX, Global_u8CurrentRightRowWall, LCD_COL20);
//	}
//
////			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, RIGHT_CUSTOM_INDEX, Global_u8CurrentRightRowWall, LCD_COL20);
//
//}






///////////////////////////////////////////////////////////////////

		/* Alram and Clock Task */

////////////////////////////////////////////////////////////////////////
//extern Lcd_4bitType Lcd;
//extern Keypad_ConfigType Keypad;
//
//Timer0_ConfigType Timer0 ={
//		.select_mode= TIMER0_SELECT_MODE_NORMAL,
//		.prescaler_value =TIMER0_PRESCALER_DIV_1024,
//		.init_value = 0
//};

//
//u32 Global_u32GlobalAramCounter =10;
//
//
//u32 Global_u32GlobalHour;
//u32 Global_u32GlobalMin ;
//u32 Global_u32GlobalSec;
//
//void Application_GetKeypadAlarm(void);
//void Application_GetKeypadHour(void);
//void Application_GetKeypadMin(void);
//void Application_GetKeypadSecond(void);
//
//void Application_AlaramMode(void);
//void Application_ClockMode(void);
//
//void Alram_Isr(void);
//void Clock_Isr(void);
//
//
//
//
//int main(void){
//
//		u8 Loc_u8KeypadResult=5;
//		Keypad_ErrorStatusType Loc_KeypadStatus = KEYPAD_STATUS_NOT_PRESSED;
//		Port_voidInit();
//		Lcd_4bit_enuInit(&Lcd);
//
//
//
//
//				/////////////
//
//		Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL3);
//		Lcd_4bit_enuDisplayString(&Lcd, "Choose Which Mode :");
//
//		Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW3, LCD_COL1);
//		Lcd_4bit_enuDisplayString(&Lcd, "1- Alram");
//
//		Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW4, LCD_COL1);
//		Lcd_4bit_enuDisplayString(&Lcd, "2- Clock");
//
//			////////////
//
//
//		while(1){
//
//			Keypad_enuRead(&Keypad, &Loc_u8KeypadResult);
//
//			if(Loc_u8KeypadResult == '1'){
//
//				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
//				_delay_ms(KEYPAD_DELAY);
//
//
//
//				Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL1);
//				Lcd_4bit_enuDisplayString(&Lcd, "Alarm: ");
//
//				_delay_ms(LCD_DISPLAY_DELAY);
//
//				Application_GetKeypadAlarm();
//
//				Timer0_enuInit(&Timer0);
//				Timer0_SetCallbackFunction(&Timer0,Alram_Isr);
//				Timer0_enuEnableInterrupt(&Timer0);
//				Gie_enuEnableGlobalInterrupt();
//				Application_AlaramMode();
//
//			}
//
//			else if(Loc_u8KeypadResult == '2'){
//
//								Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
//								_delay_ms(KEYPAD_DELAY);
//
//								Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Clock  ", LCD_ROW2, LCD_COL1);
//								Application_GetKeypadHour();
//								Lcd_4bit_enuDisplayStringWithPosition(&Lcd, ":", LCD_ROW2, LCD_COL10);
//								Application_GetKeypadMin();
//								Lcd_4bit_enuDisplayStringWithPosition(&Lcd, ":", LCD_ROW2, LCD_COL13);
//								Application_GetKeypadSecond();
//
//								Timer0_enuInit(&Timer0);
//								Timer0_SetCallbackFunction(&Timer0,Clock_Isr);
//								Timer0_enuEnableInterrupt(&Timer0);
//								Gie_enuEnableGlobalInterrupt();
//
//								Application_ClockMode();
//									while(1){
//
//									}
//			}
//
//		}
//}
//
//
//
//
//
//
//void Alram_Isr(void){
//
//	static volatile u8 Loc_u8Counter = ZERO_VALUE;
//
//
//
//	if(Loc_u8Counter ==  61){
//		Global_u32GlobalAramCounter --;
//
//		Loc_u8Counter = ZERO_VALUE;
//	}
//
//	else{
//		Loc_u8Counter++;
//	}
//}
//
//
//void Clock_Isr(void){
//	static volatile u8 Loc_u8Counter = ZERO_VALUE;
//
//
//	if(Loc_u8Counter ==  61){
//		Global_u32GlobalSec ++;
//		if(Global_u32GlobalSec == 60){
//			Global_u32GlobalSec =0;
//			Global_u32GlobalMin++;
//		}
//		if(Global_u32GlobalMin == 60){
//			Global_u32GlobalSec = 0;
//			Global_u32GlobalMin = 0;
//			Global_u32GlobalHour++;
//		}
//	if(Global_u32GlobalHour == 24){
//		Global_u32GlobalSec = ZERO_VALUE;
//		Global_u32GlobalMin = ZERO_VALUE;
//		Global_u32GlobalHour= ZERO_VALUE;
//	}
//
//	Loc_u8Counter = ZERO_VALUE;
//	}
//
//	else{
//		Loc_u8Counter++;
//	}
//}
//
//void Application_AlaramMode(void){
//
//	while(1){
//		Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL8);
//		Lcd_4bit_enuDisplayString(&Lcd,"    ");
//
//		if(Global_u32GlobalAramCounter != 0){
//			Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL8);
//			Lcd_4bit_enuDisplayNumber(&Lcd, Global_u32GlobalAramCounter);
//
//		_delay_ms(100);
//		}
//		else {
//			Dio_enuWriteChannel(DIO_PINC6_CHANNEL22,DIO_HIGH);
//			Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Buzzer is On", LCD_ROW2, LCD_COL8);
//
//			Timer0_enuDisableInterrupt(&Timer0);
//			while(1);
//		}
//
//	}
//
//}
//
//
////								Hour 8,9
////								min 11,12
////								sec 14,15
//
//
//
//void Application_ClockMode(void){
//	while(1){
//
//
//		if(Global_u32GlobalHour<=9){
//			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,'0', LCD_ROW2, LCD_COL8);
//			Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalHour,LCD_ROW2,LCD_COL9);
//		}
//		else{
//			Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalHour,LCD_ROW2,LCD_COL8);
//		}
//
//		if(Global_u32GlobalMin<=9){
//					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,'0', LCD_ROW2, LCD_COL11);
//					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalMin,LCD_ROW2,LCD_COL12);
//				}
//				else{
//					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalMin,LCD_ROW2,LCD_COL11);
//				}
//
//		if(Global_u32GlobalSec<=9){
//					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,'0', LCD_ROW2, LCD_COL14);
//					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalSec,LCD_ROW2,LCD_COL15);
//				}
//				else{
//					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Global_u32GlobalSec,LCD_ROW2,LCD_COL14);
//				}
//
//			_delay_ms(LCD_DISPLAY_DELAY);
//
//
//
//		}
//}
//
//
//
//
//void Application_GetKeypadAlarm(void){
//
//	u8 temp='a';
//	Keypad_ErrorStatusType Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
//	u8 tempArr[100];
//	u8 Loc_u8Index = 0;
//	u8 Loc_u8Check = ONE_VALUE;
//
//	while(Loc_u8Check == ONE_VALUE){
//
//		Keypad_Status = Keypad_enuRead(&Keypad, &temp);
//		if(Keypad_Status == KEYPAD_IS_PRESSED){
//
//			if(temp>='0' && temp<='9'){
//				Lcd_4bit_enuDisplayCharacter(&Lcd, temp);
//				tempArr[Loc_u8Index++]=temp;
//				_delay_ms(KEYPAD_DELAY);
//			}
//			else if(temp == '='){
//				Loc_u8Check = ZERO_VALUE;
//			}
//		}
//	}
//
//	tempArr[Loc_u8Index]='\0';
//	Convert_StringTou32(&Global_u32GlobalAramCounter, tempArr);
//
//}
//
//void Application_GetKeypadHour(void){
//	u8 temp='a';
//	Keypad_ErrorStatusType Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
//	u8 tempArr[100];
//	u8 Loc_u8Index = 0;
//	u8 Loc_u8Check = 2;
//
//	while(Loc_u8Check != ZERO_VALUE){
//
//		Keypad_Status = Keypad_enuRead(&Keypad, &temp);
//		if(Keypad_Status == KEYPAD_IS_PRESSED){
//
//			if(temp>='0' && temp<='9'){
//				Lcd_4bit_enuDisplayCharacter(&Lcd, temp);
//				tempArr[Loc_u8Index++]=temp;
//
//				Loc_u8Check--;
//				_delay_ms(KEYPAD_DELAY);
//			}
//
//		}
//	}
//
//	tempArr[Loc_u8Index]='\0';
//	Convert_StringTou32(&Global_u32GlobalHour, tempArr);
//}
//
//
//void Application_GetKeypadSecond(void){
//	u8 temp='a';
//	Keypad_ErrorStatusType Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
//	u8 tempArr[100];
//	u8 Loc_u8Index = 0;
//	u8 Loc_u8Check = 2;
//
//	while(Loc_u8Check != ZERO_VALUE){
//
//		Keypad_Status = Keypad_enuRead(&Keypad, &temp);
//		if(Keypad_Status == KEYPAD_IS_PRESSED){
//
//			if(temp>='0' && temp<='9'){
//				Lcd_4bit_enuDisplayCharacter(&Lcd, temp);
//				tempArr[Loc_u8Index++]=temp;
//
//				Loc_u8Check--;
//				_delay_ms(KEYPAD_DELAY);
//			}
//
//		}
//	}
//
//	tempArr[Loc_u8Index]='\0';
//	Convert_StringTou32(&Global_u32GlobalSec, tempArr);
//}
//
//void Application_GetKeypadMin(void){
//	u8 temp='a';
//	Keypad_ErrorStatusType Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
//	u8 tempArr[100];
//	u8 Loc_u8Index = 0;
//	u8 Loc_u8Check = 2;
//
//	while(Loc_u8Check != ZERO_VALUE){
//
//		Keypad_Status = Keypad_enuRead(&Keypad, &temp);
//		if(Keypad_Status == KEYPAD_IS_PRESSED){
//
//			if(temp>='0' && temp<='9'){
//				Lcd_4bit_enuDisplayCharacter(&Lcd, temp);
//				tempArr[Loc_u8Index++]=temp;
//
//				Loc_u8Check--;
//				_delay_ms(KEYPAD_DELAY);
//			}
//
//		}
//	}
//
//	tempArr[Loc_u8Index]='\0';
//	Convert_StringTou32(&Global_u32GlobalMin, tempArr);
//}
//////////////////////////////////////////////////////////////

//
//
//Timer0_ConfigType Timer0 ={
//		.select_mode= TIMER0_SELECT_MODE_NORMAL,
//		.prescaler_value =TIMER0_PRESCALER_DIV_1024,
//		.init_value = 0
//};
//
//
/////////////////////////////////////////////////////////////////////
//
//extern Lcd_4bitType Lcd;
//extern Keypad_ConfigType Keypad;
////////////////////////////////////////////////////
//
//void Keypad_IsrRead(void);
//
//void Calculator_GetEquation(void);
//void Calculator_DisplayResult(void);
//void Calculator_DoOperations(void);
//
//void Calculator_DisplaySyntxError(void);
//void Calculator_DisplayMathError(void);
//void Calculator_Clear(void);
//
//void Calculator_DoMulandDivide(void);
//void Calculator_DoSumandSub(void);
//
//void Calculator_InitValues(void);
///////////////////////////////////////////////////
//
//typedef enum{
//	CALCULATOR_FLAG_CLEAR,
//	CALCULATOR_FLAG_OK
//
//}Calculator_FlagType;
//
///////////////////////////////////////////////////
//u8 Keypad_Result;
//Keypad_ErrorStatusType Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
//u8 Global_u8EquationArray[100];
//u8 Global_u8Index =ZERO_VALUE;
//
//u8 Global_u8Mul_Divide_Operations =0;
//u8 Global_u8Mul_Divide_Inxdex =0;
//u8 Global_u8Operations =0;
//
//Calculator_FlagType Global_enuFlag = CALCULATOR_FLAG_OK;
////////////////////////////////////////////////////////////////////
//
//int main(void){
//
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//
//	Timer0_enuInit(&Timer0);
//	Timer0_SetCallbackFunction(&Timer0,Keypad_IsrRead);
//	Timer0_enuEnableInterrupt(&Timer0);
//	Gie_enuEnableGlobalInterrupt();
//
//
//
//	while(1){
//		Calculator_InitValues();
//		Calculator_GetEquation();
//		Calculator_DisplayResult();
//
//
//
//
//	}
//	return 0;
//}
/////////////////////////////////////////////////////////////////////
//
//void Calculator_GetEquation(void){
//
//	u8 Loc_u8Flag = ONE_VALUE;
//	Global_enuFlag = CALCULATOR_FLAG_OK;
//
//
//	while(Loc_u8Flag != ZERO_VALUE){
//			if(Keypad_Status == KEYPAD_IS_PRESSED){
//				switch(Keypad_Result){
//
//				case 'c' :
//					Global_enuFlag = CALCULATOR_FLAG_CLEAR;
//					Loc_u8Flag = ZERO_VALUE;
//					break;
//
//				case '=' :
//					Loc_u8Flag = ZERO_VALUE;
//					Lcd_4bit_enuDisplayCharacter(&Lcd, Keypad_Result);
//					break;
//
//
//				case '+' :
//				case '-' :
//
//					Global_u8EquationArray[Global_u8Index++]=Keypad_Result;
//					Global_u8Operations++;
//					Lcd_4bit_enuDisplayCharacter(&Lcd, Keypad_Result);
//					break;
//
//				case '/' :
//				case '*' :
//
//					Global_u8Mul_Divide_Inxdex = Global_u8Index;
//					Global_u8EquationArray[Global_u8Index++]=Keypad_Result;
//					Global_u8Mul_Divide_Operations++;
//					Global_u8Operations++;
//					Lcd_4bit_enuDisplayCharacter(&Lcd, Keypad_Result);
//					break;
//
//				default:
//
//					Global_u8EquationArray[Global_u8Index++]=Keypad_Result;
//
//					Lcd_4bit_enuDisplayCharacter(&Lcd, Keypad_Result);
//					break;
//
//				}
//
//
//
//
//
//				Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
//			}
//	}
//
//	Global_u8EquationArray[Global_u8Index]='\0';
//
//}
//
//
//void Calculator_DisplayResult(void){
//
//	u8 Loc_u8Flag = ONE_VALUE;
//
//
//	switch(Global_enuFlag){
//
//	case CALCULATOR_FLAG_CLEAR:
//		Calculator_Clear();
//		break;
//
//	case CALCULATOR_FLAG_OK :
//
//			if(Global_u8Mul_Divide_Operations >1 || (Global_u8EquationArray[0]=='*' ||Global_u8EquationArray[0]=='/') ){
//				// more than one * /
//				Calculator_DisplaySyntxError();
//			}
//			else if(Global_u8EquationArray[Global_u8Index-1]=='*' ||Global_u8EquationArray[Global_u8Index-1]=='/' ||
//					Global_u8EquationArray[Global_u8Index-1]=='-' || Global_u8EquationArray[Global_u8Index-1]=='+'  ) {
//				// ends with += -=
//				Calculator_DisplaySyntxError();
//			}
//
//			else if(Global_u8Operations == 0){
//
//				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, Global_u8EquationArray,LCD_ROW3,LCD_COL5);
//
//			}
//			else if(Global_u8Mul_Divide_Inxdex != 0 && (Global_u8EquationArray[Global_u8Mul_Divide_Inxdex-1]=='*' ||Global_u8EquationArray[Global_u8Mul_Divide_Inxdex-1]=='/'||
//					Global_u8EquationArray[Global_u8Mul_Divide_Inxdex-1]=='-' || Global_u8EquationArray[Global_u8Mul_Divide_Inxdex-1]=='+'  )  ){
//						Calculator_DisplaySyntxError();
//			}
//			else{
//
//				Calculator_DoOperations();
//
//				// poing til press Clear
//						while(Loc_u8Flag != ZERO_VALUE){
//							if(Keypad_Status == KEYPAD_IS_PRESSED && Keypad_Result =='c'){
//								Calculator_Clear();
//
//								Loc_u8Flag = ZERO_VALUE;
//
//							}
//						}
//			}
//
//		break;
//
//	default :
//			break;
//
//	}
//}
//
/////////////////////////////////////////////////////////////////////
//
//
//
//void Calculator_DisplaySyntxError(void){
//
//	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
//	_delay_ms(LCD_CLEAR_DELAY);
//	Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Syntax Error", LCD_ROW2, LCD_COL2);
//}
//
//
//void Calculator_DisplayMathError(void){
//	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
//	_delay_ms(LCD_CLEAR_DELAY);
//	Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Math Error", LCD_ROW2, LCD_COL2);
//}
//
//void Calculator_Clear(void){
//	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
//	_delay_ms(LCD_CLEAR_DELAY);
//}
//
/////////////////////////////////////////////////////////////////////
//
//void Calculator_DoOperations(void){
//
//
//			if(Global_u8Mul_Divide_Operations != 0){  // it's mul or division
//				Calculator_DoMulandDivide();
//			}
//
//		// it's + - operations
//			else{
//				Calculator_DoSumandSub();
//			}
//}
//
//
/////////////////////////////////////////////////////////////////////
//
//
//void Calculator_DoMulandDivide(void){
//	u8 Loc_u8Counter = ZERO_VALUE;
//
//	s8 Loc_s8FirstOperandSign = 1;
//	u8 Loc_u8FirstOperandArr[100] ;
//	u8 Loc_u8FirstOperandIndex = 0;
//	u32 Loc_u32FirstOperand;
//
//	u8 Loc_u8Operation ;
//
//
//	s8 Loc_s8SecondOperandSign = 1;
//	u8 Loc_u8SecondOperandArr[100] ;
//	u8 Loc_u8SecondOperandIndex = 0;
//	u32 Loc_u32SecondOperand;
//
//
//	s8 Loc_s8ResultSign = 1;
//	u32 Loc_u32ResultOperand;
//	f32 Loc_f32ResultOperandInFloat;
//	u8 Loc_u8ArrResultOperandInFloat[100];
//	while( (Global_u8EquationArray[Loc_u8Counter] != '/') && (Global_u8EquationArray[Loc_u8Counter] != '*') ){
//
//		if (Global_u8EquationArray[Loc_u8Counter] == '-'){
//			Loc_s8FirstOperandSign*=-1;
//		}
//		else if(Global_u8EquationArray[Loc_u8Counter] >= '0' && Global_u8EquationArray[Loc_u8Counter] <= '9' ){
//			Loc_u8FirstOperandArr[Loc_u8FirstOperandIndex++]= Global_u8EquationArray[Loc_u8Counter];
//
//
//		}
//
//		Loc_u8Counter++;
//	}
//
//
//
//	Loc_u8FirstOperandArr[Loc_u8FirstOperandIndex]= '\0';
//	Convert_StringTou32(&Loc_u32FirstOperand, Loc_u8FirstOperandArr);
//
//
//
//	Loc_u8Operation = Global_u8EquationArray[Loc_u8Counter];
//
//
//
//	for(Loc_u8Counter= Loc_u8Counter+1;Loc_u8Counter<Global_u8Index;Loc_u8Counter++){
//		if (Global_u8EquationArray[Loc_u8Counter] == '-'){
//			Loc_s8SecondOperandSign*=-1;
//		}
//		else if(Global_u8EquationArray[Loc_u8Counter] >= '0' && Global_u8EquationArray[Loc_u8Counter] <= '9' ){
//			Loc_u8SecondOperandArr[Loc_u8SecondOperandIndex++]= Global_u8EquationArray[Loc_u8Counter];
//		}
//	}
//
//	Loc_u8SecondOperandArr[Loc_u8SecondOperandIndex]= '\0';
//	Convert_StringTou32(&Loc_u32SecondOperand, Loc_u8SecondOperandArr);
//
//
//
//
//	if(Loc_u8FirstOperandIndex == ZERO_VALUE){
//		// -+-*5
//		Calculator_DisplaySyntxError();
//
//	}
//
//	else{
//
//
//		Loc_s8ResultSign = Loc_s8FirstOperandSign * Loc_s8SecondOperandSign;
//
//		if(Loc_u8Operation =='*'){
//			Loc_u32ResultOperand = Loc_u32SecondOperand *Loc_u32FirstOperand;
//
//			if(Loc_u32FirstOperand == 0){
//
//				Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, 0,LCD_ROW3, LCD_COL6);
//			}
//			else{
//				if(Loc_s8ResultSign==-1)
//					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);
//
//
//				Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u32ResultOperand,LCD_ROW3, LCD_COL6);
//			}
//		}
//
//		else if(Loc_u8Operation =='/'){
//
//			if(Loc_u32SecondOperand == 0){
//				Calculator_DisplayMathError();
//			}
//
//			else{
//				Loc_f32ResultOperandInFloat = (float)Loc_u32FirstOperand/Loc_u32SecondOperand;
//				if(Loc_u32FirstOperand == 0){
//
//					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, 0,LCD_ROW3, LCD_COL6);
//				}
//				else {
//
//
//				if(Loc_s8ResultSign==-1)
//					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);
//				Convert_FloatToString(Loc_f32ResultOperandInFloat, Loc_u8ArrResultOperandInFloat);
//				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, Loc_u8ArrResultOperandInFloat,LCD_ROW3, LCD_COL6);
//
//
//				}
//			}
//		}
//	}
//
//
//
//
//
//
//}
//
//void Calculator_DoSumandSub(void){
//	u8 Loc_u8Counter = ZERO_VALUE;
//
//	s8 Loc_s8FirstOperandSign = 1;
//	u8 Loc_u8FirstOperandArr[100] ;
//	u8 Loc_u8FirstOperandIndex = 0;
//	u32 Loc_u32FirstOperand;
//	u8 Loc_u8FirstOperandFlag= ZERO_VALUE;
//
//	u8 Loc_u8Operation ;
//
//
//	s8 Loc_s8SecondOperandSign = 1;
//	u8 Loc_u8SecondOperandArr[100]={'0'} ;
//	u8 Loc_u8SecondOperandIndex = 0;
//	u32 Loc_u32SecondOperand;
//
//
//	s8 Loc_s8ResultSign = 1;
//	u32 Loc_u32ResultOperand;
//	f32 Loc_f32ResultOperandInFloat;
//	u8 Loc_u8ArrResultOperandInFloat[100];
//
//	// first find position of starting of first operand
//
//	for(Loc_u8Counter = ZERO_VALUE;   (Global_u8EquationArray[Loc_u8Counter] >= '0' && Global_u8EquationArray[Loc_u8Counter] <= '9') ==ZERO_VALUE;  Loc_u8Counter++ ){
//
//		if (Global_u8EquationArray[Loc_u8Counter] == '-'){
//			Loc_s8FirstOperandSign*=-1;
//		}
//
//	}
//
//
//
//	// loop til find first operation
//	for( ;  Global_u8EquationArray[Loc_u8Counter]!= '\0' && (Global_u8EquationArray[Loc_u8Counter] >= '0' && Global_u8EquationArray[Loc_u8Counter] <= '9');  Loc_u8Counter++ ){
//
//		Loc_u8FirstOperandArr[Loc_u8FirstOperandIndex++]= Global_u8EquationArray[Loc_u8Counter];
//
//		}
//
//
//
//	Loc_u8FirstOperandArr[Loc_u8FirstOperandIndex]= '\0';
//	Convert_StringTou32(&Loc_u32FirstOperand, Loc_u8FirstOperandArr);
//
//	if( Global_u8EquationArray[Loc_u8Counter]== '\0'){
//
//		if(Loc_u32FirstOperand == 0){
//			Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, 0,LCD_ROW3, LCD_COL6);
//		}
//		else{
//			if(Loc_s8FirstOperandSign==-1)
//						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);
//
//					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, Loc_u8FirstOperandArr,LCD_ROW3, LCD_COL6);
//		}
//
//	}
//
//
//	else{
//		// loop til find second operation
//			for(; (Global_u8EquationArray[Loc_u8Counter] >= '0' && Global_u8EquationArray[Loc_u8Counter] <= '9') ==ZERO_VALUE;  Loc_u8Counter++ ){
//
//				if (Global_u8EquationArray[Loc_u8Counter] == '-'){
//					Loc_s8SecondOperandSign*=-1;
//				}
//
//			}
//
//
//			// loop til find second operation
//			while (Global_u8EquationArray[Loc_u8Counter]!= '\0' ){
//
//				Loc_u8SecondOperandArr[Loc_u8SecondOperandIndex++]= Global_u8EquationArray[Loc_u8Counter++];
//
//				}
//			Loc_u8SecondOperandArr[Loc_u8SecondOperandIndex]= '\0';
//				Convert_StringTou32(&Loc_u32SecondOperand, Loc_u8SecondOperandArr);
//
//				if(Loc_s8SecondOperandSign == Loc_s8FirstOperandSign){
//
//					Loc_u32ResultOperand = Loc_u32SecondOperand + Loc_u32FirstOperand;
//					if(Loc_s8FirstOperandSign==-1)
//						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);
//
//					Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u32ResultOperand,LCD_ROW3, LCD_COL6);
//				}
//
//
//				else{
//					if(Loc_u32SecondOperand== Loc_u32FirstOperand){
//						Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, 0,LCD_ROW3, LCD_COL6);
//					}
//					else if (Loc_u32SecondOperand < Loc_u32FirstOperand){
//						Loc_u32ResultOperand = Loc_u32FirstOperand-Loc_u32SecondOperand;
//						if(Loc_s8FirstOperandSign==-1)
//							Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);
//
//						Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u32ResultOperand,LCD_ROW3, LCD_COL6);
//					}
//
//					else{
//						Loc_u32ResultOperand = Loc_u32SecondOperand-Loc_u32FirstOperand;
//						if(Loc_u32SecondOperand==-1)
//							Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, '-', LCD_ROW3, LCD_COL5);
//
//						Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u32ResultOperand,LCD_ROW3, LCD_COL6);
//					}
//
//				}
//
//
//
//	}
//
//
//
//
//
//
//}
//
//
//
//void Keypad_IsrRead(void){
//
//	static u8 counter = 0;
//	counter ++;
//
//	if(counter == 8){
//
//		counter = 0;
//		Keypad_Status = Keypad_enuRead(&Keypad, &Keypad_Result);
//	}
//
//
//}
//
//void Calculator_InitValues(void){
//	Keypad_Result='g';
//	Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
//	Global_u8EquationArray[0]='\0';
//	Global_u8Index =ZERO_VALUE;
//
//	Global_u8Mul_Divide_Operations =0;
//	Global_u8Operations =0;
//	Global_enuFlag = CALCULATOR_FLAG_OK;
//	Global_u8Mul_Divide_Inxdex=0;
//
//
//}


///////////////////////////////////////////////////////////////////

//Timer0_ConfigType Timer0 ={
//		.select_mode= TIMER0_SELECT_MODE_PWM_FAST_NOT_INVERTED_OC0_CLEAR_ON_MATCH_SET_AT_TOP,  /*period= (prescaler/clock) * 2^n   */
//		.prescaler_value =TIMER0_PRESCALER_DIV_1024,
//		.init_value = 0
//};


/////////////////////////Watch Dog Test//////////////////////////////////////////////////////////////


//int main(void){
//
//	Port_voidInit();
//	u8 Loc_u8Counter = ZERO_VALUE;
//	Dio_enuWriteChannel(DIO_PINA6_CHANNEL6,DIO_HIGH);
//
//
//	Wtd_enuSleep(WTD_SELECT_SLEEP_1_Sec);
//
//	while(1){
//
//		_delay_ms(500);
//		Dio_enuWriteChannel(DIO_PINA6_CHANNEL6,DIO_LOW);
//
//
//
//	}
//	return 0;
//}


//////////////////////////////////////////////////// ICUSW TEST ///////////////////////////////////////////////////////


//
//Icusw_ConfigType Icusw0={
//		.exti_Intx_Index = EXTI_INT0_INDEX,
//		.timer_index = ICUSW_TIMER_INDEX_TIMER0
//};
//
//
//extern Lcd_4bitType Lcd;
//
//int main(void){
//
//	Port_voidInit();
//	Icusw_enuInit(&Icusw0);
//	Lcd_4bit_enuInit(&Lcd);
//
//	u32 Loc_u32Dutycycle = 0;
//	u32 Loc_u32OnTime = 0;
//	u32 Loc_u32TotalTime = 0;
//
//	while(1){
//
//		Icusw_enuGetOnTimeMilliSeconds(&Icusw0,&Loc_u32OnTime );
//
//		Icusw_enuGetTotalTimeMilliSeconds(&Icusw0,&Loc_u32TotalTime );
//
//		Icusw_enuGetDutyCycleMilliSeconds(&Icusw0,&Loc_u32Dutycycle );
//
//		Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Total Time", LCD_ROW1, LCD_COL1);
//		Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u32TotalTime);
//		Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "on Time", LCD_ROW2, LCD_COL1);
//
//		Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u32OnTime);
//		Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Duty Time", LCD_ROW3, LCD_COL1);
//
//		Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u32Dutycycle);
//
//		_delay_ms(1000);
//
//
//	}
//	return 0;
//}


/////////////////////////////////////////////////////////////////////////

					/* ICUHw (Timer1 Peripheral ) Test
					 *
					 */
////////////////////////////////////////////////////////////////////////
//extern Lcd_4bitType Lcd;
//Timer1_ConfigType Timer1={
//		.init_counter_value = ZERO_VALUE,
//		.prescaler_value = TIMER1_PRESCALER_DIV_256,
//		.select_mode= TIMER1_SELECT_MODE_NORMAL_MODE0,
//		.select_output_mode_channelA = TIMER1_SELECT_OUTPUT_MODE_NORMAL_CHANNELA,
//		.select_output_mode_channelB = TIMER1_SELECT_OUTPUT_MODE_NORMAL_CHANNELB
//};
///////////////////////////////////////////////////////////////////
//
//u64 Global_u64OnTime =ZERO_VALUE;
//u64 Global_u64TotalTime =ZERO_VALUE;
//u64 Global_u64DutyCycle =ZERO_VALUE;
//
//
//u64 Global_u64OnTicks =ZERO_VALUE;
//u64 Global_u64TotalTicks =ZERO_VALUE;
//
//
//
//u64 Global_u64OverflowCounter =ZERO_VALUE;
//
//////////////////////////////////////////////////////////
//
//void Timer1_Isr(void){
//	Global_u64OverflowCounter++;
//}
//
//void Icu_Isr(void){
//
//	f64 Loc_f64TickTimeMiliSeconds = 0.016;  /* Prescaler/16000000 */
//	static u8 Loc_u8Counter = ZERO_VALUE;
//
//	static u16 Loc_u16FirstTicks = ZERO_VALUE;
//	static u16 Loc_u16SecondTicks = ZERO_VALUE;
//	static u16 Loc_u16ThirdTicks = ZERO_VALUE;
//
//
//	if(Loc_u8Counter == ZERO_VALUE){
//		Loc_u8Counter++;
//		Global_u64OverflowCounter = ZERO_VALUE;
//		Timer1_enuToggleEdgeIcu();
//		Timer1_enuGetTimeElapsedIcu(&Loc_u16FirstTicks);
//
//
//	}
//	else if (Loc_u8Counter == ONE_VALUE){
//		Loc_u8Counter++;
//		Timer1_enuToggleEdgeIcu();
//		Timer1_enuGetTimeElapsedIcu(&Loc_u16SecondTicks);
//		Global_u64OnTicks = Loc_u16SecondTicks + (Global_u64OverflowCounter * TIMER1_16BIT_MAX_REGISTER_VALUE)-Loc_u16FirstTicks;
//		Global_u64OnTime = Global_u64OnTicks * Loc_f64TickTimeMiliSeconds;
//	}
//
//	else if (Loc_u8Counter == TWO_VALUE){
//
//		Dio_enuFlipChannel(DIO_PINC0_CHANNEL16);
//		Timer1_enuGetTimeElapsedIcu(&Loc_u16ThirdTicks);
//		Global_u64TotalTicks = Loc_u16ThirdTicks + (Global_u64OverflowCounter * TIMER1_16BIT_MAX_REGISTER_VALUE)-Loc_u16FirstTicks;
//		Global_u64TotalTime = Global_u64TotalTicks * Loc_f64TickTimeMiliSeconds;
//		Global_u64DutyCycle = (u64)((Global_u64OnTime*100.0)/Global_u64TotalTime);
//		/* start of First Edge Already */
//		Loc_u8Counter = ONE_VALUE;
//		Timer1_enuToggleEdgeIcu();
//		Loc_u16FirstTicks = Loc_u16ThirdTicks;
//		Global_u64OverflowCounter = ZERO_VALUE;
//
//	}
//
//}
///////////////////////////////////////////////////////////////////
//int main(void){
//
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//
//	Timer1_enuSetCallbackFunctionOverflow(Timer1_Isr);
//	Timer1_enuSetCallbackFunctionIcu(Icu_Isr);
//
//	Timer1_enuSetRisingEdgeIcu();
//	Timer1_enuEnableInterruptIcu();
//	Timer1_enuEnableInterruptOverflow();
//	Gie_enuEnableGlobalInterrupt();
//
//	Timer1_enuInit(&Timer1);
//	while(1){
//
//				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Total Time: ", LCD_ROW1, LCD_COL1);
//				Lcd_4bit_enuDisplayNumber(&Lcd, Global_u64TotalTime);
//				Lcd_4bit_enuDisplayString(&Lcd, " [mV]");
//
//				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "on Time: ", LCD_ROW2, LCD_COL1);
//				Lcd_4bit_enuDisplayNumber(&Lcd, Global_u64OnTime);
//				Lcd_4bit_enuDisplayString(&Lcd, " [mV]");
//
//				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Duty Cycle:", LCD_ROW3, LCD_COL1);
//				Lcd_4bit_enuDisplayNumber(&Lcd, Global_u64DutyCycle);
//				Lcd_4bit_enuDisplayString(&Lcd, "%");
//
//				_delay_ms(1000);
//
//	}
//	return 0;
//}

////////////////////////////////////////////////////////////////////

/************* Timer2 Test **************************************/

/////////////////////////////////////////////////////////////////////

//extern Lcd_4bitType Lcd;
//Timer2_ConfigType Timer2 ={
//		.init_value_general_counter = ZERO_VALUE,
//		.select_mode = TIMER2_SELECT_MODE_NORMAL,
//		.prescaler_value = TIMER2_PRESCALER_DIV_1024
//
//};
//
//////////////////////////////////////////////////////////////////////////////////////
//void Timer2_Isr(void);
////////////////////////////////////////////////////////////////////////////////////////
//
//
//int main(void){
//
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//
//	Timer2_enuInit(&Timer2);
//	Timer2_enuEnableOverflowInterrupt();
//	Timer2_enuSetCallbackOverflowInterrupt(&Timer2_Isr);
//	Gie_enuEnableGlobalInterrupt();
//
//	while(1){
//
//
//
//
//	}
//	return 0;
//}
//
//
//
//
//void Timer2_Isr(void){
//
//	// every 1 sec
//	static volatile u8 Loc_u8Counter = ZERO_VALUE;
//	Loc_u8Counter++;
//
//
//	if(Loc_u8Counter ==  61){
//		 Dio_enuFlipChannel(DIO_PINA6_CHANNEL6);
//
//		Loc_u8Counter = ZERO_VALUE;
//	}
//
//
//}


/************************************ UART PART *********************************/
////////////////////////////////////////////////////////////////////////////////////////
//
//Usart_ConfigType Usart1={
//		.baude_rate = 9600,
//		.character_size = USART_CHARACTER_SIZE_8_BIT,
//		.parity_bits = USART_SELECT_PARITY_DISABLE,
//		.stop_bits= USART_SELECT_1STOP_BIT,
//		.sync_mode = USAR_SELECT_ASYNCHRONOUS_MODE
//};
//
//extern Lcd_4bitType Lcd;
////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//void usart_Rxisr(u16 Copy_u16Result){
//
//	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,Copy_u16Result,LCD_ROW1,LCD_COL1);
//
//}
//
//int main(void){
//
//
//
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//	Usart_enuInit(&Usart1);
//	Usart_enuEnableRxInterrupt();
//	Usart_enuSetCallbackRxFunction(usart_Rxisr);
//	Gie_enuEnableGlobalInterrupt();
//	while(1){
//
//
//
//
//	}
//	return 0;
//}

////////////////////////////////////////////////////////////////////////////////////

			/* SPI Part */
////////////////////////////////////////////////////////////////////////////////////////

//Spi_ConfigType Spi={
//		.select_clk_speed = SPI_SELECT_CLK_FREQ_DIV_128,
//		.select_data_ording = SPI_SELECT_DATA_LSB_FIRST,
//		.select_master_or_slave = SPI_SELECT_MASTER_MODE,
//		.select_phase = SPI_SELECT_PHASE_SETUP_WRITE_FIRST_AT_LEADING_EDGE,
//		.select_polarity = SPI_SELECT_POLARITY_IDLE_LOW_LEADING_EDGE_RISING
//};
//
//extern Lcd_4bitType Lcd;
////////////////////////////////////////////////////////////////////////////////////////
//
//
//int main(void){
//
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//	Spi_enuInit(&Spi);
//	u8 Loc_u8Result;
//
//	while(1){
//
//		Spi_enuTransmitBlocking(SLAVE_SS1, '1', &Loc_u8Result);
//		if(Loc_u8Result == '8'){
//			Dio_enuWriteChannel(DIO_PINC0_CHANNEL16, DIO_HIGH);
//		}
//		else if(Loc_u8Result == '9'){
//			Dio_enuWriteChannel(DIO_PINC0_CHANNEL16, DIO_LOW);
//		}
//		_delay_ms(1000);
//		Spi_enuTransmitBlocking(SLAVE_SS1, '0', &Loc_u8Result);
//		if(Loc_u8Result == '8'){
//			Dio_enuWriteChannel(DIO_PINC0_CHANNEL16, DIO_HIGH);
//		}
//		else if(Loc_u8Result == '9'){
//			Dio_enuWriteChannel(DIO_PINC0_CHANNEL16, DIO_LOW);
//		}
//		_delay_ms(1000);
//
//	}
//	return 0;
//}


////////////////////////////////////////////////////////////////////////////////////////

/****************************SPI Master **********************************************/

//extern Lcd_4bitType Lcd;
////////////////////////////////////////////////////////////////////////////////////////
//
//Spi_ConfigType Spi ={
//		.select_clk_speed = SPI_SELECT_CLK_FREQ_DIV_128,
//		.select_data_ording = SPI_SELECT_DATA_LSB_FIRST,
//		.select_master_or_slave = SPI_SELECT_MASTER_MODE,
//		.select_phase = SPI_SELECT_PHASE_SETUP_WRITE_FIRST_AT_LEADING_EDGE,
//		.select_polarity = SPI_SELECT_POLARITY_IDLE_LOW_LEADING_EDGE_RISING
//};
//
//int main(void){
//
//	Port_voidInit();
//	u8 Data;
//	Spi_enuInit(&Spi);
//	Lcd_4bit_enuInit(&Lcd);
//
//
//
//
//
//	u8 arr[]="Node2: Data is Sent";
//	int i = 0;
//	while(arr[i]){
//		Spi_enuTransmitBlocking(SLAVE_SS1, arr[i++], &Data);
//		Lcd_4bit_enuDisplayCharacter(&Lcd, Data);
//		if(Data == 'l'){
//			Dio_enuWriteChannel(DIO_PINC0_CHANNEL16, DIO_HIGH);
//		}
//	}
//	while(1){
//
//
//
//	}
//	return 0;
//}



///////////////////////////I2c Test///////////////////////////////////////////////////////////////
//
//extern Lcd_4bitType Lcd;
//#define SLAVE_ADDRESS 0b1010000
//
////////////////////////////////////////////////////////////////////////////////////////
//
//I2c_ConfigType I2c={
//		.clock_freq =(u32)400000,
//		.select_prescale_value_twps = I2C_SELECT_PRESCALER_VALUE_1,
//		.slave_address_or_minus_one_for_master_mode = -1
//};
//
//
//int main(void){
//
//	u8 Loc_u8Temp = 1;
//	u8 Loc_u8Counter = ZERO_VALUE;
//	u8 Loc_u8TempCounter = ZERO_VALUE;
//	Port_voidInit();
//	I2c_enuInit(&I2c);
//	Lcd_4bit_enuInit(&Lcd);
//	u8 Loc_ArrofChar[]="123";
//	u8 Loc_AnswerArray[100]={};
////	for(Loc_u8Counter = ZERO_VALUE; Loc_ArrofChar[Loc_u8Counter];Loc_u8Counter++){
////		ExternalEeprom_WriteByte(Loc_u8Counter, Loc_ArrofChar[Loc_u8Counter]);
////		_delay_us(1);
////	}
//
//	ExternalEeprom_WriteU8Array(SLAVE_ADDRESS,0,Loc_ArrofChar,strlen(Loc_ArrofChar));
//
//	for(int i = 0;i<(u8)strlen(Loc_ArrofChar);++i){
//		ExternalEeprom_ReadByte(SLAVE_ADDRESS,i, &Loc_u8Temp);
//		Lcd_4bit_enuDisplayCharacter(&Lcd, Loc_u8Temp);
//	}
//
//
//	while(1){
//
//
//
//
//
//
//
//
//	}
//	return 0;
//}


//////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////I2c TC74 Test///////////////////////////////////////////////////////////////
//
//extern Lcd_4bitType Lcd;
//#define SLAVE_ADDRESS 0b1001000
//
////////////////////////////////////////////////////////////////////////////////////////
//
//I2c_ConfigType I2c={
//		.clock_freq =(u32)400000,
//		.select_prescale_value_twps = I2C_SELECT_PRESCALER_VALUE_1,
//		.slave_address_or_minus_one_for_master_mode = -1
//};
//
//
//int main(void){
//
//	u8 Loc_u8Temp = 1;
//	Port_voidInit();
//	I2c_enuInit(&I2c);
//	Lcd_4bit_enuInit(&Lcd);
//
//
//	while(1){
//
//
//
//
//		Tc74_ReadByte(TC74_SLAVE_ADDRESS,&Loc_u8Temp);
//		Lcd_4bit_enuDisplayNumberWithPosition(&Lcd,Loc_u8Temp,LCD_ROW1,LCD_COL1);
//
//		_delay_ms(500);
//
//
//
//	}
//	return 0;
//}

////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////I2c TC74 Test///////////////////////////////////////////////////////////////
//
//extern Lcd_4bitType Lcd;
//
////////////////////////////////////////////////////////////////////////////////////////
//
//I2c_ConfigType I2c={
//		.clock_freq =(u32)400000,
//		.select_prescale_value_twps = I2C_SELECT_PRESCALER_VALUE_1,
//		.slave_address_or_minus_one_for_master_mode = -1
//};
//
//
//int main(void){
//
//	u8 Loc_u8Temp = 1;
//	Port_voidInit();
//	I2c_enuInit(&I2c);
//	Lcd_4bit_enuInit(&Lcd);
//
//
//	while(1){
//
//
//
//
//		Rtc_enuGetSecond(&Loc_u8Temp);
//		Lcd_4bit_enuDisplayStringWithPosition(&Lcd,"     ",LCD_ROW1, LCD_COL1);
//		Lcd_4bit_enuDisplayNumberWithPosition(&Lcd,Loc_u8Temp,LCD_ROW1,LCD_COL1);
//
//		_delay_ms(100);
//		Rtc_enuGetMinute(&Loc_u8Temp);
//		Lcd_4bit_enuDisplayStringWithPosition(&Lcd,"     ",LCD_ROW2, LCD_COL1);
//		Lcd_4bit_enuDisplayNumberWithPosition(&Lcd,Loc_u8Temp,LCD_ROW2,LCD_COL1);
//
//		_delay_ms(100);
//		Rtc_enuGetHour(&Loc_u8Temp);
//		Lcd_4bit_enuDisplayStringWithPosition(&Lcd,"     ",LCD_ROW3, LCD_COL1);
//		Lcd_4bit_enuDisplayNumberWithPosition(&Lcd,Loc_u8Temp,LCD_ROW3,LCD_COL1);
//
//		_delay_ms(100);
//
//
//	}
//	return 0;
//}

////////////////////////////////////////////////////////////////////////////////////////

///****************************SPI Master **********************************************/
//
//extern Lcd_4bitType Lcd;
////////////////////////////////////////////////////////////////////////////////////////
//
//Spi_ConfigType Spi ={
//		.select_clk_speed = SPI_SELECT_CLK_FREQ_DIV_128,
//		.select_data_ording = SPI_SELECT_DATA_LSB_FIRST,
//		.select_master_or_slave = SPI_SELECT_MASTER_MODE,
//		.select_phase = SPI_SELECT_PHASE_SETUP_WRITE_FIRST_AT_LEADING_EDGE,
//		.select_polarity = SPI_SELECT_POLARITY_IDLE_LOW_LEADING_EDGE_RISING
//};
//
//int main(void){
//
//	Port_voidInit();
//	u8 Data;
//	Spi_enuInit(&Spi);
//	Lcd_4bit_enuInit(&Lcd);
//
//
//
//
//
//	u8 arr[]="Interrupt Is working";
//	int i = 0;
//	while(arr[i]){
//		Spi_enuTransmitBlocking(SLAVE_SS1, arr[i++], &Data);
//		Lcd_4bit_enuDisplayCharacter(&Lcd, Data);
//
//	}
//	while(1){
//
////		Lcd_4bit_enuDisplayCharacter(&Lcd, 'a');
//
//
//	}
//	return 0;
//}

//////////////////////////////////////////////////////////////////////////////////////////

///* SPI Part Salve Part Using Interrupts */
//////////////////////////////////////////////////////////////////////////////////////////
//
//Spi_ConfigType Spi={
//.select_clk_speed = SPI_SELECT_CLK_FREQ_DIV_128,
//.select_data_ording = SPI_SELECT_DATA_LSB_FIRST,
//.select_master_or_slave = SPI_SELECT_SLAVE_MODE,
//.select_phase = SPI_SELECT_PHASE_SETUP_WRITE_FIRST_AT_LEADING_EDGE,
//.select_polarity = SPI_SELECT_POLARITY_IDLE_LOW_LEADING_EDGE_RISING
//};
//
//extern Lcd_4bitType Lcd;
////////////////////////////////////////////////////////////////////////////////////////
//
//
//void spi_isr(u8 result){
//Lcd_4bit_enuDisplayCharacter(&Lcd, result);
//
//}
//
//int main(void){
//
//Port_voidInit();
//Lcd_4bit_enuInit(&Lcd);
//Spi_enuInit(&Spi);
//Spi_enuEnableInterrupt();
//Spi_enuSetCallbackFunction(spi_isr);
//Gie_enuEnableGlobalInterrupt();
//
//
//
//
//
//while(1){
//
//
//}
//return 0;
//}
//
//


////////////////////////////////////////////////////////////////////////////////////////

/* LM35 Temp Sensor */

////////////////////////////////////////////////////////////////////
//extern Lcd_4bitType Lcd;
//
//
//Adc_PinConfigType Adc0 ={
//		.channel_number = ADC_SELECT_CHANNEL0,
//		.conversion_frequancy = ADC_FOSC_DIV_128,
//		.result_format = ADC_RIGHT_JUSTIFIED,
//		.vref_source = ADC_REF_VOLTAGE_AVCC_WITH_EXTERNAL_CAPACITOR
//
//};
//
//
//
//int main(void){
//
//	u16 Loc_u16Result= ZERO_VALUE;
//	f32 Loc_f32Result;
//
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//	Adc_enuInit(&Adc0);
//
//
//	while(1){
//		Adc_enuStartConversionSync(&Adc0, &Loc_u16Result);
//		Adc_ConvertResultToVoltage(Loc_u16Result, &Loc_f32Result);
//		Convert_VoltToTempLm35(Loc_f32Result, &Loc_u16Result);
//		Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u16Result,LCD_ROW1,LCD_COL1);
//		_delay_ms(1000);
//
//
//	}
//	return 0;
//}



////////////////////////////////////////////////////////////////////////////////////////

extern Lcd_4bitType Lcd;
//////////////////////////////////////////////////////////////////////////////////////


int main(void){

	Port_voidInit();
	Lcd_4bit_enuInit(&Lcd);
	Servo_enuInitTimer1();


	while(1){

		Servo_enuSetAngle(0);
		_delay_ms(1000);

		Servo_enuSetAngle(90);
		_delay_ms(1000);

		Servo_enuSetAngle(180);
		_delay_ms(1000);


	}
	return 0;
}




////////////////////////////////////////////////////////////////////////////////////////

//extern Lcd_4bitType Lcd;
////////////////////////////////////////////////////////////////////////////////////////
//
//
//int main(void){
//
//	Port_voidInit();
//	Lcd_4bit_enuInit(&Lcd);
//
//
//	while(1){
//
//
//
//
//	}
//	return 0;
//}
