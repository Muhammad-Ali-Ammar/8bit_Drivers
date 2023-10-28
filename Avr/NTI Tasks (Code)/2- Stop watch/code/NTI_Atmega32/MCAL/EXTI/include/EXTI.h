/**************************************************************************/
/* Filename						: EXTI.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 22 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_EXTI_INCLUDE_EXTI_H_
#define MCAL_EXTI_INCLUDE_EXTI_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/



/********************************** Macros Function Declarations *********************/

#define Int0_DisableInterrupt()				(CLEAR_BIT((GICR),INTc0_BIT))
#define Int0_EnableInterrupt()				(SET_BIT((GICR),INTc0_BIT))

#define Int1_DisableInterrupt()				(CLEAR_BIT((GICR),INTc1_BIT))
#define Int1_EnableInterrupt()				(SET_BIT((GICR),INTc1_BIT))

#define Int2_DisableInterrupt()				(CLEAR_BIT((GICR),INTc2_BIT))
#define Int2_EnableInterrupt()				(SET_BIT((GICR),INTc2_BIT))


#define Int0_ClearFlag()				(SET_BIT((GIFR),INTF0_BIT))
#define Int1_ClearFlag()				(SET_BIT((GIFR),INTF1_BIT))
#define Int2_ClearFlag()				(SET_BIT((GIFR),INTF2_BIT))






/********************************** Data Type Declarations ****************************/

typedef enum{
	EXTI_INT0_INDEX,
	EXTI_INT1_INDEX,
	EXTI_INT2_INDEX
}Exti_IntIndexType;


typedef enum{
	EXTI_INT0_SELECT_LOW_LEVEL=0,
	EXTI_INT0_SELECT_ON_CHANGE=1,
	EXTI_INT0_SELECT_FAILING_EDGE=2,
	EXTI_INT0_SELECT_RISING_EDGE=3,

	EXTI_INT1_SELECT_LOW_LEVEL=0,
	EXTI_INT1_SELECT_ON_CHANGE=1,
	EXTI_INT1_SELECT_FAILING_EDGE=2,
	EXTI_INT1_SELECT_RISING_EDGE=3,

	EXTI_INT2_SELECT_FAILING_EDGE=0,
	EXTI_INT2_SELECT_RISING_EDGE=1
}Exti_Intx_SelectConfigType;



typedef enum{
	EXTI_STATUS_FAIL,
	EXTI_STATUS_OK,
	EXTI_STATUS_NULL_POINTER_ADDRESS,
	EXTI_STATUS_WRONG_INDEX
}Exti_StatusErrorType;



/********************************** Software Interfaces Declarations *******************/

Exti_StatusErrorType	Exti_enuEnable(Exti_IntIndexType Copy_enuIntIndex,  Exti_Intx_SelectConfigType Copy_enuConfiguration);
Exti_StatusErrorType	Exti_enuDisable(Exti_IntIndexType Copy_enuIntIndex);

Exti_StatusErrorType	Exti_enuSetCallbackFunction(Exti_IntIndexType Copy_enuIntIndex, void (*Address_Interrupt)(void)  );


#endif /* MCAL_EXTI_INCLUDE_EXTI_H_ */
