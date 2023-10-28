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
#include <stdio.h>

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/
Std_StatusType Convert_IntToString (u32 Copy_u32Number, pu8 Address_str){
		Std_StatusType Loc_enuStatus = STD_STATUS_OK;
	if(NULL == Address_str){
		Loc_enuStatus = STD_STATUS_NULL_POINTER_ADDRESS;
	}

	else{

		sprintf(Address_str, "%lu", Copy_u32Number);
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


Std_StatusType Convert_StringToInt (u64* Address_Number, pu8 Address_str){

			Std_StatusType Loc_enuStatus = STD_STATUS_OK;
			u8 Loc_u8Counter = 0;
			u64 Loc_u64Result = 0;
			if(NULL == Address_str || NULL == Address_Number ){
				Loc_enuStatus = STD_STATUS_NULL_POINTER_ADDRESS;
			}

			else{

				for(Loc_u8Counter = 0; Address_str[Loc_u8Counter];++Loc_u8Counter){
					Loc_u64Result = Loc_u64Result*10 +  (Address_str[Loc_u8Counter]-'0');
				}

				*Address_Number = Loc_u64Result;
			}

			return Loc_enuStatus;

}
