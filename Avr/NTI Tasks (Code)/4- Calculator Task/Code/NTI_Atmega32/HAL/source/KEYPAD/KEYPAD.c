/**************************************************************************/
/* Filename						: KEYPAD.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 22 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/calculation_functions.h"

#include "../../../MCAL/DIO/include/DIO.h"
#include "../../../MCAL/PORT/include/PORT.h"
#include "../../include/KEYPAD/KEYPAD_config.h"
#include "../../include/KEYPAD/KEYPAD.h"
#include "../../include/KEYPAD/KEYPAD_private.h"


///////////////////////////Static Functions /////////////////////////
static Keypad_ErrorStatusType Keypad_DisableControlPins(const Keypad_ConfigType* Address_Keypad);

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/



/********************************** Software Interfaces Declarations *******************/


Keypad_ErrorStatusType Keypad_enuRead(const Keypad_ConfigType* Address_Keypad, pu8 Address_ResultValue){

	extern const u8 Keypad_Matrix[KEYPAD_ROWS_NUMBER][KEYPAD_COLS_NUMBER];
	Keypad_ErrorStatusType Loc_KeypadStatusError =KEYPAD_STATUS_NOT_PRESSED;
	Dio_ErrorStatusType Loc_DioStatusError =DIO_STATUS_OK;
	u8 Loc_u8RowsCounter = ZERO_VALUE;
	u8 Loc_u8ColsCounter = ZERO_VALUE;
	u8 Loc_u8Check = Address_Keypad->keypad_idle_volt;
	if (NULL == Address_Keypad || (NULL == Address_ResultValue ) ){

		Loc_KeypadStatusError = KEYPAD_STATUS_NULL_POINTER_ADDRESS;
	    }

	     else{
	    	  Loc_KeypadStatusError = Keypad_DisableControlPins(Address_Keypad);

	    	  switch(Address_Keypad->keypad_control_pins){
	    	             case KEYPAD_ROW_CONTROL:

	    	                 /* first thing : active row */
	    	                 for(Loc_u8RowsCounter=ZERO_VALUE;Loc_u8RowsCounter<KEYPAD_ROWS_NUMBER;Loc_u8RowsCounter++){
	    	                	 Loc_DioStatusError = Dio_enuWriteChannel((Address_Keypad->keypad_rows_pins[Loc_u8RowsCounter]),  !(Address_Keypad->keypad_idle_volt ) );

	    	                     /* second thing : read col */
	    	                     for(Loc_u8ColsCounter= ZERO_VALUE;Loc_u8ColsCounter<KEYPAD_COLS_NUMBER;Loc_u8ColsCounter++){
	    	                    	 Loc_DioStatusError = Dio_enuReadChannel((Address_Keypad->keypad_cols_pins[Loc_u8ColsCounter]), &Loc_u8Check);

	    	                         if( Loc_u8Check != Address_Keypad->keypad_idle_volt )
	    	                         {
	    	                              *Address_ResultValue = Keypad_Matrix[Loc_u8RowsCounter][Loc_u8ColsCounter];
	    	                              Loc_KeypadStatusError = KEYPAD_IS_PRESSED;
	    	                         }
	    	                         else {
	    	                             /* nothing*/
	    	                         }
	    	                     }



	    	                     Loc_DioStatusError = Dio_enuWriteChannel((Address_Keypad->keypad_rows_pins[Loc_u8RowsCounter]), Address_Keypad->keypad_idle_volt  );
	    	                 }

	    	                 break;

	    	             case KEYPAD_COL_CONTROL :

	    	                  /* first thing : active col */
	    	                 for(Loc_u8ColsCounter=ZERO_VALUE;Loc_u8ColsCounter<KEYPAD_COLS_NUMBER;Loc_u8ColsCounter++){
	    	                	 Loc_DioStatusError = Dio_enuWriteChannel((Address_Keypad->keypad_cols_pins[Loc_u8ColsCounter]),  !(Address_Keypad->keypad_idle_volt ) );

	    	                     /* second thing : read row */
	    	                     for(Loc_u8RowsCounter= ZERO_VALUE;Loc_u8RowsCounter<KEYPAD_COLS_NUMBER;Loc_u8RowsCounter++){
	    	                    	 Loc_DioStatusError = Dio_enuReadChannel((Address_Keypad->keypad_rows_pins[Loc_u8RowsCounter]),&Loc_u8Check );

	    	                         if(Loc_u8Check != Address_Keypad->keypad_idle_volt )
	    	                         {
	    	                             *Address_ResultValue = Keypad_Matrix[Loc_u8RowsCounter][Loc_u8ColsCounter];
	    	                         }
	    	                         else {
	    	                             /* nothing*/
	    	                         }
	    	                     }



	    	                     Loc_DioStatusError = Dio_enuWriteChannel((Address_Keypad->keypad_cols_pins[Loc_u8ColsCounter]), Address_Keypad->keypad_idle_volt  );
	    	                 }

	    	                 break;

	    	             default :
	    	                 Loc_KeypadStatusError = KEYPAD_STATUS_FAIL;
	    	         }


	     }
	return Loc_KeypadStatusError;
}


/********************************** Static  Interfaces Implementation *******************/
static Keypad_ErrorStatusType Keypad_DisableControlPins(const Keypad_ConfigType* Address_Keypad){

	Keypad_ErrorStatusType Loc_KeypadStatusError =KEYPAD_STATUS_NOT_PRESSED;
	Dio_ErrorStatusType Loc_DioStatusError = DIO_STATUS_OK;
    	u8 Loc_u8Counter = ZERO_VALUE;
	if (NULL == Address_Keypad   ){

		Loc_KeypadStatusError = KEYPAD_STATUS_NULL_POINTER_ADDRESS;
	    }

	else{

	        switch(Address_Keypad->keypad_control_pins){
	            case KEYPAD_ROW_CONTROL:

	                for(Loc_u8Counter=ZERO_VALUE;Loc_u8Counter<KEYPAD_ROWS_NUMBER;Loc_u8Counter++){
	                	Loc_DioStatusError = Dio_enuWriteChannel((Address_Keypad->keypad_rows_pins[Loc_u8Counter]), Address_Keypad->keypad_idle_volt);
	                }

	                break;

	            case KEYPAD_COL_CONTROL :

	                for(Loc_u8Counter=ZERO_VALUE;Loc_u8Counter<KEYPAD_COLS_NUMBER;Loc_u8Counter++){
	                	Loc_DioStatusError = Dio_enuWriteChannel((Address_Keypad->keypad_cols_pins[Loc_u8Counter]), Address_Keypad->keypad_idle_volt);
	                }
	                break;

	            default :
	                Loc_KeypadStatusError = KEYPAD_STATUS_FAIL;
	        }

	    }
	return Loc_KeypadStatusError;
}


