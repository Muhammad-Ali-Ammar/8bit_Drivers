/**************************************************************************/
/* Filename						: USART_private.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 28 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef MCAL_USART_INCLUDE_USART_PRIVATE_H_
#define MCAL_USART_INCLUDE_USART_PRIVATE_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define UDR		    	(*(volatile u8*)(0x2C))
#define UCSRA			(*(volatile u8*)(0x2B))
#define UCSRB			(*(volatile u8*)(0x2A))
#define UCSRC			(*(volatile u8*)(0x40))

#define UBRRL			(*(volatile u8*)(0x29))
#define UBRRH			(*(volatile u8*)(0x40))


#define UCSRB_RX_EN_BIT				(FOUR_VALUE)
#define UCSRB_TX_EN_BIT				(THREE_VALUE)

#define UCSRC_USBS_BIT				(THREE_VALUE)
#define UCSRC_UMSEL_BIT				(SIX_VALUE)


#define UCSRA_RXC_BIT				(SEVEN_VALUE)
#define UCSRA_TXC_BIT				(SIX_VALUE)
#define UCSRA_UDRE_BIT				(FIVE_VALUE)

/********************************** Macros Function Declarations *********************/

#define Usart_SelectUcsrcReg()			SET_BIT(UCSRC,SEVEN_VALUE);
#define Usart_SelectUbbrhReg()			CLEAR_BIT(UCSRC,SEVEN_VALUE);

#define	Usart_SelectCharacterSize(ARG)		do{\
											Usart_SelectUcsrcReg();\
											(UCSRC) = (UCSRC &0xF9)| ( (ARG<<1) & 0b00000110);\
											(UCSRB) = (UCSRB &0xFB)| ((ARG) & 0b00000100);\
											}while(ZERO_VALUE)


#define Usart_SelectParityBitConfg(ARG)		( (UCSRC) = ((UCSRC) &0b11001111 )|  (ARG<<FOUR_VALUE))

#define Usart_SelectStopBitConfig(ARG)		WRITE_BIT(UCSRC,UCSRC_USBS_BIT,ARG)

#define Usart_SelectSyncConfig(ARG)		WRITE_BIT(UCSRC,UCSRC_UMSEL_BIT,ARG)

#define Usart_IsRecevingDone()				( (READ_BIT(UCSRA,UCSRA_RXC_BIT) == ONE_VALUE))
#define Usart_IsRegisterDataEmpty()			(READ_BIT(UCSRA,UCSRA_UDRE_BIT) == ONE_VALUE)


#define Usart_EnableRxInterrupt()			(SET_BIT(UCSRB,SEVEN_VALUE))
#define Usart_DisableRxInterrupt()			(CLEAR_BIT(UCSRB,SEVEN_VALUE))

#define Usart_EnableTxInterrupt()			(SET_BIT(UCSRB,SIX_VALUE))
#define Usart_DisableTxInterrupt()			(CLEAR_BIT(UCSRB,SIX_VALUE))

#define Usart_EnableDataRegEmpyInterrupt()			(SET_BIT(UCSRB,FIVE_VALUE))
#define Usart_DisableDataRegEmpyInterrupt()			(CLEAR_BIT(UCSRB,FIVE_VALUE))



/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


#endif /* MCAL_USART_INCLUDE_USART_PRIVATE_H_ */
