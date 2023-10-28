/**************************************************************************/
/* Filename						: TIMER1.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 26 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/
#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../DIO/include/DIO.h"

#include "../include/TIMER1_private.h"
#include "../include/TIMER1_config.h"
#include "../include/TIMER1.h"

/*********************************** Private Part *********************/


static void (*Timer1_OverflowInterruptHandler)( void);
static void (*Timer1_CompareChannelAInterruptHandler)( void);
static void (*Timer1_CompareChannelBInterruptHandler)( void);
static void (*Timer1_IcuInterruptHandler)( void);

static  u16 Timer1_StaticU16InitValue;

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/

Timer1_StatusErrorType Timer1_enuInit(const Timer1_ConfigType* Address_Timer1){
	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

			    if(NULL == Address_Timer1){

			    	Loc_enuTimer1Status = TIMER1_STATUS_NULL_POINTER_ADDRESS;
			    }
			    else{

			    	/* Disable Timer1 Peripheral */
			    	        Timer1_Disable();

			    	        /* Select Mode timer */
			    	        Timer1_SelectMode((Address_Timer1->select_mode));

			    	        /* Select Mode timer ChannelA*/
			    	        Timer1_SelectOutputModeChannelA(Address_Timer1->select_output_mode_channelA);

			    	        /* Select Mode timer Channel B*/
			    	        Timer1_SelectOutputModeChannelB((Address_Timer1->select_output_mode_channelB));

			    	        Timer1_StaticU16InitValue = Address_Timer1->init_counter_value;

			    	        /* Update Init Value*/
			    	        Loc_enuTimer1Status= Timer1_enuSetValueNormalCounter(Address_Timer1->init_counter_value);

			    	        /* Enable Timer1 Peripheral */
			    	        Timer1_Enable(Address_Timer1->prescaler_value);

			    }

			    return Loc_enuTimer1Status;
}

Timer1_StatusErrorType Timer1_DeInit(const Timer1_ConfigType* Address_Timer1){
	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

			    if(NULL == Address_Timer1){

			    	Loc_enuTimer1Status = TIMER1_STATUS_NULL_POINTER_ADDRESS;
			    }
			    else{

			    	/* Disable Timer1 Peripheral */
			    	        Timer1_Disable();
			    }

			    return Loc_enuTimer1Status;
}

Timer1_StatusErrorType Timer1_enuEnableInterruptOverflow(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	Timer1_EnableOverviewInterrupt();

	return Loc_enuTimer1Status;
}

Timer1_StatusErrorType Timer1_enuDisableInterruptOverflow(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

	Timer1_DisableOverviewInterrupt();
	return Loc_enuTimer1Status;
}

Timer1_StatusErrorType Timer1_enuEnableInterruptCompareChannelA(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	Timer1_EnableChannelA_ComparePwmInterrupt();

	return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuDisableInterruptCompareChannelA(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	Timer1_DisbleChannelA_ComparePwmInterrupt();

	return Loc_enuTimer1Status;
}


Timer1_StatusErrorType Timer1_enuEnableInterruptCompareChannelB(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

	Timer1_EnableChannelB_ComparePwmInterrupt();

	return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuDisableInterruptCompareChannelB(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	Timer1_DisbleChannelB_ComparePwmInterrupt();

	return Loc_enuTimer1Status;
}


Timer1_StatusErrorType Timer1_enuEnableInterruptIcu(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	Timer1_EnableIcuInterrupt();

	return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuDisableInterruptIcu(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	Timer1_DisableIcuInterrupt();

	return Loc_enuTimer1Status;
}



Timer1_StatusErrorType Timer1_enuSetCallbackFunctionOverflow(void (*callback)(void)){

		Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

		if(NULL == callback){

			Loc_enuTimer1Status = TIMER1_STATUS_NULL_POINTER_ADDRESS;
		}
		else{
			Timer1_OverflowInterruptHandler = callback;
		}

		return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuSetCallbackFunctionCompareChannelA(void (*callback)(void)){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

			if(NULL == callback){

				Loc_enuTimer1Status = TIMER1_STATUS_NULL_POINTER_ADDRESS;
			}
			else{
				Timer1_CompareChannelAInterruptHandler = callback;
			}

			return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuSetCallbackFunctionCompareChannelB(void (*callback)(void)){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

				if(NULL == callback){

					Loc_enuTimer1Status = TIMER1_STATUS_NULL_POINTER_ADDRESS;
				}
				else{
					Timer1_CompareChannelBInterruptHandler = callback;
				}

				return Loc_enuTimer1Status;
}

Timer1_StatusErrorType Timer1_enuSetCallbackFunctionIcu(void (*callback)(void)){
	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

				if(NULL == callback){

					Loc_enuTimer1Status = TIMER1_STATUS_NULL_POINTER_ADDRESS;
				}
				else{
					Timer1_IcuInterruptHandler = callback;
				}

				return Loc_enuTimer1Status;
}


Timer1_StatusErrorType Timer1_enuSetValueNormalCounter(u16 Copy_u16Value){
	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	ASSIGN_REG(TCNT1H,(Copy_u16Value>>8));
	ASSIGN_REG(TCNT1L,(Copy_u16Value &0x0F));

		return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuSetValueCompareChannelA(u16 Copy_u16Value){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	ASSIGN_REG(OCR1AH,(Copy_u16Value>>8));
	ASSIGN_REG(OCR1AL,(Copy_u16Value &0x0F));

	return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuSetValueCompareChannelB(u16 Copy_u16Value){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	ASSIGN_REG(OCR1BH,(Copy_u16Value>>8));
	ASSIGN_REG(OCR1BL,(Copy_u16Value &0x0F));

	return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuSetValueIcu(u16 Copy_u16Value){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	ASSIGN_REG(ICR1H,(Copy_u16Value>>8));
	ASSIGN_REG(ICR1L,(Copy_u16Value &0x0F));

	return Loc_enuTimer1Status;
}

Timer1_StatusErrorType Timer1_enuGetTimeElapsedNormalCounter(u16* Address_Value){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

	if(NULL == Address_Value){

		Loc_enuTimer1Status = TIMER1_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_Value=TCNT1L;
		*Address_Value|=(TCNT1H<<EIGHT_VALUE);
	}

	return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuGetTimeElapsedCompareChannelA(u16* Address_Value){
	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

	if(NULL == Address_Value){

		Loc_enuTimer1Status = TIMER1_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_Value=OCR1AL;
		*Address_Value|=(OCR1AH<<EIGHT_VALUE);
	}

	return Loc_enuTimer1Status;

}

Timer1_StatusErrorType Timer1_enuGetTimeElapsedCompareChannelB(u16* Address_Value){
	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

				    if(NULL == Address_Value){

				    	Loc_enuTimer1Status = TIMER1_STATUS_NULL_POINTER_ADDRESS;
				    }
				    else{
						*Address_Value=OCR1BL;
						*Address_Value|=(OCR1BH<<EIGHT_VALUE);
				    }

				    return Loc_enuTimer1Status;

}

Timer1_StatusErrorType Timer1_enuGetTimeElapsedIcu(u16* Address_Value){
	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;

	if(NULL == Address_Value){

		Loc_enuTimer1Status = TIMER1_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_Value=ICR1L;
		*Address_Value|=(ICR1H<<EIGHT_VALUE);
	}

	return Loc_enuTimer1Status;

}




Timer1_StatusErrorType Timer1_enuCtcForcePinImmediatlyChannelA(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	SET_BIT(TCCR1A,TCCR1A_FOC1A_BIT);

	return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuCtcForcePinImmediatlyChannelB(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	SET_BIT(TCCR1A,TCCR1A_FOC1B_BIT);

	return Loc_enuTimer1Status;
}

Timer1_StatusErrorType Timer1_enuSetRisingEdgeIcu(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	SET_BIT(TCCR1B,TCCR1B_ICES1_BIT);

	return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuSetFailingEdgeIcu(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	CLEAR_BIT(TCCR1B,TCCR1B_ICES1_BIT);

	return Loc_enuTimer1Status;
}
Timer1_StatusErrorType Timer1_enuToggleEdgeIcu(void){

	Timer1_StatusErrorType Loc_enuTimer1Status = TIMER1_STATUS_OK;
	TOGGLE_BIT(TCCR1B,TCCR1B_ICES1_BIT);

	return Loc_enuTimer1Status;
}

///////////////////////////////////////////////////////////////////////////////////////////

	/* Isr Part */
///////////////////////////////////////////////////////////////////////////////////////////

// ISR function For TIMER1 OverFlow
void __vector_9(void) __attribute__((signal));

void __vector_9(void){

//	Timer1_DisableOverviewInterrupt();



    if(NULL !=Timer1_OverflowInterruptHandler ){

    	Timer1_enuSetValueNormalCounter(Timer1_StaticU16InitValue);
    	Timer1_OverflowInterruptHandler();


    }
    else {/*  error in declaration */   }

//    Timer1_EnableOverviewInterrupt();
}


// ISR function For TIMER1 ICU
void __vector_6(void) __attribute__((signal));

void __vector_6(void){

//	Timer1_DisableOverviewInterrupt();

	Dio_enuFlipChannel(DIO_PINC0_CHANNEL16);


    if(NULL !=Timer1_IcuInterruptHandler ){

    	Timer1_IcuInterruptHandler();


    }
    else {/*  error in declaration */   }

//    Timer1_EnableOverviewInterrupt();
}




