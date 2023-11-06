/**************************************************************************/
/* Filename						: smart_home_config.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 2 Nov 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/





/********************************** Includes *********************************************/


#include "master_smart_home.h"




/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/



/********************************** Data Type Definition ****************************/



/********************************** Software Interfaces Declarations *******************/

Smart_ErrorStatusType Smart_enuInit(void){
	Smart_ErrorStatusType Loc_enuSmartStatusError = SMART_ERROR_STATUS_OK;

	/* Port Init */
	Port_voidInit();

	/* Uart Init */
	Usart_enuInit(&Usart1);
	Usart_enuEnableRxInterrupt();
	Usart_enuSetCallbackRxFunction(smart_voidUartIsr);

	/* Timer0 Init Overflow */
	Timer0_enuInit(&Timer0);
	Timer0_enuSetCallbackFunction(&Timer0,smart_voidTimer0Isr);
	Timer0_enuEnableInterrupt(&Timer0);


	/* Spi Init Master */
	Spi_enuInit(&Spi);

	/* I2c Init Master */
	I2c_enuInit(&I2c);
	/* Lcd Init */
	Lcd_4bit_enuInit(&Lcd);

   /* Servo Init */
	Servo_enuInitTimer1();
	Servo_enuSetAngle(ZERO_VALUE);

	/* Enable Global Interrupt */
	Gie_enuEnableGlobalInterrupt();




	return Loc_enuSmartStatusError;
}
