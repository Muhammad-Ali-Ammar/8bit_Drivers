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
Std_StatusType Convert_FloatToString (f32 Copy_f32Number, pu8 Address_str);

Std_StatusType Convert_StringToInt (u64* Address_Number, pu8 Address_str);


#endif /* SERIVICES_INCLUDE_CALCULATION_FUNCTIONS_H_ */
