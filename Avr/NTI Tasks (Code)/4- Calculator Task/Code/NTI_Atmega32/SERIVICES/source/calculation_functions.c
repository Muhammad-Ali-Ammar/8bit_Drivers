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
#include "../include/BIT_UTILS.h"
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
Std_StatusType Convert_FloatToString (f64 Copy_f64Number, pu8 Address_str){

	//-5.99

	Std_StatusType Loc_enuStatus = STD_STATUS_OK;
	u8 Loc_u8TempSign[2]="";
	s32  Loc_s64IntPart;
	f32 Loc_f32FractionPart;
	s32  Loc_s64FractionPartAsInteger;


		if(NULL == Address_str){
			Loc_enuStatus = STD_STATUS_NULL_POINTER_ADDRESS;
		}

		else{

			if(Copy_f64Number<0){
				Copy_f64Number = -Copy_f64Number ;
				Loc_u8TempSign[0] ='-';
			}


			Loc_s64IntPart = Copy_f64Number;                  // Get the integer (5).
			Loc_f32FractionPart = Copy_f64Number - Loc_s64IntPart;      // Get fraction (.99).
			 Loc_s64FractionPartAsInteger = (Loc_f32FractionPart * 10000);  // Turn into integer (9900).

			// Print as parts, note that you need 0-padding for fractional bit.

			sprintf (Address_str, "%s%ld.%04d", Loc_u8TempSign, Loc_s64IntPart, Loc_s64FractionPartAsInteger);



		}

		return Loc_enuStatus;


}



Std_StatusType Convert_StringTou8 (u8* Address_Number, pu8 Address_str){

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


Std_StatusType Convert_StringTou16 (u16* Address_Number, pu8 Address_str){

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


Std_StatusType Convert_StringTou32 (u32* Address_Number, pu8 Address_str){

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


Std_StatusType Convert_StringTou64 (u64* Address_Number, pu8 Address_str){

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
