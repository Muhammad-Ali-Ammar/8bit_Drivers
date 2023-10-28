/**************************************************************************/
/* Filename						: GIE.c                                   */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 22 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/



#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/HELPERS.h"


#include "../include/GIE_private.h"
#include "../include/GIE.h"


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


Gie_ErrorStatusType Gie_enuEnableGlobalInterrupt(void){
	Gie_ErrorStatusType Loc_enuGieState = GIE_STATUS_OK;

	SET_BIT(SREG,GIE_BIT);

	return Loc_enuGieState;

}
Gie_ErrorStatusType Gie_enuDisableGlobalInterrupt(void){
	Gie_ErrorStatusType Loc_enuGieState = GIE_STATUS_OK;

		CLEAR_BIT(SREG,GIE_BIT);

		return Loc_enuGieState;
}

Gie_ErrorStatusType Gie_enuSetGloablInterrupt(Gie_EnableDisableType Copy_enuGlobalState){

	Gie_ErrorStatusType Loc_enuGieState = GIE_STATUS_OK;

			WRITE_BIT(SREG,GIE_BIT,Copy_enuGlobalState);

			return Loc_enuGieState;
}


Gie_ErrorStatusType Gie_enuGetGloablInterrupt(Gie_EnableDisableType Copy_enuGlobalState, Gie_EnableDisableType* Address_GlobalStateResult){

	Gie_ErrorStatusType Loc_enuGieState = GIE_STATUS_OK;

	if(NULL == Address_GlobalStateResult){
		Loc_enuGieState = GIE_STATUS_NULL_POINTER_ADDRESS;
	}
	else {
		*Address_GlobalStateResult = (Gie_EnableDisableType)READ_BIT(SREG,GIE_BIT);

	}

			return Loc_enuGieState;
}
