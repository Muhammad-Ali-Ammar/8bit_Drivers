/**************************************************************************/
/* Filename						: calculation_functions.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 21 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef SERIVICES_INCLUDE_CALCULATION_FUNCTIONS_H_
#define SERIVICES_INCLUDE_CALCULATION_FUNCTIONS_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/



/********************************** Data Type Declarations ****************************/

typedef enum{
	STD_STATUS_OK,
	STD_STATUS_NULL_POINTER_ADDRESS,
	STD_FAIL

}Std_StatusType;



/********************************** Software Interfaces Declarations *******************/

Std_StatusType Convert_IntToString (u32 Copy_u32Number, pu8 Address_str);
Std_StatusType Convert_FloatToString (f64 Copy_f64Number, pu8 Address_str);

Std_StatusType Convert_StringTou8 (u8* Address_Number, pu8 Address_str);
Std_StatusType Convert_StringTou16 (u16* Address_Number, pu8 Address_str);
Std_StatusType Convert_StringTou32 (u32* Address_Number, pu8 Address_str);
Std_StatusType Convert_StringTou64 (u64* Address_Number, pu8 Address_str);
Std_StatusType Convert_BCDToInt(u8 Copy_u8BCDdata, u8* Address_Asnwer);
Std_StatusType Convert_VoltToTempLm35(f32 Copy_, u16* Address_Result);


#endif /* SERIVICES_INCLUDE_CALCULATION_FUNCTIONS_H_ */
