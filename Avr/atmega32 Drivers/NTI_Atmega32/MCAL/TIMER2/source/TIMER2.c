/**************************************************************************/
/* Filename						: TIMER2.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 27 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/


/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../DIO/include/DIO.h"

#include "../include/TIMER2_config.h"
#include "../include/TIMER2.h"
#include "../include/TIMER2_private.h"

/*********************************Static/ Pirvate Part *************************************/

static void (*Timer2_OverflowInterruptHandler)( void);
static void (*Timer2_CompareInterruptHandler)( void);

static  u8 Global_StaticU8InitValueTimer2;
static  Timer2_SelectMode Global_enuTimer2Mode;


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/
Timer2_StatusErrorType Timer2_enuInit(const Timer2_ConfigType* Address_Timer2){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

			    if(NULL == Address_Timer2){

			    	Loc_enuTimer2Status = TIMER2_STATUS_NULL_POINTER_ADDRESS;
			    }
			    else{

			    	/* Disable Timer2 Peripheral */
			    	        Timer2_Disable();

			    	        /* Select Mode timer */
			    	        Timer2_SelectMode((Address_Timer2->select_mode));

			    	        Global_StaticU8InitValueTimer2 = Address_Timer2->init_value_general_counter;
			    	        Global_enuTimer2Mode = Address_Timer2->select_mode;
			    	        /* Update Init Value*/
			    	        Loc_enuTimer2Status= Timer2_enuSetValueNormalCounter(Address_Timer2->init_value_general_counter);

			    	        /* Enable Timer2 Peripheral */
			    	        Timer2_Enable(Address_Timer2->prescaler_value);

			    }

			    return Loc_enuTimer2Status;
}

Timer2_StatusErrorType Timer2_DeInit(const Timer2_ConfigType* Address_Timer2){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

			    if(NULL == Address_Timer2){

			    	Loc_enuTimer2Status = TIMER2_STATUS_NULL_POINTER_ADDRESS;
			    }
			    else{
			    	/* Disable Timer2 Peripheral */
			    	Timer2_Disable();


			    }

			    return Loc_enuTimer2Status;
}

Timer2_StatusErrorType Timer2_enuEnableOverflowInterrupt(void){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

	Timer2_EnableOverviewInterrupt();

	return Loc_enuTimer2Status;
}


Timer2_StatusErrorType Timer2_enuEnableCaptureInterrupt(void){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

	Timer2_EnableComparePwmInterrupt();
	return Loc_enuTimer2Status;
}

Timer2_StatusErrorType Timer2_enuDisableOverflowInterrupt(void){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

	Timer2_DisableOverviewInterrupt();

	return Loc_enuTimer2Status;
}
Timer2_StatusErrorType Timer2_enuDisableCaptureInterrupt(void){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;
	Timer2_DisbleComparePwmInterrupt();

	return Loc_enuTimer2Status;
}

Timer2_StatusErrorType Timer2_enuSetCallbackOverflowInterrupt(void (*callback)(void)){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

	if(NULL == callback){

		Loc_enuTimer2Status = TIMER2_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		Timer2_OverflowInterruptHandler = callback;


	}

	return Loc_enuTimer2Status;
}

Timer2_StatusErrorType Timer2_enuSetCallbackCompareInterrupt(void (*callback)(void)){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

			    if(NULL == callback){

			    	Loc_enuTimer2Status = TIMER2_STATUS_NULL_POINTER_ADDRESS;
			    }
			    else{

			    	Timer2_CompareInterruptHandler = callback;

			    }

			    return Loc_enuTimer2Status;
}

Timer2_StatusErrorType Timer2_enuCtcForcePinImmediatly(void){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

	SET_BIT(TCCR2,TCCR2_FOC2_BIT);

	return Loc_enuTimer2Status;
}




Timer2_StatusErrorType Timer2_enuSetDutyCyclePwm(u8 Copy_u8DutyCylePrecentage){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;
	u8 Loc_u8DutyCycle;
	Copy_u8DutyCylePrecentage = (Copy_u8DutyCylePrecentage >= 100) ? 100 :Copy_u8DutyCylePrecentage;

	switch(Global_enuTimer2Mode){

	case  TIMER2_SELECT_MODE_NORMAL:
	case  TIMER2_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC2_NORMAEL:
	case  TIMER2_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC2_TOGGLE :
	case  TIMER2_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC2_CLEAR  :
	case  TIMER2_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC2_SET :
		Loc_enuTimer2Status = TIMER2_STATUS_FAIL;
		break;

	case TIMER2_SELECT_MODE_PWM_FAST_NORMAL_OC2:
	case TIMER2_SELECT_MODE_PWM_PHASE_CORRECT_OC2_NORMAL:
		/* i don't know what is the usage of this */
		break;

	case TIMER2_SELECT_MODE_PWM_FAST_INVERTED_OC2_SET_ON_MATCH_CLEAR_AT_TOP:
	case TIMER2_SELECT_MODE_PWM_PHASE_CORRECT_OC2_SET_ON_MATCH_UPCOUNTING_CLEAR_ON_MATCH_DOWNCOUNTING:
		Loc_u8DutyCycle = TIMER2_FULL_VALUE_IN_REGISTER- (u8)((f32)Copy_u8DutyCylePrecentage/100 * TIMER2_FULL_VALUE_IN_REGISTER);
		ASSIGN_REG(OCR2,Loc_u8DutyCycle);

		break;

	case TIMER2_SELECT_MODE_PWM_FAST_NOT_INVERTED_OC2_CLEAR_ON_MATCH_SET_AT_TOP:
	case TIMER2_SELECT_MODE_PWM_PHASE_CORRECT_OC2_CLEAR_ON_MATCH_UPCOUNTING_SET_ON_MATCH_DOWNCOUNTING:
		Loc_u8DutyCycle = (u8)((f32)Copy_u8DutyCylePrecentage/100 * TIMER2_FULL_VALUE_IN_REGISTER);
		ASSIGN_REG(OCR2,Loc_u8DutyCycle);

		break;

	}

	return Loc_enuTimer2Status;
}



Timer2_StatusErrorType Timer2_enuSetValueNormalCounter(u8 Copy_u8Value){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;
	ASSIGN_REG(TCNT2,Copy_u8Value);

	return Loc_enuTimer2Status;
}
Timer2_StatusErrorType Timer2_enuGetTimeElapsedNormalCounter(u8* Address_Value){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

	if(NULL == Address_Value){

		Loc_enuTimer2Status = TIMER2_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		*Address_Value = TCNT2;

	}

	return Loc_enuTimer2Status;
}


Timer2_StatusErrorType Timer2_enuGetRemainingNormalCounter(u8* Address_Value){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

	if(NULL == Address_Value){

		Loc_enuTimer2Status = TIMER2_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		*Address_Value = TIMER2_FULL_VALUE_IN_REGISTER - TCNT2;

	}

	return Loc_enuTimer2Status;
}



Timer2_StatusErrorType Timer2_enuSetValueCompareMode(u8 Copy_u8Value){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

	ASSIGN_REG(OCR2,Copy_u8Value);

	return Loc_enuTimer2Status;
}


Timer2_StatusErrorType Timer2_enuGetTimeElapsedCompareMode(u8* Address_Value){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

	if(NULL == Address_Value){

		Loc_enuTimer2Status = TIMER2_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		*Address_Value = TCNT2;

	}

			    return Loc_enuTimer2Status;
}
Timer2_StatusErrorType Timer2_enuGetRemainingCompareMode(u8* Address_Value){
	Timer2_StatusErrorType Loc_enuTimer2Status = TIMER2_STATUS_OK;

			    if(NULL == Address_Value){

			    	Loc_enuTimer2Status = TIMER2_STATUS_NULL_POINTER_ADDRESS;
			    }
			    else{

			    	*Address_Value = OCR2 - TCNT2;

			    }

			    return Loc_enuTimer2Status;
}





// ISR function For TIMER2 Compare Match
void __vector_4(void) __attribute__((signal));

void __vector_4(void){

	    if(NULL !=Timer2_CompareInterruptHandler ){
	    	Timer2_CompareInterruptHandler();
	    }
	    else {/*  error in declaration */}

}




// ISR function For TIMER2 OverFlow
void __vector_5(void) __attribute__((signal));

void __vector_5(void){

//	Timer0_DisableOverviewInterrupt();



    if(NULL !=Timer2_OverflowInterruptHandler ){

    	TCNT2= Global_StaticU8InitValueTimer2;
    	Timer2_OverflowInterruptHandler();


    }
    else {/*  error in declaration */   }

//    Timer0_EnableOverviewInterrupt();
}

