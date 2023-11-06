/**************************************************************************/
/* Filename						: TIMER2.h                                */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 27 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef MCAL_TIMER2_INCLUDE_TIMER2_H_
#define MCAL_TIMER2_INCLUDE_TIMER2_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

typedef enum{


    TIMER2_PRESCALER_NO_DIV=1,
    TIMER2_PRESCALER_DIV_8,
    TIMER2_PRESCALER_DIV_32,
    TIMER2_PRESCALER_DIV_64,
    TIMER2_PRESCALER_DIV_128,
    TIMER2_PRESCALER_DIV_256,
    TIMER2_PRESCALER_DIV_1024

}Timer2_PrescalerTYpe;


// 		COM01	COM00   WGM20 WGM21

typedef enum{
    TIMER2_SELECT_MODE_NORMAL = 0b0000,

    TIMER2_SELECT_MODE_PWM_PHASE_CORRECT_OC2_NORMAL = 0b0001,
    TIMER2_SELECT_MODE_PWM_PHASE_CORRECT_OC2_CLEAR_ON_MATCH_UPCOUNTING_SET_ON_MATCH_DOWNCOUNTING = 0b1001,
    TIMER2_SELECT_MODE_PWM_PHASE_CORRECT_OC2_SET_ON_MATCH_UPCOUNTING_CLEAR_ON_MATCH_DOWNCOUNTING = 0b1101,

	TIMER2_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC2_NORMAEL = 0b0010,
	TIMER2_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC2_TOGGLE =  0b0110,
	TIMER2_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC2_CLEAR =   0b1010,
	TIMER2_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC2_SET = 0b1110,



    TIMER2_SELECT_MODE_PWM_FAST_NORMAL_OC2 = 0b0011,
    TIMER2_SELECT_MODE_PWM_FAST_NOT_INVERTED_OC2_CLEAR_ON_MATCH_SET_AT_TOP= 0b1011,
    TIMER2_SELECT_MODE_PWM_FAST_INVERTED_OC2_SET_ON_MATCH_CLEAR_AT_TOP= 0b1111,

}Timer2_SelectMode;

typedef struct{
	Timer2_PrescalerTYpe prescaler_value;
	Timer2_SelectMode select_mode;
	u8  	init_value_general_counter;

}Timer2_ConfigType;


typedef enum{
	TIMER2_STATUS_FAIL,
	TIMER2_STATUS_OK,
	TIMER2_STATUS_NULL_POINTER_ADDRESS,
}Timer2_StatusErrorType;




/********************************** Software Interfaces Declarations *******************/

Timer2_StatusErrorType Timer2_enuInit(const Timer2_ConfigType* Address_Timer2);

Timer2_StatusErrorType Timer2_DeInit(const Timer2_ConfigType* Address_Timer2);
Timer2_StatusErrorType Timer2_enuEnableOverflowInterrupt(void);
Timer2_StatusErrorType Timer2_enuEnableCaptureInterrupt(void);

Timer2_StatusErrorType Timer2_enuDisableOverflowInterrupt(void);
Timer2_StatusErrorType Timer2_enuDisableCaptureInterrupt(void);

Timer2_StatusErrorType Timer2_enuSetCallbackOverflowInterrupt(void (*callback)(void));
Timer2_StatusErrorType Timer2_enuSetCallbackCompareInterrupt(void (*callback)(void));

Timer2_StatusErrorType Timer2_enuCtcForcePinImmediatly(void);
Timer2_StatusErrorType Timer2_enuSetDutyCyclePwm(u8 Copy_u8DutyCylePrecentage);

Timer2_StatusErrorType Timer2_enuSetValueNormalCounter(u8 Copy_u8Value);
Timer2_StatusErrorType Timer2_enuGetTimeElapsedNormalCounter(u8* Address_Value);
Timer2_StatusErrorType Timer2_enuGetRemainingNormalCounter(u8* Address_Value);

Timer2_StatusErrorType Timer2_enuSetValueCompareMode(u8 Copy_u8Value);
Timer2_StatusErrorType Timer2_enuGetTimeElapsedCompareMode(u8* Address_Value);
Timer2_StatusErrorType Timer2_enuGetRemainingCompareMode(u8* Address_Value);





#endif /* MCAL_TIMER2_INCLUDE_TIMER2_H_ */
