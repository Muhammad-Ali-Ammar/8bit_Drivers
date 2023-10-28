/**************************************************************************/
/* Filename						: BUTTON.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 22 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/STD_TYPES.h"

#include "../../../MCAL/DIO/include/DIO.h"

#include "../../include/BUTTON/BUTTON.h"


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/

Button_StatusErrorType Button_enuRead(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State ){

	Button_StatusErrorType Loc_enuStatus = BUTTON_STATUS_OK;
	Dio_ErrorStatusType Loc_enuDioState = DIO_STATUS_OK;
	if( NULL == Address_Button || NULL == Address_State ){
		Loc_enuStatus = BUTTON_STATUS_NULL_POINTER_ADDRESS;

	}
	else{
	        switch(Address_Button->button_connection){

	            case BUTTON_CONNECTION_PULL_DOWN:
	            	Loc_enuDioState = Dio_enuReadChannel( (Address_Button->button_pin), (pu8) Address_State);
	                break;
	            case BUTTON_CONNECTION_PULL_UP:

	            	Loc_enuDioState = Dio_enuReadChannel( (Address_Button->button_pin), (pu8) Address_State);
	                *Address_State = !(*Address_State);
	                break;

	            default:
	                Loc_enuStatus = BUTTON_STATUS_FAIL;
	        }

	    }




	return Loc_enuStatus;

}
