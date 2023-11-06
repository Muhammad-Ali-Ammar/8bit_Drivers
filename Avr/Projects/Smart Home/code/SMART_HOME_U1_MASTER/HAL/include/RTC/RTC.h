/**************************************************************************/
/* Filename						: RTC.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 30 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef HAL_INCLUDE_RTC_RTC_H_
#define HAL_INCLUDE_RTC_RTC_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/


typedef enum{
	RTC_STATUS_OK,
	RTC_STATUS_FAIL,
	RTC_STATUS_NULL_POINTER_ADDRESS
}Rtc_StatusErrorType;



/********************************** Software Interfaces Declarations *******************/

Rtc_StatusErrorType Rtc_enuGetSecond(u8* Address_Result);
Rtc_StatusErrorType Rtc_enuGetMinute(u8* Address_Result);
Rtc_StatusErrorType Rtc_enuGetHour(u8* Address_Result);


Rtc_StatusErrorType Rtc_enuGetDay(u8* Address_Result);
Rtc_StatusErrorType Rtc_enuGetMonth( u8* Address_Result);
Rtc_StatusErrorType Rtc_enuGetYear(u8* Address_Result);





#endif /* HAL_INCLUDE_RTC_RTC_H_ */
