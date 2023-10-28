/**************************************************************************/
/* Filename						: EXTI_private.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 22 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_EXTI_INCLUDE_EXTI_PRIVATE_H_
#define MCAL_EXTI_INCLUDE_EXTI_PRIVATE_H_

/********************************** Includes *********************************************/





/********************************** Macros Function Declarations *********************/

#define MCUCR		(*(volatile u8*)(0x55))
#define MCUCSR		(*(volatile u8*)(0x54))

#define GICR		(*(volatile u8*)(0x5B))
#define GIFR		(*(volatile u8*)(0x5A))



/********************************** Macros Declarations *******************************/

#define INTF1_BIT			7
#define INTF0_BIT			6
#define INTF2_BIT			5


#define INTc1_BIT			7
#define INTc0_BIT			6
#define INTc2_BIT			5


#define EXTI_MAX_NUMBER_OF_PINS				3
#define EXTI_MAX_INDEX_NUMBER_OF_PINS		2




/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/




#endif /* MCAL_EXTI_INCLUDE_EXTI_PRIVATE_H_ */
