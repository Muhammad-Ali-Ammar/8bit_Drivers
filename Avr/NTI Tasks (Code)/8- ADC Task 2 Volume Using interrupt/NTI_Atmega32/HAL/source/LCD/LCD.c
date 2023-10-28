/**************************************************************************/
/* Filename						: LCD.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 21 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/calculation_functions.h"

#include "../../../MCAL/DIO/include/DIO.h"
#include "../../../MCAL/PORT/include/PORT.h"
#include <util/delay.h>
#include "../../include/LCD/LCD.h"
#include "../../include/LCD/LCD_private.h"
#include "../../include/LCD/LCD_config.h"


/********************************** * private functions declarations * *******************************/


static Lcd_ErrorStatusType Lcd_4bit_enuSet4BitsOnPins(const Lcd_4bitType* Address_Lcd, u8 Copy_u8Data4Bits);
static Lcd_ErrorStatusType Lcd_4bit_enuSendEnableSignal(const Lcd_4bitType* Address_Lcd);




/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/



/********************************** Software Interfaces Declarations *******************/


Lcd_ErrorStatusType Lcd_4bit_enuInit(const Lcd_4bitType* Address_lcd){

	Lcd_ErrorStatusType Loc_enuStatus = LCD_STATUS_OK;
	if( NULL == Address_lcd){
		Loc_enuStatus = LCD_STATUS_NULL_POINTER_ADDRESS;

	}
	else{

			  Loc_enuStatus= Lcd_4bit_enuSendCommand(Address_lcd,LCD_FUNCTION_SET_8_BIT_2_LINE_8_DOTS);
			        _delay_ms(5);
			   Loc_enuStatus=  Lcd_4bit_enuSendCommand(Address_lcd, LCD_FUNCTION_SET_8_BIT_2_LINE_8_DOTS);
			       _delay_us(150);
			   Loc_enuStatus= Lcd_4bit_enuSendCommand(Address_lcd,LCD_FUNCTION_SET_8_BIT_2_LINE_8_DOTS);

			       /* This is optional */
				   Loc_enuStatus = Lcd_4bit_enuSendCommand(Address_lcd, LCD_CLEAR_COMMAND);
			       Loc_enuStatus = Lcd_4bit_enuSendCommand(Address_lcd, LCD_CURSOR_HOME);
			       Loc_enuStatus = Lcd_4bit_enuSendCommand(Address_lcd, LCD_ENTRY_MODE_INC_SHIFT_OFF);
			       Loc_enuStatus = Lcd_4bit_enuSendCommand(Address_lcd, LCD_DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_OFF);
			       Loc_enuStatus = Lcd_4bit_enuSendCommand(Address_lcd, LCD_FUNCTION_SET_4_BIT_2_LINE_8_DOTS);
			       Loc_enuStatus = Lcd_4bit_enuSendCommand(Address_lcd,0x80);
			       Loc_enuStatus= Lcd_4bit_enuSendCommand(Address_lcd,LCD_CLEAR_COMMAND);
			       			        _delay_ms(5);
	}




	return Loc_enuStatus;

}


Lcd_ErrorStatusType Lcd_4bit_enuSendCommand(const Lcd_4bitType* Address_Lcd, u8 Copy_u8Command){

	Lcd_ErrorStatusType Loc_enuStatus = LCD_STATUS_OK;
	Dio_ErrorStatusType Loc_enuDioStatus = DIO_STATUS_OK;
		if( NULL == Address_Lcd){
			Loc_enuStatus = LCD_STATUS_NULL_POINTER_ADDRESS;

		}
		else {

			Loc_enuDioStatus  = Dio_enuWriteChannel(Address_Lcd->lcd_rs_pin, DIO_LOW);
//			Loc_enuDioStatus = Dio_enuWriteChannel(Address_Lcd->lcd_rw_pin,DIO_LOW);

			Loc_enuStatus = Lcd_4bit_enuSet4BitsOnPins(Address_Lcd,(Copy_u8Command>>4) &0xF);  // higher nibble first
			Loc_enuStatus = Lcd_4bit_enuSendEnableSignal(Address_Lcd);

			Loc_enuStatus = Lcd_4bit_enuSet4BitsOnPins(Address_Lcd,Copy_u8Command);  // lower nibble
			Loc_enuStatus = Lcd_4bit_enuSendEnableSignal(Address_Lcd);
		}


		// 1111 0000


		return Loc_enuStatus;

}

Lcd_ErrorStatusType Lcd_4bit_enuDisplayCharacter(const Lcd_4bitType* Address_Lcd, u8 Copy_u8Data){

	Lcd_ErrorStatusType Loc_enuStatus = LCD_STATUS_OK;
		if( NULL == Address_Lcd){
			Loc_enuStatus = LCD_STATUS_NULL_POINTER_ADDRESS;

		}
		else{


				   Loc_enuStatus  = Dio_enuWriteChannel(Address_Lcd->lcd_rs_pin,DIO_HIGH);
//			        Loc_enuStatus = Dio_enuWriteChannel(Address_Lcd->lcd_rw_pin,DIO_LOW);

			        Loc_enuStatus = Lcd_4bit_enuSet4BitsOnPins(Address_Lcd,(Copy_u8Data>>4) &0xF);  // higher nibble first
			        Loc_enuStatus = Lcd_4bit_enuSendEnableSignal(Address_Lcd);

			        Loc_enuStatus = Lcd_4bit_enuSet4BitsOnPins(Address_Lcd,Copy_u8Data);  // lower nibble
			        Loc_enuStatus = Lcd_4bit_enuSendEnableSignal(Address_Lcd);
		}




		return Loc_enuStatus;

}


Lcd_ErrorStatusType Lcd_4bit_enuDisplayCharacterWithPosition(const Lcd_4bitType* Address_Lcd, u8 Copy_u8Data, u8 Copy_u8Row, u8 Copy_u8Col){
	Lcd_ErrorStatusType Loc_enuStatus = LCD_STATUS_OK;
			if( NULL == Address_Lcd){
				Loc_enuStatus = LCD_STATUS_NULL_POINTER_ADDRESS;

			}
			else{


					    Loc_enuStatus = Lcd_4bit_enuGoToXY(Address_Lcd, Copy_u8Row, Copy_u8Col);
					   Loc_enuStatus  = Dio_enuWriteChannel(Address_Lcd->lcd_rs_pin,DIO_HIGH);
	//			        Loc_enuStatus = Dio_enuWriteChannel(Address_Lcd->lcd_rw_pin,DIO_LOW);

				        Loc_enuStatus = Lcd_4bit_enuSet4BitsOnPins(Address_Lcd,(Copy_u8Data>>4) &0xF);  // higher nibble first
				        Loc_enuStatus = Lcd_4bit_enuSendEnableSignal(Address_Lcd);

				        Loc_enuStatus = Lcd_4bit_enuSet4BitsOnPins(Address_Lcd,Copy_u8Data);  // lower nibble
				        Loc_enuStatus = Lcd_4bit_enuSendEnableSignal(Address_Lcd);
			}




			return Loc_enuStatus;
}


Lcd_ErrorStatusType Lcd_4bit_enuCreateCustomCharacter(const Lcd_4bitType* Address_Lcd, pu8 Address_pu8CustomCharacter, u8 Copy_u8MemoryIndex){

	Lcd_ErrorStatusType Loc_enuStatus = LCD_STATUS_OK;
	u8	Loc_u8Counter =ZERO_VALUE;
		if( (NULL == Address_Lcd) || (NULL == Address_pu8CustomCharacter)){
			Loc_enuStatus = LCD_STATUS_NULL_POINTER_ADDRESS;

		}
		else if (Copy_u8MemoryIndex> LCD_MAX_INDEX_OF_CUSTOM_CHAR){
			Loc_enuStatus = LCD_STATUS_WRONG_CUSTOM_CHAR_INDEX;
		}
		else{

			Loc_enuStatus = Lcd_4bit_enuSendCommand(Address_Lcd,(LCD_CGRAM_START+(Copy_u8MemoryIndex*EIGHT_VALUE)));

			        for(Loc_u8Counter = ZERO_VALUE;Loc_u8Counter<EIGHT_VALUE;Loc_u8Counter++)
			            Lcd_4bit_enuDisplayCharacter(Address_Lcd, Address_pu8CustomCharacter[Loc_u8Counter]);

			        Loc_enuStatus = Lcd_4bit_enuSendCommand(Address_Lcd,0x80);
		}




		return Loc_enuStatus;

}

Lcd_ErrorStatusType Lcd_4bit_enuGoToXY(const Lcd_4bitType* Address_Lcd, u8 Copy_u8Row, u8 Copy_u8Col){

	Lcd_ErrorStatusType Loc_enuStatus = LCD_STATUS_OK;
		if( NULL == Address_Lcd){
			Loc_enuStatus = LCD_STATUS_NULL_POINTER_ADDRESS;

		}
		else if (Copy_u8Row > LCD_ROW_NUMBERS){
			Loc_enuStatus = LCD_STATUS_WRONG_ROW_INDEX;
		}

		else if (Copy_u8Col > LCD_COL_NUMBERS){
			Loc_enuStatus = LCD_STATUS_WRONG_COL_INDEX;
		}
		else{

			/* decrement col because use it as row1 col 1 which means col 0*/
			Copy_u8Col--;

			        switch(Copy_u8Row){

			            case LCD_ROW1:
			                Loc_enuStatus &= Lcd_4bit_enuSendCommand(Address_Lcd,(0x80+Copy_u8Col));
			                break;

			            case LCD_ROW2:
			                Loc_enuStatus &= Lcd_4bit_enuSendCommand(Address_Lcd,(0xc0+Copy_u8Col));
			                break;

			            case LCD_ROW3:
			                Loc_enuStatus &= Lcd_4bit_enuSendCommand(Address_Lcd,(0x94+Copy_u8Col));
			                break;

			            case LCD_ROW4:
			                Loc_enuStatus &= Lcd_4bit_enuSendCommand(Address_Lcd,(0xd4+Copy_u8Col));
			                break;

			            default :
			                Loc_enuStatus = LCD_STATUS_OK;

		}

		}




		return Loc_enuStatus;

}

Lcd_ErrorStatusType Lcd_4bit_enuDisplayString(const Lcd_4bitType* Address_Lcd, pu8 Address_pu8String){

	Lcd_ErrorStatusType Loc_enuStatus = LCD_STATUS_OK;
	u8 Loc_u8Counter = ZERO_VALUE;
		if( (NULL == Address_Lcd) || (NULL == Address_pu8String)){
			Loc_enuStatus = LCD_STATUS_NULL_POINTER_ADDRESS;

		}
		else{

			while(Address_pu8String[Loc_u8Counter] !=0){
			            Loc_enuStatus = Lcd_4bit_enuDisplayCharacter(Address_Lcd,Address_pu8String[Loc_u8Counter]);
			            Loc_u8Counter++;
			        }


		}




		return Loc_enuStatus;

}

Lcd_ErrorStatusType Lcd_4bit_enuDisplayNumber(const Lcd_4bitType* Address_Lcd, u32 Copy_u32Number){

	Lcd_ErrorStatusType Loc_enuStatus = LCD_STATUS_OK;
	Std_StatusType Loc_enuStdStatus = STD_STATUS_OK;
	u8 Loc_u8ConvertedNumberInArray[100];
		if( NULL == Address_Lcd){
			Loc_enuStatus = LCD_STATUS_NULL_POINTER_ADDRESS;

		}
		else{

			Loc_enuStdStatus= Convert_IntToString(Copy_u32Number, Loc_u8ConvertedNumberInArray);
			Loc_enuStatus = Lcd_4bit_enuDisplayString(Address_Lcd,Loc_u8ConvertedNumberInArray);

		}




		return Loc_enuStatus;

}



Lcd_ErrorStatusType Lcd_4bit_enuDisplayFloatNumber(const Lcd_4bitType* Address_Lcd, f32 Copy_f32Number){

	Lcd_ErrorStatusType Loc_enuStatus = LCD_STATUS_OK;
	Std_StatusType Loc_enuStdStatus = STD_STATUS_OK;
	u8 Loc_u8ConvertedNumberInArray[100];
		if( NULL == Address_Lcd){
			Loc_enuStatus = LCD_STATUS_NULL_POINTER_ADDRESS;

		}
		else{

			Loc_enuStdStatus= Convert_FloatToString(Copy_f32Number, Loc_u8ConvertedNumberInArray);
			Loc_enuStatus = Lcd_4bit_enuDisplayString(Address_Lcd,Loc_u8ConvertedNumberInArray);

		}




		return Loc_enuStatus;

}














//////////////////////////////////////*Implementation of Private Functions*////////////////////////////

static Lcd_ErrorStatusType Lcd_4bit_enuSet4BitsOnPins(const Lcd_4bitType* Address_Lcd, u8 Copy_u8Data4Bits){

	Lcd_ErrorStatusType Loc_enuStatus = LCD_STATUS_OK;
	u8 Loc_u8Counter = ZERO_VALUE;
		if( NULL == Address_Lcd){
			Loc_enuStatus = LCD_STATUS_NULL_POINTER_ADDRESS;

		}
		else{
			 for(Loc_u8Counter =ZERO_VALUE; Loc_u8Counter<4;Loc_u8Counter++){

				 Loc_enuStatus =Dio_enuWriteChannel((Address_Lcd->lcd_data_pins[Loc_u8Counter]),(Copy_u8Data4Bits>>Loc_u8Counter)& ONE_VALUE);
			        }

		}




		return Loc_enuStatus;

}



static Lcd_ErrorStatusType Lcd_4bit_enuSendEnableSignal(const Lcd_4bitType* Address_Lcd){

	Lcd_ErrorStatusType Loc_enuStatus = LCD_STATUS_OK;
		if( NULL == Address_Lcd){
			Loc_enuStatus = LCD_STATUS_NULL_POINTER_ADDRESS;

		}
		else{

			   Loc_enuStatus = Dio_enuWriteChannel((Address_Lcd->lcd_enable_pin), DIO_HIGH);
			        _delay_us(5);
			  Loc_enuStatus = Dio_enuWriteChannel((Address_Lcd->lcd_enable_pin), DIO_LOW);

		}




		return Loc_enuStatus;

}

