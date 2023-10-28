/**************************************************************************/
/* Filename						: ICUSW.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 27 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef HAL_INCLUDE_ICUSW_ICUSW_H_
#define HAL_INCLUDE_ICUSW_ICUSW_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define ICUSW_TIMER_INDEX_TIMER0			ZERO_VALUE
#define ICUSW_TIMER_INDEX_TIMER1			ONE_VALUE
#define ICUSW_TIMER_INDEX_TIMER2			TWO_VALUE

/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

typedef struct{

	Exti_IntIndexType exti_Intx_Index;
	u8		timer_index;
}Icusw_ConfigType;



typedef enum{
    ICUSW_STATUS_OK,
	ICUSW_STATUS_FAIL,
	ICUSW_STATUS_NULL_POINTER_ADDRESS
}Icusw_StatusErrorType;


/********************************** Software Interfaces Declarations *******************/

Icusw_StatusErrorType Icusw_enuInit(Icusw_ConfigType* Address_Icusw );
Icusw_StatusErrorType Icusw_enuDeint(Icusw_ConfigType* Address_Icusw );
Icusw_StatusErrorType Icusw_enuGetOnTimeMilliSeconds(Icusw_ConfigType* Address_Icusw, u32* Address_OnTime);
Icusw_StatusErrorType Icusw_enuGetTotalTimeMilliSeconds(Icusw_ConfigType* Address_Icusw, u32* Address_TotalTime);
Icusw_StatusErrorType Icusw_enuGetDutyCycleMilliSeconds(Icusw_ConfigType* Address_Icusw, u32* Address_DutyTime);


#endif /* HAL_INCLUDE_ICUSW_ICUSW_H_ */
