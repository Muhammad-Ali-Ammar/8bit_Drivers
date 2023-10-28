/**************************************************************************/
/* Filename						: LCD_config.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 21 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/


#include "../../SERIVICES/include/BIT_UTILS.h"
#include "../../SERIVICES/include/STD_TYPES.h"
#include "../../MCAL/DIO/include/DIO.h"
#include "../include/LCD.h"
#include "../include/LCD_config.h"


Lcd_4bitType Lcd ={
		.lcd_data_pins[0] = LCD_4BIT_D4,
		.lcd_data_pins[1] = LCD_4BIT_D5,
		.lcd_data_pins[2] = LCD_4BIT_D6,
		.lcd_data_pins[3] = LCD_4BIT_D7,

		.lcd_enable_pin = LCD_4BIT_EN,
		.lcd_rs_pin = LCD_4BIT_RS
};



/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/
