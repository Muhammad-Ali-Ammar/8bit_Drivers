/**************************************************************************/
/* Filename						: TIMER1.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 26 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_TIMER1_INCLUDE_TIMER1_H_
#define MCAL_TIMER1_INCLUDE_TIMER1_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define	TIMER1_16BIT_MAX_REGISTER_VALUE			(65535)


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

typedef enum{


    TIMER1_PRESCALER_NO_DIV=1,
    TIMER1_PRESCALER_DIV_8,
    TIMER1_PRESCALER_DIV_64,
    TIMER1_PRESCALER_DIV_256,
    TIMER1_PRESCALER_DIV_1024,
    TIMER1_PRESCALER_EXTERNAL_CLOCK_SORUCE_FAILING_EDGE_T1PIN,
    TIMER1_PRESCALER_EXTERNAL_CLOCK_SORUCE_RASING_EDGE_T1PIN

}Timer1_PrescalerType;



typedef enum{
    TIMER1_SELECT_MODE_NORMAL_MODE0 ,

    TIMER1_SELECT_MODE_PWM_PHASE_CORRECT_8BIT_MODE1,
    TIMER1_SELECT_MODE_PWM_PHASE_CORRECT_9BIT_MODE2,
    TIMER1_SELECT_MODE_PWM_PHASE_CORRECT_10BIT_MODE3,

    TIMER1_SELECT_MODE_CTC_OCR1A_MODE4,

    TIMER1_SELECT_MODE_PWM_FAST_8BIT_MODE5,
    TIMER1_SELECT_MODE_PWM_FAST_9BIT_MODE6,
    TIMER1_SELECT_MODE_PWM_FAST_10BIT_MODE7,

    TIMER1_SELECT_MODE_PWM_PHASE__FREQ_CORRECT_8BIT_ICR1_MODE8,
    TIMER1_SELECT_MODE_PWM_PHASE_FREQ_CORRECT_9BIT_OCR1A_MODE9,

    TIMER1_SELECT_MODE_PWM_PHASE_CORRECT_ICR1_MODE10,
    TIMER1_SELECT_MODE_PWM_PHASE_CORRECT_OCR1A_MODE11,

	TIMER1_SELECT_MODE_CTC_ICR1_MODE12,

    TIMER1_SELECT_MODE_PWM_FAST_ICR1_MODE14= 14,
    TIMER1_SELECT_MODE_PWM_FAST_OCR1A_MODE15

}Timer1_SelectModeType;


typedef enum{
	TIMER1_SELECT_OUTPUT_MODE_NORMAL_CHANNELA,
	TIMER1_SELECT_OUTPUT_MODE_IN_CTC_TOGGLE__IN_FAST_PWM_ORCIA_TOP_TOGGLE__IN_PHASE_CORRECT_ORCIA_TOP_TOGGLE__IN_OTHERS_DISCONNECTED_CHANNELA,
	TIMER1_SELECT_OUTPUT_MODE_IN_CTC_CLEAR__IN_FAST_PWM_CLEAR_ON_MATCH___IN_PHASE_CORRECT_CLEAR_AT_MATCH_UPCOUNTING_SET_AT_MATCH_AT_DOCOUNTING_CHANNELA,
	TIMER1_SELECT_OUTPUT_MODE_IN_CTC_SET__IN_FAST_PWM_SET_ON_MATCH___IN_PHASE_CORRECT_SET_AT_MATCH_UPCOUNTING_CLEAR_AT_MATCH_AT_DOCOUNTING_CHANNELA
}Timer1_SelectOutputModeChannelAType;

typedef enum{
	TIMER1_SELECT_OUTPUT_MODE_NORMAL_CHANNELB,
	TIMER1_SELECT_OUTPUT_MODE_IN_CTC_DISCONNECTED_CHANNELB,
	TIMER1_SELECT_OUTPUT_MODE_IN_CTC_CLEAR__IN_FAST_PWM_CLEAR_ON_MATCH___IN_PHASE_CORRECT_CLEAR_AT_MATCH_UPCOUNTING_SET_AT_MATCH_AT_DOCOUNTING_CHANNELB,
	TIMER1_SELECT_OUTPUT_MODE_IN_CTC_SET__IN_FAST_PWM_SET_ON_MATCH___IN_PHASE_CORRECT_SET_AT_MATCH_UPCOUNTING_CLEAR_AT_MATCH_AT_DOCOUNTING_CHANNELB
}Timer1_SelectOutputModeChannelBType;


typedef struct{
	Timer1_PrescalerType prescaler_value;
	Timer1_SelectModeType select_mode;
	Timer1_SelectOutputModeChannelAType select_output_mode_channelA;
	Timer1_SelectOutputModeChannelBType select_output_mode_channelB;
	u16  	init_counter_value;

}Timer1_ConfigType;

typedef enum{
	TIMER1_STATUS_OK,
	TIMER1_STATUS_FAIL,
	TIMER1_STATUS_NULL_POINTER_ADDRESS
}Timer1_StatusErrorType;

/********************************** Software Interfaces Declarations *******************/



Timer1_StatusErrorType Timer1_enuInit(const Timer1_ConfigType* Address_Timer1);
Timer1_StatusErrorType Timer1_DeInit(const Timer1_ConfigType* Address_Timer1);

Timer1_StatusErrorType Timer1_enuEnableInterruptOverflow(void);
Timer1_StatusErrorType Timer1_enuDisableInterruptOverflow(void);

Timer1_StatusErrorType Timer1_enuEnableInterruptCompareChannelA(void);
Timer1_StatusErrorType Timer1_enuDisableInterruptCompareChannelA(void);


Timer1_StatusErrorType Timer1_enuEnableInterruptCompareChannelB(void);
Timer1_StatusErrorType Timer1_enuDisableInterruptCompareChannelB(void);


Timer1_StatusErrorType Timer1_enuEnableInterruptIcu(void);
Timer1_StatusErrorType Timer1_enuDisableInterruptIcu(void);



Timer1_StatusErrorType Timer1_enuSetCallbackFunctionOverflow(void (*callback)(void));
Timer1_StatusErrorType Timer1_enuSetCallbackFunctionCompareChannelA(void (*callback)(void));
Timer1_StatusErrorType Timer1_enuSetCallbackFunctionCompareChannelB(void (*callback)(void));
Timer1_StatusErrorType Timer1_enuSetCallbackFunctionIcu(void (*callback)(void));


Timer1_StatusErrorType Timer1_enuSetValueNormalCounter(u16 Copy_u16Value);
Timer1_StatusErrorType Timer1_enuSetValueCompareChannelA(u16 Copy_u16Value);
Timer1_StatusErrorType Timer1_enuSetValueCompareChannelB(u16 Copy_u16Value);
Timer1_StatusErrorType Timer1_enuSetValueIcu(u16 Copy_u16Value);

Timer1_StatusErrorType Timer1_enuGetTimeElapsedNormalCounter(u16* Address_Value);
Timer1_StatusErrorType Timer1_enuGetTimeElapsedCompareChannelA(u16* Address_Value);
Timer1_StatusErrorType Timer1_enuGetTimeElapsedCompareChannelB(u16* Address_Value);
Timer1_StatusErrorType Timer1_enuGetTimeElapsedIcu(u16* Address_Value);



Timer1_StatusErrorType Timer1_enuCtcForcePinImmediatlyChannelA(void);
Timer1_StatusErrorType Timer1_enuCtcForcePinImmediatlyChannelB(void);

Timer1_StatusErrorType Timer1_enuSetRisingEdgeIcu(void);
Timer1_StatusErrorType Timer1_enuSetFailingEdgeIcu(void);
Timer1_StatusErrorType Timer1_enuToggleEdgeIcu(void);





#endif /* MCAL_TIMER1_INCLUDE_TIMER1_H_ */
