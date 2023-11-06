/**************************************************************************/
/* Filename						: USART_config.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 28 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/





/********************************** Includes *********************************************/


#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../DIO/include/DIO.h"
#include <util/delay.h>
#include "../include/USART_private.h"

#include "../include/USART_config.h"
#include "../include/USART.h"



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Definition ****************************/
Usart_ConfigType Usart1={
		.baude_rate = 9600,
		.character_size = USART_CHARACTER_SIZE_8_BIT,
		.parity_bits = USART_SELECT_PARITY_DISABLE,
		.stop_bits= USART_SELECT_1STOP_BIT,
		.sync_mode = USAR_SELECT_ASYNCHRONOUS_MODE
};





/********************************** Software Interfaces Declarations *******************/
