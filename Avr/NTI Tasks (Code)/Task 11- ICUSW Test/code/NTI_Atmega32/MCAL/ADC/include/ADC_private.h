/**************************************************************************/
/* Filename						: ADC_private.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 23 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_ADC_INCLUDE_ADC_PRIVATE_H_
#define MCAL_ADC_INCLUDE_ADC_PRIVATE_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define ADMUX			(*(volatile u8*)(0x27))
#define ADCL		    (*(volatile u8*)(0x24))
#define ADCH		    (*(volatile u8*)(0x25))
#define ADCSRA		    (*(volatile u8*)(0x26))
#define SFIOR		    (*(volatile u8*)(0x50))

#define ADCHL		    (*(volatile u16*)(0x24))


#define ADC_NUMBER_OF_CHANNELS			8


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


#endif /* MCAL_ADC_INCLUDE_ADC_PRIVATE_H_ */
