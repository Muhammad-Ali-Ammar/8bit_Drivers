/**************************************************************************/
/* Filename						: TIMER0_config.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 24 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/


#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../DIO/include/DIO.h"

#include "../include/TIMER0_config.h"
#include "../include/TIMER0.h"
#include "../include/TIMER0_private.h"


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

Timer0_ConfigType Timer0 ={
		.init_value = ZERO_VALUE,
		.prescaler_value = TIMER0_PRESCALER_DIV_1024,
		.select_mode = TIMER0_SELECT_MODE_NORMAL

};


/********************************** Software Interfaces Declarations *******************/
