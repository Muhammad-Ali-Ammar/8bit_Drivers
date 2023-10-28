/**************************************************************************/
/* Filename						: ICUSW.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 27 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/


#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/HELPERS.h"

#include "../../../MCAL/DIO/include/DIO.h"

#include "../../../MCAL/EXTI/include/EXTI.h"
#include "../../../MCAL/GIE/include/GIE.h"

#include "../../../MCAL/TIMER0/include/TIMER0.h"

#include "../../include/ICUSW/ICUSW_config.h"
#include "../../include/ICUSW/ICUSW.h"
#include "../../include/ICUSW/ICUSW_private.h"


/*********************************Static Elements *************************************/

static u32 Global_StaticU32OnTime =ZERO_VALUE;
static u32 Global_StaticU32TotalTime =ZERO_VALUE;
static u32 Global_StaticU32DutyTime =ZERO_VALUE;


static u32 Global_StaticU32OverflowCounter =ZERO_VALUE;

static u32 Global_StaticINTxWhichTimer[3];

static Timer0_ConfigType Global_StaticTimer0={
		.init_value = ZERO_VALUE,
		.prescaler_value = TIMER0_PRESCALER_DIV_1024,
		.select_mode = TIMER0_SELECT_MODE_NORMAL
};

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/


void Timer_voidTimerOverflowIsr(void);

void Icusw_voidINT0Isr(void);
void Icusw_voidINT1Isr(void);
void Icusw_voidINT2Isr(void);


/********************************** Software Interfaces Declarations *******************/


Icusw_StatusErrorType Icusw_enuInit(Icusw_ConfigType* Address_Icusw ){
	Icusw_StatusErrorType Loc_enuIcuswStatus = ICUSW_STATUS_OK;
	Exti_StatusErrorType Loc_enuExtiswStatus = EXTI_STATUS_OK;

	if(NULL == Address_Icusw){
		Loc_enuIcuswStatus = ICUSW_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		switch(Address_Icusw->exti_Intx_Index){
		case EXTI_INT0_INDEX :
			Loc_enuExtiswStatus = Exti_enuEnable(EXTI_INT0_INDEX,EXTI_INT0_SELECT_RISING_EDGE);
			Loc_enuExtiswStatus = Exti_enuSetCallbackFunction(EXTI_INT0_INDEX, Icusw_voidINT0Isr);

			break;
		case EXTI_INT1_INDEX :
			Loc_enuExtiswStatus = Exti_enuEnable(EXTI_INT1_INDEX,EXTI_INT1_SELECT_RISING_EDGE);
			Loc_enuExtiswStatus = Exti_enuSetCallbackFunction(EXTI_INT1_INDEX, Icusw_voidINT1Isr);

			break;
		case EXTI_INT2_INDEX :
			Loc_enuExtiswStatus = Exti_enuEnable(EXTI_INT2_INDEX,EXTI_INT2_SELECT_RISING_EDGE);
			Loc_enuExtiswStatus = Exti_enuSetCallbackFunction(EXTI_INT2_INDEX, Icusw_voidINT2Isr);


			break;
		default:

			Loc_enuExtiswStatus = EXTI_STATUS_FAIL;
			break;

		}

		switch(Address_Icusw->timer_index){

		case ICUSW_TIMER_INDEX_TIMER0 :

			Timer0_enuInit(&Global_StaticTimer0);
			Timer0_enuSetCallbackFunction(&Global_StaticTimer0,Timer_voidTimerOverflowIsr);
			Timer0_enuEnableInterrupt(&Global_StaticTimer0);
			Global_StaticINTxWhichTimer[Address_Icusw->exti_Intx_Index]=ICUSW_TIMER_INDEX_TIMER0;

			break;
		case ICUSW_TIMER_INDEX_TIMER1:

			break;
		case ICUSW_TIMER_INDEX_TIMER2:

			break;

		default:

			Loc_enuIcuswStatus = ICUSW_STATUS_FAIL;
			break;
		}


	}
	Gie_enuEnableGlobalInterrupt();

	return Loc_enuIcuswStatus;
}

Icusw_StatusErrorType Icusw_enuDeint(Icusw_ConfigType* Address_Icusw ){
	Icusw_StatusErrorType Loc_enuIcuswStatus = ICUSW_STATUS_OK;

	if(NULL == Address_Icusw){
		Loc_enuIcuswStatus = ICUSW_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

	}

	return Loc_enuIcuswStatus;
}
Icusw_StatusErrorType Icusw_enuGetOnTimeMilliSeconds(Icusw_ConfigType* Address_Icusw, u32* Address_OnTime){
	Icusw_StatusErrorType Loc_enuIcuswStatus = ICUSW_STATUS_OK;

	if(NULL == Address_Icusw ||NULL == Address_OnTime ){
		Loc_enuIcuswStatus = ICUSW_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		*Address_OnTime = Global_StaticU32OnTime;
	}

	return Loc_enuIcuswStatus;
}

Icusw_StatusErrorType Icusw_enuGetTotalTimeMilliSeconds(Icusw_ConfigType* Address_Icusw, u32* Address_TotalTime){
	Icusw_StatusErrorType Loc_enuIcuswStatus = ICUSW_STATUS_OK;

	if(NULL == Address_Icusw||NULL == Address_TotalTime ){
		Loc_enuIcuswStatus = ICUSW_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_TotalTime = Global_StaticU32TotalTime;
	}

	return Loc_enuIcuswStatus;
}

Icusw_StatusErrorType Icusw_enuGetDutyCycleMilliSeconds(Icusw_ConfigType* Address_Icusw, u32* Address_DutyTime){
	Icusw_StatusErrorType Loc_enuIcuswStatus = ICUSW_STATUS_OK;

	if(NULL == Address_Icusw ||NULL ==Address_DutyTime){
		Loc_enuIcuswStatus = ICUSW_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_DutyTime = Global_StaticU32DutyTime;
	}

	return Loc_enuIcuswStatus;
}


/************************************Static implementation ************************/

void Timer_voidTimerOverflowIsr(void){
	Global_StaticU32OverflowCounter++;

}



void Icusw_voidINT0Isr(void){

	static u8 Loc_u8Counter = ZERO_VALUE;
	static u16 Loc_u16FirstTicks = ZERO_VALUE;
	static u16 Loc_u16SecondTicks = ZERO_VALUE;
	static u16 Loc_u16ThirdTicks = ZERO_VALUE;


	static u16 Loc_u32OnTicks = ZERO_VALUE;
	static u16 Loc_u32TotalTicks = ZERO_VALUE;

	// first edge = Rising
	if(Loc_u8Counter == ZERO_VALUE){
		Loc_u8Counter++;
		Global_StaticU32OverflowCounter = ZERO_VALUE;
		 Exti_enuEnable(EXTI_INT0_INDEX,EXTI_INT0_SELECT_FAILING_EDGE);

		switch(Global_StaticINTxWhichTimer[EXTI_INT0_INDEX]){

		case ICUSW_TIMER_INDEX_TIMER0 :
			Timer0_enuGetTimeElapsed(&Global_StaticTimer0, &Loc_u16FirstTicks);

			break;
		case ICUSW_TIMER_INDEX_TIMER1:

			break;
		case ICUSW_TIMER_INDEX_TIMER2:

			break;

		default:
			break;
		}


	}

	else if(Loc_u8Counter == ONE_VALUE){

		Loc_u8Counter++;
		Exti_enuEnable(EXTI_INT0_INDEX,EXTI_INT0_SELECT_RISING_EDGE);
		switch(Global_StaticINTxWhichTimer[EXTI_INT0_INDEX]){

		case ICUSW_TIMER_INDEX_TIMER0 :
			Timer0_enuGetTimeElapsed(&Global_StaticTimer0, &Loc_u16SecondTicks);
			Loc_u32OnTicks = Loc_u16SecondTicks + (Global_StaticU32OverflowCounter*255)-Loc_u16FirstTicks;



			break;
		case ICUSW_TIMER_INDEX_TIMER1:

			break;
		case ICUSW_TIMER_INDEX_TIMER2:

			break;

		default:
			break;
		}
	}

	else if(Loc_u8Counter == TWO_VALUE){
		Loc_u8Counter = ZERO_VALUE;
		Exti_enuEnable(EXTI_INT0_INDEX,EXTI_INT0_SELECT_FAILING_EDGE);

		switch(Global_StaticINTxWhichTimer[EXTI_INT0_INDEX]){

		case ICUSW_TIMER_INDEX_TIMER0 :
			Timer0_enuGetTimeElapsed(&Global_StaticTimer0, &Loc_u16ThirdTicks);
			Loc_u32TotalTicks = Loc_u16ThirdTicks + (Global_StaticU32OverflowCounter*255)-Loc_u16FirstTicks;


			break;
		case ICUSW_TIMER_INDEX_TIMER1:

			break;
		case ICUSW_TIMER_INDEX_TIMER2:

			break;

		default:
			break;
		}
		if(Global_StaticU32TotalTime > Global_StaticU32OnTime){
			Dio_enuFlipChannel(DIO_PINA6_CHANNEL6);
		}
		Global_StaticU32TotalTime = Loc_u32TotalTicks*ICUSW_16M_PRESCALER_DIV_1024_TIMER0;
		Global_StaticU32OnTime = Loc_u32OnTicks*ICUSW_16M_PRESCALER_DIV_1024_TIMER0 ;
		Global_StaticU32DutyTime = ((f32)Global_StaticU32OnTime /Global_StaticU32TotalTime)*100;

		Global_StaticU32OverflowCounter = ZERO_VALUE;
		Loc_u8Counter = ONE_VALUE;
		Loc_u16FirstTicks =Loc_u16ThirdTicks;



	}

}


void Icusw_voidINT1Isr(void){

}
void Icusw_voidINT2Isr(void){

}
