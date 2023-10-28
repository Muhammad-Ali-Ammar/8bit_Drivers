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






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern Seven_Segment_BCDType Seven_Segment;
extern u8 	Seven_SegmentCom4 ;
extern u8 	Seven_SegmentCom3 ;
extern u8 	Seven_SegmentCom2 ;
extern u8 	Seven_SegmentCom1 ;

extern Button_ConfigType StartButton;
extern Button_ConfigType StopButton;
extern Button_ConfigType ResetButton;

///////////////////////////////////////////////////////////////////////


#define START_FLAG 				    	ZERO_VALUE
#define STOP_FLAG 			    		ONE_VALUE
#define RESET_FLAG			            TWO_VALUE



///////////////////////////////////////////////////////////////////
u8 Global_u8ForthDigit = ZERO_VALUE;
u8 Global_u8ThirdDigit = ZERO_VALUE;
u8 Global_u8SecondDigit = ZERO_VALUE;
u8 Global_u8FirstDigit = ZERO_VALUE;
u8 Global_u8Flag = RESET_FLAG;

Button_PressStatusType Start_ButtonState = BUTTON_NOT_PRESSED;
Button_PressStatusType Stop_ButtonState = BUTTON_NOT_PRESSED;
Button_PressStatusType Reset_ButtonState = BUTTON_NOT_PRESSED;
///////////////////////////////////////////////////////////////////////

void DisableSegment(u8 Copy_u8SegmentCom);
void EnableSegment(u8 Copy_u8SegmentCom);
void StartSegments(void);
void StopSegments(void);
void ResetSegments(void);

///////////////////////////////////////////////////////////////////////

int main(void){


	Port_voidInit();

	ResetSegments();

	while(1){

		switch(Global_u8Flag){
			case START_FLAG:
				StartSegments();
				break;
			case STOP_FLAG:
				StopSegments();
				break;
			case RESET_FLAG:
				ResetSegments();
				break;
			default:
				break;


		}




	}
	return 0;
}

void DisableSegment(u8 Copy_u8SegmentCom){

	Dio_enuWriteChannel(Copy_u8SegmentCom, 1);
}

void EnableSegment(u8 Copy_u8SegmentCom){

	Dio_enuWriteChannel(Copy_u8SegmentCom, 0);
}
void StartSegments(void){



	u32 Loc_u32Ticks = ZERO_VALUE;


	do{
		do{
			do{
				do{


					for( Loc_u32Ticks = 0;Loc_u32Ticks<40;++Loc_u32Ticks){

									Button_enuRead(&StopButton, &Stop_ButtonState);
									if(Stop_ButtonState == BUTTON_PRESSED){
										Global_u8Flag = STOP_FLAG;
										return ;
									}
									Button_enuRead(&ResetButton, &Reset_ButtonState);
									if(Reset_ButtonState == BUTTON_PRESSED){
										Global_u8Flag = RESET_FLAG;
										return ;
									}

						Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ForthDigit);
						DisableSegment(Seven_SegmentCom1);
						EnableSegment(Seven_SegmentCom4);
						_delay_ms(5);

													Button_enuRead(&StopButton, &Stop_ButtonState);
													if(Stop_ButtonState == BUTTON_PRESSED){
														Global_u8Flag = STOP_FLAG;
														return ;
													}
													Button_enuRead(&ResetButton, &Reset_ButtonState);
													if(Reset_ButtonState == BUTTON_PRESSED){
														Global_u8Flag = RESET_FLAG;
														return ;
													}
						Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ThirdDigit);
						DisableSegment(Seven_SegmentCom4);
						EnableSegment(Seven_SegmentCom3);
						_delay_ms(5);


						Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8SecondDigit);
						DisableSegment(Seven_SegmentCom3);
						EnableSegment(Seven_SegmentCom2);
						_delay_ms(5);

										Button_enuRead(&StopButton, &Stop_ButtonState);
										if(Stop_ButtonState == BUTTON_PRESSED){
											Global_u8Flag = STOP_FLAG;
											return ;
										}
										Button_enuRead(&ResetButton, &Reset_ButtonState);
										if(Reset_ButtonState == BUTTON_PRESSED){
											Global_u8Flag = RESET_FLAG;
											return ;
										}


						Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8FirstDigit);
						DisableSegment(Seven_SegmentCom2);
						EnableSegment(Seven_SegmentCom1);
						_delay_ms(15);
					}// for

					Global_u8FirstDigit++;
				}while(Global_u8FirstDigit<=9);

				Global_u8FirstDigit = 0;
				Global_u8SecondDigit++;
			}while(Global_u8SecondDigit<=9);

			Global_u8SecondDigit=0;
			Global_u8ThirdDigit++;
		}while(Global_u8ThirdDigit<=9);

		Global_u8ThirdDigit=0;
		Global_u8ForthDigit++;
	}while(Global_u8ForthDigit<=9);

}

void StopSegments(void){

	u32 Loc_u32Ticks = ZERO_VALUE;
	for( Loc_u32Ticks = 0;Loc_u32Ticks<40;++Loc_u32Ticks){

				Button_enuRead(&StartButton, &Start_ButtonState);
				if(Start_ButtonState == BUTTON_PRESSED){
					Global_u8Flag = START_FLAG;
					return ;
				}
				Button_enuRead(&ResetButton, &Reset_ButtonState);
				if(Reset_ButtonState == BUTTON_PRESSED){
					Global_u8Flag = RESET_FLAG;
					return ;
				}

		Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ForthDigit);
		DisableSegment(Seven_SegmentCom1);
		EnableSegment(Seven_SegmentCom4);
		_delay_ms(5);


		Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ThirdDigit);
		DisableSegment(Seven_SegmentCom4);
		EnableSegment(Seven_SegmentCom3);
		_delay_ms(5);

					Button_enuRead(&StartButton, &Start_ButtonState);
					if(Start_ButtonState == BUTTON_PRESSED){
						Global_u8Flag = START_FLAG;
						return ;
					}
					Button_enuRead(&ResetButton, &Reset_ButtonState);
					if(Reset_ButtonState == BUTTON_PRESSED){
						Global_u8Flag = RESET_FLAG;
						return ;
					}




		Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8SecondDigit);
		DisableSegment(Seven_SegmentCom3);
		EnableSegment(Seven_SegmentCom2);
		_delay_ms(5);

					Button_enuRead(&StartButton, &Start_ButtonState);
					if(Start_ButtonState == BUTTON_PRESSED){
						Global_u8Flag = START_FLAG;
						return ;
					}
					Button_enuRead(&ResetButton, &Reset_ButtonState);
					if(Reset_ButtonState == BUTTON_PRESSED){
						Global_u8Flag = RESET_FLAG;
						return ;
					}

		Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8FirstDigit);
		DisableSegment(Seven_SegmentCom2);
		EnableSegment(Seven_SegmentCom1);
		_delay_ms(15);
	}// for


}


void ResetSegments(void){

	u32 Loc_u32Ticks = ZERO_VALUE;

	Global_u8FirstDigit = 0;
	Global_u8SecondDigit = 0;
	Global_u8ThirdDigit = 0;
	Global_u8ForthDigit = 0;

						for( Loc_u32Ticks = 0;Loc_u32Ticks<40;++Loc_u32Ticks){

								Button_enuRead(&StartButton, &Start_ButtonState);
								if(Start_ButtonState == BUTTON_PRESSED){
									Global_u8Flag = START_FLAG;
									return ;
								}

							Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ForthDigit);
							DisableSegment(Seven_SegmentCom1);
							EnableSegment(Seven_SegmentCom4);
							_delay_ms(5);


							Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8ThirdDigit);
							DisableSegment(Seven_SegmentCom4);
							EnableSegment(Seven_SegmentCom3);
							_delay_ms(5);

									Button_enuRead(&StartButton, &Start_ButtonState);
									if(Start_ButtonState == BUTTON_PRESSED){
										Global_u8Flag = START_FLAG;
										return ;
									}




							Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8SecondDigit);
							DisableSegment(Seven_SegmentCom3);
							EnableSegment(Seven_SegmentCom2);
							_delay_ms(5);


									Button_enuRead(&StartButton, &Start_ButtonState);
									if(Start_ButtonState == BUTTON_PRESSED){
										Global_u8Flag = START_FLAG;
										return ;
									}

							Seven_Segment_WriteBCDConnection(&Seven_Segment, Global_u8FirstDigit);
							DisableSegment(Seven_SegmentCom2);
							EnableSegment(Seven_SegmentCom1);
							_delay_ms(15);
						}// for




}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

