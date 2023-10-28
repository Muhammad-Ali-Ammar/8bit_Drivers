/**************************************************************************/
/* Filename						: TIMER1_private.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 26 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_TIMER1_INCLUDE_TIMER1_PRIVATE_H_
#define MCAL_TIMER1_INCLUDE_TIMER1_PRIVATE_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define TCCR1A			(*(volatile u8*)(0x4F))
#define TCCR1B			(*(volatile u8*)(0x4B))
#define TCNT1H			(*(volatile u8*)(0x4D))
#define TCNT1L			(*(volatile u8*)(0x4C))
#define TCNT1			(*(volatile u16*)(0x4D))

#define OCR1AH			(*(volatile u8*)(0x4B))
#define OCR1AL			(*(volatile u8*)(0x4A))
#define OCR1A			(*(volatile u16*)(0x4A))

#define OCR1BH			(*(volatile u8*)(0x49))
#define OCR1BL			(*(volatile u8*)(0x48))
#define OCR1B			(*(volatile u16*)(0x48))

#define ICR1H			(*(volatile u8*)(0x47))
#define ICR1L			(*(volatile u8*)(0x46))
#define ICR1			(*(volatile u16*)(0x46))



#define TIFR			(*(volatile u8*)(0x58))
#define TIMSK			(*(volatile u8*)(0x59))

#define TIMSK_TOVIE1_BIT			(2)
#define TIMSK_OCIE1A_BIT			(3)
#define TIMSK_OCIE1B_BIT			(4)
#define TIMSK_TICIE1_BIT			(5)


#define TCCR1A_FOC1A_BIT			(THREE_VALUE)
#define TCCR1A_FOC1B_BIT			(TWO_VALUE)

#define TIMER1_FULL_VALUE_IN_REGISTER_16BIT		(65535)
#define TIMER1_FULL_VALUE_IN_REGISTER_8BIT		(255)
#define TIMER1_FULL_VALUE_IN_REGISTER_9BIT		(511)
#define TIMER1_FULL_VALUE_IN_REGISTER_10BIT		(1023)

#define TIMER1_OVERFLOW_TIME_PRESCALER_1024_8BIT				0.016384
#define TIMER1_OVERFLOW_TIME_PRESCALER_1024_9BIT				0.032768
#define TIMER1_OVERFLOW_TIME_PRESCALER_1024_10BIT				0.065536
#define TIMER1_OVERFLOW_TIME_PRESCALER_1024_16BIT				4.194304

///////////////////////////////////////////////////////////////////////////////



#define Timer1_Disable()		( (TCCR1B) = ((TCCR1B) & 0xF8) )


//#define Timer0_SelectMode(ARGU)	 do{\
//								 	WRITE_BIT((TCCR0),6,(ARGU)&0x01);\
//									WRITE_BIT((TCCR0),3,(ARGU>>1)&0x01);\
//									WRITE_BIT((TCCR0),4,(ARGU>>2)&0x01);\
//									WRITE_BIT((TCCR0),5,(ARGU>>3)&0x01);\
//									}while(0)


#define Timer1_Enable(ARGU)		( (TCCR1B) = ((TCCR1B) & 0xF8) | (ARGU) )

#define Timer1_EnableOverviewInterrupt()	SET_BIT(TIMSK,TIMSK_TOVIE1_BIT)
#define Timer1_DisableOverviewInterrupt()	CLEAR_BIT(TIMSK,TIMSK_TOVIE1_BIT)


#define Timer1_EnableChannelA_ComparePwmInterrupt()	SET_BIT(TIMSK,TIMSK_OCIE1A_BIT)
#define Timer1_DisbleChannelA_ComparePwmInterrupt()	CLEAR_BIT(TIMSK,TIMSK_OCIE1A_BIT)

#define Timer1_EnableChannelB_ComparePwmInterrupt()	SET_BIT(TIMSK,TIMSK_OCIE1B_BIT)
#define Timer1_DisbleChannelB_ComparePwmInterrupt()	CLEAR_BIT(TIMSK,TIMSK_OCIE1B_BIT)






/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


#endif /* MCAL_TIMER1_INCLUDE_TIMER1_PRIVATE_H_ */
