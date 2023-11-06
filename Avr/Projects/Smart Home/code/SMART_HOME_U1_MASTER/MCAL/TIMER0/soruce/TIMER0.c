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
		    	       Loc_enuTimer0Status= Timer0_enuSetValue(Address_Timer0, Address_Timer0->init_value);

		    	        /* Enable Timer0 Peripheral */
		    	        Timer0_Enable(Address_Timer0->prescaler_value);

		    }

		    return Loc_enuTimer0Status;
}

Timer0_StatusErrorType Timer0_enuDeInit(const Timer0_ConfigType* Address_Timer0){
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


Timer0_StatusErrorType Timer0_enuSetValue(const Timer0_ConfigType* Address_Timer0, u8 Copy_u8Value){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{

		    	if(Address_Timer0->select_mode == TIMER0_SELECT_MODE_NORMAL){



		    		ASSIGN_REG(TCNT0,Copy_u8Value);

		    	}
		    	else{
		    		ASSIGN_REG(OCR0,Copy_u8Value);
		    	}



		    }

		    return Loc_enuTimer0Status;
}
Timer0_StatusErrorType Timer0_enuGetTimeElapsed(const Timer0_ConfigType* Address_Timer0, u16* Address_Value){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{

		    	*Address_Value = TCNT0;
		    }

		    return Loc_enuTimer0Status;
}
Timer0_StatusErrorType Timer0_enuGetRemaining(const Timer0_ConfigType* Address_Timer0, u16* Address_Value){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{


		    }

		    return Loc_enuTimer0Status;
}


Timer0_StatusErrorType Timer0_enuSetCallbackFunction(const Timer0_ConfigType* Address_Timer0,void (*callback)(void)){
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

Timer0_StatusErrorType Timer0_enuEnableOverflowInterrupt(void){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

			Timer0_EnableOverviewInterrupt();

		    return Loc_enuTimer0Status;
}

Timer0_StatusErrorType Timer0_enuEnableCaptureInterrupt(void){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

			Timer0_EnableComparePwmInterrupt();

		    return Loc_enuTimer0Status;
}


Timer0_StatusErrorType Timer0_enuSetCallbackOverflowInterrupt(void (*callback)(void)){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == callback){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }

		    else{
		    		Timer0_OverflowInterruptHandler = callback;


		    }

		    return Loc_enuTimer0Status;
}
Timer0_StatusErrorType Timer0_enuSetCallbackCompareInterrupt(void (*callback)(void)){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == callback){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }

		    else{
		    		Timer0_CompareInterruptHandler = callback;


		    }

		    return Loc_enuTimer0Status;
}


Timer0_StatusErrorType Timer0_enuDisableOverflowInterrupt(void){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

			Timer0_DisableOverviewInterrupt();

		    return Loc_enuTimer0Status;
}

Timer0_StatusErrorType Timer0_enuDisableCaptureInterrupt(void){

		Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

	  	Timer0_DisbleComparePwmInterrupt();

			    return Loc_enuTimer0Status;

}



Timer0_StatusErrorType Timer0_enuCtcForcePinImmediatly(const Timer0_ConfigType* Address_Timer0){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{

		    	SET_BIT(TCCR0,FOC0_BIT);


		    }

		    return Loc_enuTimer0Status;
}


Timer0_StatusErrorType Timer0_enuSetDutyCyclePwm(const Timer0_ConfigType* Address_Timer0,u8 Copy_u8DutyCylePrecentage){
	Timer0_StatusErrorType Loc_enuTimer0Status = TIMER0_STATUS_OK;

//	u8 Loc_u8DutyCycle = (u8)((f32)Copy_u8DutyCylePrecentage/100 * 255);
	u8 Loc_u8DutyCycle;

		    if(NULL == Address_Timer0){

		    	Loc_enuTimer0Status = TIMER0_STATUS_NULL_POINTER_ADDRESS;
		    }

		    else {

		    	Copy_u8DutyCylePrecentage = (Copy_u8DutyCylePrecentage >= 100) ? 100 :Copy_u8DutyCylePrecentage;

		    	switch(Address_Timer0->select_mode){

		    	case  TIMER0_SELECT_MODE_NORMAL:
		    	case  TIMER0_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC0_NORMAEL:
		    	case  TIMER0_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC0_TOGGLE :
		    	case  TIMER0_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC0_CLEAR  :
		    	case  TIMER0_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC0_SET :
		    		Loc_enuTimer0Status = TIMER0_STATUS_FAIL;
		    		break;

		    	case TIMER0_SELECT_MODE_PWM_FAST_NORMAL_OC0:
		    	case TIMER0_SELECT_MODE_PWM_PHASE_CORRECT_OC0_NORMAL:
		    		/* i don't know what is the usage of this */
		    		break;

		    	case TIMER0_SELECT_MODE_PWM_FAST_INVERTED_OC0_SET_ON_MATCH_CLEAR_AT_TOP:
		    	case TIMER0_SELECT_MODE_PWM_PHASE_CORRECT_OC0_SET_ON_MATCH_UPCOUNTING_CLEAR_ON_MATCH_DOWNCOUNTING:
		    		Loc_u8DutyCycle = TIMER0_FULL_VALUE_IN_REGISTER- (u8)((f32)Copy_u8DutyCylePrecentage/100 * TIMER0_FULL_VALUE_IN_REGISTER);
		    		ASSIGN_REG(OCR0,Loc_u8DutyCycle);

		    		break;

		    	case TIMER0_SELECT_MODE_PWM_FAST_NOT_INVERTED_OC0_CLEAR_ON_MATCH_SET_AT_TOP:
		    	case TIMER0_SELECT_MODE_PWM_PHASE_CORRECT_OC0_CLEAR_ON_MATCH_UPCOUNTING_SET_ON_MATCH_DOWNCOUNTING:
		    		Loc_u8DutyCycle = (u8)((f32)Copy_u8DutyCylePrecentage/100 * TIMER0_FULL_VALUE_IN_REGISTER);
		    		ASSIGN_REG(OCR0,Loc_u8DutyCycle);

		    		break;



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

    	TCNT0 = Timer0_InitValue;
    	Timer0_OverflowInterruptHandler();


    }
    else {/*  error in declaration */   }

//    Timer0_EnableOverviewInterrupt();
}


