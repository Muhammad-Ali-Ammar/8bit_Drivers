/**************************************************************************/
/* Filename						: slave_smart_home_config.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 4 Nov 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/





/********************************** Includes *********************************************/


#include "slave_smart_home.h"

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/
SlaveSmart_ErrorStatusType SlaveSmart_enuInit(void){
	SlaveSmart_ErrorStatusType Loc_enuSmartStatusError = SLAVE_SMART_ERROR_STATUS_OK;

		/* Port Init */
		Port_voidInit();


		/* Timer0 Init Overflow */
		Timer0_enuInit(&Timer0);
		Timer0_enuSetCallbackFunction(&Timer0,smart_voidTimer0Isr);
		Timer0_enuEnableInterrupt(&Timer0);
		Timer0_enuSetDutyCyclePwm(&Timer0, 0);

		/* Spi Init Slave */
		Spi_enuInit(&Spi);
		Spi_enuEnableInterrupt();
		Spi_enuSetCallbackFunction(smart_voidSpiIsr);

		/* Adc Init */
		Adc_enuInit(&Adc0);
		/* Enable Global Interrupt */
		Gie_enuEnableGlobalInterrupt();

		return Loc_enuSmartStatusError;
}
