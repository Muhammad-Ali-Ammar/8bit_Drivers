/**************************************************************************/
/* Filename						: WDT_private.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 27 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_WTD_INCLUDE_WDT_PRIVATE_H_
#define MCAL_WTD_INCLUDE_WDT_PRIVATE_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define WDTCR			(*(volatile u8*)(0x41))

#define WDE_BIT			(THREE_VALUE)
#define WDTOE_BIT		(FOUR_VALUE)


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


#endif /* MCAL_WTD_INCLUDE_WDT_PRIVATE_H_ */
