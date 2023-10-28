/**************************************************************************/
/* Filename						: calculation_functions.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 21 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/
#include "../include/STD_TYPES.h"
#include "../include/calculation_functions.h"

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/
Std_StatusType Convert_IntToString (u8 Copy_u8Number, pu8 Address_str){
		Std_StatusType Loc_enuStatus = STD_STATUS_OK;
	if(NULL == Address_str){
		Loc_enuStatus = STD_STATUS_NULL_POINTER_ADDRESS;
	}

	else{

		sprintf(Address_str, "%lu", Copy_u8Number);
	}

	return Loc_enuStatus;
}
Std_StatusType Convert_FloatToString (f32 Copy_f32Number, pu8 Address_str){


	Std_StatusType Loc_enuStatus = STD_STATUS_OK;
		if(NULL == Address_str){
			Loc_enuStatus = STD_STATUS_NULL_POINTER_ADDRESS;
		}

		else{

			sprintf(Address_str, "%f", Copy_f32Number);
		}

		return Loc_enuStatus;


}
