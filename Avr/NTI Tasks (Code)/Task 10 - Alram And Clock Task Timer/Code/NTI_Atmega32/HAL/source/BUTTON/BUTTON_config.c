/**************************************************************************/
/* Filename						: BUTTON_config.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 22 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/STD_TYPES.h"

#include "../../../MCAL/DIO/include/DIO.h"

#include "../../include/BUTTON/BUTTON.h"


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

Button_ConfigType Inc_Button={
		.button_connection = BUTTON_CONNECTION_PULL_UP,
		.button_pin = DIO_PIND7_CHANNEL31
};


Button_ConfigType Dec_Button={
		.button_connection = BUTTON_CONNECTION_PULL_UP,
		.button_pin = DIO_PIND6_CHANNEL30
};


Button_ConfigType Reset_Button={
		.button_connection = BUTTON_CONNECTION_PULL_UP,
		.button_pin = DIO_PIND5_CHANNEL29
};




/********************************** Software Interfaces Declarations *******************/
