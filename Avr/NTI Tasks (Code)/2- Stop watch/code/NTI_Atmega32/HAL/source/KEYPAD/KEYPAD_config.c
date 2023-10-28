/**************************************************************************/
/* Filename						: KEYPAD_config.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 22 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../MCAL/DIO/include/DIO.h"
#include "../../include/KEYPAD/KEYPAD_config.h"

#include "../../include/KEYPAD/KEYPAD.h"



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type definition ****************************/

const u8 Keypad_Matrix[KEYPAD_ROWS_NUMBER][KEYPAD_COLS_NUMBER]={
                                                {'7','8','9','/'},
                                                {'4','5','6','*'},
                                                {'1','2','3','-'},
                                                {'c','0','=','+'}};


Keypad_ConfigType Keypad ={
		.keypad_cols_pins[0]= DIO_PIND7_CHANNEL31,
		.keypad_cols_pins[1]= DIO_PIND6_CHANNEL30,
		.keypad_cols_pins[2]= DIO_PIND5_CHANNEL29,
		.keypad_cols_pins[3]= DIO_PIND3_CHANNEL27,
		.keypad_control_pins = KEYPAD_ROW_CONTROL,

		.keypad_rows_pins[0]=DIO_PINC5_CHANNEL21,
		.keypad_rows_pins[1]=DIO_PINC4_CHANNEL20,
		.keypad_rows_pins[2]=DIO_PINC3_CHANNEL19,
		.keypad_rows_pins[3]=DIO_PINC2_CHANNEL18,
		.keypad_idle_volt = KEYPAD_IDLE_VOLTAGE_HIGH
};



/********************************** Software Interfaces Declarations *******************/
