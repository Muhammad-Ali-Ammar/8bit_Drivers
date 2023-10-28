/**************************************************************************/
/* Filename						: TIMER.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 24 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/


#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../DIO/include/DIO.h"

#include "../include/TIMER0_config.h"
#include "../include/TIMER0.h"
#include "../include/TIMER0_private.h"


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

static void (*Timer0_OverflowInterruptHandler)( void);
static void (*Timer0_CompareInterruptHandler)( void);

static  u8 Timer0_InitValue;
/********************************** Software Interfaces Declarations *******************/



Timer0_StatusErrorType Timer0_enuInit(const Timer0_ConfigType* Address_Timer0){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{

		    	/* Disable Timer0 Peripheral */
		    	        Timer0_Disable();

		    	        /* Select Mode timer */
		    	        Timer0_SelectMode((Address_Timer0->select_mode));

		    	        Timer0_InitValue = Address_Timer0->init_value;
		    	        /* Update Init Value*/
		    	       Loc_enuTimer0Status= Timer0_SetValue(Address_Timer0, Address_Timer0->init_value);

		    	        /* Enable Timer0 Peripheral */
		    	        Timer0_Enable(Address_Timer0->prescaler_value);

		    }

		    return Loc_enuTimer0Status;
}

Timer0_StatusErrorType Timer0_DeInit(const Timer0_ConfigType* Address_Timer0){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{

		    	/* Disable Timer0 Peripheral */
		    	Timer0_Disable();

		    }

		    return Loc_enuTimer0Status;
}

Timer0_StatusErrorType Timer0_enuEnableInterrupt(const Timer0_ConfigType* Address_Timer0){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{

		    	if(Address_Timer0->select_mode == TIMER0_SELECT_MODE_NORMAL){

		    		Timer0_EnableOverviewInterrupt();


		    	}
		    	else{
		    		Timer0_EnableComparePwmInterrupt();
		    	}

		    }

		    return Loc_enuTimer0Status;
}

Timer0_StatusErrorType Timer0_enuDisableInterrupt(const Timer0_ConfigType* Address_Timer0){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{

		    	if(Address_Timer0->select_mode == TIMER0_SELECT_MODE_NORMAL){

		    		Timer0_DisableOverviewInterrupt();


		    	}
		    	else{
		    		Timer0_DisbleComparePwmInterrupt();
		    	}

		    }

		    return Loc_enuTimer0Status;
}


Timer0_StatusErrorType Timer0_SetValue(const Timer0_ConfigType* Address_Timer0, u8 Copy_u8Value){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{

		    	TCNT0 =Copy_u8Value;

		    }

		    return Loc_enuTimer0Status;
}
Timer0_StatusErrorType Timer0_GetTimeElapsed(const Timer0_ConfigType* Address_Timer0, u16* Address_Value){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{


		    }

		    return Loc_enuTimer0Status;
}
Timer0_StatusErrorType Timer0_GetRemaining(const Timer0_ConfigType* Address_Timer0, u16* Address_Value){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{

		    	*Address_Value = TCNT0;
		    }

		    return Loc_enuTimer0Status;
}


Timer0_StatusErrorType Timer0_SetCallbackFunction(const Timer0_ConfigType* Address_Timer0,void (*callback)(void)){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{

		    	if(Address_Timer0->select_mode == TIMER0_SELECT_MODE_NORMAL){

		    		Timer0_OverflowInterruptHandler = callback;


		    	}
		    	else{
		    		Timer0_CompareInterruptHandler = callback;
		    	}


		    }

		    return Loc_enuTimer0Status;
}




// ISR function For TIMER0 Compare Match
void __vector_10(void) __attribute__((signal));

void __vector_10(void){

	    if(NULL !=Timer0_CompareInterruptHandler ){
	    	Timer0_CompareInterruptHandler();
	    }
	    else {/*  error in declaration */}

}




// ISR function For TIMER0 OverFlow
void __vector_11(void) __attribute__((signal));

void __vector_11(void){

//	Timer0_DisableOverviewInterrupt();




    if(NULL !=Timer0_OverflowInterruptHandler ){

    	Timer0_OverflowInterruptHandler();

    	TCNT0 = Timer0_InitValue;
    }
    else {/*  error in declaration */   }

//    Timer0_EnableOverviewInterrupt();
}


