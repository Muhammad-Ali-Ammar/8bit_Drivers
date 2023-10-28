/**************************************************************************/
/* Filename						: GIE.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 22 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_GIE_INCLUDE_GIE_H_
#define MCAL_GIE_INCLUDE_GIE_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/



/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

typedef enum {

	GIE_STATUS_OK,
	GIE_STATUS_FAIL,
	GIE_STATUS_NULL_POINTER_ADDRESS
}Gie_ErrorStatusType;


typedef enum{
	GIE_DISABLE =0,
	GIE_ENABLE =1
}Gie_EnableDisableType;


/********************************** Software Interfaces Declarations *******************/

Gie_ErrorStatusType Gie_enuEnableGlobalInterrupt(void);
Gie_ErrorStatusType Gie_enuDisableGlobalInterrupt(void);
Gie_ErrorStatusType Gie_enuSetGloablInterrupt(Gie_EnableDisableType Copy_enuGlobalState);
Gie_ErrorStatusType Gie_enuGetGloablInterrupt(Gie_EnableDisableType Copy_enuGlobalState, Gie_EnableDisableType* Address_GlobalStateResult);



#endif /* MCAL_GIE_INCLUDE_GIE_H_ */
