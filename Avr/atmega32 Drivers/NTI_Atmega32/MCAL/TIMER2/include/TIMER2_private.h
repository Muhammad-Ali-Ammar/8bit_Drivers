/**************************************************************************/
/* Filename						: TIMER2_private.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 27 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef MCAL_TIMER2_INCLUDE_TIMER2_PRIVATE_H_
#define MCAL_TIMER2_INCLUDE_TIMER2_PRIVATE_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/
#define TCNT2			(*(volatile u8*)(0x44))
#define TCCR2			(*(volatile u8*)(0x45))

#define TIFR			(*(volatile u8*)(0x58))
#define TIMSK			(*(volatile u8*)(0x59))

#define OCR2			(*(volatile u8*)(0x43))


#define TIMER2_FULL_VALUE_IN_REGISTER		(255)

#define TCCR2_FOC2_BIT			(SEVEN_VALUE)

#define TIMSK_OCIE2_BIT			(SEVEN_VALUE)
#define TIMSK_TOIE2_BIT			(SIX_VALUE)

/********************************** Macros Function Declarations *********************/
#define Timer2_Disable()		( (TCCR2) = ((TCCR2) & 0xF8) )

#define Timer2_SelectMode(ARGU)	 do{\
								 	WRITE_BIT((TCCR2),SIX_VALUE,(ARGU)&0x01);\
									WRITE_BIT((TCCR2),THREE_VALUE,(ARGU>>1)&0x01);\
									WRITE_BIT((TCCR2),FOUR_VALUE,(ARGU>>2)&0x01);\
									WRITE_BIT((TCCR2),FIVE_VALUE,(ARGU>>3)&0x01);\
									}while(ZERO_VALUE)

#define Timer2_Enable(ARGU)		( (TCCR2) = ((TCCR2) & 0xF8) | (ARGU) )

#define Timer2_EnableOverviewInterrupt()	SET_BIT(TIMSK,TIMSK_TOIE2_BIT)
#define Timer2_DisableOverviewInterrupt()	CLEAR_BIT(TIMSK,TIMSK_TOIE2_BIT)

#define Timer2_EnableComparePwmInterrupt()	SET_BIT(TIMSK,TIMSK_OCIE2_BIT)
#define Timer2_DisbleComparePwmInterrupt()	CLEAR_BIT(TIMSK,TIMSK_OCIE2_BIT)


#define TIMER2_OVERFLOW_TIME_PRESCALER_1024				0.016384




/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


#endif /* MCAL_TIMER2_INCLUDE_TIMER2_PRIVATE_H_ */
