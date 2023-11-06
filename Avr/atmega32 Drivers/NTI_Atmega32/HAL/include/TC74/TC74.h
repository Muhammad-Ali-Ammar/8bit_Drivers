/**************************************************************************/
/* Filename						: TC74.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 30 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef HAL_INCLUDE_TC74_TC74_H_
#define HAL_INCLUDE_TC74_TC74_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/


typedef enum{
	TC74_STATUS_OK,
	TC74_STATUS_FAIL,
	TC74_STATUS_NULL_POINTER_ADDRESS
}Tc74_StatusErrorType;



/********************************** Software Interfaces Declarations *******************/
Tc74_StatusErrorType Tc74_ReadByte(u8 Copy_u8SlaveAddress,u8* Address_Result);

#endif /* HAL_INCLUDE_TC74_TC74_H_ */
