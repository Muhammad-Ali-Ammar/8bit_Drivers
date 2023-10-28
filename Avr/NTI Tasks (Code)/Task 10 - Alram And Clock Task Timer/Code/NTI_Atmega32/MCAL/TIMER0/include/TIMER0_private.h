/**************************************************************************/
/* Filename						: TIMER0_prinvate.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 24 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_TIMER0_INCLUDE_TIMER0_PRIVATE_H_
#define MCAL_TIMER0_INCLUDE_TIMER0_PRIVATE_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define TCNT0			(*(volatile u8*)(0x52))
#define TCCR0			(*(volatile u8*)(0x53))

#define TIFR			(*(volatile u8*)(0x58))
#define TIMSK			(*(volatile u8*)(0x59))



#define Timer0_Disable()		( (TCCR0) = ((TCCR0) & 0xF8) )

#define Timer0_SelectMode(ARGU)	 do{\
								 	WRITE_BIT((TCCR0),6,(ARGU)&0x01);\
									WRITE_BIT((TCCR0),3,(ARGU>>1)&0x01);\
									WRITE_BIT((TCCR0),4,(ARGU>>2)&0x01);\
									WRITE_BIT((TCCR0),5,(ARGU>>3)&0x01);\
									}while(0)


#define Timer0_Enable(ARGU)		( (TCCR0) = ((TCCR0) & 0xF8) | (ARGU) )

#define Timer0_EnableOverviewInterrupt()	SET_BIT(TIMSK,0)
#define Timer0_DisableOverviewInterrupt()	CLEAR_BIT(TIMSK,0)

#define Timer0_EnableComparePwmInterrupt()	SET_BIT(TIMSK,1)
#define Timer0_DisbleComparePwmInterrupt()	CLEAR_BIT(TIMSK,1)

/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


#endif /* MCAL_TIMER0_INCLUDE_TIMER0_PRIVATE_H_ */
