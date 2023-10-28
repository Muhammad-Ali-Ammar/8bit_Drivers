/**************************************************************************/
/* Filename						: TIMER0.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 24 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_TIMER0_INCLUDE_TIMER0_H_
#define MCAL_TIMER0_INCLUDE_TIMER0_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/


typedef enum{


    TIMER0_PRESCALER_NO_DIV,
    TIMER0_PRESCALER_DIV_8,
    TIMER0_PRESCALER_DIV_64,
    TIMER0_PRESCALER_DIV_128,
    TIMER0_PRESCALER_DIV_256,
    TIMER0_PRESCALER_DIV_1024,
    TIMER0_PRESCALER_EXTERNAL_CLOCK_SORUCE_FAILING_EDGE_T0PIN,
    TIMER0_PRESCALER_EXTERNAL_CLOCK_SORUCE_RASING_EDGE_T0PIN

}Timer0_PrescalerTYpe;


// 		COM01	COM00   WGM01 WGM00
typedef enum{
    TIMER0_SELECT_MODE_NORMAL = 0b0000,

    TIMER0_SELECT_MODE_PWM_PHASE_CORRECT_OC0_NORMAL = 0b0001,
    TIMER0_SELECT_MODE_PWM_PHASE_CORRECT_OC0_CLEAR_UPCOUNTING_SET_DOWNCOUNTING = 0b1001,
    TIMER0_SELECT_MODE_PWM_PHASE_CORRECT_OC0_SET_UPCOUNTING_CLEAR_DOWNCOUNTING = 0b1101,

	TIMER0_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC0_NORMAEL = 0b0010,
	TIMER0_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC0_TOGGLE =  0b0110,
	TIMER0_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC0_CLEAR =   0b1010,
	TIMER0_SELECT_MODE_CTC_CLEAR_TIME_COMPARE_MATCH_OC0_SET = 0b1110,



    TIMER0_SELECT_MODE_PWM_FAST_MODE_OC0_NORMAL = 0b0011,
    TIMER0_SELECT_MODE_PWM_FAST_MODE_OC0_CLEAR_ON_MATCH_SET_AT_TOP= 0b1011,
    TIMER0_SELECT_MODE_PWM_FAST_MODE_OC0_SET_ON_MATCH_CLEAR_AT_TOP= 0b1111,

}Timer0_SelectMode;



typedef struct{
	Timer0_PrescalerTYpe prescaler_value;
	Timer0_SelectMode select_mode;
	u8  	init_value;

}Timer0_ConfigType;


typedef enum{
	TIMER0_STATUS_FAIL,
	TIMER0_STATUS_OK,
	TIMER0_STATUS_NULL_POINTER_ADDRESS,
}Timer0_StatusErrorType;

/********************************** Software Interfaces Declarations *******************/

Timer0_StatusErrorType Timer0_enuInit(const Timer0_ConfigType* Address_Timer0);
Timer0_StatusErrorType Timer0_DeInit(const Timer0_ConfigType* Address_Timer0);

Timer0_StatusErrorType Timer0_enuEnableInterrupt(const Timer0_ConfigType* Address_Timer0);
Timer0_StatusErrorType Timer0_enuDisableInterrupt(const Timer0_ConfigType* Address_Timer0);



Timer0_StatusErrorType Timer0_SetValue(const Timer0_ConfigType* Address_Timer0, u8 Copy_u8Value);
Timer0_StatusErrorType Timer0_GetTimeElapsed(const Timer0_ConfigType* Address_Timer0, u16* Address_Value);
Timer0_StatusErrorType Timer0_GetRemaining(const Timer0_ConfigType* Address_Timer0, u16* Address_Value);


Timer0_StatusErrorType Timer0_SetCallbackFunction(const Timer0_ConfigType* Address_Timer0,void (*callback)(void));




#endif /* MCAL_TIMER0_INCLUDE_TIMER0_H_ */
