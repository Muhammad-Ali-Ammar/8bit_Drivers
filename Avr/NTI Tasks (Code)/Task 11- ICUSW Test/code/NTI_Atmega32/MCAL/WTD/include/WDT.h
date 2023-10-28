/**************************************************************************/
/* Filename						: WDT.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 27 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_WTD_INCLUDE_WDT_H_
#define MCAL_WTD_INCLUDE_WDT_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/
typedef enum{

	WTD_SELECT_SLEEP_16point3_MilliSec = 0,
	WTD_SELECT_SLEEP_32point5_MilliSec = 1,
	WTD_SELECT_SLEEP_65MilliSec = 2,
	WTD_SELECT_SLEEP_0point13_Sec = 3,
	WTD_SELECT_SLEEP_0point26_Sec = 4,
	WTD_SELECT_SLEEP_0point52_Sec = 5,
	WTD_SELECT_SLEEP_1_Sec = 6,
	WTD_SELECT_SLEEP_2point1_Sec = 7

}Wtd_SelectSleepTime;


typedef enum{
	WTD_STATUS_FAIL,
	WTD_STATUS_OK

}Wtd_StatusErrorType;



/********************************** Software Interfaces Declarations *******************/

Wtd_StatusErrorType Wtd_enuSleep (Wtd_SelectSleepTime Copy_enuSleepTime);
Wtd_StatusErrorType Wtd_enuDisable (void);

#endif /* MCAL_WTD_INCLUDE_WDT_H_ */
