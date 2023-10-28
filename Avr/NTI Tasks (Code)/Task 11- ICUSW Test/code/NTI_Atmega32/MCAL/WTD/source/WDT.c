/**************************************************************************/
/* Filename						: WDT.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 27 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/






/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../DIO/include/DIO.h"

#include "../include/WDT_config.h"
#include "../include/WDT.h"
#include "../include/WDT_private.h"


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/

#define Wtd_Enable(ARG)					((WDTCR) = (WDTCR & 0xE0) | (ARG) | (ONE_VALUE<< WDE_BIT))

#define Wtd_Disable()					do{\
								 	(		(WDTCR) = (WDTCR & 0xE0) | (ONE_VALUE<< WDTOE_BIT) | (ONE_VALUE<< WDE_BIT));\
											ASSIGN_REG(WDTCR,ZERO_VALUE);\
									}while(0)

/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/

Wtd_StatusErrorType Wtd_enuSleep (Wtd_SelectSleepTime Copy_enuSleepTime){
	Wtd_StatusErrorType Loc_enuWtdStatus = WTD_STATUS_OK;

	Wtd_Enable(Copy_enuSleepTime);

			return Loc_enuWtdStatus;
}

Wtd_StatusErrorType Wtd_enuDisable (void){

	Wtd_StatusErrorType Loc_enuWtdStatus = WTD_STATUS_OK;
	Wtd_Disable();



	return Loc_enuWtdStatus;
}
