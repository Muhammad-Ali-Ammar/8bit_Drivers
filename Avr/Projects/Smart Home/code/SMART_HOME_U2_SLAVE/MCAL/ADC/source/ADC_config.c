/**************************************************************************/
/* Filename						: ADC_config.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 23 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../DIO/include/DIO.h"
#include <util/delay.h>
#include "../include/ADC_config.h"
#include "../include/ADC.h"
#include "../include/ADC_private.h"



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/


Adc_PinConfigType Adc0 ={
		.channel_number = ADC_SELECT_CHANNEL0,
		.conversion_frequancy = ADC_FOSC_DIV_128,
		.result_format = ADC_RIGHT_JUSTIFIED,
		.vref_source = ADC_REF_VOLTAGE_AVCC_WITH_EXTERNAL_CAPACITOR

};


/********************************** Software Interfaces Declarations *******************/
