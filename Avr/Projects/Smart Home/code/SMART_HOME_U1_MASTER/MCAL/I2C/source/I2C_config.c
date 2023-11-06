/**************************************************************************/
/* Filename						: I2C_config.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 30 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/





/********************************** Includes *********************************************/
#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"

#include "../../DIO/include/DIO.h"
#include "../include/I2C_config.h"
#include "../include/I2C_private.h"
#include "../include/I2C.h"



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Definition ****************************/
I2c_ConfigType I2c={
		.clock_freq =(u32)400000,
		.select_prescale_value_twps = I2C_SELECT_PRESCALER_VALUE_1,
		.slave_address_or_minus_one_for_master_mode = -1
};



/********************************** Software Interfaces Declarations *******************/
