/**************************************************************************/
/* Filename						: EXTI.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 22 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/HELPERS.h"

#include "../include/EXTI_config.h"
#include "../include/EXTI.h"
#include "../include/EXTI_private.h"

#include "../../DIO/include/DIO.h"

/*************************************Private Part **********************************/
static void (* Exti_InterruptHandler[EXTI_MAX_NUMBER_OF_PINS])(void);


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


Exti_StatusErrorType Exti_enuEnable(Exti_IntIndexType Copy_enuIntIndex,  Exti_Intx_SelectConfigType Copy_enuConfiguration){

	Exti_StatusErrorType Loc_enuExtiStatus = EXTI_STATUS_OK;
	if(Copy_enuIntIndex>EXTI_MAX_INDEX_NUMBER_OF_PINS){
		Loc_enuExtiStatus = EXTI_STATUS_WRONG_INDEX;
	}
	else{
		switch(Copy_enuIntIndex){

		case EXTI_INT0_INDEX :
			WRITE_BIT(MCUCR,0,(Copy_enuConfiguration>>0)& 0x01);
			WRITE_BIT(MCUCR,1,(Copy_enuConfiguration>>1)& 0x01);

			Int0_EnableInterrupt();

			break;

		case EXTI_INT1_INDEX :
			WRITE_BIT(MCUCR,2,(Copy_enuConfiguration>>0)& 0x01);
			WRITE_BIT(MCUCR,3,(Copy_enuConfiguration>>1)& 0x01);
			Int1_EnableInterrupt();
			break;

		case EXTI_INT2_INDEX :
			WRITE_BIT(MCUCSR,6,(Copy_enuConfiguration>>0)& 0x01);
			Int2_EnableInterrupt();
			break;

		default:
			break;
			//impoisslbe


		}

	}

	return Loc_enuExtiStatus;

}
Exti_StatusErrorType	Exti_enuDisable(Exti_IntIndexType Copy_enuIntIndex){

	Exti_StatusErrorType Loc_enuExtiStatus = EXTI_STATUS_OK;
	if(Copy_enuIntIndex>EXTI_MAX_INDEX_NUMBER_OF_PINS){
		Loc_enuExtiStatus = EXTI_STATUS_WRONG_INDEX;
	}
	else{
		switch(Copy_enuIntIndex){

		case EXTI_INT0_INDEX :

			Int0_DisableInterrupt();
			break;

		case EXTI_INT1_INDEX :

			Int1_DisableInterrupt();
			break;

		case EXTI_INT2_INDEX :
			Int2_DisableInterrupt();
			break;

		default:
				// impossible
			break;



		}

	}

	return Loc_enuExtiStatus;

}

Exti_StatusErrorType	Exti_enuSetCallbackFunction(Exti_IntIndexType Copy_enuIntIndex, void (*Address_Interrupt)(void)  ){
	Exti_StatusErrorType Loc_enuExtiStatus = EXTI_STATUS_OK;
		if(Copy_enuIntIndex>EXTI_MAX_INDEX_NUMBER_OF_PINS){
			Loc_enuExtiStatus = EXTI_STATUS_WRONG_INDEX;

		}
		else if(Address_Interrupt == NULL){
			Loc_enuExtiStatus = EXTI_STATUS_NULL_POINTER_ADDRESS;
		}
		else{
			Exti_InterruptHandler[Copy_enuIntIndex] = Address_Interrupt;

		}

		return Loc_enuExtiStatus;

}




/********************************** ISR Section *****************************************************/


// ISR function For INT0
void __vector_1(void) __attribute__((signal));

void __vector_1(void){

		if(Exti_InterruptHandler[EXTI_INT0_INDEX] != NULL)
			Exti_InterruptHandler[EXTI_INT0_INDEX]();

}

// ISR function For INT1
void __vector_2(void) __attribute__((signal));

void __vector_2(void){

	if(Exti_InterruptHandler[EXTI_INT1_INDEX] != NULL)
		Exti_InterruptHandler[EXTI_INT1_INDEX]();

}


// ISR function For INT2
void __vector_3(void) __attribute__((signal));

void __vector_3(void){
	if(Exti_InterruptHandler[EXTI_INT2_INDEX] != NULL)
			Exti_InterruptHandler[EXTI_INT2_INDEX]();

}

