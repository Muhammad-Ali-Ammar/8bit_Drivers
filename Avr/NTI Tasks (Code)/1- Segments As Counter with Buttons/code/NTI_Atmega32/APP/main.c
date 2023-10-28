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





extern Seven_Segment_BCDType Seven_Segment;
extern u8 	Seven_SegmentCom4 ;
extern u8 	Seven_SegmentCom3 ;
extern u8 	Seven_SegmentCom2 ;
extern u8 	Seven_SegmentCom1 ;

extern Button_ConfigType Inc_Button;
extern Button_ConfigType Dec_Button;
extern Button_ConfigType Reset_Button;

///////////////////////////////////////////////////////////////////////


#define START_FLAG 				    	ZERO_VALUE
#define STOP_FLAG 			    		ONE_VALUE
#define RESET_FLAG			            TWO_VALUE



///////////////////////////////////////////////////////////////////


Button_StatusErrorType IncButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State );
Button_StatusErrorType DecButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State );
Button_StatusErrorType ResetButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State );
void DisableSegment(u8 Copy_u8SegmentCom);
void EnableSegment(u8 Copy_u8SegmentCom);

///////////////////////////////////////////////////////////////////////





int main(void){


	u8 Loc_u8ForthDigit = ZERO_VALUE;
	u8 Loc_u8ThirdDigit = ZERO_VALUE;
	u8 Loc_u8SecondDigit = ZERO_VALUE;
	u8 Loc_u8FirstDigit = ZERO_VALUE;

	u32 Loc_u32Number = ZERO_VALUE;

	Button_PressStatusType Inc_ButtonState = BUTTON_NOT_PRESSED;
	Button_PressStatusType Dec_ButtonState = BUTTON_NOT_PRESSED;
	Button_PressStatusType Reset_ButtonState = BUTTON_NOT_PRESSED;
	Port_voidInit();


	while(1){

		u32 Loc_u32Ticks = ZERO_VALUE;
			for( Loc_u32Ticks = 0;Loc_u32Ticks<40;++Loc_u32Ticks){

				IncButton_enuReadWithDebouncing(&Inc_Button, &Inc_ButtonState);
				if(Inc_ButtonState == BUTTON_PRESSED && Loc_u32Number<9999){
					Loc_u32Number++;


				}

				DecButton_enuReadWithDebouncing(&Dec_Button, &Dec_ButtonState);
				if(Dec_ButtonState == BUTTON_PRESSED && Loc_u32Number!=0){
					Loc_u32Number--;

				}
				ResetButton_enuReadWithDebouncing(&Reset_Button, &Reset_ButtonState);
				if(Reset_ButtonState == BUTTON_PRESSED){
					Loc_u32Number=0;

				}

				Loc_u8FirstDigit = Loc_u32Number %10;
				Loc_u8SecondDigit = (Loc_u32Number/10) %10;
				Loc_u8ThirdDigit = (Loc_u32Number/100) %10;
				Loc_u8ForthDigit = (Loc_u32Number/1000) %10; //9999 --> 9.9999

				Seven_Segment_WriteBCDConnection(&Seven_Segment, Loc_u8ForthDigit);
				DisableSegment(Seven_SegmentCom1);
				EnableSegment(Seven_SegmentCom4);
				_delay_ms(5);


				Seven_Segment_WriteBCDConnection(&Seven_Segment, Loc_u8ThirdDigit);
				DisableSegment(Seven_SegmentCom4);
				EnableSegment(Seven_SegmentCom3);
				_delay_ms(5);


				Seven_Segment_WriteBCDConnection(&Seven_Segment, Loc_u8SecondDigit);
				DisableSegment(Seven_SegmentCom3);
				EnableSegment(Seven_SegmentCom2);
				_delay_ms(5);


				Seven_Segment_WriteBCDConnection(&Seven_Segment, Loc_u8FirstDigit);
				DisableSegment(Seven_SegmentCom2);
				EnableSegment(Seven_SegmentCom1);
				_delay_ms(15);
			}// for


		}



	return 0;
}

Button_StatusErrorType IncButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State ){

	Button_StatusErrorType Loc_enuStatus = BUTTON_STATUS_OK;

	/* Button Part */
	static u16 Loc_u16ButtonCounter = 0;

	Button_PressStatusType Loc_enuButton1Temp = BUTTON_NOT_PRESSED;
	Button_PressStatusType Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
	static Button_PressStatusType Loc_enuButton1AcutalLastState = BUTTON_NOT_PRESSED;

	////////////////////////////////////////////////////////////////////////////
	Button_PressStatusType Loc_enuButton1Result = BUTTON_NOT_PRESSED;

	/////////////////////////////////////////////////////////////////
		if( NULL == Address_Button || NULL == Address_State ){
			Loc_enuStatus = BUTTON_STATUS_NULL_POINTER_ADDRESS;

		}
		else{
			/* Bouncing Part */
						    Button_enuRead(Address_Button,&Loc_enuButton1Temp);
						    if(BUTTON_PRESSED == Loc_enuButton1Temp){
						    	Loc_u16ButtonCounter++;
						        if(Loc_u16ButtonCounter>2){
						        	Loc_enuButton1TrueState = BUTTON_PRESSED;
						        }
						        else {/* nothing */}
						    }

						    else{
						    	Loc_u16ButtonCounter = 0;
						    	Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
						    }

						    if(Loc_enuButton1TrueState != Loc_enuButton1AcutalLastState){
						        /* there is change on the button */

						    	Loc_enuButton1AcutalLastState = Loc_enuButton1TrueState;

						        if(BUTTON_PRESSED == Loc_enuButton1AcutalLastState){
						            /* TAKE THE ACTION*/
						        	Loc_enuButton1Result = BUTTON_PRESSED;
						        }

						    }

		    }
		*Address_State = Loc_enuButton1Result;




		return Loc_enuStatus;

}

Button_StatusErrorType ResetButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State ){

	Button_StatusErrorType Loc_enuStatus = BUTTON_STATUS_OK;

	/* Button Part */
	static u16 Loc_u16ButtonCounter = 0;

	Button_PressStatusType Loc_enuButton1Temp = BUTTON_NOT_PRESSED;
	Button_PressStatusType Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
	static Button_PressStatusType Loc_enuButton1AcutalLastState = BUTTON_NOT_PRESSED;

	////////////////////////////////////////////////////////////////////////////
	Button_PressStatusType Loc_enuButton1Result = BUTTON_NOT_PRESSED;

	/////////////////////////////////////////////////////////////////
		if( NULL == Address_Button || NULL == Address_State ){
			Loc_enuStatus = BUTTON_STATUS_NULL_POINTER_ADDRESS;

		}
		else{
			/* Bouncing Part */
						    Button_enuRead(Address_Button,&Loc_enuButton1Temp);
						    if(BUTTON_PRESSED == Loc_enuButton1Temp){
						    	Loc_u16ButtonCounter++;
						        if(Loc_u16ButtonCounter>2){
						        	Loc_enuButton1TrueState = BUTTON_PRESSED;
						        }
						        else {/* nothing */}
						    }

						    else{
						    	Loc_u16ButtonCounter = 0;
						    	Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
						    }

						    if(Loc_enuButton1TrueState != Loc_enuButton1AcutalLastState){
						        /* there is change on the button */

						    	Loc_enuButton1AcutalLastState = Loc_enuButton1TrueState;

						        if(BUTTON_PRESSED == Loc_enuButton1AcutalLastState){
						            /* TAKE THE ACTION*/
						        	Loc_enuButton1Result = BUTTON_PRESSED;
						        }

						    }

		    }
		*Address_State = Loc_enuButton1Result;




		return Loc_enuStatus;

}


Button_StatusErrorType DecButton_enuReadWithDebouncing(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State ){

	Button_StatusErrorType Loc_enuStatus = BUTTON_STATUS_OK;

	/* Button Part */
	static u16 Loc_u16ButtonCounter = 0;

	Button_PressStatusType Loc_enuButton1Temp = BUTTON_NOT_PRESSED;
	Button_PressStatusType Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
	static Button_PressStatusType Loc_enuButton1AcutalLastState = BUTTON_NOT_PRESSED;

	////////////////////////////////////////////////////////////////////////////
	Button_PressStatusType Loc_enuButton1Result = BUTTON_NOT_PRESSED;

	/////////////////////////////////////////////////////////////////
		if( NULL == Address_Button || NULL == Address_State ){
			Loc_enuStatus = BUTTON_STATUS_NULL_POINTER_ADDRESS;

		}
		else{
			/* Bouncing Part */
						    Button_enuRead(Address_Button,&Loc_enuButton1Temp);
						    if(BUTTON_PRESSED == Loc_enuButton1Temp){
						    	Loc_u16ButtonCounter++;
						        if(Loc_u16ButtonCounter>2){
						        	Loc_enuButton1TrueState = BUTTON_PRESSED;
						        }
						        else {/* nothing */}
						    }

						    else{
						    	Loc_u16ButtonCounter = 0;
						    	Loc_enuButton1TrueState = BUTTON_NOT_PRESSED;
						    }

						    if(Loc_enuButton1TrueState != Loc_enuButton1AcutalLastState){
						        /* there is change on the button */

						    	Loc_enuButton1AcutalLastState = Loc_enuButton1TrueState;

						        if(BUTTON_PRESSED == Loc_enuButton1AcutalLastState){
						            /* TAKE THE ACTION*/
						        	Loc_enuButton1Result = BUTTON_PRESSED;
						        }

						    }

		    }
		*Address_State = Loc_enuButton1Result;




		return Loc_enuStatus;

}



void DisableSegment(u8 Copy_u8SegmentCom){

	Dio_enuWriteChannel(Copy_u8SegmentCom, 1);
}

void EnableSegment(u8 Copy_u8SegmentCom){

	Dio_enuWriteChannel(Copy_u8SegmentCom, 0);
}


